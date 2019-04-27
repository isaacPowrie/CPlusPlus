#include <iostream>
#include "attribute.h"

Attribute::Attribute(int idx_start, int idx_end, Document* doc):Node::Node(idx_start, idx_end, doc)
{
	char** tag_and_val = cutAt('=', returnStart(), returnEnd());
	type_ = deleteChar(tag_and_val[0], '=');
	value_ = deleteChar(tag_and_val[1], '"');
	delete[] tag_and_val;
}

Attribute::Attribute(int idx_start, int idx_end, Document* doc, Node* parent):Node::Node(idx_start, idx_end, doc, parent)
{
	char** tag_and_val = cutAt('=', returnStart(), returnEnd());
	type_ = deleteChar(tag_and_val[0], '=');
	value_ = deleteChar(tag_and_val[1], '"');
	delete[] tag_and_val;
}

Attribute::~Attribute() 
{
	delete[] type_;
	delete[] value_;
}

void Attribute::displayValue() const
{
	std::cout << value_;
}

char* Attribute::returnValue()const
{
	return this->value_;
}

void Attribute::displayType() const
{
	std::cout << type_;
}

char* Attribute::returnType() const
{
	return this->type_;
}

bool Attribute::checkEqualValue(char* chk_value)
{
	return checkStrEqual(this->value_, chk_value);
}

bool Attribute::checkEqualType(char* chk_type)
{
	return checkStrEqual(this->type_, chk_type);
}

Node* Attribute::operator[](int idx)
{
	return this;
}
