#include "Play_game.h"



using namespace std;

Play_game::Play_game()
{
}


Play_game::~Play_game()
{
}


void Play_game::Play_1(Array_data a,int color,const char *player_role,int order,int state)
{
	Game g;
	Show show;//��ʾ����
	Judge judge;
	int current_result = 0;//�����о����,1Ϊִ��ʤ��2Ϊִ��ʤ��0Ϊδ��ʤ��,3Ϊƽ��
	char col = ' ';
	int row = -1;

	while (1)
	{
		//ѭ��һ�����

		if (state == 0)
		{
			//��ǰ����

			if (color == 0)
			{
				//ִ��"��"
				//����
				cout << "\nRound "<< order << ": " << player_role << " (��) please input piece position (eg:A1 or a1):";//����������ʽ���룬��ĸΪ�У�����Ϊ��
				//scanf("%c%d",&col,&row);
				cin >> col >> row;
				while (cin.fail())
				{
					system("cls");//����
					a.Show_data();
					cin.clear(); //��������
					cin.sync();  //�����
					cout << "\nInput Illegal.\nPlease input piece position again:";
					cin >> col >> row;
				}


				//�����ж���ǰ�Ƿ�Ϸ�
				if (order == 1)
				{
					//��һ�غ�
					while (judge.Rule_order(color, row, col) != 1)
					{
						system("cls");//����
						a.Show_data();
						//show.gotoxy(1,22);//�����̺��һ�н�����ʾ��Ϣ��ʾ����˴Ӵ˴���ʼ�����Ϣ
						cout << "\nThe first piece must be in the position: TianYuan (H8 or h8) for Round 1.\nPlease input piece position again:";
						scanf("%c%d", &col, &row);
					}
				}
				//���뷶Χ�Ϸ��ж�,��������ߵ�ҲҪʶ��
				while (((col > 79 && col < 97) || col < 65 || col >111) || row > 15 || row < 1)
				{
					system("cls");//����
					a.Show_data();
					//show.gotoxy(1, 22);//�����̺��һ�н�����ʾ��Ϣ��ʾ����˴Ӵ˴���ʼ�����Ϣ
					//col����Ƿ�
					cout << "\nInput Illegal.\nPlease input piece position again:";
					cin >> col >> row;
					while (cin.fail())
					{
						system("cls");//����
						a.Show_data();
						cin.clear(); //��������
						cin.sync();  //�����
						cout << "\nInput Illegal.\nPlease input piece position again:";
						cin >> col >> row;
					}
				}
				//���벻�����Ѵ�������λ��
				while (1)
				{
					//�����������תΪ���ִ���,�ҷ���Array_data��������
					if (col > 96)
					{
						col = col - 96;
					}
					else if (col > 64 && col < 97)
					{
						col = col - 64;
					}
					row = 15 - row;//ͬcol����

					int temp = 0;
					temp = a.Read_data(row, col);
					if (temp == 1 || temp == 2)
					{
						system("cls");//����
						a.Show_data();
						//show.gotoxy(1, 22);//�����̺��һ�н�����ʾ��Ϣ��ʾ����˴Ӵ˴���ʼ�����Ϣ
										   //col��������λ���Ѵ�������
						cout << "\nInput position is occupied.\nPlease input piece position again:";
						cin >> col >> row;
						while (cin.fail())
						{
							system("cls");//����
							a.Show_data();
							cin.clear(); //��������
							cin.sync();  //�����
							cout << "\nInput Illegal.\nPlease input piece position again:";
							cin >> col >> row;
						}
					}
					else
						break;//δռ�е�ǰ�������ӣ�����ѭ��
				}


				//ֻ��ִ�ڷ����н����ж�
				int judge_result = 10;//-1�ǳ������֣�-2��˫�������֣�-3��˫�Ľ���
				//int judge_double_3 = 10;
				//int judge_double_4 = 10;
				judge_result = judge.Rule_disallowed_moves(a, row, col);

				//cout << judge_long;
				if (judge_result == -1)//-1�򴥷�����
				{
					current_result = 2;//����ʤ
					cout << "\nLong Ban.\n";
				}
				else if (judge_result == -2)//-2������˫��������
				{
					current_result = 2;
					cout << "\nDouble_3 Ban.\n";
				}
				else if (judge_result == -3)//-3������˫�Ľ���
				{
					current_result = 2;
					cout << "\nDouble_4 Ban.\n";
				}
				else
				{
					//���й��򶼺Ϸ�,д��
					a.Write_data(row, col, 1, color, state);//���һ������state=0��ʾ��ǰ����
					system("cls");//����
					a.Show_data();

					//ʤ���ж�(����ƽ��)
					int judge_temp = 0;
					judge_temp = judge.Judgement(a, row, col, color);
					if (judge_temp == 1)
					{
						current_result = 1;
					}
					else if (judge_temp == 2)
					{
						current_result = 3;//����
					}

					state = 1;
					//order ++;//�غ�����1
					//Play_1(a, color, player_role, order, state, row, col);
				}

			}
			else
			{
				//ִ��"��"��
				//����
				if (strcmp(player_role,"Player1") == 0)
				{
					//����ǰ��ҽ�ɫ�Ǵ�Player1��ʼ�������ΪPlayer2
					cout << "\nRound " << order << ": " << "Player2" << " (��) please input piece position (eg:A1 or a1):";//����������ʽ���룬��ĸΪ�У�����Ϊ��
				}
				else
				{
					cout << "\nRound " << order << ": " << "Player1" << " (��) please input piece position (eg:A1 or a1):";
				}
				cin >> col >> row;
				while (cin.fail())
				{
					system("cls");//����
					a.Show_data();
					cin.clear(); //��������
					cin.sync();  //�����
					cout << "\nInput Illegal.\nPlease input piece position again:";
					cin >> col >> row;
				}

				//�����ж���ǰ�Ƿ�Ϸ�
				//���뷶Χ�Ϸ��ж�
				while ((col > 79 && col < 97) || col < 65 || col >111 || row > 15 || row < 1)
				{
					system("cls");//����
					a.Show_data();
					//show.gotoxy(1, 22);//�����̺��һ�н�����ʾ��Ϣ��ʾ����˴Ӵ˴���ʼ�����Ϣ
									   //col����Ƿ�
					cout << "\nInput Illegal.\nPlease input piece position again:";
					cin >> col >> row;
					while (cin.fail())
					{
						system("cls");//����
						a.Show_data();
						cin.clear(); //��������
						cin.sync();  //�����
						cout << "\nInput Illegal.\nPlease input piece position again:";
						cin >> col >> row;
					}
				}

				//���벻�����Ѵ�������λ��
				while (1)
				{
					//�����������תΪ���ִ���,�ҷ���Array_data��������
					if (col > 96)
					{
						col = col - 96;
					}
					else if (col > 64 && col < 97)
					{
						col = col - 64;
					}
					row = 15 - row;

					int temp = 0;
					temp = a.Read_data(row, col);
					cout << temp;
					//if (temp == "��" || temp == "��" || temp == "��" || temp == "��")
					if (temp != 0)
					{
						system("cls");//����
						a.Show_data();
						//show.gotoxy(1, 22);//�����̺��һ�н�����ʾ��Ϣ��ʾ����˴Ӵ˴���ʼ�����Ϣ
										   //col��������λ���Ѵ�������
						cout << "\nInput position is occupied.\nPlease input piece position again:";
						cin >> col >> row;
						while (cin.fail())
						{
							system("cls");//����
							a.Show_data();
							cin.clear(); //��������
							cin.sync();  //�����
							cout << "\nInput Illegal.\nPlease input piece position again:";
							cin >> col >> row;
						}
					}
					else
					{
						cout << temp;
						break;//δռ�е�ǰ�������ӣ�����ѭ��
					}

				}

				//��Χ�Ϸ�,д��
				a.Write_data(row, col, 1, color, state);//���һ������state=0��ʾ��ǰ����
				system("cls");//����
				a.Show_data();
				//�ж�ʤ��
				int judge_temp = 0;
				judge_temp = judge.Judgement(a, row, col, color);
				if (judge_temp == 1)
				{
					current_result = 2;
				}
				else if (judge_temp == 2)
				{
					current_result = 3;
				}

				state = 1;
				order++;//�غ�����1
				//Play_1(a, color, player_role, order, state, row, col);
			}
		}
		else
		{
			//state =1,�ǵ�ǰ����
			a.Write_data(row, col, 1, color, state);//����������������ʽ
			state = 0;
			if (color == 0)
			{
				color = 1;//ת��Ϊ����
			}
			else
			{
				color = 0;//ת��Ϊ����
			}
		}


		if (current_result == 0)
		{
			continue;//��ǰ���δ����
		}
		else if (current_result == 1)
		{
			//ִ�����ʤ��
			cout << "\n " << player_role << " wins!\n";
			
			break;//��ǰ��ֽ���
		}
		else if (current_result == 2)
		{
			//ִ�����ʤ��
			if (strcmp(player_role,"Player1") == 0)
			{
				cout << "\n	Player2 wins!\n";
			}
			else
			{
				cout << "\n Player1 wins!\n";
			}

			break;//��ǰ��ֽ���
		}
		else
		{
			//����������������δ��ʤ��ʱ
			cout << "\n This game draws!\n";

			break;//��ǰ��ֽ���
		}
	}

	//�����Ƿ�����¿�ʼһ�̵Ķ���
	Play_again(g);
	
}

