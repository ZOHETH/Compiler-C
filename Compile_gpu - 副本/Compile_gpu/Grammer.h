#ifndef _ANALYSIS_H_
#define _ANALYSIS_H_
#include"lex.h"
#include "Semantic.h"
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>
#include <iomanip>
#include <map>
#include <cmath>
#include <stack>
#include <fstream>
#include <stack>
/*
extern enum Token_tag {
	Num = 128, Fun, Sys, Glo, Loc,
	Id, Char, String, Else, Enum, If, Int, Return, Sizeof, While, Void, //��Ӧ�ؼ��ֲ�ѯ�� Id��λ
	Assign, Add, Sub, Open_paren, Close_paren, Open_curly, Close_curly, Comma, Semicolon, Mul, Div, Mod, Xor, Brak, Cond,			  //��Ӧ�����ѯ�� Assign��λ
	Lor, Lan, Or, And, Eq, Ne, Lt, Gt, Le, Ge, Shl, Shr,
	Inc, Dec
};*/

enum Action_tag {
	add_ptr=0,				//0
	ident_rec,				//1
	id_to_glo,				//2
	parameter_rec,			//3
	loc_var_rec,			//4
	loc_index_rec,			//5
	type_rec,				//6
	func_enter,				//7
	leave,					//8
	if_begin,				//9
	else_begin,				//10
	if_end,					//11
	after_while,			//12
	while_begin,			//13
	while_end,				//14
	imm_num,
	ptr_init,
	ptr_inc,
	ptr_clear,
	var_value,
	pk_assign,
	pk_paren,
	pk_add,
	pk_mul,
	pk_sub,
	pk_div,
	pk_land,
	pk_lor,
	pk_gt,
	pk_lt,
	pk_eq,
	pk_neq,
	back,
	back_a,
	array_type_rec,
	array_ok,
	call_init,
	call,
	load_param
};
enum ItemType
{VT = 0,VN = 1,Action = 2};
struct Item
{
	ItemType type;
	string name; 
	int tag;		//�����嶯������
};
struct Production
{
	Item left;			//��
	vector<Item> right;		//�Ҳ�			
};

class Grammer
{
protected:
	int T;//�ķ�����
	Item start;
	Token cur;				
	Token pre;
	Lex lex;
	Semantic semantic;
	Production productions[100]; //�ķ�����
	set<string> firstSet[50];//first��
	set<string> followSet[50];//follow��
	vector<Item> ter_withoutblack; //ȥ�����ս��
	vector<Item> vt;//�ս��
	vector<Item> vn;//���ս��
	vector<Item> action;//���嶯����
	int LL1_Map[50][50];			

public:
	Grammer() :T(0) {  }
	bool isNotTerminal(Item c);//�ж��Ƿ�Ϊ���ս��
	bool isTerminal(Item c);//�ж��Ƿ�Ϊ���ս��
	bool isAction(Item c);//�ж��Ƿ�Ϊ���ս��
	void remove();			  //��ݹ�����
	int getVTindex(Item target);//������ս�������е��±�
	int getVTindex(string target);
	int getVTindex(Token target);
	int getAction_index(Item target);	//����ڶ����������е��±�
	int getVNindex(Item target);//����ڷ��ս�������е��±�
	void setType();			//��������
	void setTag();
	void createVN_VT_ACTION();		//�����ս���ͷ��ս����
	void createFirstSet();
	void createFollowSet();
	void getFirstSet(Item target); //�õ�first����
	void getFollowSet(Item target);//�õ�follow����
	void inputAndSolve(); //����õ�first��follow
	void display(); //��ʾ
	bool createLL1_Map(); //�õ�Ԥ���
	void print_out();//���
	void manage(); //�ۺ�
	void runParserLL1();	//�﷨����
	/////////////////////////////����
	bool match(Item x);			//ƥ��
	void push_right(stack<Item>&SYN,int index);	    //����ѹջ
	string next();				   //ȡ��һ��token

};


class VM {
private:
	int ax = 0;//ax�Ĵ���
	int *bp,//Ѱַָ��
		*pc,//����ָ��
		*sp,//��ջָ��
		*out;
	int *tmp;
	int *stack;
	int  poolsize;
	void step(int i);
	int flag;
public:
	VM();
	int fetch();
	int run();
	void print(int i);
};
#endif 
