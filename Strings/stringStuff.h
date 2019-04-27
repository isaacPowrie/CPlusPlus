#ifndef STRING_CLASS
#define STRING_CLASS

class String {
	char* string_strt;
	char** subs;
	float* nums;
	int length;
	int word_cnt;
	int letter_cnt;
	int num_cnt;

	// modifiers
	int str_length(char inpt_string[]);
	void str_length();
	int count_char(char cnt_char = ' ');
	void count_nums();
	float string_to_num(char []);
	void get_subs(char delimeter = ' ');
	void get_nums();

public:
	String();
	String(char* usr_string);
	~String();
	// modifiers
	void load_string(char* usr_string);
	void delete_string(char verbose = 'n');
	char shift();
	char pop();
	void trim_left();
	void trim_right();
	void trim();
	String& operator=(String&);
	String& operator+=(char);
	String& operator+=(char*);
	String& operator+=(String&);
	// queries
	void return_subs(char* subs_cpy) const;
	void return_nums(float* nums_cpy) const;
	char charAt(int idx) const;
	int charCodeAt(int idx) const;
	int indexOf(char lk_up) const;
	int indexOf(char* lk_up) const;
	int lastIndexOf(char lk_up) const;
	int lastIndexOf(char* lk_up) const;
	void substr(char* substr, int strt_idx, int len) const;
	void substring(char* substring, int strt_idx, int end_idx) const;
	friend bool operator==(String& lhs, String& rhs);
	friend bool operator!=(String& lhs, String& rhs);
	friend String operator+(String&, String&);
	friend String operator+(String&, char);
	friend String operator+(char, String&);
	friend String operator+(String&, char*);
	friend String operator+(char*, String&);
};

#endif
