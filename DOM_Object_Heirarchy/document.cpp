#include <iostream>
#include <fstream>
#include "element.h"

Document::Document(char* html)
{
	int html_len_ = getStrLength(html);
	char* temp = new (std::nothrow) char[html_len_ + 1];
	if (temp != nullptr) {
		for (int i = 0; i <= html_len_; i++) {
			temp[i] = html[i];
		}
	}
	html_ = temp;
	Node** nodes_ = nullptr;
	num_children_ = 0;
	
	Element* first_child = new Element(0, (html_len_ - 1), this);
}

Document::~Document()
{
	if (num_children_ > 0) 
		delete[] nodes_[num_children_ - 1];
	delete[] nodes_;
	delete[] html_;
}

void Document::append(Node* new_node)
{
	Node** temp = new (std::nothrow) Node*[num_children_ + 1];
	if (temp != nullptr) {
		for (int i = 0; i < num_children_; i++) {
			temp[i] = nodes_[i];
		}
		temp[num_children_] = new_node;
		nodes_ = nullptr;
		delete[] nodes_;
		nodes_ = temp;
		num_children_++;
	}
}

/*****************************
PRIVATE SELECTOR HELPERS: FIND
******************************/
int Document::findId(char* search_string, int idx_start)
{
	int idx = -1;
	char attribute[3] = "id";
	for (int i = idx_start; i < num_children_; i++) {
		if (nodes_[i]->isElement()) {
			int j = 1;
			while (nodes_[i + j]->isAttribute()) {
				j++;
				if (nodes_[i]->checkEqualType(attribute) && nodes_[i]->checkEqualValue(search_string)) {
					idx = i;
					i = num_children_;
				}
			}
			i += j;
		}
	}
	return idx;
}

int Document::findClass(char* search_string, int idx_start)
{
	int idx = -1;
	char attribute[6] = "class";
	for (int i = idx_start; i < num_children_; i++) {
		if (nodes_[i]->isElement()) {
			int j = 1;
			while (nodes_[i + j]->isAttribute()) {
				j++;
				if (nodes_[i]->checkEqualType(attribute) && nodes_[i]->checkEqualValue(search_string)) {
					idx = i;
					i = num_children_;
				}
			}
			i += j;
		}
	}
	return idx;
}

int Document::findTag(char* search_string, int idx_start)
{
	int idx = -1;
	for (int i = idx_start; i < num_children_; i++) {
		if (nodes_[i]->isElement()) {
			if (nodes_[i]->checkEqualType(search_string)) {
				idx = i;
				i = num_children_;
			}
		}
	}
	return idx;
}

int Document::findTextNode(int idx_start)
{
	int idx = -1;
	for (int i = idx_start; i < num_children_; i++) {
		if (nodes_[i]->isTextNode()) {
			idx = i;
			i = num_children_;
		}
	}
	return idx;
}


/*****************************
PRIVATE SELECTOR HELPERS: DISPLAY
******************************/
void Document::displayElement(int idx)
{
	if (nodes_[idx]->isElement()) {
		nodes_[idx]->displayValue();
	} else {
		std::cout << "The node selected is not an element." << std::endl;
	}
}

void Document::displayText(int idx)
{
	if (nodes_[idx]->isTextNode()) {
		nodes_[idx]->displayValue();
	} else {
		std::cout << "The node selected is not a text node." << std::endl;
	}
}

void Document::displayInnerHTML(int idx)
{
	if (nodes_[idx]->isElement()) {
		Element* elem = dynamic_cast<Element*>(nodes_[idx]);
		elem->displayChildren();
	} else {
		std::cout << "The node selected is not an element." << std::endl;
	}
}

/*****************************
PRIVATE SELECTOR HELPERS: PRINT
******************************/
std::ofstream& Document::printElement(std::ofstream& ofs, int idx)
{
	if (nodes_[idx]->isElement()) {
		ofs << nodes_[idx]->returnValue();
	} 
	return ofs;
}

std::ofstream& Document::printInnerHTML(std::ofstream& ofs, int idx)
{
	if (nodes_[idx]->isElement()) {
		Element* elem = dynamic_cast<Element*>(nodes_[idx]);
		elem->printChildren(ofs);
	}
	return ofs;
}

std::ofstream& Document::printText(std::ofstream& ofs, int idx)
{

	return ofs;
}

/*****************************
PUBLIC SELECTOR AND DISPLAY FUNCTIONS
******************************/
void Document::displayHTML()
{
	std::cout << html_;
}

