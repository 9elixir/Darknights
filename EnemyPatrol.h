#pragma once
#include"Enemy.h"
#include"move.h"
//距离计算
double distance(double x1, double y1, double x2, double y2)
{
	double dx = x1 - x2;
	double dy = y1 - y2;
	double distance = sqrt(dx * dx + dy * dy);
	return distance;
}
//怪物巡逻函数，依次设定巡逻怪物，怪物起始地xy值，结束地xy值
void patrol(Enemy& e, double ex1, double ey1, double ex2, double ey2)
{
	e.ex = ex1;
	e.ey = ey1;
	double d = distance(ex1, ey1, ex2, ey2);
	double time = d / e.speed;
	while (1)
	{
		move(e, ex2, ey2, time);
		Sleep(1000);
		move(e, ex1, ey2, time);
		Sleep(1000);
	}
}