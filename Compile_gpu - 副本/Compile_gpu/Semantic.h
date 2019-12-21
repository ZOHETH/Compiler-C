#pragma once
#include <iostream>
#include <vector>
#include <stack>
#include "lex.h"
using namespace std;
extern int *asm_text;
extern int *asm_data;
extern int *main_addr;
class Semantic {
	int type;
	int *code_text;
	int *cur_data;
	Token token;
	Token prev_token;
	//Identifier *cur_id; //�洢��Ծ��id��Ϣ
	vector<Identifier> *IDENTS;
	int cur_id_index;
	int params;
	int index_of_bp;
	int pos_local;
	int expr_type;
	int not_main;
	stack<int>level;
	stack<int> adj_size;
	stack<Identifier *> the_func_id;
	stack<int>ptr_nums;
	stack<int>array_type;
	int gpu_data_dm;
	int *addr;
	int *mark_a;
	int *mark_b; //ֻ��������� if��while���� ���Բ���Ƕ��

public:
	Semantic();
	void set_ident(vector<Identifier> *i) {
		IDENTS = i;
	}
	void set_prev_token(Token t) {
		prev_token = t;
	}
	void set_cur_token(Token t) {
		token = t;
	}
	vector<void(Semantic::*)()> func;//���庯������
	void ident_rec();
	void type_rec();
	void add_ptr();
	void id_to_glo();//�����ع����֮ǰ��ֵ   //������������֮����Ҫ�Ľ�
	void parameter_rec();//��¼����
	void loc_index_rec();
	void loc_var_rec();
	void func_enter();//д�뺯����ʼ���
	void fun_end();
	void leave();
	void if_begin();
	void else_begin();
	void if_end();
	void after_while();
	void while_begin();
	void while_end();
	
	void imm_num();
	void ptr_init();
	void ptr_inc();
	void ptr_clear();
	void pk_assign();
	void pk_paren();
	void pk_add();
	void pk_mul();
	void pk_div();
	void pk_sub();
	void pk_land();
	void pk_lor();
	void pk_and();
	void pk_or();
	void pk_xor();
	void pk_gt();
	void pk_lt();
	void pk_eq();
	void pk_neq();
	void back();
	void back_a();
	void array_type_rec();
	void array_ok();
	void gpu_parameter_rec();
	void call_init();
	void load_param();
	void call();
	void var_value();
	void gpu_load();
	void push();
};