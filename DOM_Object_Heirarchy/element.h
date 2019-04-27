/*
This file contains the header information for the derived class "Element"
in a DOM heirarchy.
Isaac Powrie
2019-03-07
*/

#ifndef ELEMENT
#define ELEMENT

#include "node.h"

class Element : public Node {
	char* tag_;
	char* tag_type_;
	Node** child_nodes_;
	int num_children_;
	Node** attribute_nodes_;
	int num_attributes_;

	// These functions are used in self parsing during construction:
	// getTag(), getTagType(), appendChild(), parseForChildren(),
	// appendAttribute(), parseForAttributes()
	char* getTag();
	char* getTagType();

	// This function is used by the element to add children to itself
	// after they have undertaken their own construction
	void appendChild(Node* newChild);

	// This function is used by the element to parse through itself
	// looking for and intiating the construction of child elements;
	// it is the integral piece of the whole model's self construction
	void parseForChildren();

	// Thise function is used by the element to add attributes to
	// itself after the have undertaken their own construction
	void appendAttribute(Node* newAttribute);

	// This function is used by the element to parse through its
	// own tag looking for and initiating the construction of
	// attributes.
	void parseForAttributes();

public:
	Element(int idx_start, int idx_end, Document* doc, Node* parent, bool empty);
	Element(int idx_start, int idx_end, Document* doc);
	virtual ~Element();
	Node* operator[](int idx);

	// print or return the tag type
	void displayValue() const;
	char* returnValue() const;

	// print or return the full opening tag
	void displayType() const;
	char* returnType() const;

	// display of print to file children
	void displayChildren() const;
	std::ofstream& printChildren(std::ofstream& ofs) const;

	virtual bool checkEqualType(char* chk_type);
	virtual bool checkEqualValue(char* chk_value);
	bool isElement() const { return true; };
};

#endif //ELEMENT