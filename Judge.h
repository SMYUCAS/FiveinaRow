#pragma once

#include<iostream>

#include "Array_data.h"

class Judge
{
public:
	Judge();
	~Judge();

	int Rule_order(int color,int row,char col);//�����ж�,colorΪ��ǰ������ɫ

	int Rule_disallowed_moves(Array_data a, int row,int col);//���ֹ���,����0��ʾδΥ�����ֹ���
	int LongConnect_judge(Array_data a,int row,int col,int count,char flag);//��������,row��col�ֱ�Ϊ��������,countΪ���ȼ���,flag�ǳ�����λѡ��
	int Double_3_judge(Array_data a,int row,int col,int color);//˫��������,�����Խ���������
	int Ban_lift_ban(Array_data a, int row, int col);//�Խ��������
	int Double_4_judge(Array_data a, int row, int col,int color);//˫�Ľ���
	int Double_2_judge(Array_data a, int row, int col, int color);//˫���ж�
	int Alive_3(Array_data a,int row,int col,char flag,int color);//�����������������ж�
	int Alive_4(Array_data a, int row, int col,char flag,int color);//���ġ����ġ������ж�,colorΪ��ǰִ����ɫ(����account����ɫ����)
	int Alive_2(Array_data a, int row, int col,char flag,int color);//������������Ƕ��ж�

	int Judgement(Array_data a,int row,int col,int color);//�ж���Ӯ
};

