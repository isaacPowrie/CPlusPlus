#ifndef ATTRIBUTE
#define ATTRIBUTE

#include "node.h"

class Attribute : public Node {
	char* type_;
	char* value_;
public:
	Attribute(int idx_start, int idx_end, Document* doc);
	Attribute(int idx_start, int idx_end, Document* doc, Node* parent);
	~Attribute();

	// print or display the value assigned to an attribute
	void displayValue() const;
	char* returnValue() const;

	// print or display the attribute's name
	void displayType() const;
	char* returnType() const;

	bool checkEqualValue(char* chk_value);
	bool checkEqualType(char* chk_type);
	Node* operator[](int idx);
	bool isAttribute() { return true; };
};

#endif ATTRIBUTE