/*
This file contains the header information for the derivded class "TextNode"
in a DOM heirarchy.
Isaac Powrie
2019-03-07
*/

#ifndef TEXTNODE
#define TEXTNODE

#include "node.h"

class TextNode : public Node {
	char* type_;
	char* text_;
public:
	TextNode(int idx_start, int idx_end, Document* doc, Node* parent);
	virtual ~TextNode();

	// print or return "text" (literally)
	void displayType() const;
	char* returnType() const;

	// print or return actual text
	void displayValue() const;
	char* returnValue() const;

	virtual bool checkEqualType(char* chk_type);
	virtual bool checkEqualValue(char* chk_value);
	Node* operator[](int idx);
	bool isTextNode() const { return true; };
};

#endif //TEXTNODE