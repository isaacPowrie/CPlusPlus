// This file contains C++ versions of JS string methods
// Isaac Powrie
// stringStuff.cpp
// 2019-01-17

#include <iostream>
#include "stringStuff.h"

// CONSTRUCTOR & DECONSTRUCTOR
String::String() 
{
	load_string('\0');
}

String::String(char* usr_string)
{
	load_string(usr_string);
}

String::~String()
{
	delete_string();
}

//PUBLIC
void String::load_string(char* usr_string)
{
	int i = 0;

	length = str_length(usr_string);
	string_strt = new char[length + 1];

	do {
		string_strt[i] = usr_string[i];
		i++;
	} while (usr_string[i - 1] != '\0');

	word_cnt = count_char() + 1;
	count_nums();
	get_subs();
	get_nums();
}

void String::delete_string(char verbose) 
{
	delete[] string_strt;
	string_strt = nullptr;
	delete[] subs[0];
	subs[0] = nullptr;
	delete[] subs;
	subs = nullptr;
	delete[] nums;
	nums = nullptr;

	if (verbose != 'n') {
		std::cout << "Your string has been successfully removed." << std::endl;
	}
}

void String::return_nums(float* nums_cpy) const
{
	for (int i = 0; i < num_cnt; i++) {
		std::cout << nums[i] << "\n";
	}
}

void String::return_subs(char* subs_cpy) const
{
	for (int i = 0; i < word_cnt; i++) {
		std::cout << subs[i] << "\n";
	}
}

char String::shift()
{
	char shift_char = string_strt[0];
	char* shifted_string = nullptr;

	shifted_string = new char[length];
	for (int i = 0; i < length; i++) {
		shifted_string[i] = string_strt[i + 1];
	}
	length -= 1;

	delete[] string_strt;
	string_strt = shifted_string;

	return shift_char;
}

char String::pop()
{
	char pop_char = string_strt[length - 1];
	char* popped_string = nullptr;

	popped_string = new char[length];
	length -= 1;
	for (int i = length; i >= 0; i--) {
		if (i == length) {
			popped_string[i] = '\0';
		} else {
			popped_string[i] = string_strt[i];
		}
	}

	delete[] string_strt;
	string_strt = popped_string;

	return pop_char;
}

char String::charAt(int idx) const
{
	return string_strt[idx];
}

int String::charCodeAt(int idx) const
{
	int code = (int)string_strt[idx];
	return code;
}

int String::indexOf(char lk_up) const
{
	int idx = -1;
	for (int i = 0; i <= length; i++) {
		if (string_strt[i] == lk_up) {
			idx = i;
			break;
		}
	}
	return idx;
}

int String::indexOf(char* lk_up) const
{
	int idx = -1;
	for (int i = 0; i <= length; i++) {
		if (string_strt[i] == lk_up[i]) {
			idx = i;
			while (lk_up[i] == string_strt[i] && lk_up[i] != '\n') {
				i++;
			}
			if (lk_up[i] == '\0') {
				break;
			} else {
				idx = -1;
			}
		}
	}
	return idx;
}

int String::lastIndexOf(char lk_up) const
{
	int idx = -1;
	for (int i = 0; i <= length; i++) {
		if (string_strt[i] == lk_up) {
			idx = i;
		}
	}
	return idx;
}

int String::lastIndexOf(char* lk_up) const
{
	int idx = -1;
	for (int i = 0; i <= length; i++) {
		if (string_strt[i] == lk_up[i]) {
			idx = i;
			while (lk_up[i] == string_strt[i] && lk_up[i] != '\n') {
				i++;
			}
			if (lk_up[i] != '\0') 
				idx = -1;
		}
	}
	return idx;
}

void String::substr(char* substr, int strt_idx, int len) const
{
	substr = new char[len + 1];
	for (int i = strt_idx; i < len + strt_idx; i++) {
		substr[i - strt_idx] = string_strt[i];
	}
	substr[len] = '\0';
} 

