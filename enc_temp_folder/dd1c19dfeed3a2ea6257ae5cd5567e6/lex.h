#pragma once
#pragma once
#include <string>
#include <vector>
using namespace std;
enum {
	Num = 128, Fun, Sys, Glo, Loc,
	Id, Char, String, Else, Enum, If, Int, Return, Sizeof, While,  //��Ӧ�ؼ��ֲ�ѯ�� Id��λ
	Assign, Add, Sub, Mul, Div, Mod, Xor, Brak, Cond,   //��Ӧ�����ѯ�� Assign��λ
	Lor, Lan, Or, And, Eq, Ne, Lt, Gt, Le, Ge, Shl, Shr,
	Inc, Dec
};

class Token { 
public:
	int id;
	int value;
	Token(int i, int v);
	Token();
	void set(int i);
	void set(int i, int v);
};
class Synbl { //�������ű�

};
class Identifier {  //��C4�ṹһ�� name�ĳ���string ��ʱ�������ű�
public:
	int token;
	int hash;
	string name;
	int class_;
	int tpye;
	int value;
	int Bcalss;
	int Btype;
	int Bvalue;
	string get_name() const;
	bool operator==(const Identifier & obj2) const;
	bool operator==(string str) const;
	void print();
};

class Lex {
	string text;
	Token cur;
	unsigned pos;
	unsigned line;
	vector<string> I, C, S, K, P;
	vector<float> N;
	bool is_i(char c);
	void init();
	float to_float(string str);
	Token number_token();
	Token key_and_i_token(string str);
	Token char_end(string str);
	Token char_token(string str);
	Token string_end(string str);
	Token string_token(string str);
	Token delimiter_token();
public:
	Lex();
	Lex(string str); 
	void set(string str);
	Token next_token();
};