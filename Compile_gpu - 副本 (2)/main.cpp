// main.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include"Grammer.h"

int main()
{
	asm_text = (int *)malloc(1000 * sizeof(int));
	asm_data = (int *)malloc(1000 * sizeof(int));
	/*TableStack res;
	res.manage();*/
	Grammer g;
	//g.inputAndSolve();
	g.manage();
	/*int a;
	cin >> a;//�ȴ��س��˳�
	/*
	ifstream in("Input.txt");			//�Ķ������Զ���ʵ��
	string s;
	getline(in, s);
	cout << s.length();*/

	/*Lex test("int a;");
	cout << endl;
	test.next_token();
	cout << endl;
	test.next_token();
	cout << endl;
	test.next_token();
	cout << endl;
	*/
	cout << "\n+++++++++++++++++++++++++++++++++++++\n" << endl;
	for (int i = 0; i < 50; i++) {
		cout << asm_text[i] << endl;
	}
	return 0;
}

