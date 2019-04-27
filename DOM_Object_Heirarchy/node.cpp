#include <iostream>
#include <fstream>
#include "node.h"

Node::Node(int idx_start, int idx_end, Document* doc) 
{
	idx_start_ = idx_start;
	idx_end_ = idx_end;
	parent_node_ = nullptr;
	document_ = doc;

	document_->append(this);
}

Node::Node(int idx_start, int idx_end, Document* doc, Node* parent)
{
	idx_start_ = idx_start;
	idx_end_ = idx_end;
	parent_node_ = parent;
	document_ = doc;

	Node** temp = new (std::nothrow) Node*[document_->num_children_ + 1];
	if (temp != nullptr) {
		for (int i = 0; i < document_->num_children_; i++) {
			temp[i] = document_->nodes_[i];
		}
		document_->append(this);
	}
}

int Node::returnStart()
{
	return idx_start_;
}

int Node::returnEnd()
{
	return idx_end_;
}

int Node::getCharIdx(char srch, int idx_start, int idx_end)
{
	int idx = -1;
	for (int i = idx_start; i < idx_end; i++) {
		if (document_->html_[i] == srch) {
			idx = i;
			break;
		}
	}
	return idx;
}

int Node::getCharIdx(char* srch, int idx_start, int idx_end)
{
	int idx = -1;
	int chk_length = getStrLength(srch);
	for (int i = idx_start; i <= idx_end; i++) {
		bool success = 1;
		for (int j = 0; j < chk_length; j++) {
			if (document_->html_[i + j] != srch[j]) {
				success = 0;
				break;
			}
		}
		if (success) {
			idx = i;
			break;
		}
	}
	return idx;
}

int Node::getCharIdxRev(char srch, int idx_end) {
	int idx = -1;
	for (int i = idx_end; i >= 0; i--) {
		if (document_->html_[i] == srch) {
			idx = i;
			break;
		}
	}
	return idx;
}

int Node::countOccs(char srch, int idx_start, int idx_end)
{
	int count = 0;
	int length = (idx_end + 1) - idx_end;
	for (int i = 0; i < length; i++) {
		count += document_->html_[i] == srch ? 1 : 0;
	}
	return count;
}

int Node::countOccs(char* string, char srch)
{
	int count = 0;
	int length = getStrLength(string);
	for (int i = 0; i < length; i++) {
		count += string[i] == srch ? 1 : 0;
	}
	return count;
}

int Node::countOccs(char* srch, int idx_start, int idx_end)
{
	int count = 0;
	int length = (idx_end + 1) - idx_start;
	int srch_length = getStrLength(srch);
	for (int i = 0; i < length; i++) {
		if (document_->html_[i] == srch[0]) {
			for (int j = 1; j < srch_length; j++) {
				if (document_->html_[i + j] != srch[j]) {
					count--;
					break;
				}
			}
			count++;
		}
	}
	return count;
}

int Node::countOccs(char* string, char* srch)
{
	int count = 0;
	int length = getStrLength(string);
	int srch_length = getStrLength(srch);
	for (int i = 0; i < length; i++) {
		if (string[i] == srch[0]) {
			for (int j = 1; j < srch_length; j++) {
				if (string[i + j] != srch[j]) {
					count--;
					break;
				}
			}
			count++;
		}
	}
	return count;
}

char* Node::deleteChar(char* string, char rmv_char)
{
	int length = getStrLength(string);
	int num_occurences = countOccs(string, rmv_char);
	int clean_length = length - num_occurences;
	char* clean_string = new (std::nothrow) char[clean_length];
	if (clean_string != nullptr) {
		int j = 0;
		for (int i = 0; i <= length; i++) {
			if (string[i] != rmv_char) {
				clean_string[j] = string[i];
				j++;
			}
		}
	}
	delete[] string;
	return clean_string;
}

char* Node::substring(int idx_start, int idx_end)
{
	int length = (idx_end + 1) - idx_start;
	char* sub = new (std::nothrow) char[length + 1];
	if (sub != nullptr) {
		for (int i = idx_start; i <= idx_end; i++) {
			sub[i - idx_start] = document_->html_[i];
		}
		sub[length] = '\0';
	}
	return sub;
}

char** Node::cutAt(char cut_char, int idx_start, int idx_end)
{
	int length = (idx_end + 1) - idx_start;
	char* string = substring(idx_start, idx_end);
	int num_occurences = countOccs(string, cut_char);
	int num_subs = num_occurences + 1;
	char** subs = new (std::nothrow) char*[num_subs];
	int idx = idx_start;

	if (subs != nullptr) {
		for (int i = 0; i < num_occurences; i++) {
			int next_idx = getCharIdx(cut_char, idx, idx_end);
			int sub_length = next_idx - idx;
			subs[i] = substring(idx, next_idx);
			idx = next_idx + 1;
		}
		subs[num_occurences] = substring(idx, idx_end);
	}
	delete[] string;
	return subs;
}

bool Node::checkStrEqual(char* first_str, char* second_str)
{
	bool equal = 1;
	int chk_length = getStrLength(second_str);
	int length = getStrLength(first_str);
	if (length == chk_length) {
		for (int i = 0; i < length; i++) {
			if (first_str[i] != second_str[i]) {
				equal = 0;
				break;
			}
		}
	} else {
		equal = 0;
	}
	return equal;
}

bool Node::isWhitespace(int idx, char* str)
{
	const int num_chars = 7;
	char whitespaceChars[num_chars] = { '\n','\t',' ','\v','\f','\r' };
	bool isWhitespace = 0;
	for (int i = 0; i < num_chars; i++) {
		if (whitespaceChars[i] == str[idx]) {
			isWhitespace = 1;
			break;
		}
	}
	return isWhitespace;
}

bool Node::isWhitespace(int idx)
{
	const int num_chars = 7;
	char whitespaceChars[num_chars] = { '\n','\t',' ','\v','\f','\r' };
	bool isWhitespace = 0;
	for (int i = 0; i < num_chars; i++) {
		if (whitespaceChars[i] == document_->html_[idx]) {
			isWhitespace = 1;
			break;
		}
	}
	return isWhitespace;
}