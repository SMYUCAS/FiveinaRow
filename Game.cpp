#include "Game.h"


Game::Game()
{
}


Game::~Game()
{
}

void Game::Load_Game()
{
	Chess_data.Write_data(0,0,0,0,0);//��ʼ�����
}

void Game::show(Array_data a)
{
	display.ChessBoardShow(a);
}

void Game::Play_1(Array_data a)
{
	player.People_vs_People(a);
}

void Game::Play_2(Array_data a)
{
	player.People_vs_Machine(a);
}

void Game::Run_Game(Game g)
{
	//��ʼ������
	g.Load_Game();
	g.show(g.Chess_data);

	//ѡ�����ģʽ
	int mode = 0;
	mode = g.player.Mode_choose();
	if (mode == 1)
	{
		//����ģʽ
		g.Play_1(g.Chess_data);
	}
	else if(mode == 2)
	{
		//�˻�ģʽ
		g.Play_2(g.Chess_data);
	}
}