#include<stdio.h>
#include<math.h>
#include<time.h>
#include<windows.h>
#include"Enemy.h"
#include"Character.h"
#include"move.h"
#include"EnemyPatrol.h"
#include"A.h"
#include"Goto.h"
#include<QPixmap>
void Move(Enemy& e, Character c, double ex1, double ey1, double ex2, double ey2)
{
	if(distance(e.ex, e.ey, c.cx, c.cy) > e.sight)
	{
		patrol(e, ex1, ey1, ex2, ey2);
	}
	else
	{
		Goto(e, c);
	}
}