void String::substring(char* substring, int strt_idx, int end_idx) const
{
	int len = end_idx - strt_idx;
	substring = new char[len + 1];
	for (int i = strt_idx; i < len + strt_idx; i++) {
		substring[i - strt_idx] = string_strt[i];
	}
	substring[len] = '\0';
}

void String::trim_left()
{
	int spc_cnt = 0;
	int i = 0;
	while (string_strt[i] == ' ') {
		spc_cnt++;
		i++;
	}
	char* trimmed_str = new char[length - spc_cnt];
	for (int j = spc_cnt; j <= length; j++) {
		trimmed_str[j - spc_cnt] = string_strt[j];
	}
	length -= spc_cnt;

	delete[] string_strt;
	string_strt = trimmed_str;
}

void String::trim_right()
{
	int spc_cnt = 0;
	int i = 0;
	while (string_strt[length - 1] == ' ') {
		spc_cnt++;
		i--;
	}
	char* trimmed_str = new char[length - spc_cnt];
	for (int j = length; j >= spc_cnt; j--) {
		trimmed_str[j - spc_cnt] = string_strt[j];
	}
	length -= spc_cnt;

	delete[] string_strt;
	string_strt = trimmed_str;
}

void String::trim()
{
	trim_left();
	trim_right();
}

//PRIVATE
String& String::operator=(String& new_str)
{
	this->delete_string();
	string_strt = new_str.string_strt;
	subs = new_str.subs;
	nums = new_str.nums;
	length = new_str.length;
	word_cnt = new_str.word_cnt;
	letter_cnt = new_str.letter_cnt;
	num_cnt = new_str.num_cnt;
}

String& String::operator+=(String& add_str)
{
	char* new_str = new (std::nothrow) char[length + add_str.length + 1];
	for (int i = 0; i < length; i++) {
		new_str[i] = string_strt[i];
	}
	for (int i = 0; i <= add_str.length; i++) {
		new_str[i + length] = string_strt[i];
	}

	String concat(new_str);
	*this = concat;

	delete[] new_str;
}

String& String::operator+=(char add_str)
{
	char* new_str = new (std::nothrow) char[length + 1];
	for (int i = 0; i < length; i++) {
		new_str[i] = string_strt[i];
	}
	new_str[length] = add_str;
	new_str[length + 1] = '\0';

	String concat(new_str);
	*this = concat;

	delete[] new_str;
}

String& String::operator+=(char* add_str)
{
	int add_length = 0;
	while (add_str[add_length] != '\0') {
		add_length++;
	}
	char* new_str = new (std::nothrow) char[length + 1];
	int count = 0;
	for (int i = 0; i < length; i++) {
		new_str[i] = string_strt[i];
	}
	for (int i = 0; i <= add_length; i++) {
		new_str[i + length] = string_strt[i];
	}

	String concat(new_str);
	*this = concat;

	delete[] new_str;
}

int String::str_length(char inpt_string[])
{
	int count = 0;
	for (int i = 0; i >= 0; i++) {
		if (inpt_string[i] != '\0') {
			count += 1;
		} else {
			break;
		}
	}
	return count;
}

void String::str_length()
{
	int count = 0;
	for (int i = 0; i >= 0; i++) {
		if (string_strt[i] != '\0') {
			count += 1;
		} else {
			break;
		}
	}
	length = count;
}

