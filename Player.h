#pragma once

#include<iostream>


#include "Array_data.h"

class Player
{
public:
	Player();
	~Player();

	int Mode_choose();//���˺��˻�ģʽ��ѡ��
	void People_vs_People(Array_data a);//����ģʽ
	void People_vs_Machine(Array_data a);//�˻�ģʽ

	int player1_color = 0;//���ִ����ɫ��0Ϊ�ڣ�1Ϊ��
	int player2_color = 1;

	int result = 0;//
	int order = 1;//�غ���
};

