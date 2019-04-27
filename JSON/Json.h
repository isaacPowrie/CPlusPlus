#ifndef JSON
#define JSON

#include <fstream>
#include <string>

class JObject {
	std::string* keys;
	std::string* values;
	int length;

public:
	JObject();
	JObject(std::string keys[], std::string values[]);
	JObject(const JObject& source);
	~JObject();
	JObject& operator=(const JObject& source);
	JObject& operator+=(const JObject& r_op);
	void save_obj(std::ofstream& ofs);
	void retrieve_obj(std::ifstream& ifs);
	std::string operator[](std::string key);
	std::string keyLookup(std::string value);
	void display();
	void getKeys(std::string* cpy);
	void getValues(std::string* cpy);
	void deleteByIndex(int idx);
	void deleteByKey(std::string key);
	void deleteAllKey(std::string key);
	void deleteByValue(std::string value);
	void deleteAllValue(std::string value);
	friend JObject operator+(JObject l_op, JObject r_op);
	friend std::ostream& operator<<(std::ostream& os, const JObject source);
};

int getLength(std::string []);

#endif

// TODO: add "sort" methods
// TODO: update test for "sort" and "delete" methods