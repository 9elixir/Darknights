#pragma once
#include"Enemy.h"
//移动中位置
double lerp(double start, double end, double t)
{
	return start + (end - start) * t;
}
//怪物移动
void move(Enemy& e, double x, double y, double time)
{
	double dx = x - e.ex;
	double dy = y - e.ey;
	double steps = (time * 1000) / 100.0;
	double t = 0;
	double s = e.speed / 1000 * 10;
	while (t <= steps)
	{
		e.ex = lerp(e.ex, x, t / steps);
		e.ey = lerp(e.ey, y, t / steps);
		t += s;
	}
}