int Document::getNumChildren() const
{
	return num_children_;
}

int Document::displayNext(char search_type, char* search_string, int idx_start)
{
	int idx = -1;
	switch (search_type) {
	// Id attribute
	case '#':
		idx = findId(search_string, idx_start);
		if (idx >= 0) {
			displayElement(idx);
		}
		break;
	// Class attribute
	case '.':
		idx = findClass(search_string, idx_start);
		if (idx >= 0) {
			displayElement(idx);
		}
		break;
	// Tag name (e for element)
	case 'e':
		idx = findTag(search_string, idx_start);
		if (idx >= 0) {
			displayElement(idx);
		}
		break;
	// Text
	case 't':
		idx = findTextNode(idx_start);
		if (idx >= 0) {
			displayText(idx);
		}
		break;
	default:
		std::cout << "Invalid search type '" << search_type << "'." << std::endl;
	}
	return idx;
}

int Document::printNext(std::ofstream& ofs, char search_type, char* search_string, int idx_start)
{
	int idx = -1;
	switch (search_type) {
		// Id attribute
	case '#':
		idx = findId(search_string, idx_start);
		if (idx >= 0) {
			printElement(ofs, idx);
		}
		break;
		// Class attribute
	case '.':
		idx = findClass(search_string, idx_start);
		if (idx >= 0) {
			printElement(ofs, idx);
		}
		break;
		// Tag name (e for element)
	case 'e':
		idx = findTag(search_string, idx_start);
		if (idx >= 0) {
			printElement(ofs, idx);
		}
		break;
		// Text
	case 't':
		idx = findTextNode(idx_start);
		if (idx >= 0) {
			printText(ofs, idx);
		}
		break;
	default:
		std::cout << "Invalid search type '" << search_type << "'." << std::endl;
	}
	return idx;
}

int Document::displayNextInner(char search_type, char* search_string, int idx_start)
{
	int idx = -1;
	switch (search_type) {
		// Id attribute
	case '#':
		idx = findId(search_string, idx_start);
		if (idx >= 0) {
			displayInnerHTML(idx);
		}
		break;
		// Class attribute
	case '.':
		idx = findClass(search_string, idx_start);
		if (idx >= 0) {
			displayInnerHTML(idx);
		}
		break;
		// Tag name (e for element)
	case 'e':
		idx = findTag(search_string, idx_start);
		if (idx >= 0) {
			displayInnerHTML(idx);
		}
		break;
	default:
		std::cout << "Invalid search type '" << search_type << "'." << std::endl;
	}
	return idx;
}

int Document::printNextInner(std::ofstream& ofs, char search_type, char* search_string, int idx_start)
{
	int idx = -1;
	switch (search_type) {
		// Id attribute
	case '#':
		idx = findId(search_string, idx_start);
		if (idx >= 0) {
			printInnerHTML(ofs, idx);
		}
		break;
		// Class attribute
	case '.':
		idx = findClass(search_string, idx_start);
		if (idx >= 0) {
			printInnerHTML(ofs, idx);
		}
		break;
		// Tag name (e for element)
	case 'e':
		idx = findTag(search_string, idx_start);
		if (idx >= 0) {
			printInnerHTML(ofs, idx);
		}
		break;
	default:
		std::cout << "Invalid search type '" << search_type << "'." << std::endl;
	}
	return idx;
}

void Document::displayAttributeValue(int idx, char* attribute)
{
	if (nodes_[idx]->isElement()) {
		int j = 1;
		bool match = false;
		while (nodes_[idx + j]->isAttribute()) {
			if (nodes_[idx + j]->checkEqualType(attribute)) {
				nodes_[idx + j]->displayValue();
			}
		}
		if (!match) {
			std::cout << "(none)" << std::endl;
		}
	} else {
		std::cout << "The node selected is not an element." << std::endl;
	}
}

std::ofstream& Document::printAttributeValue(std::ofstream& ofs, int idx, char* attribute)
{
	if (nodes_[idx]->isElement()) {
		int j = 1;
		while (nodes_[idx + j]->isAttribute()) {
			if (nodes_[idx + j]->checkEqualType(attribute)) {
				ofs << nodes_[idx + j]->returnValue();
			}
		}
	}
	return ofs;
}

const char* Document::getNodeValue(int idx) const
{
	return nodes_[idx]->returnValue();
}

const char* Document::getNodeType(int idx) const
{
	return nodes_[idx]->returnType();
}

int getStrLength(char* string)
{
	int length = 0;
	while (string[length] != '\0') {
		length++;
	}
	return length;
}

