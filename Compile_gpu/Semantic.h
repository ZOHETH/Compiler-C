#pragma once
#include <iostream>
#include <vector>
#include "lex.h"
using namespace std;

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
	int *mark_a;
	int *mark_b; //ֻ��������� if��while���� ���Բ���Ƕ��

public:
	Semantic() {
		cur_id_index = -1;
		code_text = asm_text;
		/////////////
		cur_data = asm_data;
	}
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
	void leave();
	void if_begin();
	void else_begin();
	void if_end();
	void after_while();
	void while_begin();
	void while_end();
	void load_num();
	void push();
};