#include <iostream>
#include <fstream>
#include <string>
#include "Json.h"

int main() {
	std::string keys[9] = {
		"one", "two" , "three", "four", "five", "six", "seven", "eight", "nine"
	};

	std::string values[9] = {
		"ten", "twenty" , "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"
	};

	std::cout << "CAN OBJECT LOAD?\n";
	JObject tst_obj(keys, values);

	tst_obj.display();
	std::cout << "\n\n";

	std::cout << "CAN OBJECT COPY?\n";
	JObject scd_tst = tst_obj;
	std::string value = "ninety";

	if (scd_tst["nine"] == value)
		std::cout << "yes";
	else {
		std::cout << "no";
		scd_tst.display();
	}
	std::cout << "\n\n";

	std::cout << "CAN OBJECT READ/WRITE FROM FILE?\n";
	std::ofstream ofs("test.txt");
	scd_tst.save_obj(ofs);
	ofs.close();
	JObject thd_tst;
	std::ifstream ifs("test.txt");
	thd_tst.retrieve_obj(ifs);
	if (thd_tst["nine"] == value)
		std::cout << "yes";
	else {
		std::cout << "no";
		thd_tst.display();
	}
	std::cout << "\n\n";

	std::cout << "DOES DELETE WORK?\n";
	std::cout << "by value: ";

	std::cout << "\n";
	std::cout << "by key: ";

	std::cout << "\n";
	std::cout << "by index: ";

	std::cout << "\n\n";

	std::cout << "DOES SORT WORK?\n";
	std::cout << "by value: ";

	std::cout << "\n";
	std::cout << "by key: ";

	std::cout << "\n";
	std::cout << "by index: ";

	std::cout << "\n\n";

	return 0;
}

