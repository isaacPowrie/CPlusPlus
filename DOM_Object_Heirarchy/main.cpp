/*
This is a test module for the DOCUMENT object heirarchy. A successful test will
run through the "runTest" function for each HTML example being tested. An
unsuccessful test will stop after proccessing HTML which gave unexpected results,
and will show the test auditor where the error occured in the load.
*/

#include <iostream>
#include <fstream>
#include "node.h"
#include "element.h"

bool runTest(char* html);

int main() {
	char testOneHTML[112] = "<html>\n<body>\n\n<h1>My First Heading</h1>\n<p>My first paragraph.</p><img src=\"test\" alt=\"test\"/></body>\n</html>";
	char testTwoHTML[112] = "<html>\n<body>\n\n<h1>My First Heading</h1>\n<p>My first paragraph.</p><img src=\"test\" alt=\"test\"></body>\n</html>";
	bool success;

	success = runTest(testOneHTML);
	if (success) {
		success = runTest(testTwoHTML);
		if (!success)
			std::cout << "\nERRORS HAVE OCCURED IN THE SECOND HTML";
	} else {
		std::cout << "\nERRORS HAVE OCCURED IN FIRST HTML";
	}

	return 0;
}

bool documentExists(Document* doc)
{
	return doc != nullptr ? 1 : 0;
}

template <typename T>
bool numsEqual(T actual_num, T expected_num)
{
	bool success = 0;
	if (actual_num == expected_num) {
		success = 1;
		std::cout << "yes" << std::endl;
	} else {
		std::cout << "no" << std::endl;
	}
	return success;
}

bool cStringsEqual(const char* actual_str, const char* expected_str)
{
	bool success = 0;
	int i = 0;
	do {
		if (actual_str[i] == expected_str[i]) {
			success = 1;
		}
		i++;
	} while (actual_str[i] != '\0' && expected_str[i] != '\0' && success);
	return success;
}

bool runTest(char* html)
{
	bool success = 1;
	bool chk = 1;
	Document *test_doc = new Document(html);
	if (documentExists(test_doc)) {
		std::cout << "|+++============ DOCUMENT LOADED ============+++|\n\n";
		test_doc->displayHTML();
		std::cout << std::endl;

		std::cout << "\nDoes the document contain the expected number of children?\n";
		success = success ? numsEqual(test_doc->getNumChildren(), 9) : 0;

		std::cout << "\nDoes the document contain the expected children?\n";
		std::cout << "HTML:\t\t\t";
		chk = cStringsEqual(test_doc->getNodeType(0), "html");
		success = success ? chk : 0;
		chk ? std::cout << "yes\n" : std::cout << "no\n";
		std::cout << "BODY:\t\t\t";
		chk = cStringsEqual(test_doc->getNodeType(1), "body");
		success = success ? chk : 0;
		chk ? std::cout << "yes\n" : std::cout << "no\n";
		std::cout << "H1:\t\t\t";
		chk = cStringsEqual(test_doc->getNodeType(2), "h1");
		success = success ? chk : 0;
		chk ? std::cout << "yes\n" : std::cout << "no\n";
		std::cout << "Header Text:\t\t";
		chk = cStringsEqual(test_doc->getNodeValue(3), "My First Heading");
		success = success ? chk : 0;
		chk ? std::cout << "yes\n" : std::cout << "no\n";
		std::cout << "P:\t\t\t";
		chk = cStringsEqual(test_doc->getNodeType(4), "p");
		success = success ? chk : 0;
		chk ? std::cout << "yes\n" : std::cout << "no\n";
		std::cout << "Paragraph Text:\t\t";
		chk = cStringsEqual(test_doc->getNodeValue(5), "My first paragraph.");
		success = success ? chk : 0;
		chk ? std::cout << "yes\n" : std::cout << "no\n";
		std::cout << "IMG:\t\t\t";
		chk = cStringsEqual(test_doc->getNodeType(6), "img");
		success = success ? chk : 0;
		chk ? std::cout << "yes\n" : std::cout << "no\n";
		std::cout << "Src Attribute:\t\t";
		chk = cStringsEqual(test_doc->getNodeValue(7), "test");
		success = success ? chk : 0;
		chk ? std::cout << "yes\n" : std::cout << "no\n";
		std::cout << "Alt Attribute:\t\t";
		chk = cStringsEqual(test_doc->getNodeType(8), "alt");
		success = success ? chk : 0;
		chk ? std::cout << "yes\n" : std::cout << "no\n";
		std::cout << "|+++=========================================+++|" << std::endl;
	}
	delete[] test_doc;
	return success;
}