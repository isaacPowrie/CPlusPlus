#include <iostream>
#include "Json.h"

JObject::JObject() {
	this->keys = nullptr;
	this->values = nullptr;
	this->length = 0;
}

JObject::JObject(std::string keys[], std::string values[]) {
	int keys_len = getLength(keys);
	int values_len = getLength(values);
	if (keys_len == values_len) {
		this->length = keys_len;
		this->keys = new (std::nothrow) std::string[this->length];
		this->values = new (std::nothrow) std::string[this->length];
		for (int i = 0; i < this->length; i++) {
			this->keys[i] = keys[i];
			this->values[i] = values[i];
		}
	} else {
		*this = JObject();
	}
}

JObject::JObject(const JObject& source) {
	this->keys = nullptr;
	this->values = nullptr;
	*this = source;
}

JObject::~JObject() {
	delete[] this->keys;
	delete[] this->values;
}

JObject& JObject::operator=(const JObject& source) {
	if (this != &source) {
		delete[] this->keys;
		delete[] this->values;
		this->length = source.length;
		this->keys = new (std::nothrow) std::string[this->length];
		this->values = new (std::nothrow) std::string[this->length];
		for (int i = 0; i < this->length; i++) {
			this->keys[i] = source.keys[i];
			this->values[i] = source.values[i];
		}
	}
	return *this;
}

JObject& JObject::operator+=(const JObject& r_op) {
	std::string*  new_keys = new (std::nothrow) std::string[this->length + r_op.length];
	std::string*  new_values = new (std::nothrow) std::string[this->length + r_op.length];
	if (new_keys != nullptr && new_values != nullptr) {
		int l_op_length = this->length;
		this->length += r_op.length;
		for (int i = 0; i < l_op_length; i++) {
			new_keys[i] = this->keys[i];
			new_values[i] = this->values[i];
		}
		for (int i = 0; i < this->length; i++) {
			new_keys[i + l_op_length] = r_op.keys[i];
			new_values[i + l_op_length] = r_op.values[i];
		}
		delete[] this->keys;
		delete[] this->values;
		this->keys = new_keys;
		this->values = new_values;
	}

	return *this;
}

std::string JObject::operator[](std::string key) {
	std::string value = "";
	for (int i = 0; i < length; i++) {
		if (this->keys[i] == key) {
			value = this->values[i];
			break;
		}
	}
	return value;
}

void JObject::save_obj(std::ofstream& ofs)
{
	if (length > 0) {
		ofs << length << "\n";
		for (int i = 0; i < length; i++) {
			ofs << keys[i] << ":" << values[i] << "\n";
		}
		ofs << "\n";
	}
}

void JObject::retrieve_obj(std::ifstream& ifs)
{
	if (ifs.is_open()) {
		int tmp_length;
		ifs >> tmp_length;
		std::string* tmp_keys = new (std::nothrow) std::string[tmp_length];
		std::string* tmp_values = new (std::nothrow) std::string[tmp_length];
		if (tmp_values != nullptr && tmp_keys != nullptr) {
			length = tmp_length;
			delete[] keys;
			delete[] values;
			keys = tmp_keys;
			values = tmp_values;
			if (length > 0) {
				ifs.ignore(2000, '\n');
				for (int i = 0; i < length; i++) {
					std::getline(ifs, keys[i], ':');
					std::getline(ifs, values[i]);
				}
			}
		} else {
			delete[] tmp_keys;
			delete[] tmp_values;
		}
	}
}

std::ostream& operator<<(std::ostream& os, const JObject source)
{
	for (int i = 0; i < source.length; i++) {
		os << source.keys[i] << ":" << source.values[i] << "\n";
	}

	return os;
}

void JObject::display() {
	std::cout << *this;
}

std::string JObject::keyLookup(std::string value) {
	std::string key = "";
	for (int i = 0; i < length; i++) {
		if (this->values[i] == value) {
			key = this->keys[i];
			break;
		}
	}
	return key;
}

void JObject::getKeys(std::string* cpy) {
	cpy = new (std::nothrow) std::string[this->length];
	if (cpy != nullptr) {
		for (int i = 0; i < this->length; i++) {
			cpy[i] = this->keys[i];
		}
	}
}

void JObject::getValues(std::string* cpy) {
	cpy = new (std::nothrow) std::string[this->length];
	if (cpy != nullptr) {
		for (int i = 0; i < this->length; i++) {
			cpy[i] = this->values[i];
		}
	}
}

void JObject::deleteByIndex(int idx) {
	std::string* temp_keys = new (std::nothrow) std::string[this->length - 1];
	std::string* temp_values = new (std::nothrow) std::string[this->length - 1];
	if (temp_keys != nullptr && temp_values != nullptr) {
		int i, j = 0;
		for (i = 0; i < this->length; i++) {
			if (i != idx) {
				temp_keys[j] = this->keys[i];
				temp_values[j] = this->values[i];
				j++;
			}
		}
		delete[] this->keys;
		delete[] this->values;
		this->values = temp_values;
		this->keys = temp_keys;
	}
}

void JObject::deleteByKey(std::string key) {
	int idx = -1;
	for (int i = 0; i < this->length; i++) {
		if (this->keys[i] == key) {
			idx = i;
			break;
		}
	}
	if (idx >= 0) {
		this->deleteByIndex(idx);
	}
}

void JObject::deleteAllKey(std::string key) {
	for (int i = 0; i < this->length; i++) {
		if (this->keys[i] == key) {
			this->deleteByIndex(i);
		}
	}
}

void JObject::deleteByValue(std::string value) {
	int idx = -1;
	for (int i = 0; i < this->length; i++) {
		if (this->values[i] == value) {
			idx = i;
			break;
		}
	}
	if (idx >= 0) {
		this->deleteByIndex(idx);
	}
}

void JObject::deleteAllValue(std::string value) {
	for (int i = 0; i < this->length; i++) {
		if (this->values[i] == value) {
			this->deleteByIndex(i);
		}
	}
}

JObject operator+(JObject l_op, JObject r_op) {
	JObject new_obj(l_op);
	new_obj += r_op;
	return new_obj;
}

int getLength(std::string array[]) {
	int count = 1;
	while ((int)&array[count - 1] < (int)array + (int)(sizeof(*array) * 8)) {
		count++;
	}
	return count;
}