#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <string>
#include <vector>
using namespace std;

class AttributeGenerator;

//Base class with pure virtual methods which will be derived as per different types of attribute generation
class Attribute
{
public:
	//Name of attribute
	string attribute;
	//Attribute generation probability
	int attribute_probability;
	Attribute(string, int);
	//Checks attribute probability and generate is accordingly
	virtual string OutputAttributes() = 0;
};

//Generates Boolean attributes such as hot, cold, used, unused, deprecated, etc
class BooleanAttribute : public Attribute
{
public:
	BooleanAttribute(string, int);
	string OutputAttributes();
};

//Generates Multi Valued attributes such as visibility("option"), no_sanitize("option"), etc
class MultiValuedAttribute : public Attribute
{
public:
	//stores various options of attributes e.g. visibility options - default, hidden, internal and protected
	vector<string> attribute_values;
	MultiValuedAttribute(string, int, vector<string>);
	string OutputAttributes();
};

//Generates function and types attributes
class AttributeGenerator
{
public:
	//stores instances of Attribute
	vector<Attribute*> attributes;
	void GenerateAllAttributes(std::ostream &);
};

#endif
