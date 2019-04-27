#ifndef DOCNODE
#define DOCNODE

#include "node.h"

class Document {
	const char* html_;
	int html_len_;
	Node** nodes_;
	int num_children_;
public:
	Document(char* html);
	~Document();
	const char* returnHTML();
	friend class Node;
};

int getStrLength(char* string);

#endif // DOCNODE