float String::string_to_num(char inpt_string[])
{
	float decimal_val = 0;
	int size = str_length(inpt_string);
	float before_dec = 0.1;
	bool left_of_dec = true;

	for (int i = 0; i < size; i++) {
		if (inpt_string[i] != '.')
			before_dec *= 10;
		else
			break;
	}

	for (int i = 0; i < size; i++) {
		switch (inpt_string[i]) {
		case '1':
			decimal_val += 1 * before_dec;
			break;
		case '2':
			decimal_val += 2 * before_dec;
			break;
		case '3':
			decimal_val += 3 * before_dec;
			break;
		case '4':
			decimal_val += 4 * before_dec;
			break;
		case '5':
			decimal_val += 5 * before_dec;
			break;
		case '6':
			decimal_val += 6 * before_dec;
			break;
		case '7':
			decimal_val += 7 * before_dec;
			break;
		case '8':
			decimal_val += 8 * before_dec;
			break;
		case '9':
			decimal_val += 9 * before_dec;
			break;
		}
		if (inpt_string[i] != '.')
			before_dec /= 10;
	}

	return decimal_val;
}

void String::count_nums()
{
	num_cnt = 0;
	bool dec_flag = false;
	bool prev_digit_flag = false;

	for (int i = 0; i < length; i++) {
		if (string_strt[i] >= '0' && string_strt[i] <= '9') {
			if (!prev_digit_flag) {
				num_cnt++;
				prev_digit_flag = true;
			}
		} else if (string_strt[i] == '.' && !dec_flag) {
			dec_flag = true;
		} else {
			prev_digit_flag = false;
			dec_flag = false;
		}
	}
}

int String::count_char(char cnt_char)
{
	int count = 0;
	int i = 0;

	while (string_strt[i] != '\0') {
		if (string_strt[i] == cnt_char) {
			count++;
		}
		i++;
	}

	return count;
}

void String::get_subs(char delimeter)
{
	int sub_idx = 1;
	bool new_sub_flag = 0;
	subs = new char*[word_cnt];
	subs[0] = new char[length + 1];

	for (int i = 0; i <= length; i++) {
		subs[0][i] = string_strt[i];
	}

	for (int i = 0; i < length; i++) {
		if (new_sub_flag == 1 && subs[0][i] != delimeter) {
			subs[sub_idx] = &subs[0][i];
			sub_idx++;
			new_sub_flag = 0;
		} else if (subs[0][i] == delimeter) {
			subs[0][i] = '\0';
			new_sub_flag = 1;
		}
	}
}

void String::get_nums()
{
	nums = new float[num_cnt];
	int j = 0;
	
	for (int i = 0; i < num_cnt; i++) {
		int idx = 0;
		bool dec_flag = false;
		bool in_num_flag = false;
		char* num_string = new char[24];

		while (j < length) {
			if (string_strt[j] >= '0' && string_strt[j] <= '9') {
				num_string[idx] = string_strt[j];
				in_num_flag = true;
				idx++;
			} else if (string_strt[j] == '.' && dec_flag == false) {
				num_string[idx] = string_strt[j];
				idx++;
				dec_flag = true;
			} else if (in_num_flag) {
				num_string[idx] = '\0';
				j++;
				break;
			}
			j++;
		}

		nums[i] = string_to_num(num_string);
		delete[] num_string;
	}
}

bool operator==(String& lhs, String& rhs) {
	bool equal = lhs.length == rhs.length;
	if (equal) {
		for (int i = 0; i < lhs.length; i++) {
			equal = lhs.string_strt[i] == rhs.string_strt[i];
			if (!equal) {
				i == lhs.length;
			}
		}
	}
	return equal;
}

bool operator!=(String& lhs, String& rhs) {
	return !(lhs == rhs);
}

String operator+(String& lhs, String& rhs)
{
	String copy_lhs = lhs;
	copy_lhs += rhs;
	return copy_lhs;
}

String operator+(String& lhs, char add_str)
{
	String copy_lhs = lhs;
	copy_lhs += add_str;
	return copy_lhs;
}

String operator+(char add_str, String& lhs)
{
	return lhs + add_str;
}

String operator+(String& lhs, char* add_str)
{
	String copy_lhs = lhs;
	copy_lhs += add_str;
	return copy_lhs;
}

String operator+(char* add_str, String& lhs)
{
	return lhs + add_str;
}