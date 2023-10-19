#pragma once
#include"A.h"
#include"Enemy.h"
#include"Character.h"
void GetStart(Enemy& e)
{
	start.x = e.ex;
	start.y = e.ey;
}
void GetEnd(Character c)
{
	end.x = c.cx;
	end.y = c.cy;
}
void Goto(Enemy& e, Character c)
{
	GetStart(e);
	GetEnd(c);
	astar(e, c);
}