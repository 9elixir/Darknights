#pragma once
#include"A.h"
#include"Enemy.h"
#include"Character.h"
//������ʼλ�ö�Ϊ��������λ��
void GetStart(Enemy& e)
{
	start.x = e.ex;
	start.y = e.ey;
}
//������ֹλ�ö�Ϊ��������λ��
void GetEnd(Character c)
{
	End.x = c.cx;
	End.y = c.cy;
}
//����ǰ������λ�ã���׷������
void Goto(Enemy& e, Character c)
{
	GetStart(e);
	GetEnd(c);
	astar(e, c);
}