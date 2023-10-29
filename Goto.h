#pragma once
#include"A.h"
#include"Enemy.h"
#include"Character.h"
//怪物起始位置定为怪物所在位置
void GetStart(Enemy& e)
{
	start.x = e.ex;
	start.y = e.ey;
}
//怪物终止位置定为人物所在位置
void GetEnd(Character c)
{
	End.x = c.cx;
	End.y = c.cy;
}
//怪物前往人物位置，即追击函数
void Goto(Enemy& e, Character c)
{
	GetStart(e);
	GetEnd(c);
	astar(e, c);
}