#include "stdafx.h"
#include <iostream>
#include <vector>
#include "lex.h"
#include "Semantic.h"
using namespace std;

void Semantic::ident_rec() {
	//CUR_ID = &(*IDENTS)[CUR_ID_index + 1];//��һ��id
	//CUR_ID_index++;
	//CUR_ID�ڴ�֮ǰ���Ѿ����� ����id����Ҫ���� ֱ����һ��
	CUR_ID->type = type;
	if (token == '(') {  //��ʱ��tokenΪ��һ��token
		CUR_ID->class_ = Fun;
		CUR_ID->value = int(code_text + 1);		//��������������ַ,��ʱδȷ����ʽ
												//�������������ַ����
	}
	else {
		CUR_ID->class_ = Glo; //ȫ�ֱ���
		CUR_ID->value = (int)cur_data;		//�������������ݵĵ�ַ
											//�����������ݵ�ַ����
		cur_data++;
	}
	while (type >= PTR) {
		type -= PTR;
	}
}
void Semantic::type_rec() {							//�������ͣ���Type->char <update_type>|void <update_type>|int <update_type> ��ʶ�����ͺ����ͱ�Ϊpre_token
	if (prev_token.id == Int) {
		type = INT;
	}
	else if (prev_token.id == Char) {
		type = CHAR;
	}
	else if (prev_token.id == Void) {
		type = VOID;
	}
}
void Semantic::add_ptr() {							//���ָ��
	type += PTR;
}
void Semantic::id_to_glo() {  //�����ع����֮ǰ��ֵ
							  //������������֮����Ҫ�Ľ�
	vector<Identifier>::iterator iter;
	for (iter = IDENTS->begin(); iter != IDENTS->end(); iter++) {
		if (iter->class_ == Loc) {
			/*iter->class_ = iter->Bcalss;
			iter->type = iter->Btype;
			iter->value = iter->Bvalue;*/
			;
		}
	}
}
void Semantic::parameter_rec() {  //��¼����
								  //CUR_ID = &(*IDENTS)[CUR_ID_index + 1];//��һ��id
								  //CUR_ID_index++;
	CUR_ID->Bcalss = CUR_ID->class_;
	CUR_ID->class_ = Loc;
	CUR_ID->Btype = CUR_ID->type;
	CUR_ID->type = type;
	CUR_ID->Bvalue = CUR_ID->value;
	CUR_ID->value = params;  //
	params++;
}
void Semantic::loc_index_rec() {
	pos_local = params + 1;
}
void Semantic::loc_var_rec() {
	//CUR_ID = &(*IDENTS)[CUR_ID_index + 1];//��һ��id
	//CUR_ID_index++;
	CUR_ID->Bcalss = CUR_ID->class_;
	CUR_ID->class_ = Loc;
	CUR_ID->Btype = CUR_ID->type;
	CUR_ID->type = type;
	CUR_ID->Bvalue = CUR_ID->value;
	CUR_ID->value = pos_local;
	pos_local++;  //�Ƿ��б�Ҫ�������������Ƿ��б�Ҫ�½��������
}
void Semantic::func_enter() {
	//д�뺯����ʼ���
	code_text++;
	*code_text = ENT;
	code_text++;
	*code_text = pos_local - params;
}
void Semantic::leave() {
	code_text++;
	*code_text = LEV;
}
void Semantic::if_begin() {
	code_text++;
	*code_text = JZ;
	code_text++;
	mark_b = code_text;//��¼if��ʼλ��
}
void Semantic::else_begin() {
	*mark_b = (int)(code_text + 3);
	code_text++;
	*code_text = JMP;
	code_text++;
	mark_b = code_text;
}
void Semantic::if_end() {
	*mark_b = (int)(code_text + 1);
}
void Semantic::after_while() {
	mark_a = code_text + 1;
}
void Semantic::while_begin() {
	code_text++;
	*code_text = JZ;
	code_text++;
	mark_b = code_text;
}
void Semantic::while_end() {
	//��ת��mark_a ���� ����ѭ������
	code_text++;
	*code_text = JMP;
	code_text++;
	*code_text = (int)mark_a;
	*mark_b = (int)(code_text + 1);
}
void Semantic::imm_num() {
	code_text++;
	*code_text = IMM;
	code_text++;
	*code_text = prev_token.value;
	expr_type = INT;
}
void Semantic::pk_assign() {
	if (prev_token.id >= level.top()) {
		if (*code_text == LC || *code_text == LI) {
			*code_text = PUSH; // save the lvalue's pointer
		}
		else {
			throw "��ֵ����";
		}
		level.push(Assign);
	}
}

