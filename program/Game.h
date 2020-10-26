#pragma once

#include "ChessBoard.h"
#include "Chessman.h"
#include "Show.h"
#include "Player.h"
#include "Array_data.h"
class Game
{
public:
	Game();
	~Game();
	Array_data Chess_data;//������ݶ���
	ChessBoard Board;//���̶���
	Show display;
	Player player;//��Ҷ���

	void Load_Game();//��ʼ�������Ϸ
	void show(Array_data a);
	void Play_1(Array_data a);//����ģʽ
	void Play_2(Array_data a);//�˻�ģʽ
	void Run_Game(Game g);//��ʼ����Ϸ
};

