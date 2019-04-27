#include <iostream>
#include <fstream>
#include "element.h"
#include "textNode.h"
#include "attribute.h"

Element::Element(int idx_start, int idx_end, Document* doc, Node* parent, bool non_empty):Node::Node(idx_start, idx_end, doc, parent)
{
	this->getTag();
	this->getTagType();
	child_nodes_ = nullptr;
	num_children_ = 0;
	attribute_nodes_ = nullptr;
	num_attributes_ = 0;
	if (non_empty)
		parseForChildren();
	parseForAttributes();
}

Element::Element(int idx_start, int idx_end, Document* doc):Node::Node(idx_start, idx_end, doc)
{
	this->getTag();
	this->getTagType();
	child_nodes_ = nullptr;
	num_children_ = 0;
	attribute_nodes_ = nullptr;
	num_attributes_ = 0;
	parseForChildren();
	parseForAttributes();
}

Element::~Element()
{
	for (int i = 0; i < num_attributes_; i++) {
		delete[] attribute_nodes_[i];
	}

	delete[] attribute_nodes_;
	for (int i = (num_children_ - 1); i >= 0; i--) {
		delete[] child_nodes_[i];
	}
	delete[] child_nodes_;
	delete[] tag_;
	delete[] tag_type_;
}

void Element::parseForChildren()
{
	// Make sure element is not empty
	int idx_start = getCharIdx('>', returnStart(), returnEnd());
	int idx_end = getCharIdxRev('>', returnEnd());
	if (idx_start == idx_end) {
		return;
	}

	// Find the start of the tag close
	idx_end = getCharIdxRev('<', returnEnd());
	// Increase start to beginning of first child
	idx_start++;

	while (idx_start < idx_end) {
		// Skip through empty space
		while (isWhitespace(idx_start))
			idx_start++;

		// Check that the end has not now been reached
		if (idx_start == idx_end)
			break;

		// Determine if node is text or element
		if (idx_start != getCharIdx('<', idx_start, returnEnd())) {
			// Find end of text
			int next_end = getCharIdx('<', idx_start, returnEnd()) - 1;
			// Generate textNode
			TextNode* new_text_node = new TextNode (idx_start, next_end, this->document_, this);
			appendChild(new_text_node);
			idx_start = getCharIdx('<', idx_start, returnEnd()) + 1;
		} else {
			// Find end of element
			int next_end = 0;
			int occ_count = 1;
			int next_start = idx_start;
			int tag_end = getCharIdx(' ', idx_start, returnEnd());
			if (tag_end > getCharIdx('>', idx_start, returnEnd()))
				tag_end = getCharIdx('>', idx_start, returnEnd());
			char* tag = substring(idx_start + 1, tag_end - 1);
			int length = getStrLength(tag);
			while (occ_count > 0) {
				next_start = getCharIdx(tag, next_start + 2, returnEnd());
				if ((next_start - 1) == getCharIdxRev('/', next_start)) {
					occ_count--;
				} else if ((next_start - 1) == getCharIdxRev('<', next_start)) {
					occ_count++;
				} else if (next_start < 0) {
					occ_count = -1;
					next_start = idx_start;
				}
			}
			next_end = getCharIdx('>', next_start, returnEnd());
			// Generate element
			Element* new_element = new Element(idx_start, next_end, this->document_, this, occ_count + 1);
			appendChild(new_element);
			idx_start = next_end;
			delete[] tag;
		}
		// set idx_start to next child start value
		idx_start++;
	}
}

Node* Element::operator[](int idx)
{
	return child_nodes_[idx];
}

char* Element::getTag()
{
	int elem_length = returnEnd() - returnStart() + 1;
	char* html = new (std::nothrow) char[elem_length];
	if (html != nullptr) {
		html = this->substring(returnStart(), returnEnd());
	}
	int length = 0;
	while (html[length] != '>') {
		length++;
	}
	tag_ = new (std::nothrow) char[length + 1];
	if (tag_ != nullptr) {
		for (int i = 0; i <= length; i++) {
			tag_[i] = html[i];
		}
		tag_[length + 1] = '\0';
	}
	delete[] html;

	return tag_;
}