void Play_game::Play_2(Array_data a, int color, const char *player_role, int order, int state)
{
	Game g;
	Show show;//��ʾ����
	Judge judge;
	int current_result = 0;//�����о����,1Ϊִ��ʤ��2Ϊִ��ʤ��0Ϊδ��ʤ��,3Ϊƽ��
	char col = ' ';
	int row = -1;

	int account_color = -1;//���ڻ������ж�ʱ֪��ִ����ɫ������account
	if (strcmp(player_role, "Machine") == 0)
	{
		account_color = 1;//��
	}
	else
	{
		account_color = 2;//��
	}

	while (1)
	{
		//ѭ��һ�����

		if (state == 0)
		{
			//��ǰ����

			if (color == 0)
			{
				//ִ��"��"
				//����
				if (strcmp(player_role, "Machine") == 0)
				{
					//����ִ��
					if (order == 1)
					{
						row = 8;
						col = 'H';
						a.write_row_col(row,col);
					}
					else
					{
						int* temp = new int[2];

						temp = score_account(a, judge, account_color);


						row = 15 - temp[0];
						col = (char)(64 + temp[1]);

						delete[] temp;

						a.write_row_col(row, col);
					}
				}
				else
				{
					if (order > 1)
					{
						//�ǵ�һ�غ�
						cout << "\nMachine last piece position: "<< a.read_col() << a.read_row();//����ϻغϻ������µ�λ��
					}
					//���ִ��
					cout << "\nRound " << order << ": " << player_role << " (��) please input piece position (eg:A1 or a1):";//����������ʽ���룬��ĸΪ�У�����Ϊ��
					cin >> col >> row;
					while (cin.fail())
					{
						system("cls");//����
						a.Show_data();
						cin.clear(); //��������
						cin.sync();  //�����
						cout << "\nInput Illegal.\nPlease input piece position again:";
						cin >> col >> row;
					}
				}

				//�����ж���ǰ�Ƿ�Ϸ�
				if (order == 1)
				{
					//��һ�غ�
					while (judge.Rule_order(color, row, col) != 1)
					{
						system("cls");//����
						a.Show_data();
						//show.gotoxy(1,22);//�����̺��һ�н�����ʾ��Ϣ��ʾ����˴Ӵ˴���ʼ�����Ϣ
						cout << "\nThe first piece must be in the position: TianYuan (H8 or h8).\nPlease input piece position again:";
						scanf("%c%d", &col, &row);
					}
				}
				//���뷶Χ�Ϸ��ж�,��������ߵ�ҲҪʶ��
				while (((col > 79 && col < 97) || col < 65 || col >111) || row > 15 || row < 1)
				{
					system("cls");//����
					a.Show_data();
					//show.gotoxy(1, 22);//�����̺��һ�н�����ʾ��Ϣ��ʾ����˴Ӵ˴���ʼ�����Ϣ
					//col����Ƿ�
					cout << "\nInput Illegal.\nPlease input piece position again:";
					cin >> col >> row;
					while (cin.fail())
					{
						system("cls");//����
						a.Show_data();
						cin.clear(); //��������
						cin.sync();  //�����
						cout << "\nInput Illegal.\nPlease input piece position again:";
						cin >> col >> row;
					}
				}
				//���벻�����Ѵ�������λ��
				while (1)
				{
					//�����������תΪ���ִ���,�ҷ���Array_data��������
					if (col > 96)
					{
						col = col - 96;
					}
					else if (col > 64 && col < 97)
					{
						col = col - 64;
					}
					row = 15 - row;//ͬcol����

					int temp = 0;
					temp = a.Read_data(row, col);
					if (temp == 1 || temp == 2)
					{
						system("cls");//����
						a.Show_data();
						//show.gotoxy(1, 22);//�����̺��һ�н�����ʾ��Ϣ��ʾ����˴Ӵ˴���ʼ�����Ϣ
						//col��������λ���Ѵ�������
						cout << "\nInput position is occupied.\nPlease input piece position again:";
						cin >> col >> row;
						while (cin.fail())
						{
							system("cls");//����
							a.Show_data();
							cin.clear(); //��������
							cin.sync();  //�����
							cout << "\nInput Illegal.\nPlease input piece position again:";
							cin >> col >> row;
						}
					}
					else
						break;//δռ�е�ǰ�������ӣ�����ѭ��
				}


				//ֻ��ִ�ڷ����н����ж�
				int judge_result = 10;//-1�ǳ������֣�-2��˫�������֣�-3��˫�Ľ���
									  //int judge_double_3 = 10;
									  //int judge_double_4 = 10;
				judge_result = judge.Rule_disallowed_moves(a, row, col);

				//cout << judge_long;
				if (judge_result == -1)//-1�򴥷�����
				{
					current_result = 2;//����ʤ
					cout << "\nLong Ban.\n";
				}
				else if (judge_result == -2)//-2������˫��������
				{
					current_result = 2;
					cout << "\nDouble_3 Ban.\n";
				}
				else if (judge_result == -3)//-3������˫�Ľ���
				{
					current_result = 2;
					cout << "\nDouble_4 Ban.\n";
				}
				else
				{
					//���й��򶼺Ϸ�,д��
					a.Write_data(row, col, 1, color, state);//���һ������state=0��ʾ��ǰ����
					system("cls");//����
					a.Show_data();

					//ʤ���ж�(����ƽ��)
					int judge_temp = 0;
					judge_temp = judge.Judgement(a, row, col, color);
					if (judge_temp == 1)
					{
						current_result = 1;
					}
					else if (judge_temp == 2)
					{
						current_result = 3;//����
					}

					state = 1;
					//order ++;//�غ�����1
					//Play_1(a, color, player_role, order, state, row, col);
				}

			}
			else
			{
				//ִ��"��"��
				//����
				if (strcmp(player_role, "Player") == 0)
				{
					//����ǰ��ҽ�ɫ�Ǵ�Player��ʼ�������ΪMachine
					//cout << "\nRound " << order << ": " << "Machine" << " (��) please input piece position (eg:A1 or a1):";//����������ʽ���룬��ĸΪ�У�����Ϊ��
					int* temp = new int[2];

					temp = score_account(a, judge, account_color);


					row = 15 - temp[0];
					col = (char)(64 + temp[1]);

					delete[] temp;

					a.write_row_col(row, col);
				}
				else
				{
					cout << "\nMachine last piece position: " << a.read_col() << a.read_row() << "\n";//����ϻغϻ������µ�λ��
					cout << "Round " << order << ": " << "Player" << " (��) please input piece position (eg:A1 or a1):";
					cin >> col >> row;
					while (cin.fail())
					{
						system("cls");//����
						a.Show_data();
						cin.clear(); //��������
						cin.sync();  //�����
						cout << "\nInput Illegal.\nPlease input piece position again:";
						cin >> col >> row;
					}
				}

				//�����ж���ǰ�Ƿ�Ϸ�
				//���뷶Χ�Ϸ��ж�
				while ((col > 79 && col < 97) || col < 65 || col >111 || row > 15 || row < 1)
				{
					system("cls");//����
					a.Show_data();
					//show.gotoxy(1, 22);//�����̺��һ�н�����ʾ��Ϣ��ʾ����˴Ӵ˴���ʼ�����Ϣ
					//col����Ƿ�
					cout << "\nInput Illegal.\nPlease input piece position again:";
					cin >> col >> row;
					while (cin.fail())
					{
						system("cls");//����
						a.Show_data();
						cin.clear(); //��������
						cin.sync();  //�����
						cout << "\nInput Illegal.\nPlease input piece position again:";
						cin >> col >> row;
					}
				}

				//���벻�����Ѵ�������λ��
				while (1)
				{
					//�����������תΪ���ִ���,�ҷ���Array_data��������
					if (col > 96)
					{
						col = col - 96;
					}
					else if (col > 64 && col < 97)
					{
						col = col - 64;
					}
					row = 15 - row;

					int temp = 0;
					temp = a.Read_data(row, col);
					cout << temp;
					//if (temp == "��" || temp == "��" || temp == "��" || temp == "��")
					if (temp != 0)
					{
						system("cls");//����
						a.Show_data();
						//show.gotoxy(1, 22);//�����̺��һ�н�����ʾ��Ϣ��ʾ����˴Ӵ˴���ʼ�����Ϣ
						//col��������λ���Ѵ�������
						cout << "\nInput position is occupied.\nPlease input piece position again:";
						cin >> col >> row;
						while (cin.fail())
						{
							system("cls");//����
							a.Show_data();
							cin.clear(); //��������
							cin.sync();  //�����
							cout << "\nInput Illegal.\nPlease input piece position again:";
							cin >> col >> row;
						}
					}
					else
					{
						cout << temp;
						break;//δռ�е�ǰ�������ӣ�����ѭ��
					}

				}

				//��Χ�Ϸ�,д��
				a.Write_data(row, col, 1, color, state);//���һ������state=0��ʾ��ǰ����
				system("cls");//����
				a.Show_data();
				//�ж�ʤ��
				int judge_temp = 0;
				judge_temp = judge.Judgement(a, row, col, color);
				if (judge_temp == 1)
				{
					current_result = 2;
				}
				else if (judge_temp == 2)
				{
					current_result = 3;
				}

				state = 1;
				order++;//�غ�����1
						//Play_1(a, color, player_role, order, state, row, col);
			}
		}
		else
		{
			//state =1,�ǵ�ǰ����
			a.Write_data(row, col, 1, color, state);//����������������ʽ
			state = 0;
			if (color == 0)
			{
				color = 1;//ת��Ϊ����
			}
			else
			{
				color = 0;//ת��Ϊ����
			}
		}


		if (current_result == 0)
		{
			continue;//��ǰ���δ����
		}
		else if (current_result == 1)
		{
			//ִ�����ʤ��
			cout << "\n " << player_role << " wins!\n";

			break;//��ǰ��ֽ���
		}
		else if (current_result == 2)
		{
			//ִ�����ʤ��
			if (strcmp(player_role, "Player") == 0)
			{
				cout << "\n	Machine wins!\n";
			}
			else
			{
				cout << "\n Player wins!\n";
			}

			break;//��ǰ��ֽ���
		}
		else
		{
			//����������������δ��ʤ��ʱ
			cout << "\n This game draws!\n";

			break;//��ǰ��ֽ���
		}
	}

	//�����Ƿ�����¿�ʼһ�̵Ķ���
	Play_again(g);
}

