#include "Judge.h"



Judge::Judge()
{
}


Judge::~Judge()
{
}


int Judge::Rule_order(int color,int row,char col)
{
	//����˳���ж�
	int order_judge = 0;
	//�ж��Ƿ�Ϊ��ֵ�һ��
	//��һ�غ�
	//�ж��Ƿ��Ǻڷ������һ��
	if (color == 0)
	{
		//��ǰ����Ϊ����
		//�ж���һ���Ƿ�������Ԫλ��,h8
		if (row == 8 && (col == 'H' || col == 'h'))
		{
			order_judge = 1;//�Ϲ�
		}
		else
			return order_judge;
	}
	else
		return order_judge;

	return order_judge;
}

int Judge::Rule_disallowed_moves(Array_data a,int row,int col)
{
	//int count = 1;//int h, s, z, f = 1;//������б��б�ĸ�����,�Ե�ǰ��Ϊ���㣬���м���1
	int long_result = 0;//��������
	int double_3_result = 0;//˫��3����
	int double_4_result = 0;//˫�Ľ���
	
	//˫��������
	double_3_result = Double_3_judge(a, row, col,1);
	if (double_3_result != 0)
	{
		double_3_result  = -2;
		return double_3_result;
	}
	//���Ľ���
	double_4_result = Double_4_judge(a, row, col,1);
	if (double_4_result != 0)
	{
		double_4_result = -3;
		return double_4_result;
	}
	//��������
	/**����*/
	long_result = LongConnect_judge(a,row,col,1,'h');
	if (long_result != 0)
	{
		return long_result;//-1
	}
	/**����*/
	long_result = LongConnect_judge(a, row, col, 1, 's');
	if (long_result != 0)
	{
		return long_result;
	}
	/**��б ��/��*/
	long_result = LongConnect_judge(a, row, col, 1, 'z');
	if (long_result != 0)
	{
		return long_result;
	}
	/**��б ��\��*/
	long_result = LongConnect_judge(a, row, col, 1, 'f');
	if (long_result != 0)
	{
		return long_result;
	}

	//���ɷ��ض��ֵ
	//return long_result,double_3_result,double_4_result;//�޴�������,0
	return 0;
}

int Judge::LongConnect_judge(Array_data a,int row,int col,int count,char flag)
{
	int i = 1;
	int result = 0;

	//���ݲ��Է�λ��������
	if (flag == 'h')
	{
		//Ϊ�˱���count���ظ����㣬��û�ҳ�ԭ��֮ǰʹ�������ʽ�����ٴγ�ʼ��
		count = 1;
		//������
		while ((col - i) > 0 && a.Read_data(row, col - i) == 1)
		{
			count += 1;
			if (count > 5)
			{
				result = -1;
				break;
			}
			i += 1;//��������
		}
		if (result != 0)
		{
			return result;
		}
		i = 1;
		//���Ҽ��
		while ((col + i) < 16 && a.Read_data(row, col + i) == 1)
		{
			count += 1;
			if (count > 5)
			{
				result = -1;
				break;
			}
			i += 1;
		}
		if (result != 0)
		{
			return result;
		}
	}
	else if (flag == 's')
	{
		count = 1;
		//���ϼ��
		while ((row - i) > -1 && a.Read_data(row - i, col) == 1)
		{
			count += 1;
			if (count > 5)
			{
				result = -1;
				break;
			}
			i += 1;//��������
		}
		if (result != 0)
		{
			return result;
		}
		i = 1;
		//���¼��
		while ((row + i) < 15 && a.Read_data(row + i, col) == 1)
		{
			count += 1;
			if (count > 5)
			{
				result = -1;
				break;
			}
			i += 1;
		}
		if (result != 0)
		{
			return result;
		}
	}
	else if (flag == 'z')
	{
		count = 1;
		//�����¼��
		while ((row + i) < 15 && a.Read_data(row + i, col - i) == 1)
		{
			count += 1;
			if (count > 5)
			{
				result = -1;
				break;
			}
			i += 1;//����������
		}
		if (result != 0)
		{
			return result;
		}
		i = 1;
		//�����ϼ��
		while ((row - i) > -1 && a.Read_data(row - i, col + i) == 1)
		{
			count += 1;
			if (count > 5)
			{
				result = -1;
				break;
			}
			i += 1;
		}
		if (result != 0)
		{
			return result;
		}
	}
	else
	{
		//�����ϼ��
		while ((row - i) > -1 && a.Read_data(row - i, col - i) == 1)
		{
			count += 1;
			if (count > 5)
			{
				result = -1;
				break;
			}
			i += 1;//����������
		}
		if (result != 0)
		{
			return result;
		}
		i = 1;
		//�����¼��
		while ((row + i) < 15 && a.Read_data(row + i, col + i) == 1)
		{
			count += 1;
			if (count > 5)
			{
				result = -1;
				break;
			}
			i += 1;
		}
		if (result != 0)
		{
			return result;
		}
	}

	return result;//δ��������,0
}

