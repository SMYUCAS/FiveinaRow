#pragma once
#include "Array_data.h"
#include "ChessBoard.h"
#include<string.h>
#include<stdlib.h>
#include <iostream>
#include<windows.h>
class Show
{
public:
	Show();
	~Show();
	void ChessShow(int i, int j);//�������
	void ChessBoardShow(Array_data a);//������
	void gotoxy(int x, int y);
};

