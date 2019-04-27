/*
This file contains the header information for the base class "Node"
in a DOM heirarchy, as well as the header information for the 
"Document" class which contains the relevant html as well as the
interface logic.
Isaac Powrie
2019-03-07
*/


#ifndef NODE
#define NODE

class Node;

class Document {
	const char* html_;
	int html_len_;
	Node** nodes_;
	int num_children_;

	// Used to help construction of node list
	void append(Node* new_node);

	// Used by public selector functions; returns idx of relevant node
	int findId(char* search_string, int idx_start);
	int findClass(char* search_string, int idx_start);
	int findTag(char* search_string, int idx_start);
	int findTextNode(int idx_start);

	// Used by public selector functions; displays relevant node
	void displayElement(int idx);
	void displayText(int idx);
	void displayInnerHTML(int idx);

	// Used by pulic selector functions; prints relevant node to file
	std::ofstream& printElement(std::ofstream& ofs, int idx);
	std::ofstream& printInnerHTML(std::ofstream& ofs, int idx);
	std::ofstream& printText(std::ofstream& ofs, int idx);

public:
	Document(char* html);
	virtual ~Document();
	void displayHTML();
	int getNumChildren() const;

	// Selector functions
	int displayNext(char search_type, char* search_string, int idx_start);
	int printNext(std::ofstream& ofs, char search_type, char* search_string, int idx_start);
	int displayNextInner(char search_type, char* search_string, int idx_start);
	int printNextInner(std::ofstream& ofs, char search_type, char* search_string, int idx_start);
	void displayAttributeValue(int idx, char* attribute);
	std::ofstream& printAttributeValue(std::ofstream& ofs, int idx, char* attribute);

	const char* getNodeValue(int idx) const;
	const char* getNodeType(int idx) const;

	friend class Node;
};
int getStrLength(char* string);


/*
The following is the abstract base class of the node heirarchy. The protected functions
are used by the derived classes for parsing through the document html in order
to define themselves.
*/
class Node {
	int idx_start_;
	int idx_end_;
	Node* parent_node_;
protected:
	Document* document_;

	// accessors for the private data members
	int returnStart();
	int returnEnd();

	// Get index of character starting at index
	int getCharIdx(char srch, int idx_start, int idx_end);
	int getCharIdx(char* srch, int idx_start, int idx_end);
	int getCharIdxRev(char srch, int idx_end);

	// Count occurrances of character or string
	int countOccs(char srch, int idx_start, int idx_end);
	int countOccs(char* string, char srch);
	int countOccs(char* srch, int idx_start, int idx_end);
	int countOccs(char* string, char* srch);

	// Functions which return strings
	char* deleteChar(char* string, char rmv_char);
	char* substring(int idx_start, int idx_end);
	char** cutAt(char cut_char, int idx_start, int idx_end);

	// String equivalency function
	bool checkStrEqual(char* first_str, char* second_str);
	bool isWhitespace(int idx, char* str);
	bool isWhitespace(int idx);

public:
	Node(int idx_start, int idx_end, Document* doc);
	Node(int idx_start, int idx_end, Document* doc, Node* parent);

	// The display, return, and checkEqual functions are used as query functions 
	// to return portions of the nodes to the document functions
	virtual void displayValue() const = 0;
	virtual char* returnValue() const = 0;
	virtual void displayType() const = 0;
	virtual char* returnType() const = 0;
	virtual bool checkEqualValue(char* chk_value) = 0;
	virtual bool checkEqualType(char* chk_type) = 0;
	virtual Node* operator[](int idx) = 0;
	virtual bool isElement() const { return false; };
	virtual bool isTextNode() const { return false; };
	virtual bool isAttribute() const { return false; };
};

#endif //NODE