int Judge::Alive_3(Array_data a, int row, int col,char flag,int color)
{
	//����0�Ƿ�����1�ǻ�����2Ϊ����
	int result = 0;
	int count = 1;//���ӳ���
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

	if (flag == 'h')
	{
		//ֱ����
		//������
		while ((col - i) > 0 && a.Read_data(row, col - i) == color)
		{
			count += 1;
			if (count == 3)
			{
				//��ǰ������account�����м�¼,��account�˵����ݱ�Ϊ��˽������
				a.account_data[row][col] = color;

				if ((col - i - 1) > 0 && (col + 1) < 16)
				{
					//����������������жϻ������
					if ((Alive_4(a, row, col + 1, flag,color) == 1) || (Alive_4(a, row, col - i - 1, flag,color) == 1))
					{
						//����
						result = 1;
					}
					else if ((Alive_4(a, row, col + 1, flag,color) == 0) && (Alive_4(a, row, col - i - 1, flag,color) == 0))
					{
						//����
						result = 0;
					}
					else
					{
						//����
						result = 2;
					}
				}
				else
				{
					//�����ӵ�ĳһ�಻���ڿո񣬴������̱�Ե
					if ((col == 15 && Alive_4(a, row, col - i - 1, flag,color) == 0) || ((col - i) == 1 && Alive_4(a, row, col + 1, flag,color) == 0))
					{
						//��ǰ�����������һ�У����������һ�ӵ����Ϊ����
						//��ǰ�����ӵ������һ���ڵ�һ�У���ǰ�ӵ��ұ�Ϊ����
						//����
						result = 0;
					}
					else
					{
						//����
						result = 2;
					}

				}

				//�����жϽ������ָ�account������
				a.account_data[row][col] = 0;

				break;
			}
			i += 1;//��������
		}
		if (result != 0)
		{
			return result;
		}
		i = 1;
		//���Ҽ��
		while ((col + i) < 16 && a.Read_data(row, col + i) == color)
		{
			count += 1;
			if (count == 3)
			{
				a.account_data[row][col] = color;
				if ((col - 1) > 0 && (col + i + 1) < 16)
				{
					if (Alive_4(a, row, col + i + 1, flag,color) == 1 || Alive_4(a, row, col - 1, flag,color) == 1)
					{
						result = 1;//����
					}
					else if (Alive_4(a, row, col + i + 1, flag,color) == 0 && Alive_4(a, row, col - 1, flag,color) == 0)
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				else
				{
					if ((col == 1 && Alive_4(a, row, col + i + 1, flag,color) == 0) || ((col + i) == 15 && Alive_4(a, row, col - 1, flag,color) == 0))
					{
						//��ǰ���ڵ�һ�У����ӵ����ұ�һ�ӵ��ұ�Ϊ����
						//��ǰ����������ұ�һ�������һ�У���ǰ�ӵ����һ��Ϊ����
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				a.account_data[row][col] = 0;

				break;
			}
			i += 1;
		}

		//��������
		int left_neighbor = -1;//��ǰ���ӵ����ڵ�
		int right_neighbor = -1;//��ǰ���ӵ����ڵ�

		if (col - 3 > 0)
		{
			//���ڵ����
			left_neighbor = a.Read_data(row, col - 1);
			if (left_neighbor == 0)
			{
				//���ڵ�Ϊ��
				if ((a.Read_data(row, col - 2) == color) && (a.Read_data(row, col - 3) == color))
				{
					a.account_data[row][col] = color;
					//��2��3Ϊ���壬����������������
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row, col - 1, flag, color);
					if (if_alive_4 == 1)
					{
						//���ı�����ո�
						result = 1;//����
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;
				}
				else if ((col + 1 < 16) && (a.Read_data(row, col - 2) == color) && (a.Read_data(row, col + 1) == color))
				{
					a.account_data[row][col] = color;
					//��2��1Ϊ����
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row, col - 1, flag, color);
					if (if_alive_4 == 1)
					{
						//���ı�����ո�
						result = 1;//����
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;
				}
			}
			else if (left_neighbor == color)
			{
				//���ڵ�Ϊ����
				if ((a.Read_data(row, col - 2) == 0) && (a.Read_data(row, col - 3) == color))
				{
					a.account_data[row][col] = color;
					//��2Ϊ������Ϊ���壬����������
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row, col - 2, flag, color);
					if (if_alive_4 == 1)
					{
						//���ı�����ո�
						result = 1;//����
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;
				}
			}
		}
		if (result != 0)
		{
			return result;
		}
		if (col + 3 < 16)
		{
			//���ڵ����
			right_neighbor = a.Read_data(row, col + 1);
			if (right_neighbor == 0)
			{
				//���ڵ�Ϊ��
				if ((a.Read_data(row, col + 2) == color) && (a.Read_data(row, col + 3) == color))
				{
					a.account_data[row][col] = color;
					//��2��3Ϊ���壬����������������
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row, col + 1, flag, color);
					if (if_alive_4 == 1)
					{
						//���ı�����ո�
						result = 1;//����
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;
				}
				else if ((col - 1>0) && (a.Read_data(row, col + 2) == color) && (a.Read_data(row, col - 1) == color))
				{
					a.account_data[row][col] = color;
					//��2��1Ϊ���壬����������������
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row, col + 1, flag, color);
					if (if_alive_4 == 1)
					{
						//���ı�����ո�
						result = 1;//����
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;
				}
			}
			else if (right_neighbor == color)
			{
				//���ڵ�Ϊ����
				if ((a.Read_data(row, col + 2) == 0) && (a.Read_data(row, col + 3) == color))
				{
					a.account_data[row][col] = color;
					//��2Ϊ������Ϊ���壬����������
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row, col + 2, flag, color);
					if (if_alive_4 == 1)
					{
						//���ı�����ո�
						result = 1;//����
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;
				}
			}
		}
		if (result != 0)
		{
			return result;
		}
		if (col - 2 == 1)
		{
			//��Ե����ֻ�������ͷ���
			if (a.Read_data(row, col - 1) == 0 && a.Read_data(row, col - 2) == color && a.Read_data(row, col + 1) == color)
			{
				a.account_data[row][col] = color;
				int if_alive_4 = 0;
				if_alive_4 = Alive_4(a, row, col - 1, flag, color);
				if (if_alive_4 == 2)
				{
					result = 2;//����
				}
				else
				{
					result = 0;
				}
				a.account_data[row][col] = 0;
			}
			else
			{
				result = 0;
			}
		}
		if (result != 0)
		{
			return result;
		}
		if (col + 2 == 15)
		{
			if (a.Read_data(row, col + 1) == 0 && a.Read_data(row, col + 2) == color && a.Read_data(row, col - 1) == color)
			{
				a.account_data[row][col] = color;
				int if_alive_4 = 0;
				if_alive_4 = Alive_4(a, row, col + 1, flag, color);
				if (if_alive_4 == 2)
				{
					result = 2;//����
				}
				else
				{
					result = 0;
				}
				a.account_data[row][col] = 0;
			}
			else
			{
				result = 0;
			}
		}
		
		//���������������
		if ((a.Read_data(row, col - 1) == 0 && a.Read_data(row, col - 2) == color && a.Read_data(row, col - 3) == 0 && a.Read_data(row, col - 4) == color) || (a.Read_data(row,col-1)==0 && a.Read_data(row,col-2) == 0 && a.Read_data(row,col-3) == color && a.Read_data(row,col-4) == color) || (a.Read_data(row, col - 1) == 0 && a.Read_data(row, col - 2) == 0 && a.Read_data(row, col - 3) == color && a.Read_data(row, col - 4) == color && a.Read_data(row,col-5) == op_color))
		{
			//left
			result = 2;
		}
		else if ((a.Read_data(row, col + 1) == 0 && a.Read_data(row, col + 2) == color && a.Read_data(row, col + 3) == 0 && a.Read_data(row, col + 4) == color) || (a.Read_data(row, col + 1) == 0 && a.Read_data(row, col + 2) == 0 && a.Read_data(row, col + 3) == color && a.Read_data(row, col + 4) == color) || (a.Read_data(row, col + 1) == 0 && a.Read_data(row, col + 2) == 0 && a.Read_data(row, col + 3) == color && a.Read_data(row, col + 4) == color && a.Read_data(row, col + 5) == op_color))
		{
			result = 2;
		}


		return result;

	}


	if (flag == 's')
	{
		//��
		//���ϼ��
		while ((row - i) > -1 && a.Read_data(row - i, col) == color)
		{
			count += 1;
			if (count == 3)
			{
				a.account_data[row][col] = color;
				if ((row + 1) < 15 && (row - i - 1) > -1)
				{
					if (Alive_4(a, row + 1, col, flag,color) == 1 || Alive_4(a, row - i - 1, col, flag,color) == 1)
					{
						result = 1;
					}
					else if (Alive_4(a, row + 1, col, flag,color) == 0 && Alive_4(a, row - i - 1, col, flag,color) == 0)
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				else
				{
					if ((row == 14 && Alive_4(a, row - i - 1, col, flag,color) == 0) || ((row - i) == 0 && Alive_4(a, row + 1, col, flag,color) == 0))
					{
						//��ǰ�������һ�У����ӵ����ϱ�һ�ӵ���һ����Ϊ����
						//��ǰ�ӵ����ӵ�������һ���ڵ�һ�У���ǰ�ӵ�����һ����Ϊ����
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				a.account_data[row][col] = 0;

				break;
			}
			i += 1;//��������
		}
		if (result != 0)
		{
			return result;
		}
		i = 1;
		//���¼��
		while ((row + i) < 15 && a.Read_data(row + i, col) == color)
		{
			count += 1;
			if (count == 3)
			{
				a.account_data[row][col] = color;
				if ((row - 1) > -1 && (row + i + 1) < 15)
				{
					if (Alive_4(a, row - 1, col, flag,color) == 1 || Alive_4(a, row + i + 1, col, flag,color) == 1)
					{
						result = 1;
					}
					else if (Alive_4(a, row - 1, col, flag,color) == 0 && Alive_4(a, row + i + 1, col, flag,color) == 0)
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				else
				{
					if ((row == 0 && Alive_4(a, row + i + 1, col, flag,color) == 0) || ((row + i) == 14 && Alive_4(a, row - 1, col, flag,color) == 0))
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				a.account_data[row][col] = 0;
				break;
			}
			i += 1;
		}

		//��������
		int up_neighbor = -1;
		int down_neighbor = -1;

		if (row - 3 > -1)
		{
			//���ڵ����
			up_neighbor = a.Read_data(row - 1, col);
			if (up_neighbor == 0)
			{
				//���ڵ�Ϊ��
				if ((a.Read_data(row - 2, col) == color) && (a.Read_data(row - 3, col) == color))
				{
					a.account_data[row][col] = color;
					//up2up3Ϊ���壬����������������
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row - 1, col, flag, color);
					if (if_alive_4 == 1)
					{
						//���ı�����ո�
						result = 1;//����
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;
				}
				else if ((row + 1 < 15) && (a.Read_data(row - 2, col) == color) && (a.Read_data(row + 1, col) == color))
				{
					a.account_data[row][col] = color;
					//up2down1Ϊ����
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row - 1, col, flag, color);
					if (if_alive_4 == 1)
					{
						//���ı�����ո�
						result = 1;//����
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;
				}
			}
			else if (up_neighbor == 1)
			{
				//up�ڵ�Ϊ����
				if ((a.Read_data(row - 2, col) == 0) && (a.Read_data(row - 3, col) == color))
				{
					a.account_data[row][col] = color;
					//up2Ϊ��down��Ϊ���壬����������
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row - 2, col, flag, color);
					if (if_alive_4 == 1)
					{
						//���ı�����ո�
						result = 1;//����
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;
				}
			}
		}
		if (result != 0)
		{
			return result;
		}
		if (row + 3 < 15)
		{
			//down�ڵ����
			down_neighbor = a.Read_data(row + 1, col);
			if (down_neighbor == 0)
			{
				//down�ڵ�Ϊ��
				if ((a.Read_data(row + 2, col) == color) && (a.Read_data(row + 3, col) == color))
				{
					a.account_data[row][col] = color;
					//down2down3Ϊ���壬����������������
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row + 1, col, flag, color);
					if (if_alive_4 == 1)
					{
						//���ı�����ո�
						result = 1;//����
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;
				}
				else if ((row - 1>-1) && (a.Read_data(row + 2, col) == color) && (a.Read_data(row - 1, col) == color))
				{
					a.account_data[row][col] = color;
					//down2up1Ϊ���壬����������������
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row + 1, col, flag, color);
					if (if_alive_4 == 1)
					{
						//���ı�����ո�
						result = 1;//����
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;
				}
			}
			else if (down_neighbor == 1)
			{
				//���ڵ�Ϊ����
				if ((a.Read_data(row + 2, col) == 0) && (a.Read_data(row + 3, col) == color))
				{
					a.account_data[row][col] = color;
					//��2Ϊ������Ϊ���壬����������
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row + 2, col, flag, color);
					if (if_alive_4 == 1)
					{
						//���ı�����ո�
						result = 1;//����
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;
				}
			}
		}
		if (result != 0)
		{
			return result;
		}
		if (row - 2 == 0)
		{
			//��Ե����ֻ�������ͷ���
			if (a.Read_data(row - 1, col) == 0 && a.Read_data(row - 2, col) == color && a.Read_data(row + 1, col) == color)
			{
				a.account_data[row][col] = color;
				int if_alive_4 = 0;
				if_alive_4 = Alive_4(a, row - 1, col, flag, color);
				if (if_alive_4 == 2)
				{
					result = 2;//����
				}
				else
				{
					result = 0;
				}
				a.account_data[row][col] = 0;
			}
			else
			{
				result = 0;
			}
		}
		if (result != 0)
		{
			return result;
		}
		if (row + 2 == 14)
		{
			if (a.Read_data(row + 1, col) == 0 && a.Read_data(row + 2, col) == color && a.Read_data(row - 1, col) == color)
			{
				a.account_data[row][col] = color;
				int if_alive_4 = 0;
				if_alive_4 = Alive_4(a, row + 1, col, flag, color);
				if (if_alive_4 == 2)
				{
					result = 2;//����
				}
				else
				{
					result = 0;
				}
				a.account_data[row][col] = 0;
			}
			else
			{
				result = 0;
			}
		}

		//���������������
		if ((a.Read_data(row - 1, col) == 0 && a.Read_data(row - 2, col) == color && a.Read_data(row - 3,col) == 0 && a.Read_data(row - 4, col) == color) || (a.Read_data(row - 1, col) == 0 && a.Read_data(row - 2, col) == 0 && a.Read_data(row - 3, col) == color && a.Read_data(row - 4, col) == color) || (a.Read_data(row - 1, col) == 0 && a.Read_data(row - 2, col) == 0 && a.Read_data(row - 3, col) == color && a.Read_data(row - 4, col) == color && a.Read_data(row - 5, col) == op_color))
		{
			result = 2;
		}
		else if ((a.Read_data(row + 1, col) == 0 && a.Read_data(row + 2, col) == color && a.Read_data(row + 3, col) == 0 && a.Read_data(row + 4, col) == color) || (a.Read_data(row + 1, col) == 0 && a.Read_data(row + 2, col) == 0 && a.Read_data(row + 3, col) == color && a.Read_data(row + 4, col) == color) || (a.Read_data(row + 1, col) == 0 && a.Read_data(row + 2, col) == 0 && a.Read_data(row + 3, col) == color && a.Read_data(row + 4, col) == color && a.Read_data(row + 5, col) == op_color))
		{
			result = 2;
		}

		return result;
	}


	if (flag == 'z')
	{
		//��б
		//�����¼��
		while ((row + i) < 15 && a.Read_data(row + i, col - i) == color)
		{
			count += 1;
			if (count == 3)
			{
				a.account_data[row][col] = color;
				if ((row - 1) > -1 && (col + 1) < 16 && (row + i + 1) < 15 && (col - i - 1) > 0)
				{
					if (Alive_4(a, row - 1, col + 1, flag,color) == 1 || Alive_4(a, row + i + 1, col - i - 1, flag,color) == 1)
					{
						result = 1;
					}
					else if (Alive_4(a, row - 1, col + 1, flag,color) == 0 && Alive_4(a, row + i + 1, col - i - 1, flag,color) == 0)
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				else
				{
					if ((row == 0 && col == 15 && Alive_4(a, row + i + 1, col - i - 1, flag,color) == 0) || ((row + i) == 14 && (col - i) == 1 && Alive_4(a, row - 1, col + 1, flag,color) == 0))
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				a.account_data[row][col] = 0;
				break;
			}
			i += 1;//����������
		}
		if (result != 0)
		{
			return result;
		}
		i = 1;
		//�����ϼ��
		while ((row - i) > -1 && a.Read_data(row - i, col + i) == color)
		{
			count += 1;
			if (count == 3)
			{
				a.account_data[row][col] = color;
				if ((row + 1) < 15 && (col - 1) > 0 && (row - i - 1) > -1 && (col + i + 1) < 16)
				{
					if (Alive_4(a, row + 1, col - 1, flag,color) == 1 || Alive_4(a, row - i - 1, col + i + 1, flag,color) == 1)
					{
						result = 1;
					}
					else if (Alive_4(a, row + 1, col - 1, flag,color) == 0 && Alive_4(a, row - i - 1, col + i + 1, flag,color) == 0)
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				else
				{
					if ((row == 14 && col == 1 && Alive_4(a, row - i - 1, col + i + 1, flag,color) == 0) || ((row - i) == 0 && (col + i) == 15 && Alive_4(a, row + 1, col - 1, flag,color) == 0))
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				a.account_data[row][col] = 0;
				break;
			}
			i += 1;
		}

		//��������
		int up_right_neighbor = -1;
		//��������
		int down_left_neighbor = -1;

		if (row - 3 > -1)
		{
			//�����ڵ����
			up_right_neighbor = a.Read_data(row - 1, col + 1);
			if (up_right_neighbor == 0)
			{
				//�����ڵ�Ϊ��
				if ((a.Read_data(row - 2, col + 2) == color) && (a.Read_data(row - 3, col + 3) == color))
				{
					a.account_data[row][col] = color;
					//up2up3Ϊ���壬����������������
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row - 1, col + 1, flag, color);
					if (if_alive_4 == 1)
					{
						//���ı�����ո�
						result = 1;//����
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;
				}
				else if ((row + 1 < 15) && (a.Read_data(row - 2, col + 2) == color) && (a.Read_data(row + 1, col - 1) == color))
				{
					a.account_data[row][col] = color;
					//up2down1Ϊ����
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row - 1, col + 1, flag, color);
					if (if_alive_4 == 1)
					{
						//���ı�����ո�
						result = 1;//����
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;
				}
			}
			else if (up_right_neighbor == 1)
			{
				//up_right�ڵ�Ϊ����
				if ((a.Read_data(row - 2, col + 2) == 0) && (a.Read_data(row - 3, col + 3) == color))
				{
					a.account_data[row][col] = color;
					//up2Ϊ��down��Ϊ���壬����������
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row - 2, col + 2, flag, color);
					if (if_alive_4 == 1)
					{
						//���ı�����ո�
						result = 1;//����
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;
				}
			}
		}
		if (result != 0)
		{
			return result;
		}
		if (row + 3 < 15)
		{
			//down�ڵ����
			down_left_neighbor = a.Read_data(row + 1, col - 1);
			if (down_left_neighbor == 0)
			{
				//down_left�ڵ�Ϊ��
				if ((a.Read_data(row + 2, col - 2) == color) && (a.Read_data(row + 3, col - 3) == color))
				{
					a.account_data[row][col] = color;
					//down2down3Ϊ���壬����������������
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row + 1, col - 1, flag, color);
					if (if_alive_4 == 1)
					{
						//���ı�����ո�
						result = 1;//����
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;
				}
				else if ((row - 1>-1) && (a.Read_data(row + 2, col - 2) == color) && (a.Read_data(row - 1, col + 1) == color))
				{
					a.account_data[row][col] = color;
					//down2up1Ϊ���壬����������������
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row + 1, col - 1, flag, color);
					if (if_alive_4 == 1)
					{
						//���ı�����ո�
						result = 1;//����
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;
				}
			}
			else if (down_left_neighbor == 1)
			{
				//down_left�ڵ�Ϊ����
				if ((a.Read_data(row + 2, col - 2) == 0) && (a.Read_data(row + 3, col - 3) == color))
				{
					a.account_data[row][col] = color;
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row + 2, col - 2, flag, color);
					if (if_alive_4 == 1)
					{
						//���ı�����ո�
						result = 1;//����
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;
				}
			}
		}
		if (result != 0)
		{
			return result;
		}
		if (row - 2 == 0)
		{
			//��Ե����ֻ�������ͷ���
			if (a.Read_data(row - 1, col + 1) == 0 && a.Read_data(row - 2, col + 2) == color && a.Read_data(row + 1, col - 1) == color)
			{
				a.account_data[row][col] = color;
				int if_alive_4 = 0;
				if_alive_4 = Alive_4(a, row - 1, col + 1, flag, color);
				if (if_alive_4 == 2)
				{
					result = 2;//����
				}
				else
				{
					result = 0;
				}
				a.account_data[row][col] = 0;
			}
			else
			{
				result = 0;
			}
		}
		if (result != 0)
		{
			return result;
		}
		if (row + 2 == 14)
		{
			if (a.Read_data(row + 1, col - 1) == 0 && a.Read_data(row + 2, col - 2) == color && a.Read_data(row - 1, col + 1) == color)
			{
				a.account_data[row][col] = color;//
				int if_alive_4 = 0;
				if_alive_4 = Alive_4(a, row + 1, col - 1, flag, color);
				if (if_alive_4 == 2)
				{
					result = 2;//����
				}
				else
				{
					result = 0;
				}
				a.account_data[row][col] = 0;//
			}
			else
			{
				result = 0;
			}
		}

		//���������������
		if ((a.Read_data(row - 1, col + 1) == 0 && a.Read_data(row - 2, col + 2) == color && a.Read_data(row - 3, col + 3) == 0 && a.Read_data(row - 4, col + 4) == color) || (a.Read_data(row - 1, col + 1) == 0 && a.Read_data(row - 2, col + 2) == 0 && a.Read_data(row - 3, col + 3) == color && a.Read_data(row - 4, col + 4) == color) || (a.Read_data(row - 1, col + 1) == 0 && a.Read_data(row - 2, col + 2) == 0 && a.Read_data(row - 3, col + 3) == color && a.Read_data(row - 4, col + 4) == color && a.Read_data(row - 5, col + 5) == op_color))
		{
			result = 2;
		}
		else if ((a.Read_data(row + 1, col - 1) == 0 && a.Read_data(row + 2, col - 2) == color && a.Read_data(row + 3, col - 3) == 0 && a.Read_data(row + 4, col - 4) == color) || (a.Read_data(row + 1, col - 1) == 0 && a.Read_data(row + 2, col - 2) == 0 && a.Read_data(row + 3, col - 3) == color && a.Read_data(row + 4, col - 4) == color) || (a.Read_data(row + 1, col - 1) == 0 && a.Read_data(row + 2, col - 2) == 0 && a.Read_data(row + 3, col - 3) == color && a.Read_data(row + 4, col - 4) == color && a.Read_data(row + 5, col - 5) == op_color))
		{
			result = 2;
		}

		return result;
	}


	if (flag == 'f')
	{
		//��б,��б
		//�����ϼ��
		while ((row - i) > -1 && a.Read_data(row - i, col - i) == color)
		{
			count += 1;
			if (count == 3)
			{
				a.account_data[row][col] = color;
				if ((row + 1) < 15 && (col + 1) < 16 && (row - i - 1) > -1 && (col - i - 1) > 0)
				{
					if (Alive_4(a, row + 1, col + 1, flag,color) == 1 || Alive_4(a, row - i - 1, col - i - 1, flag,color) == 1)
					{
						result = 1;
					}
					else if (Alive_4(a, row + 1, col + 1, flag,color) == 0 && Alive_4(a, row - i - 1, col - i - 1, flag,color) == 0)
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				else
				{
					if ((row == 14 && col == 15 && Alive_4(a, row - i - 1, col - i - 1, flag,color) == 0) || ((row - i) == 0 && (col - i) == 1 && Alive_4(a, row + 1, col + 1, flag,color) == 0))
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				a.account_data[row][col] = 0;
				break;
			}
			i += 1;//����������
		}
		if (result != 0)
		{
			return result;
		}
		i = 1;
		//�����¼��
		while ((row + i) < 15 && a.Read_data(row + i, col + i) == color)
		{
			count += 1;
			if (count == 3)
			{
				a.account_data[row][col] = color;
				if ((row - 1) > -1 && (col - 1) > 0 && (row + i + 1) < 15 && (col + i + 1) < 16)
				{
					if (Alive_4(a, row - 1, col - 1, flag,color) == 1 || Alive_4(a, row + i + 1, col + i + 1, flag,color) == 1)
					{
						result = 1;
					}
					else if (Alive_4(a, row - 1, col - 1, flag,color) == 0 && Alive_4(a, row + i + 1, col + i + 1, flag,color) == 0)
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				else
				{
					if ((row == 0 && col == 1 && Alive_4(a, row + i + 1, col + i + 1, flag,color) == 0) || ((row + i) == 14 && (col + i) == 15 && Alive_4(a, row - 1, col - 1, flag,color) == 0))
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				a.account_data[row][col] = 0;
				break;
			}
			i += 1;
		}

		//��������
		int up_left_neighbor = -1;
		//��������
		int down_right_neighbor = -1;

		if (row - 3 > -1)
		{
			//left���ڵ����
			up_left_neighbor = a.Read_data(row - 1, col - 1);
			if (up_left_neighbor == 0)
			{
				//left���ڵ�Ϊ��
				if ((a.Read_data(row - 2, col - 2) == color) && (a.Read_data(row - 3, col - 3) == color))
				{
					a.account_data[row][col] = color;//
													 //up2up3Ϊ���壬����������������
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row - 1, col - 1, flag, color);
					if (if_alive_4 == 1)
					{
						//���ı�����ո�
						result = 1;//����
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;//
				}
				else if ((row + 1 < 15) && (a.Read_data(row - 2, col - 2) == color) && (a.Read_data(row + 1, col + 1) == color))
				{
					a.account_data[row][col] = color;//
													 //up2down1Ϊ����
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row - 1, col - 1, flag, color);
					if (if_alive_4 == 1)
					{
						//���ı�����ո�
						result = 1;//����
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;//
				}
			}
			else if (up_left_neighbor == 1)
			{
				//up_left�ڵ�Ϊ����
				if ((a.Read_data(row - 2, col - 2) == 0) && (a.Read_data(row - 3, col - 3) == color))
				{
					a.account_data[row][col] = color;//
													 //up2Ϊ��down��Ϊ���壬����������
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row - 2, col - 2, flag, color);
					if (if_alive_4 == 1)
					{
						//���ı�����ո�
						result = 1;//����
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;//
				}
			}
		}
		if (result != 0)
		{
			return result;
		}
		if (row + 3 < 15)
		{
			//down�ڵ����
			down_right_neighbor = a.Read_data(row + 1, col + 1);
			if (down_right_neighbor == 0)
			{
				//down_right�ڵ�Ϊ��
				if ((a.Read_data(row + 2, col + 2) == color) && (a.Read_data(row + 3, col + 3) == color))
				{
					a.account_data[row][col] = color;//
													 //down2down3Ϊ���壬����������������
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row + 1, col + 1, flag, color);
					if (if_alive_4 == 1)
					{
						//���ı�����ո�
						result = 1;//����
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;//
				}
				else if ((row - 1>-1) && (a.Read_data(row + 2, col + 2) == color) && (a.Read_data(row - 1, col - 1) == color))
				{
					a.account_data[row][col] = color;//
													 //down2up1Ϊ���壬����������������
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row + 1, col + 1, flag, color);
					if (if_alive_4 == 1)
					{
						//���ı�����ո�
						result = 1;//����
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;//
				}
			}
			else if (down_right_neighbor == 1)
			{
				//down_right�ڵ�Ϊ����
				if ((a.Read_data(row + 2, col + 2) == 0) && (a.Read_data(row + 3, col + 3) == color))
				{
					a.account_data[row][col] = color;//
					int if_alive_4 = 0;
					if_alive_4 = Alive_4(a, row + 2, col + 2, flag, color);
					if (if_alive_4 == 1)
					{
						//���ı�����ո�
						result = 1;//����
					}
					else if (if_alive_4 == 2)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
					a.account_data[row][col] = 0;//
				}
			}
		}
		if (result != 0)
		{
			return result;
		}
		if (row - 2 == 0)
		{
			//��Ե����ֻ�������ͷ���
			if (a.Read_data(row - 1, col - 1) == 0 && a.Read_data(row - 2, col - 2) == color && a.Read_data(row + 1, col + 1) == color)
			{
				a.account_data[row][col] = color;//
				int if_alive_4 = 0;
				if_alive_4 = Alive_4(a, row - 1, col - 1, flag, color);
				if (if_alive_4 == 2)
				{
					result = 2;//����
				}
				else
				{
					result = 0;
				}
				a.account_data[row][col] = 0;//
			}
			else
			{
				result = 0;
			}
		}
		if (result != 0)
		{
			return result;
		}
		if (row + 2 == 14)
		{
			if (a.Read_data(row + 1, col + 1) == 0 && a.Read_data(row + 2, col + 2) == color && a.Read_data(row - 1, col - 1) == color)
			{
				a.account_data[row][col] = color;//
				int if_alive_4 = 0;
				if_alive_4 = Alive_4(a, row + 1, col + 1, flag, color);
				if (if_alive_4 == 2)
				{
					result = 2;//����
				}
				else
				{
					result = 0;
				}
				a.account_data[row][col] = 0;//
			}
			else
			{
				result = 0;
			}
		}

		//���������������
		if ((a.Read_data(row - 1, col - 1) == 0 && a.Read_data(row - 2, col - 2) == color && a.Read_data(row - 3, col - 3) == 0 && a.Read_data(row - 4, col - 4) == color) || (a.Read_data(row - 1, col - 1) == 0 && a.Read_data(row - 2, col - 2) == 0 && a.Read_data(row - 3, col - 3) == color && a.Read_data(row - 4, col - 4) == color) || (a.Read_data(row - 1, col - 1) == 0 && a.Read_data(row - 2, col - 2) == 0 && a.Read_data(row - 3, col - 3) == color && a.Read_data(row - 4, col - 4) == color && a.Read_data(row - 5, col - 5) == op_color))
		{
			result = 2;
		}
		else if ((a.Read_data(row + 1, col + 1) == 0 && a.Read_data(row + 2, col + 2) == color && a.Read_data(row + 3, col + 3) == 0 && a.Read_data(row + 4, col + 4) == color) || (a.Read_data(row + 1, col + 1) == 0 && a.Read_data(row + 2, col + 2) == 0 && a.Read_data(row + 3, col + 3) == color && a.Read_data(row + 4, col + 4) == color) || (a.Read_data(row + 1, col + 1) == 0 && a.Read_data(row + 2, col + 2) == 0 && a.Read_data(row + 3, col + 3) == color && a.Read_data(row + 4, col + 4) == color && a.Read_data(row + 5, col + 5) == op_color))
		{
			result = 2;
		}

		return result;
	}

	//����������ʣ���������
	
	return 0;
}

int Judge::Alive_4(Array_data a, int row, int col,char flag,int color)
{
	//����0�Ƿ���,����1�ǻ��ģ�2������
	int result = 0;
	int i = 1;
	int count = 1;//ִ�����ӳ���

	int op_color = -1;//�ǵ�ǰִ����ɫ
	if (color == 1)
	{
		op_color = 2;
	}
	else
	{
		op_color = 1;
	}

	if(flag == 'h')
	{
		//��
		//������
		while ((col - i) > 0 && a.Read_data(row, col - i) == color)
		{
			count += 1;
			if (count == 4)
			{
				if ((col - i - 1) > 0 && (col + 1) < 16)
				{
					//����������������жϻ������
					if (a.Read_data(row, col - i - 1) == 0 && a.Read_data(row, col + 1) == 0)
					{
						//����
						result = 1;
					}
					else if (a.Read_data(row, col - i - 1) == op_color && a.Read_data(row, col + 1) == op_color)
					{
						//����
						result = 0;
					}
					else
					{
						//����
						result = 2;
					}
				}
				else
				{
					//�����ӵ���һ�಻���ڿո񣬴������̱�Ե
					if ((col == 15 && a.Read_data(row, col - i - 1) == op_color) || ((col - i) == 1 && a.Read_data(row, col + 1) == op_color))
					{
						//��ǰ�����������һ�У����������һ�ӵ����Ϊ����
						//��ǰ�����ӵ������һ���ڵ�һ�У���ǰ�ӵ��ұ�Ϊ����
						//����
						result = 0;
					}
					else
					{
						//����
						result = 2;
					}
					
				}
				break;
			}
			i += 1;//��������
		}
		if (result != 0)
		{
			return result;
		}
		i = 1;
		//���Ҽ��
		while ((col + i) < 16 && a.Read_data(row, col + i) == color)
		{
			count += 1;
			if (count == 4)
			{
				if ((col - 1) > 0 && (col + i + 1) < 16)
				{
					if (a.Read_data(row, col + i + 1) == 0 && a.Read_data(row, col - 1) == 0)
					{
						result = 1;//����
					}
					else if (a.Read_data(row, col + i + 1) == op_color && a.Read_data(row, col - 1) == op_color)
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				else
				{
					if ((col == 1 && a.Read_data(row, col + i + 1) == op_color) || ((col + i) == 15 && a.Read_data(row, col - 1) == op_color))
					{
						//��ǰ���ڵ�һ�У����ӵ����ұ�һ�ӵ��ұ�Ϊ����
						//��ǰ����������ұ�һ�������һ�У���ǰ�ӵ����һ��Ϊ����
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				
				break;
			}
			i += 1;
		}
		
		return result;

	}
	if(flag == 's')
	{
		//��
		//���ϼ��
		while ((row - i) > -1 && a.Read_data(row - i, col) == color)
		{
			count += 1;
			if (count == 4)
			{
				if ((row + 1) < 15 && (row - i - 1) > -1)
				{
					if (a.Read_data(row + 1, col) == 0 && a.Read_data(row - i - 1, col) == 0)
					{
						result = 1;
					}
					else if (a.Read_data(row + 1, col) == op_color && a.Read_data(row - i - 1, col) == op_color)
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				else
				{
					if ((row == 14 && a.Read_data(row - i - 1, col) == op_color) || ((row - i) == 0 && a.Read_data(row + 1, col) == op_color))
					{
						//��ǰ�������һ�У����ӵ����ϱ�һ�ӵ���һ����Ϊ����
						//��ǰ�ӵ����ӵ�������һ���ڵ�һ�У���ǰ�ӵ�����һ����Ϊ����
						result = 0;
					}
					else
					{
						result = 2;
					}
				}

				break;
			}
			i += 1;//��������
		}
		if (result != 0)
		{
			return result;
		}
		i = 1;
		//���¼��
		while ((row + i) < 15 && a.Read_data(row + i, col) == color)
		{
			count += 1;
			if (count == 4)
			{
				if ((row - 1) > -1 && (row + i + 1) < 15)
				{
					if (a.Read_data(row - 1, col) == 0 && a.Read_data(row + i + 1, col) == 0)
					{
						result = 1;
					}
					else if (a.Read_data(row - 1, col) == op_color && a.Read_data(row + i + 1, col) == op_color)
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				else
				{
					if ((row == 0 && a.Read_data(row + i + 1, col) == op_color) || ((row + i) == 14 && a.Read_data(row - 1, col) == op_color))
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				break;
			}
			i += 1;
		}
		
		return result;
	}
	if(flag == 'z')
	{
		//��б
		//�����¼��
		while ((row + i) < 15 && a.Read_data(row + i, col - i) == color)
		{
			count += 1;
			if (count == 4)
			{
				if ((row - 1) > -1 && (col + 1) < 16 && (row + i + 1) < 15 && (col - i - 1) > 0)
				{
					if (a.Read_data(row - 1, col + 1) == 0 && a.Read_data(row + i + 1, col - i - 1) == 0)
					{
						result = 1;
					}
					else if (a.Read_data(row - 1, col + 1) == op_color && a.Read_data(row + i + 1, col - i - 1) == op_color)
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				else
				{
					if ((row == 0 && col == 15 && a.Read_data(row + i + 1, col - i - 1) == op_color) || ((row + i) == 14 && (col - i) == 1 && a.Read_data(row - 1, col + 1) == op_color))
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				break;
			}
			i += 1;//����������
		}
		if (result != 0)
		{
			return result;
		}
		i = 1;
		//�����ϼ��
		while ((row - i) > -1 && a.Read_data(row - i, col + i) == color)
		{
			count += 1;
			if (count == 4)
			{
				if ((row + 1) < 15 && (col - 1) > 0 && (row - i - 1) > -1 && (col + i + 1) < 16)
				{
					if (a.Read_data(row + 1, col - 1) == 0 && a.Read_data(row - i - 1, col + i + 1) == 0)
					{
						result = 1;
					}
					else if (a.Read_data(row + 1, col - 1) == op_color && a.Read_data(row - i - 1, col + i + 1) == op_color)
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				else
				{
					if ((row == 14 && col == 1 && a.Read_data(row - i - 1, col + i + 1) == op_color) || ((row - i) == 0 && (col + i) == 15 && a.Read_data(row + 1, col - 1) == op_color))
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}

				break;
			}
			i += 1;
		}
		
		return result;
	}
	if(flag == 'f')
	{
		//��б,��б
		//�����ϼ��
		while ((row - i) > -1 && a.Read_data(row - i, col - i) == color)
		{
			count += 1;
			if (count == 4)
			{
				if ((row + 1) < 15 && (col + 1) < 16 && (row - i - 1) > -1 && (col - i - 1) > 0)
				{
					if (a.Read_data(row + 1, col + 1) == 0 && a.Read_data(row - i - 1, col - i - 1) == 0)
					{
						result = 1;
					}
					else if (a.Read_data(row + 1, col + 1) == op_color && a.Read_data(row - i - 1, col - i - 1) == op_color)
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				else
				{
					if ((row == 14 && col == 15 && a.Read_data(row - i - 1, col - i - 1) == op_color) || ((row - i) == 0 && (col - i) == 1 && a.Read_data(row + 1, col + 1) == op_color))
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}

				break;
			}
			i += 1;//����������
		}
		if (result != 0)
		{
			return result;
		}
		i = 1;
		//�����¼��
		while ((row + i) < 15 && a.Read_data(row + i, col + i) == color)
		{
			count += 1;
			if (count == 4)
			{
				if ((row - 1) > -1 && (col - 1) > 0 && (row + i + 1) < 15 && (col + i + 1) < 16)
				{
					if (a.Read_data(row - 1, col - 1) == 0 && a.Read_data(row + i + 1, col + i + 1) == 0)
					{
						result = 1;
					}
					else if (a.Read_data(row - 1, col - 1) == op_color && a.Read_data(row + i + 1, col + i + 1) == op_color)
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}
				else
				{
					if ((row == 0 && col == 1 && a.Read_data(row + i + 1, col + i + 1) == op_color) || ((row + i) == 14 && (col + i) == 15 && a.Read_data(row - 1, col - 1) == op_color))
					{
						result = 0;
					}
					else
					{
						result = 2;
					}
				}

				break;
			}
			i += 1;
		}
		
		return result;
	}

	//return result;
	return 0;
}

int Judge::Alive_2(Array_data a,int row, int col, char flag, int color)
{
	//����0�ǷǶ�,����1�ǻ����2������
	int result = 0;
	int i = 1;
	int count = 1;//���ӳ���

	int op_color = -1;//�ǵ�ǰִ����ɫ
	if (color == 1)
	{
		op_color = 2;
	}
	else
	{
		op_color = 1;
	}

	if (flag == 'h')
	{
		//���
		while (col - i > 0 && i < 5)
		{
			if (a.account_data[row][col - i] == color)
			{
				count += 1;
			}
			else if (a.account_data[row][col - i] == op_color)
			{
				break;
			}
			if (count == 2)
			{
				a.account_data[row][col] = color;
				//���ڶ�����
				if (i == 4)
				{
					result = 2;
				}
				if (i == 3)
				{
					if (Alive_3(a, row, col - 1, flag, color) == 1 || Alive_3(a, row, col - 2, flag, color) == 1)
					{
						result = 1;//���
					}
					else if (a.account_data[row][col+1] == op_color)
					{
						result = 2;//����
					}
					else
					{
						result = 0;//�Ƕ�
					}
				}
				if (i == 2)
				{
					if (((col - 3) > 0 && a.account_data[row][col - 3] == 0 && Alive_3(a, row, col - 3, flag, color) == 1) || (Alive_3(a, row, col - 1, flag, color) == 1) || ((col + 1) < 16 && a.account_data[row][col + 1] == 0 && Alive_3(a, row, col + 1, flag, color) == 1))
					{
						result = 1;
					}
					else if (a.account_data[row][col + 1] == op_color)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
				}
				if (i == 1)
				{
					if (((col - 2) > 0 && a.account_data[row][col - 2] == 0 && Alive_3(a, row, col - 2, flag, color) == 1) || ((col - 3) > 0 && a.account_data[row][col - 3] == 0 && Alive_3(a, row, col - 3, flag, color) == 1) || ((col + 1) < 16 && a.account_data[row][col + 1] == 0 && Alive_3(a, row, col + 1, flag, color) == 1) || ((col + 2) < 16 && a.account_data[row][col + 2] == 0 && Alive_3(a, row, col + 2, flag, color) == 1))
					{
						result = 1;
					}
					else if (a.account_data[row][col + 1] == op_color)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
				}
				
				a.account_data[row][col] = 0;
				break;
			}
			i += 1;
		}
		if (result != 0)
		{
			return result;
		}
		//�Ҳ�
		i = 1;
		while (col + i < 16 && i < 5)
		{
			if (a.account_data[row][col + i] == color)
			{
				count += 1;
			}
			else if (a.account_data[row][col + i] == op_color)
			{
				break;
			}
			if (count == 2)
			{
				a.account_data[row][col] = color;
				//���ڶ�����
				
				if (i == 4)
				{
					result = 2;
				}
				if (i == 3)
				{
					if (Alive_3(a, row, col + 1, flag, color) == 1 || Alive_3(a, row, col + 2, flag, color) == 1)
					{
						result = 1;//���
					}
					else if (a.account_data[row][col - 1] == op_color)
					{
						result = 2;//����
					}
					else
					{
						result = 0;//�Ƕ�
					}
				}
				if (i == 2)
				{
					if (((col + 3) < 16 && a.account_data[row][col + 3] == 0 && Alive_3(a, row, col + 3, flag, color) == 1) || (Alive_3(a, row, col + 1, flag, color) == 1) || ((col - 1) > 0 && a.account_data[row][col - 1] == 0 && Alive_3(a, row, col - 1, flag, color) == 1))
					{
						result = 1;
					}
					else if (a.account_data[row][col - 1] == op_color)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
				}
				if (i == 1)
				{
					if (((col + 2) < 16 && a.account_data[row][col + 2] == 0 && Alive_3(a, row, col + 2, flag, color) == 1) || ((col + 3) < 16 && a.account_data[row][col + 3] == 0 && Alive_3(a, row, col + 3, flag, color) == 1) || ((col - 1) > 0 && a.account_data[row][col - 1] == 0 && Alive_3(a, row, col - 1, flag, color) == 1) || ((col - 2) > 0 && a.account_data[row][col - 2] == 0 && Alive_3(a, row, col - 2, flag, color) == 1))
					{
						result = 1;
					}
					else if (a.account_data[row][col - 1] == op_color)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
				}

				a.account_data[row][col] = 0;
				break;
			}
			i += 1;
		}

		return result;
	}
	if (flag == 's')
	{
		//up��
		while (row - i > -1 && i < 4)
		{
			if (a.account_data[row - i][col] == color)
			{
				count += 1;
			}
			else if (a.account_data[row - i][col] == op_color)
			{
				break;
			}
			if (count == 2)
			{
				a.account_data[row][col] = color;
				//���ڶ�����
				
				if (i == 4)
				{
					result = 2;
				}
				if (i == 3)
				{
					if (Alive_3(a, row - 1, col, flag, color) == 1 || Alive_3(a, row-2, col, flag, color) == 1)
					{
						result = 1;//���
					}
					else if (a.account_data[row+1][col] == op_color)
					{
						result = 2;//����
					}
					else
					{
						result = 0;//�Ƕ�
					}
				}
				if (i == 2)
				{
					if (((row - 3) > -1 && a.account_data[row - 3][col] == 0 && Alive_3(a, row - 3, col, flag, color) == 1) || (Alive_3(a, row - 1, col, flag, color) == 1) || ((row + 1) < 15 && a.account_data[row + 1][col] == 0 && Alive_3(a, row + 1, col, flag, color) == 1))
					{
						result = 1;
					}
					else if (a.account_data[row + 1][col] == op_color)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
				}
				if (i == 1)
				{
					if (((row - 2) > -1 && a.account_data[row - 2][col] == 0 && Alive_3(a, row - 2, col, flag, color) == 1) || ((row - 3) > -1 && a.account_data[row - 3][col] == 0 && Alive_3(a, row - 3, col, flag, color) == 1) || ((row + 1) < 15 && a.account_data[row + 1][col] == 0 && Alive_3(a, row + 1, col, flag, color) == 1) || ((row + 2) < 15 && a.account_data[row + 2][col] == 0 && Alive_3(a, row + 2, col, flag, color) == 1))
					{
						result = 1;
					}
					else if (a.account_data[row + 1][col] == op_color)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
				}

				a.account_data[row][col] = 0;
				break;
			}
			i += 1;
		}
		if (result != 0)
		{
			return result;
		}
		//down��
		i = 1;
		while (col + i < 15 && i < 4)
		{
			if (a.account_data[row + i][col] == color)
			{
				count += 1;
			}
			else if (a.account_data[row + i][col] == op_color)
			{
				break;
			}
			if (count == 2)
			{
				a.account_data[row][col] = color;
				//���ڶ�����
				
				if (i == 4)
				{
					result = 2;
				}
				if (i == 3)
				{
					if (Alive_3(a, row + 1, col, flag, color) == 1 || Alive_3(a, row + 2, col, flag, color) == 1)
					{
						result = 1;//���
					}
					else if (a.account_data[row - 1][col] == op_color)
					{
						result = 2;//����
					}
					else
					{
						result = 0;//�Ƕ�
					}
				}
				if (i == 2)
				{
					if (((row + 3) < 15 && a.account_data[row + 3][col] == 0 && Alive_3(a, row + 3, col, flag, color) == 1) || (Alive_3(a, row + 1, col, flag, color) == 1) || ((row - 1) > -1 && a.account_data[row - 1][col] == 0 && Alive_3(a, row - 1, col, flag, color) == 1))
					{
						result = 1;
					}
					else if (a.account_data[row - 1][col] == op_color)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
				}
				if (i == 1)
				{
					if (((row + 2) < 15 && a.account_data[row + 2][col] == 0 && Alive_3(a, row + 2, col, flag, color) == 1) || ((row + 3) < 15 && a.account_data[row + 3][col] == 0 && Alive_3(a, row + 3, col, flag, color) == 1) || ((row - 1) > -1 && a.account_data[row - 1][col] == 0 && Alive_3(a, row - 1, col, flag, color) == 1) || ((row - 2) > -1 && a.account_data[row - 2][col] == 0 && Alive_3(a, row - 2, col, flag, color) == 1))
					{
						result = 1;
					}
					else if (a.account_data[row - 1][col] == op_color)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
				}

				a.account_data[row][col] = 0;
				break;
			}
			i += 1;
		}

		return result;
	}
	if (flag == 'z')
	{
		//��down��
		while (col - i > 0 && i < 4)
		{
			if (a.account_data[row + i][col - i] == color)
			{
				count += 1;
			}
			else if (a.account_data[row + i][col - i] == op_color)
			{
				break;
			}
			if (count == 2)
			{
				a.account_data[row][col] = color;
				//���ڶ�����
				
				if (i == 4)
				{
					result = 2;
				}
				if (i == 3)
				{
					if (Alive_3(a, row + 1, col - 1, flag, color) == 1 || Alive_3(a, row + 2, col - 2, flag, color) == 1)
					{
						result = 1;//���
					}
					else if (a.account_data[row - 1][col + 1] == op_color)
					{
						result = 2;//����
					}
					else
					{
						result = 0;//�Ƕ�
					}
				}
				if (i == 2)
				{
					if (((row + 3) < 15 && a.account_data[row + 3][col - 3] == 0 && Alive_3(a, row + 3, col - 3, flag, color) == 1) || (Alive_3(a, row + 1, col - 1, flag, color) == 1) || ((row - 1) > -1 && a.account_data[row - 1][col +1] == 0 && Alive_3(a, row - 1, col + 1, flag, color) == 1))
					{
						result = 1;
					}
					else if (a.account_data[row - 1][col + 1] == op_color)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
				}
				if (i == 1)
				{
					if (((row + 2) < 15 && a.account_data[row + 2][col - 2] == 0 && Alive_3(a, row + 2, col - 2, flag, color) == 1) || ((row + 3) < 15 && a.account_data[row + 3][col -3] == 0 && Alive_3(a, row + 3, col - 3, flag, color) == 1) || ((row - 1) > -1 && a.account_data[row - 1][col + 1] == 0 && Alive_3(a, row - 1, col + 1, flag, color) == 1) || ((row - 2) > -1 && a.account_data[row - 2][col + 2] == 0 && Alive_3(a, row - 2, col + 2, flag, color) == 1))
					{
						result = 1;
					}
					else if (a.account_data[row - 1][col + 1] == op_color)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
				}

				a.account_data[row][col] = 0;
				break;
			}
			i += 1;
		}
		if (result != 0)
		{
			return result;
		}
		//��up��
		i = 1;
		while (col + i < 16 && i < 4)
		{
			if (a.account_data[row - i][col + i] == color)
			{
				count += 1;
			}
			else if (a.account_data[row - i][col + i] == op_color)
			{
				break;
			}
			if (count == 2)
			{
				a.account_data[row][col] = color;
				//���ڶ�����
				
				if (i == 4)
				{
					result = 2;
				}
				if (i == 3)
				{
					if (Alive_3(a, row - 1, col + 1, flag, color) == 1 || Alive_3(a, row - 2, col + 2, flag, color) == 1)
					{
						result = 1;//���
					}
					else if (a.account_data[row + 1][col - 1] == op_color)
					{
						result = 2;//����
					}
					else
					{
						result = 0;//�Ƕ�
					}
				}
				if (i == 2)
				{
					if (((row - 3) > -1 && a.account_data[row - 3][col + 3] == 0 && Alive_3(a, row - 3, col + 3, flag, color) == 1) || (Alive_3(a, row - 1, col + 1, flag, color) == 1) || ((row + 1) < 15 && a.account_data[row + 1][col - 1] == 0 && Alive_3(a, row + 1, col - 1, flag, color) == 1))
					{
						result = 1;
					}
					else if (a.account_data[row + 1][col - 1] == op_color)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
				}
				if (i == 1)
				{
					if (((row - 2) > -1 && a.account_data[row - 2][col + 2] == 0 && Alive_3(a, row - 2, col + 2, flag, color) == 1) || ((row - 3) > -1 && a.account_data[row - 3][col + 3] == 0 && Alive_3(a, row - 3, col + 3, flag, color) == 1) || ((row + 1) < 15 && a.account_data[row + 1][col - 1] == 0 && Alive_3(a, row + 1, col - 1, flag, color) == 1) || ((row + 2) < 15 && a.account_data[row + 2][col - 2] == 0 && Alive_3(a, row + 2, col - 2, flag, color) == 1))
					{
						result = 1;
					}
					else if (a.account_data[row + 1][col - 1] == op_color)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
				}

				a.account_data[row][col] = 0;
				break;
			}
			i += 1;
		}

		return result;
	}
	if (flag == 'f')
	{
		//��up��
		while (col - i > 0 && i < 4)
		{
			if (a.account_data[row - i][col - i] == color)
			{
				count += 1;
			}
			else if (a.account_data[row - i][col - i] == op_color)
			{
				break;
			}
			if (count == 2)
			{
				a.account_data[row][col] = color;
				//���ڶ�����
				
				if (i == 4)
				{
					result = 2;
				}
				if (i == 3)
				{
					if (Alive_3(a, row - 1, col - 1, flag, color) == 1 || Alive_3(a, row - 2, col - 2, flag, color) == 1)
					{
						result = 1;//���
					}
					else if (a.account_data[row + 1][col + 1] == op_color)
					{
						result = 2;//����
					}
					else
					{
						result = 0;//�Ƕ�
					}
				}
				if (i == 2)
				{
					if (((row - 3) > -1 && a.account_data[row - 3][col - 3] == 0 && Alive_3(a, row - 3, col - 3, flag, color) == 1) || (Alive_3(a, row - 1, col - 1, flag, color) == 1) || ((row + 1) < 15 && a.account_data[row + 1][col + 1] == 0 && Alive_3(a, row + 1, col + 1, flag, color) == 1))
					{
						result = 1;
					}
					else if (a.account_data[row + 1][col + 1] == op_color)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
				}
				if (i == 1)
				{
					if (((row - 2) > -1 && a.account_data[row - 2][col - 2] == 0 && Alive_3(a, row - 2, col - 2, flag, color) == 1) || ((row - 3) > -1 && a.account_data[row - 3][col - 3] == 0 && Alive_3(a, row - 3, col - 3, flag, color) == 1) || ((row + 1) < 15 && a.account_data[row + 1][col + 1] == 0 && Alive_3(a, row + 1, col + 1, flag, color) == 1) || ((row + 2) < 15 && a.account_data[row + 2][col + 2] == 0 && Alive_3(a, row + 2, col +2, flag, color) == 1))
					{
						result = 1;
					}
					else if (a.account_data[row + 1][col + 1] == op_color)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
				}

				a.account_data[row][col] = 0;
				break;
			}
			i += 1;
		}
		if (result != 0)
		{
			return result;
		}
		//��down��
		i = 1;
		while (col + i < 16 && i < 4)
		{
			if (a.account_data[row + i][col + i] == color)
			{
				count += 1;
			}
			else if (a.account_data[row + i][col + i] == op_color)
			{
				break;
			}
			if (count == 2)
			{
				a.account_data[row][col] = color;
				//���ڶ�����
				
				if (i == 4)
				{
					result = 2;
				}
				if (i == 3)
				{
					if (Alive_3(a, row + 1, col + 1, flag, color) == 1 || Alive_3(a, row + 2, col + 2, flag, color) == 1)
					{
						result = 1;//���
					}
					else if (a.account_data[row - 1][col-1] == op_color)
					{
						result = 2;//����
					}
					else
					{
						result = 0;//�Ƕ�
					}
				}
				if (i == 2)
				{
					if (((row + 3) < 15 && a.account_data[row + 3][col + 3] == 0 && Alive_3(a, row + 3, col + 3, flag, color) == 1) || (Alive_3(a, row + 1, col + 1, flag, color) == 1) || ((row - 1) > -1 && a.account_data[row - 1][col - 1] == 0 && Alive_3(a, row - 1, col - 1, flag, color) == 1))
					{
						result = 1;
					}
					else if (a.account_data[row - 1][col - 1] == op_color)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
				}
				if (i == 1)
				{
					if (((row + 2) < 15 && a.account_data[row + 2][col + 2] == 0 && Alive_3(a, row + 2, col + 2, flag, color) == 1) || ((row + 3) < 15 && a.account_data[row + 3][col + 3] == 0 && Alive_3(a, row + 3, col + 3, flag, color) == 1) || ((row - 1) > -1 && a.account_data[row - 1][col - 1] == 0 && Alive_3(a, row - 1, col - 1, flag, color) == 1) || ((row - 2) > -1 && a.account_data[row - 2][col-2] == 0 && Alive_3(a, row - 2, col-2, flag, color) == 1))
					{
						result = 1;
					}
					else if (a.account_data[row - 1][col - 1] == op_color)
					{
						result = 2;
					}
					else
					{
						result = 0;
					}
				}

				a.account_data[row][col] = 0;
				break;
			}
			i += 1;
		}

		return result;
	}

	return 0;
}

/*
int Judge::Dead_4(Array_data a, int row, int col,char flag)
{
	//����0������
	int result = 0;
	int count = 1;//���ӳ���



	return result;
}
*/

int Judge::Double_4_judge(Array_data a, int row, int col,int color)
{
	//�ڷ�����������������ϻ��Ļ����ļ���
	int result = 0;//��������Ϊ-1
	int count = 0;//���γ����ӵ�������Ŀ

	if (Alive_4(a, row, col, 'h',color) == 1 || Alive_4(a, row, col, 'h',color) == 2)
	{
		count += 1;
	}
	if (count >= 2)
	{
		result = -1;
		return result;
	}
	if (Alive_4(a, row, col, 's',color) == 1 || Alive_4(a, row, col, 's',color) == 2)
	{
		count += 1;
	}
	if (count >= 2)
	{
		result = -1;
		return result;
	}
	if (Alive_4(a, row, col, 'z',color) == 1 || Alive_4(a, row, col, 'z',color) == 2)
	{
		count += 1;
	}
	if (count >= 2)
	{
		result = -1;
		return result;
	}
	if (Alive_4(a, row, col, 'f',color) == 1 || Alive_4(a, row, col, 'f',color) == 2)
	{
		count += 1;
	}
	if (count >= 2)
	{
		result = -1;
		return result;
	}

	return result;
}

int Judge::Double_3_judge(Array_data a, int row, int col,int color)
{
	//˫�����������������������Ϊ����
	int result = 0;//-1Ϊ��������
	int count = 0;//��������

	if (Alive_3(a, row, col, 'h',color) == 1)
	{
		count += 1;
	}
	if (count >= 2)
	{
		result = -1;
		return result;
	}
	if (Alive_3(a, row, col, 's',color) == 1)
	{
		count += 1;
	}
	if (count >= 2)
	{
		result = -1;
		return result;
	}
	if (Alive_3(a, row, col, 'z',color) == 1)
	{
		count += 1;
	}
	if (count >= 2)
	{
		result = -1;
		return result;
	}
	if (Alive_3(a, row, col, 'f',color) == 1)
	{
		count += 1;
	}
	if (count >= 2)
	{
		result = -1;
		return result;
	}

	return result;
}

int Judge::Double_2_judge(Array_data a, int row, int col, int color)
{
	int result = 0;//1Ϊ˫���
	int count = 0;

	if (Alive_2(a, row, col, 'h', color) == 1)
	{
		count += 1;
	}
	if (count >= 2)
	{
		result = 1;
		return result;
	}
	if (Alive_2(a, row, col, 's', color) == 1)
	{
		count += 1;
	}
	if (count >= 2)
	{
		result = 1;
		return result;
	}
	if (Alive_2(a, row, col, 'z', color) == 1)
	{
		count += 1;
	}
	if (count >= 2)
	{
		result = 1;
		return result;
	}
	if (Alive_2(a, row, col, 'f', color) == 1)
	{
		count += 1;
	}
	if (count >= 2)
	{
		result = 1;
		return result;
	}

	return 0;
}

int Judge::Ban_lift_ban(Array_data a, int row, int col)
{
	//�Խ����
	//1Ϊ�����0Ϊ�����
	int ban_lift = 0;//1Ϊ���



	return ban_lift;
}

int Judge::Judgement(Array_data a, int row, int col,int color)
{
	//�ж�ʤ��
	int result = 0;//0Ϊδ��ʤ����1Ϊ��ǰ���ӷ�ʤ,2Ϊƽ��
	int j = 0;//ѭ���ĸ�����

	int color_piece = 0;//���ݺڰ��Ӿ���������ɫ,����ƥ��account��ͬɫ����

	if (color == 0)
	{
		//ִ��
		color_piece = 1;
	}
	else
	{
		//ִ��
		color_piece = 2;
	}

	while (j < 4)
	{
		int i = 1;
		int count = 1;

		if (j == 0)
		{
			//��
			//������
			while ((col - i) > 0 && a.Read_data(row, col - i) == color_piece)
			{
				count += 1;
				if (count == 5)
				{
					result = 1;
					break;
				}
				i += 1;//��������
			}
			if (result == 1)
			{
				break;
			}
			i = 1;
			//���Ҽ��
			while ((col + i) < 16 && a.Read_data(row, col + i) == color_piece)
			{
				count += 1;
				if (count == 5)
				{
					result = 1;
					break;
				}
				i += 1;
			}
			if (result == 1)
			{
				break;
			}
		}
		else if (j == 1)
		{
			//��
			//���ϼ��
			while ((row - i) > -1 && a.Read_data(row - i, col) == color_piece)
			{
				count += 1;
				if (count == 5)
				{
					result = 1;
					break;
				}
				i += 1;//��������
			}
			if (result == 1)
			{
				break;
			}
			i = 1;
			//���¼��
			while ((row + i) < 15 && a.Read_data(row + i, col) == color_piece)
			{
				count += 1;
				if (count == 5)
				{
					result = 1;
					break;
				}
				i += 1;
			}
			if (result == 1)
			{
				break;
			}
		}
		else if (j == 2)
		{
			//��б
			//�����¼��
			while ((row + i) < 15 && a.Read_data(row + i, col - i) == color_piece)
			{
				count += 1;
				if (count == 5)
				{
					result = 1;
					break;
				}
				i += 1;//����������
			}
			if (result == 1)
			{
				break;
			}
			i = 1;
			//�����ϼ��
			while ((row - i) > -1 && a.Read_data(row - i, col + i) == color_piece)
			{
				count += 1;
				if (count == 5)
				{
					result = 1;
					break;
				}
				i += 1;
			}
			if (result == 1)
			{
				break;
			}
		}
		else
		{
			//��б
			//�����ϼ��
			while ((row - i) > -1 && a.Read_data(row - i, col - i) == color_piece)
			{
				count += 1;
				if (count == 5)
				{
					result = 1;
					break;
				}
				i += 1;//����������
			}
			if (result == 1)
			{
				break;
			}
			i = 1;
			//�����¼��
			while ((row + i) < 15 && a.Read_data(row + i, col + i) == color_piece)
			{
				count += 1;
				if (count == 5)
				{
					result = 1;
					break;
				}
				i += 1;
			}
			if (result == 1)
			{
				break;
			}
		}

		j += 1;
	}

	//ƽ���ж�����111�غϺ�Ż��ж�
	//������ִ��ڵĿո�������Ϊ0�����
	int m = 0;
	int n = 0;
	int blank_count = 0;
	for (m = 0; m < 15; m++)
	{
		for (n = 1; n < 16; n++)
		{
			if (a.Read_data(m, n) == 0)
			{
				blank_count += 1;
			}
			if (blank_count != 0)
			{
				break;
			}
		}
		if (blank_count != 0)
		{
			break;
		}
	}	
	if (blank_count == 0)
	{
		result = 2;
	}

	return result;
}