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

VectorVariable::VectorVariable(const std::string &name, const Type *type, const Expression* init, const CVQualifiers* qfer)
	: Variable(name, type, init, qfer)
{
}

VectorVariable *
VectorVariable::CreateVectorVariable(const std::string &name, const Type *type, const Expression* init, const CVQualifiers* qfer)
{
	assert(type);
	if (type->eType == eSimple)
		assert(type->simple_type != eVoid);

	VectorVariable *var = new VectorVariable(name, type, init, qfer);
	if (type->is_aggregate()) {
		var->create_field_vars(type);
	}
	ERROR_GUARD_AND_DEL1(NULL, var);
	return var;
}

void
VectorVariable::OutputDef(std::ostream &out, int indent) const
{
	output_tab(out, indent);
	if (CGOptions::force_globals_static() && is_global()) {
		out << "static ";
	}
	output_qualified_type(out);
	out << get_actual_name() << " = ";
	assert(init);
	out << "{";
	init->Output(out);
	out << "};";
	outputln(out);
}

