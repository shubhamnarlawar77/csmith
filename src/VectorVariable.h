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
	void OutputDef(std::ostream &out, int indent) const;
private:
	VectorVariable(const std::string &name, const Type *type, const Expression* init, const CVQualifiers* qfer);
};

///////////////////////////////////////////////////////////////////////////////

#endif // VECTOR_VARIABLE_H

// Local Variables:
// c-basic-offset: 4
// tab-width: 4
// End:

// End of file.
