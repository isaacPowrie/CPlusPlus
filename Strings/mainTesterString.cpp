// Contains the main test of the functionality of the String class
// Isaac Powrie
// 2019-01-19
// mainTesterString.cpp

#include <iostream>
#include "stringStuff.h"

int main()
{
	char text[22] = "Hello 123 4 4.5 Isaac";
	char* one = nullptr;
	float* two = nullptr;

	String my_string(text);

	my_string.load_string(text);

	my_string.return_nums(two);
	my_string.return_subs(one);

	my_string.delete_string();

	my_string.load_string(text);

	my_string.return_nums(two);
	my_string.return_subs(one);

	return 0;
}