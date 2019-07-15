#ifndef VECTOR_VARIABLE_H
#define VECTOR_VARIABLE_H

#include "Variable.h"
class Expression;
class Block;
using namespace std;

class VectorVariable : public Variable
{
public:
	static VectorVariable* CreateVectorVariable(const std::string &name, const Type *type, const Expression* init, const CVQualifiers* qfer);
	static string get_vector_type(eSimpleType simple_type);
	void OutputDef(std::ostream &out, int indent) const;
	void Output(std::ostream &out) const;
	void hash(std::ostream& out) const;
private:
	string element_type;
	int num_elements;
	VectorVariable(const std::string &name, const Type *type, const Expression* init, const CVQualifiers* qfer, string element_type, int num_elements);
};

///////////////////////////////////////////////////////////////////////////////

#endif // VECTOR_VARIABLE_H

// Local Variables:
// c-basic-offset: 4
// tab-width: 4
// End:

// End of file.
