#if HAVE_CONFIG_H
#  include <config.h>
#endif

#ifdef WIN32
#pragma warning(disable : 4786)   /* Disable annoying warning messages */
#endif

#include "VectorVariable.h"
#include <cassert>
#include "Error.h"

using namespace std;

VectorVariable::VectorVariable(const std::string &name, const Type *type, const Expression* init, const CVQualifiers* qfer, string element_type, int num_elements)
	: Variable(name, type, init, qfer, true), element_type(element_type), num_elements(num_elements)
{
}

VectorVariable *
VectorVariable::CreateVectorVariable(const std::string &name, const Type *type, const Expression* init, const CVQualifiers* qfer)
{
	assert(type);
	string element_type = VectorVariable::get_vector_type(type->simple_type);
	VectorVariable *var = new VectorVariable(name, type, init, qfer, element_type, rnd_upto(3)+1);
	ERROR_GUARD_AND_DEL1(NULL, var);
	return var;
}

string
VectorVariable::get_vector_type(eSimpleType simple_type) {
	string vector_type = "";
	switch(simple_type){
		case eChar:
			vector_type = "v" + std::to_string(32/sizeof(char)) + "char";
			break;
		case eInt:
			vector_type = "v" + std::to_string(32/sizeof(int)) + "int";
			break;
		case eShort:
			vector_type = "v" + std::to_string(32/sizeof(short)) + "short";
			break;
		case eLong:
			vector_type = "v" + std::to_string(32/sizeof(long)) + "long";
			break;
		case eLongLong:
			vector_type = "v" + std::to_string(32/sizeof(long long)) + "longlong";
			break;
		case eUChar:
			vector_type = "v" + std::to_string(32/sizeof(char)) + "uchar";
			break;
		case eUInt:
			vector_type = "v" + std::to_string(32/sizeof(int)) + "uint";
			break;
		case eUShort:
			vector_type = "v" + std::to_string(32/sizeof(short)) + "ushort";
			break;
		case eULong:
			vector_type = "v" + std::to_string(32/sizeof(long)) + "ulong";
			break;
		case eULongLong:
			vector_type = "v" + std::to_string(32/sizeof(long long)) + "ulonglong";
			break;
		assert(0 && "Unsupported type!");
	}
	return vector_type;
}

void
VectorVariable::OutputDef(std::ostream &out, int indent) const
{
	output_tab(out, indent);
	if (CGOptions::force_globals_static() && is_global()) {
		out << "static ";
	}
	out << element_type << " ";
	out << get_actual_name() << " = ";
	assert(init);
	out << "{";
	for(int i = 0; i < num_elements - 1; i++){
		init->Output(out);
		out << ",";
	}
	init->Output(out);
	out << "};";
	outputln(out);
}

void
VectorVariable::Output(std::ostream &out) const
{
	if (is_volatile() && CGOptions::wrap_volatiles()) {
		out << "VOL_RVAL(" << get_actual_name() << ", ";
		type->Output(out);
		out << ")";
	}
	else if (CGOptions::access_once() && isAccessOnce && !isAddrTaken) {
		assert(CGOptions::access_once() && "access_once is disabled!");
		out << "ACCESS_ONCE(" << get_actual_name() << ")";
	}
	else {
		out << get_actual_name() << "[" << rnd_upto(num_elements) << "]";
	}
}

void
VectorVariable::hash(std::ostream& out) const
{
	int indent = 1;
	output_tab(out, indent);
	out << "for (i = 0; i < " << num_elements << "; i++)";
	outputln(out);
	output_open_encloser("{", out, indent);
	output_tab(out, indent);
	out << "transparent_crc(" << name << "[i],";
	out << "\"" << name << "\"," << "print_hash_value);";
	output_close_encloser("}", out, indent);
	outputln(out);
}