char* Element::getTagType()
{
	int start = getCharIdx('<', returnStart(), returnEnd()) + 1;
	int end = getCharIdx(' ', returnStart(), returnEnd());
	int tag_end = getCharIdx('>', returnStart(), returnEnd() + 1);
	if (end >= tag_end) {
		end = tag_end;
	}
	
	tag_type_ = new (std::nothrow) char[end - start + 1];
	if (tag_ != nullptr) {
		tag_type_ = this->substring(start, end - 1);
	}

	return tag_type_;
}

void Element::appendChild(Node* newChild)
{
	Node** new_children = new (std::nothrow) Node*[num_children_ + 1];
	if (new_children != nullptr) {
		for (int i = 0; i < num_children_; i++) {
			new_children[i] = child_nodes_[i];
		}
		new_children[num_children_] = newChild;
		num_children_++;
		delete[] child_nodes_;
		child_nodes_ = new_children;
	}
}

void Element::appendAttribute(Node* newAttribute)
{
	Node** new_attributes = new (std::nothrow) Node*[num_attributes_ + 1];
	if (new_attributes != nullptr) {
		for (int i = 0; i < num_attributes_; i++)
			new_attributes[i] = attribute_nodes_[i];
	}
	new_attributes[num_attributes_] = newAttribute;
	attribute_nodes_ = nullptr;
	delete[] attribute_nodes_;
	attribute_nodes_ = new_attributes;
	num_attributes_++;
}

void Element::parseForAttributes()
{
	Node* new_attribute = nullptr;
	int idx_start = returnStart();
	int idx_end = getCharIdx('>', returnStart(), returnEnd() + 1);
	int next_end = 0;
	if (countOccs('/', idx_start, idx_end) > 0)
		idx_end = getCharIdxRev('/', idx_end);
	while (idx_start < idx_end) {
		// find beginning of attribute
		idx_start = getCharIdx(' ', idx_start, idx_end) + 1;
		if (idx_start != 0) {
			// find end of attribute
			next_end = getCharIdx(' ', idx_start, idx_end) - 1;
			if (next_end < 0)
				next_end = getCharIdxRev('/', idx_end) - 1;
			if (next_end < idx_start)
				next_end = idx_end - 1;
			// create new attribute
			if (idx_start != idx_end)
				new_attribute = new (std::nothrow) Attribute(idx_start, next_end, document_, this);
			// append attribute to attribute list
			if (new_attribute != nullptr)
				appendAttribute(new_attribute);
		} else {
			idx_start = idx_end;
		}
	}
}

void Element::displayType() const
{
	std::cout << this->tag_type_;
}

char* Element::returnType() const
{
	return this->tag_type_;
}

void Element::displayValue() const
{
	std::cout << this->tag_;
}

char* Element::returnValue() const
{
	return this->tag_;
}

void Element::displayChildren() const
{
	for (int i = 0; i < num_children_; i++) {
		if (child_nodes_[i]->isElement()) {
			Element* elem = dynamic_cast<Element*>(child_nodes_[i]);
			elem->displayValue();
			elem->displayChildren();
			std::cout << "</";
			elem->displayType();
			std::cout << ">" << std::endl;
		} else {
			child_nodes_[i]->displayValue();
		}
	}
}

std::ofstream& Element::printChildren(std::ofstream& ofs) const
{
	for (int i = 0; i < num_children_; i++) {
		if (child_nodes_[i]->isElement()) {
			Element* elem = dynamic_cast<Element*>(child_nodes_[i]);
			ofs << elem->returnValue() << std::endl;
			elem->printChildren(ofs);
			ofs << "</" << elem->returnType() << ">" << std::endl;
		} else {
			ofs << child_nodes_[i]->returnValue();
		}
	}
	return ofs;
}

bool Element::checkEqualType(char* chk_type)
{
	return checkStrEqual(this->tag_type_, chk_type);
}

bool Element::checkEqualValue(char* chk_value)
{
	return checkStrEqual(this->tag_, chk_value);
}