#pragma once

#include "Array_data.h"
#include "Judge.h"
#include "Show.h"
#include "Player.h"
#include "Game.h"

#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<time.h>

#define random(x)(rand()%2)//����0��1�������

class Play_game
{
public:
	Play_game();
	~Play_game();

	void Play_1(Array_data a,int color,const char *player_role,int order,int state);//���˶�ս����,color��ִ���ж�,role����ҽ�ɫ,order�ǻغ���,state�ǵ�ǰ״̬,x��y����һ�����ӵ�λ��
	void Play_2(Array_data a,int color,const char *player_role,int order,int state);//�˻���ս����

	int*  score_account(Array_data a,Judge judge,int color);//�����Ʒִ���,color�����жϻ�����ִ����ɫ

	void Play_again(Game g);//����ʤ���Ƿ����¿�ʼһ����Ϸ
};

