#include <iostream>
#include "textNode.h"

TextNode::TextNode(int idx_start, int idx_end, Document* doc, Node* parent):Node::Node(idx_start, idx_end, doc, parent)
{
	char type[5] = "text";
	type_ = type;
	text_ = substring(returnStart(), returnEnd());
}

TextNode::~TextNode()
{
	delete[] text_;
}

void TextNode::displayType() const
{
	std::cout << type_;
}

char* TextNode::returnType() const
{
	return type_;
}

void TextNode::displayValue() const
{
	std::cout << text_;
}

char* TextNode::returnValue() const
{
	return text_;
}

bool TextNode::checkEqualType(char* chk_type)
{
	bool equal = 1;
	int chk_length = getStrLength(chk_type);
	int length = getStrLength(text_);
	if (length == chk_length) {
		for (int i = 0; i < length; i++) {
			if (text_[i] != chk_type[i]) {
				equal = 0;
				break;
			}
		}
	} else {
		equal = 0;
	}
	return equal;
}

bool TextNode::checkEqualValue(char* chk_value)
{
	bool equal = 1;
	int chk_length = getStrLength(chk_value);
	int length = getStrLength(text_);
	if (length == chk_length) {
		for (int i = 0; i < length; i++) {
			if (text_[i] != chk_value[i]) {
				equal = 0;
				break;
			}
		}
	} else {
		equal = 0;
	}
	return equal;
}

Node* TextNode::operator[](int idx)
{
	return this;
}