void Semantic::pk_add() {
	code_text++;
	*code_text = PUSH;
	level.push(Add);
}
void Semantic::pk_mul() {
	code_text++;
	*code_text = PUSH;
	level.push(Mul);
}
void Semantic::back() {
	while (!level.empty()&&level.top()>token.id) {
		int temp = level.top();
		level.pop();
		if (temp == Assign) {
			//expr_type
			code_text++;
			*code_text = (expr_type == CHAR) ? SC : SI;
		}
		else if (temp == Add) {
			code_text++;
			*code_text = ADD;
		}
		else if (temp == Mul) {
			code_text++;
			*code_text = Mul;
		}
	}
}

void Semantic::gpu_parameter_rec() {
	CUR_ID->Bcalss = CUR_ID->class_;
	CUR_ID->class_ = Dev;
	CUR_ID->Btype = CUR_ID->type;
	CUR_ID->type = type;
	CUR_ID->Bvalue = CUR_ID->value;
	CUR_ID->value = params;  //
	params++;
}

void Semantic::call_init() {
	adj_size = 0;
	the_func_id = CUR_ID;
}
void Semantic::load_param() {
	if (the_func_id->class_ == Gpu) {

	}
	code_text++;
	*code_text = PUSH;
	adj_size++;
}
void Semantic::var_value() {
	if (CUR_ID->type == Num) {
		code_text++;
		*code_text = IMM;
		code_text++;
		*code_text = CUR_ID->value;
	}
	else if (CUR_ID->class_ == Loc) {
		code_text++;
		*code_text = LEA;
		code_text++;
		*code_text = CUR_ID->value - pos_local;
	}
	else if (CUR_ID->class_ == Glo) {
		code_text++;
		*code_text = IMM;
		code_text++;
		*code_text = CUR_ID->value;
	}
}
void Semantic::call() {
	if (the_func_id->class_ == Sys) {
		code_text++;
		*code_text = the_func_id->value;
	}
	else if (the_func_id->class_ == Fun) {
		code_text++;
		*code_text = CALL;
		code_text++;
		*code_text = the_func_id->value;
	}
	else if (the_func_id->class_ == Gpu) {
		
	}
	else {
		throw "�Ƿ�����";
	}
	if(adj_size>0){
		code_text++;
		*code_text = ADJ;
		code_text++;
		*code_text = adj_size;
	}
	expr_type = the_func_id->type;//??????
}

void Semantic::gpu_load() {

}


void Semantic::push() {
	func.push_back(&Semantic::add_ptr);					//0
	func.push_back(&Semantic::ident_rec);				//1
	func.push_back(&Semantic::id_to_glo);				//2
	func.push_back(&Semantic::parameter_rec);			//3
	func.push_back(&Semantic::loc_var_rec);				//4
	func.push_back(&Semantic::loc_index_rec);			//5
	func.push_back(&Semantic::type_rec);				//6
	func.push_back(&Semantic::func_enter);				//7
	func.push_back(&Semantic::leave);					//8
	func.push_back(&Semantic::if_begin);				//9
	func.push_back(&Semantic::else_begin);				//10
	func.push_back(&Semantic::if_end);					//11
	func.push_back(&Semantic::after_while);				//12
	func.push_back(&Semantic::while_begin);				//13
	func.push_back(&Semantic::while_end);				//14
	func.push_back(&Semantic::imm_num);
	func.push_back(&Semantic::var_value);
	func.push_back(&Semantic::pk_assign);
	func.push_back(&Semantic::pk_add);
	func.push_back(&Semantic::pk_mul);
	func.push_back(&Semantic::back);
}


