#include "stdafx.h"
#include <iostream>
#include <vector>
#include "lex.h"
using namespace std;
/*
class Semantic {
	int type;
	Token token;
	Token prev_token;
	Identifier cur_id; //�洢��Ծ��id��Ϣ
	vector<Identifier> IDENTS;
	int cur_id_index;
	int params;
	int index_of_bp;
	int pos_local;
	int *mark_a;
	int *mark_b; //ֻ��������� if��while���� ���Բ���Ƕ��

public:
	vector<void(Semantic::*)()> func;//���庯������
	void ident_rec() {

		//cur_id�ڴ�֮ǰ���Ѿ����� ����id����Ҫ���� ֱ����һ��
		cur_id.type = type;
		if (token == '(') {  //��ʱ��tokenΪ��һ��token
			cur_id.class_ = Fun;
			cur_id.value = int(code_text + 1);//��������������ַ,��ʱδȷ����ʽ
											  //�������������ַ����
		}
		else {
			cur_id.class_ = Glo; //ȫ�ֱ���
			cur_id.value = 0;//�������������ݵĵ�ַ
							 //�����������ݵ�ַ����
		}
		while (type >= PTR) {
			type -= PTR;
		}
		cur_id = IDENTS[cur_id_index + 1];//��һ��id
		cur_id_index++;
	}
	void type_rec() {
		type = prev_token.id;
	}
	void add_ptr() {
		type += PTR;
	}
	void id_to_glo() {  //�����ع����֮ǰ��ֵ
						//������������֮����Ҫ�Ľ�
		vector<Identifier>::iterator iter;
		for (iter = IDENTS.begin(); iter != IDENTS.end(); iter++) {
			if (iter->class_ == Loc) {
				iter->class_ = iter->Bcalss;
				iter->type = iter->Btype;
				iter->value = iter->Bvalue;

			}
		}
	}
	void parameter_rec() {  //��¼����
		cur_id.Bcalss = cur_id.class_;
		cur_id.class_ = Loc;
		cur_id.Btype = cur_id.type;
		cur_id.type = type;
		cur_id.Bvalue = cur_id.value;
		cur_id.value = params;  //
		params++;
	}
	void loc_index_rec() {
		pos_local = params + 1;
	}
	void loc_var_rec() {
		cur_id.Bcalss = cur_id.class_;
		cur_id.class_ = Loc;
		cur_id.Btype = cur_id.type;
		cur_id.type = type;
		cur_id.Bvalue = cur_id.value;
		cur_id.value = pos_local;
		pos_local++;  //�Ƿ��б�Ҫ�������������Ƿ��б�Ҫ�½��������
	}

	void func_enter() {
		//д�뺯����ʼ���
		code_text++;
		*code_text = ENT;
		code_text++;
		*code_text = pos_local - params;
	}
	void leave() {
		code_text++;
		*code_text = LEV;
	}
	void if_begin() {
		code_text++;
		*code_text = JZ;
		code_text++;
		mark_a = code_text;//��¼if��ʼλ��
	}
	void else_begin() {
		*mark_a = (int)(code_text + 3);
		code_text++;
		*code_text = JMP;
		code_text++;
		mark_a = code_text;
	}
	void if_end() {
		*mark_a = (int)(code_text + 1);
	}
	void after_while() {
		mark_a = code_text + 1;
	}
	void while_begin() {
		code_text++;
		*code_text = JZ;
		code_text++;
		mark_b = code_text;
	}
	void while_end() {
		//��ת��mark_a ���� ����ѭ������
		code_text++;
		*code_text = JMP;
		code_text++;
		*code_text = (int)mark_a;
		*mark_b = (int)(code_text + 1);
	}
	void load_num() {
		code_text++;
		*code_text = IMM;
		code_text++;

	}
	void push() {
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
	}
};

int main() {
	Semantic a;
	void (Semantic::*xx)() = a.func[0];
	(a.*xx)();
	return 0;
}
*/
