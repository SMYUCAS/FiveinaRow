#include "Chessman.h"



Chessman::Chessman()
{
}


Chessman::~Chessman()
{
}

const char* Chessman::chessman_type(int type,int state)
{
	if (type == 0)
	{
		//����
		if (state == 0)
		{
			//��ǰ����
			return "��";
		}
		else
		{
			return "��";
		}
	}
	else
	{
		//����
		if (state == 0)
		{
			//��ǰ����
			return "��";
		}
		else
		{
			return "��";
		}
	}
}