#pragma once

#define _CRT_SECURE_NO_WARNINGS

#define ROW 16
#define COL 16

class Array_data
{
public:
	Array_data();
	~Array_data();
	int account_data[ROW][COL] = { 0 };//�˱����ݣ������ж��Ͷ�ȡ�������ʹ��,16*16����ֻ��15*15������,��һ�к����һ��ȫ0
	int score[ROW][COL] = { 0 };//�Ʒ�����

	void Write_data(int i,int j,int flag,int color,int state);//i,j��ʾ���꣬flagΪд�������,colorΪ�ڰ��ж�,stateΪ�Ƿ�ǰ����
	void TransferType(char *dst,const char *src);//��const char����תΪchar���д洢
	void Show_data();//��ʾ�������
	int Read_data(int row,int col);//��ȡ˽�г�Ա����

	int read_row();
	char read_col();
	void write_row_col(int m_row, char m_col);

private:
	char ***data = new char**[ROW];	

	int machine_row = 0;//����ѡ������λ�ú�����
	char machine_col = ' ';//����ѡ������λ��������
	
	//1//char *last_row = new char[COL];
	//char *data[ROW][COL] = {};//�����ʼ��
};