void Play_game::Play_again(Game g)
{
	char answer = ' ';
	cout << "\n Do you want to play again? Y/N\n";
	cin >> answer;
	
	if (answer == 'Y' || answer == 'y')
	{
		system("cls");
		g.Run_Game(g);
	}
	else
	{
		system("exit");
	}
}

int* Play_game::score_account(Array_data a,Judge judge,int color)
{
	int x = 4;//row 0
	int y = 1;//col 1

	int i = 1;

	int op_color = -1;//�ǵ�ǰִ����ɫ
	if (color == 1)
	{
		op_color = 2;
	}
	else
	{
		op_color = 1;
	}

	//�Ʒֹ��̷�ֵ��ߵĿո�����
	int max_score_row = 0;
	int max_score_col = 1;
	int max_score = 0;

	while (x <= 14)
	{
		y = 1;//y����
		while (y <= 15)
		{
			int machine_score = 0;//�����˿�������ȡ��
			int human_score = 0;//�����˿����������ȡ��

			i = 1;//ÿһ��������³�ʼ��

			while (a.account_data[x][y] == 0 && i < 5)
			{
				//��ǰ�������Ϊ�ո�,��������ΧС��2
				//��
				if ((y - i) > 0 && (y + i) < 16)
				{
					if (a.account_data[x][y - i] != 0 || a.account_data[x][y + i] != 0)
					{
						//���Ҵ�����������
						//�ܳ�����
						if (judge.Alive_2(a, x, y, 'h', color) == 2)
						{
							machine_score += 5;
						}
						if (judge.Alive_2(a, x, y, 'h', op_color) == 2)
						{
							human_score -= 5;
						}
						//a.score[x][y] = machine_score - human_score;
						//�ܳɻ��
						if (judge.Alive_2(a, x, y, 'h', color) == 1)
						{
							machine_score += 10;
						}
						if (judge.Alive_2(a, x, y, 'h', op_color) == 1)
						{
							human_score -= 10;
						}
						//�ܳ�����
						if (judge.Alive_3(a, x, y, 'h', color) == 2)
						{
							machine_score += 50;
						}
						if (judge.Alive_3(a, x, y, 'h', op_color) == 2)
						{
							human_score -= 50;
						}
						//�ܳɻ���
						if (judge.Alive_3(a, x, y, 'h', color) == 1)
						{
							machine_score += 200;
						}
						if (judge.Alive_3(a, x, y, 'h', op_color) == 1)
						{
							human_score -= 200;
						}
						//�ܳ�����
						if (judge.Alive_4(a, x, y, 'h', color) == 2)
						{
							machine_score += 50000;
						}
						if (judge.Alive_4(a, x, y, 'h', op_color) == 2)
						{
							human_score -= 500000;
						}
						//�ܳɻ���
						if (judge.Alive_4(a, x, y, 'h', color) == 1)
						{
							machine_score += 10000000;
						}
						if (judge.Alive_4(a, x, y, 'h', op_color) == 1)
						{
							human_score -= 100000000;
						}
					}
				}
				//��
				if ((x - i) > -1 && (x + i) < 15)
				{
					if (a.account_data[x - i][y] != 0 || a.account_data[x + i][y] != 0)
					{
						//���´�����������
						//�ܳ�����
						if (judge.Alive_2(a, x, y, 's', color) == 2)
						{
							machine_score += 5;
						}
						if (judge.Alive_2(a, x, y, 's', op_color) == 2)
						{
							human_score -= 5;
						}
						//a.score[x][y] = machine_score - human_score;
						//�ܳɻ��
						if (judge.Alive_2(a, x, y, 's', color) == 1)
						{
							machine_score += 10;
						}
						if (judge.Alive_2(a, x, y, 's', op_color) == 1)
						{
							human_score -= 10;
						}
						//�ܳ�����
						if (judge.Alive_3(a, x, y, 's', color) == 2)
						{
							machine_score += 50;
						}
						if (judge.Alive_3(a, x, y, 's', op_color) == 2)
						{
							human_score -= 50;
						}
						//�ܳɻ���
						if (judge.Alive_3(a, x, y, 's', color) == 1)
						{
							machine_score += 200;
						}
						if (judge.Alive_3(a, x, y, 's', op_color) == 1)
						{
							human_score -= 200;
						}
						//�ܳ�����
						if (judge.Alive_4(a, x, y, 's', color) == 2)
						{
							machine_score += 50000;
						}
						if (judge.Alive_4(a, x, y, 's', op_color) == 2)
						{
							human_score -= 500000;
						}
						//�ܳɻ���
						if (judge.Alive_4(a, x, y, 's', color) == 1)
						{
							machine_score += 10000000;
						}
						if (judge.Alive_4(a, x, y, 's', op_color) == 1)
						{
							human_score -= 100000000;
						}
					}
				}
				//��б
				if ((x - i) > -1 && (x + i) < 15)
				{
					if (a.account_data[x - i][y + i] != 0 || a.account_data[x + i][y - i] != 0)
					{
						//�������´�����������
						//�ܳ�����
						if (judge.Alive_2(a, x, y, 'z', color) == 2)
						{
							machine_score += 5;
						}
						if (judge.Alive_2(a, x, y, 'z', op_color) == 2)
						{
							human_score -= 5;
						}
						//a.score[x][y] = machine_score - human_score;
						//�ܳɻ��
						if (judge.Alive_2(a, x, y, 'z', color) == 1)
						{
							machine_score += 10;
						}
						if (judge.Alive_2(a, x, y, 'z', op_color) == 1)
						{
							human_score -= 10;
						}
						//�ܳ�����
						if (judge.Alive_3(a, x, y, 'z', color) == 2)
						{
							machine_score += 50;
						}
						if (judge.Alive_3(a, x, y, 'z', op_color) == 2)
						{
							human_score -= 50;
						}
						//�ܳɻ���
						if (judge.Alive_3(a, x, y, 'z', color) == 1)
						{
							machine_score += 200;
						}
						if (judge.Alive_3(a, x, y, 'z', op_color) == 1)
						{
							human_score -= 200;
						}
						//�ܳ�����
						if (judge.Alive_4(a, x, y, 'z', color) == 2)
						{
							machine_score += 50000;
						}
						if (judge.Alive_4(a, x, y, 'z', op_color) == 2)
						{
							human_score -= 500000;
						}
						//�ܳɻ���
						if (judge.Alive_4(a, x, y, 'z', color) == 1)
						{
							machine_score += 10000000;
						}
						if (judge.Alive_4(a, x, y, 'z', op_color) == 1)
						{
							human_score -= 100000000;
						}
					}
				}
				//��б
				if ((x - i) > -1 && (x + i) < 15)
				{
					if (a.account_data[x - i][y - i] != 0 || a.account_data[x + i][y + i] != 0)
					{
						//���´�����������
						//�ܳ�����
						if (judge.Alive_2(a, x, y, 'f', color) == 2)
						{
							machine_score += 5;
						}
						if (judge.Alive_2(a, x, y, 'f', op_color) == 2)
						{
							human_score -= 5;
						}
						//a.score[x][y] = machine_score - human_score;
						//�ܳɻ��
						if (judge.Alive_2(a, x, y, 'f', color) == 1)
						{
							machine_score += 10;
						}
						if (judge.Alive_2(a, x, y, 'f', op_color) == 1)
						{
							human_score -= 10;
						}
						//�ܳ�����
						if (judge.Alive_3(a, x, y, 'f', color) == 2)
						{
							machine_score += 50;
						}
						if (judge.Alive_3(a, x, y, 'f', op_color) == 2)
						{
							human_score -= 50;
						}
						//�ܳɻ���
						if (judge.Alive_3(a, x, y, 'f', color) == 1)
						{
							machine_score += 200;
						}
						if (judge.Alive_3(a, x, y, 'f', op_color) == 1)
						{
							human_score -= 200;
						}
						//�ܳ�����
						if (judge.Alive_4(a, x, y, 'f', color) == 2)
						{
							machine_score += 50000;
						}
						if (judge.Alive_4(a, x, y, 'f', op_color) == 2)
						{
							human_score -= 500000;
						}
						//�ܳɻ���
						if (judge.Alive_4(a, x, y, 'f', color) == 1)
						{
							machine_score += 10000000;
						}
						if (judge.Alive_4(a, x, y, 'f', op_color) == 1)
						{
							human_score -= 100000000;
						}
					}
				}
				//�뷽���޹أ����ۺ϶෽��
				//�ܳ�˫���
				if (judge.Double_2_judge(a, x, y, color) == 1)
				{
					machine_score += 20;
				}
				if (judge.Double_2_judge(a, x, y, op_color) == 1)
				{
					human_score -= 20;
				}
				//�ܳ���������
				//��ͬ�����ϵ�������ϣ���һ��Ϊ������һ��Ϊ����
				//�ᣬ��
				if (judge.Alive_3(a, x, y, 'h', color) == 1)
				{
					if (judge.Alive_3(a, x, y, 's', color) == 2)
					{
						machine_score += 1000;
					}
					else if (judge.Alive_3(a, x, y, 'z', color) == 2)
					{
						machine_score += 1000;
					}
					else if (judge.Alive_3(a, x, y, 'f', color) == 2)
					{
						machine_score += 1000;
					}
				}
				if (judge.Alive_3(a, x, y, 'h', op_color) == 1)
				{
					if (judge.Alive_3(a, x, y, 's', op_color) == 2)
					{
						human_score -= 1000;
					}
					else if (judge.Alive_3(a, x, y, 'z', op_color) == 2)
					{
						human_score += 1000;
					}
					else if (judge.Alive_3(a, x, y, 'f', op_color) == 2)
					{
						human_score += 1000;
					}
				}
				//������
				if (judge.Alive_3(a, x, y, 's', color) == 1)
				{
					if (judge.Alive_3(a, x, y, 'h', color) == 2)
					{
						machine_score += 1000;
					}
					else if (judge.Alive_3(a, x, y, 'z', color) == 2)
					{
						machine_score += 1000;
					}
					else if (judge.Alive_3(a, x, y, 'f', color) == 2)
					{
						machine_score += 1000;
					}
				}
				if (judge.Alive_3(a, x, y, 's', op_color) == 1)
				{
					if (judge.Alive_3(a, x, y, 'h', op_color) == 2)
					{
						human_score -= 1000;
					}
					else if (judge.Alive_3(a, x, y, 'z', op_color) == 2)
					{
						human_score += 1000;
					}
					else if (judge.Alive_3(a, x, y, 'f', op_color) == 2)
					{
						human_score += 1000;
					}
				}
				//��б����
				if (judge.Alive_3(a, x, y, 'z', color) == 1)
				{
					if (judge.Alive_3(a, x, y, 's', color) == 2)
					{
						machine_score += 1000;
					}
					else if (judge.Alive_3(a, x, y, 'h', color) == 2)
					{
						machine_score += 1000;
					}
					else if (judge.Alive_3(a, x, y, 'f', color) == 2)
					{
						machine_score += 1000;
					}
				}
				if (judge.Alive_3(a, x, y, 'z', op_color) == 1)
				{
					if (judge.Alive_3(a, x, y, 's', op_color) == 2)
					{
						human_score -= 1000;
					}
					else if (judge.Alive_3(a, x, y, 'h', op_color) == 2)
					{
						human_score += 1000;
					}
					else if (judge.Alive_3(a, x, y, 'f', op_color) == 2)
					{
						human_score += 1000;
					}
				}
				//��б����
				if (judge.Alive_3(a, x, y, 'f', color) == 1)
				{
					if (judge.Alive_3(a, x, y, 's', color) == 2)
					{
						machine_score += 1000;
					}
					else if (judge.Alive_3(a, x, y, 'z', color) == 2)
					{
						machine_score += 1000;
					}
					else if (judge.Alive_3(a, x, y, 'h', color) == 2)
					{
						machine_score += 1000;
					}
				}
				if (judge.Alive_3(a, x, y, 'f', op_color) == 1)
				{
					if (judge.Alive_3(a, x, y, 's', op_color) == 2)
					{
						human_score -= 1000;
					}
					else if (judge.Alive_3(a, x, y, 'z', op_color) == 2)
					{
						human_score += 1000;
					}
					else if (judge.Alive_3(a, x, y, 'h', op_color) == 2)
					{
						human_score += 1000;
					}
				}
				//�ܳ�˫����
				if (judge.Double_3_judge(a, x, y, color) == -1)
				{
					if (color == 1)
					{
						//����ִ�ڽ���
						machine_score -= 10000000;
					}
					else
					{
						machine_score += 500000;
					}
				}
				if (judge.Double_3_judge(a, x, y, op_color) == -1)
				{
					if (op_color == 1)
					{
						//����ִ��
						human_score += 10000000;//�������ö�
					}
					else
					{
						human_score -= 500000;
					}
					
				}
				//�ܳ�˫��
				if (judge.Double_4_judge(a, x, y, color) == -1)
				{
					if (color == 1)
					{
						machine_score -= 10000000;
					}
					else
					{
						machine_score += 10000000;
					}
				}
				if (judge.Double_4_judge(a, x, y, op_color) == -1)
				{
					if (op_color == 1)
					{
						human_score += 10000000;
					}
					else
					{
						human_score -= 100000000;
					}
					
				}
				//�������֣�����ֻ�Ժ��ӽ��м���
				if (judge.LongConnect_judge(a, x, y, 1, 'h') == -1)
				{
					if (color == 1)
					{
						//����
						machine_score -= 10000000;
					}
					else
					{
						//���
						human_score += 10000000;
					}
					
				}

				//�ܳ����Ļ���
				//��ɲ�ͬ�����ϵ��������
				//����
				if (judge.Alive_4(a, x, y, 'h', color) == 2)
				{
					if (judge.Alive_3(a, x, y, 's', color) == 1)
					{
						machine_score += 1000000;
					}
					else if (judge.Alive_3(a, x, y, 'z', color) == 1)
					{
						machine_score += 1000000;
					}
					else if (judge.Alive_3(a, x, y, 'f', color) == 1)
					{
						machine_score += 1000000;
					}
				}
				if (judge.Alive_4(a, x, y, 'h', op_color) == 2)
				{
					if (judge.Alive_3(a, x, y, 's', op_color) == 1)
					{
						human_score -= 10000000;
					}
					else if (judge.Alive_3(a, x, y, 'z', op_color) == 1)
					{
						human_score -= 10000000;
					}
					else if (judge.Alive_3(a, x, y, 'f', op_color) == 1)
					{
						human_score -= 10000000;
					}
				}
				//����
				if (judge.Alive_4(a, x, y, 's', color) == 2)
				{
					if (judge.Alive_3(a, x, y, 'h', color) == 1)
					{
						machine_score += 1000000;
					}
					else if (judge.Alive_3(a, x, y, 'z', color) == 1)
					{
						machine_score += 1000000;
					}
					else if (judge.Alive_3(a, x, y, 'f', color) == 1)
					{
						machine_score += 1000000;
					}
				}
				if (judge.Alive_4(a, x, y, 's', op_color) == 2)
				{
					if (judge.Alive_3(a, x, y, 'h', op_color) == 1)
					{
						human_score -= 10000000;
					}
					else if (judge.Alive_3(a, x, y, 'z', op_color) == 1)
					{
						human_score -= 10000000;
					}
					else if (judge.Alive_3(a, x, y, 'f', op_color) == 1)
					{
						human_score -= 10000000;
					}
				}
				//��б����
				if (judge.Alive_4(a, x, y, 'z', color) == 2)
				{
					if (judge.Alive_3(a, x, y, 's', color) == 1)
					{
						machine_score += 1000000;
					}
					else if (judge.Alive_3(a, x, y, 'h', color) == 1)
					{
						machine_score += 1000000;
					}
					else if (judge.Alive_3(a, x, y, 'f', color) == 1)
					{
						machine_score += 1000000;
					}
				}
				if (judge.Alive_4(a, x, y, 'z', op_color) == 2)
				{
					if (judge.Alive_3(a, x, y, 's', op_color) == 1)
					{
						human_score -= 10000000;
					}
					else if (judge.Alive_3(a, x, y, 'h', op_color) == 1)
					{
						human_score -= 10000000;
					}
					else if (judge.Alive_3(a, x, y, 'f', op_color) == 1)
					{
						human_score -= 10000000;
					}
				}
				//��б����
				if (judge.Alive_4(a, x, y, 'f', color) == 2)
				{
					if (judge.Alive_3(a, x, y, 's', color) == 1)
					{
						machine_score += 1000000;
					}
					else if (judge.Alive_3(a, x, y, 'z', color) == 1)
					{
						machine_score += 1000000;
					}
					else if (judge.Alive_3(a, x, y, 'h', color) == 1)
					{
						machine_score += 1000000;
					}
				}
				if (judge.Alive_4(a, x, y, 'f', op_color) == 2)
				{
					if (judge.Alive_3(a, x, y, 's', op_color) == 1)
					{
						human_score -= 10000000;
					}
					else if (judge.Alive_3(a, x, y, 'z', op_color) == 1)
					{
						human_score -= 10000000;
					}
					else if (judge.Alive_3(a, x, y, 'h', op_color) == 1)
					{
						human_score -= 10000000;
					}
				}

				//�ܳ��壨ִ��Ϊ��������ϣ�,��������
				if (judge.Judgement(a, x, y, color) == 1)
				{
					machine_score += 10000000000;
				}
				if (judge.Judgement(a, x, y, op_color) == 1)
				{
					human_score -= 1000000000;
				}
				//���㲢�洢��ǰ�ո����յ÷�
				a.score[x][y] = machine_score - human_score;
				//��������ֵ����Ӧ����
				if (max_score < a.score[x][y])
				{
					max_score = a.score[x][y];
					max_score_row = x;
					max_score_col = y;
				}
				else if (max_score == a.score[x][y])
				{
					srand((int)time(0));
					int temp = random(1);
					if (temp == 0)
					{
						max_score = a.score[x][y];
						max_score_row = x;
						max_score_col = y;
					}
				}

				i += 1;

			}
			y += 1;
		}
		x += 1;
	}	

	int* temp = new int[2];
	
	temp[0] = max_score_row;
	temp[1] = max_score_col;

	return temp;
}