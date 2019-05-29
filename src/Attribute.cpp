#if HAVE_CONFIG_H
#  include <config.h>
#endif

#ifdef WIN32
#pragma warning(disable : 4786)   /* Disable annoying warning messages */
#endif

#include "random.h"
#include "OutputMgr.h"
#include "Attribute.h"

void
AttributeGenerator::GenerateAllAttributes(std::ostream &out)
{
	bool attr_emitted = false;
	vector<Attribute*>::iterator itr;
	for(itr = attributes.begin(); itr != attributes.end(); itr++){
		string attr_generated;
		attr_generated = (*itr)->OutputAttributes();
		if(attr_generated != ""){
			if(!attr_emitted){
				out << " __attribute__((" << attr_generated;
				attr_emitted = true;
			}
			else
				out << ", " << attr_generated;
		}
	}
	if(attr_emitted)
		out << "))";
}

Attribute::Attribute(string name, int prob)
	:  attribute(name), attribute_probability(prob)
{
}

BooleanAttribute::BooleanAttribute(string name, int prob)
	: Attribute(name, prob)
{
}

string
BooleanAttribute::OutputAttributes()
{
	if(rnd_flipcoin(attribute_probability))
		return attribute;
	else
		return "";
}

MultiValuedAttribute::MultiValuedAttribute(string name, int prob, vector<string> arguments)
	: Attribute(name, prob), attribute_values(arguments)
{
}

string
MultiValuedAttribute::OutputAttributes()
{
	if(rnd_flipcoin(attribute_probability))
		return attribute + "(\"" + attribute_values[rnd_upto(attribute_values.size())] + "\")";
	else
		return "";
}
