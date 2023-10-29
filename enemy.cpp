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
//Move函数，依次设定相应的怪物，角色，怪物起始巡逻xy值，怪物终止巡逻xy值，怪物移动图，图长，宽
void Move(Enemy& e, Character c, double ex1, double ey1, double ex2, double ey2,QMovie &emovemovie,int chang,int kuan)
{
	e.emoveshow(emovemovie,chang,kuan);
	if (distance(e.ex, e.ey, c.cx, c.cy) > e.sight)
	{
		patrol(e, ex1, ey1, ex2, ey2);
	}
	else
	{
		Goto(e, c);
	}
}
int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	
	Enemy paxingzhe(100, 100, 1, 1);//创建enemy paxingzhe,数据依次为初始x，y，视野大小，速度
	QMovie ep1("C:/Users/123/Desktop/cailiao/paxingzhe/富营养的爬行者-默认-战斗-Move-x1.gif");//导入爬行者运动时gif图
	paxingzhe.emoveshow(ep1,2,3);//设定爬行者战斗外巡逻的状态，用enemy.cpp中Move函数
	QMovie ep2("C:/Users/123/Desktop/cailiao/paxingzhe/富营养的爬行者-默认-战斗-Idle-x1.gif");//导入爬行者战斗时gif图
	//if()进行战斗时条件判断，进入战斗切换为战斗时图
	paxingzhe.eattackshow(ep2, 2, 3);//爬行者战斗时图
	QMovie ep3("C:/Users/123/Desktop/cailiao/paxingzhe/富营养的爬行者-默认-战斗-Die-x1.gif");//导入爬行者死亡gif图
	paxingzhe.edieshow(ep3, 2, 3);//爬行者战斗死亡时图
	
	Enemy huadianfeng(100, 100, 1, 1);//创建enemy huadianfeng, 数据依次为初始x，y，视野大小，速度
	QMovie eh1("C:/Users/123/Desktop/cailiao/huadianfeng/富营养的收割者-默认-战斗-Move-x1.gif");//导入花癫疯运动时gif图
	huadianfeng.emoveshow(eh1, 2, 3); //设定花癫疯战斗外巡逻的状态，用enemy.cpp中Move函数
	//if()进行战斗时条件判断，进入战斗切换为战斗时图
	QMovie eh2("C:/Users/123/Desktop/cailiao/huadianfeng/富营养的收割者-默认-战斗-Skill_Attack-x1.gif");//导入花癫疯战斗时gif图
	huadianfeng.eattackshow(eh2, 2, 3);//花癫疯战斗时图
	QMovie eh3("C:/Users/123/Desktop/cailiao/huadianfeng/富营养的收割者-默认-战斗-Die-x1.gif");//导入花癫疯死亡gif图
	huadianfeng.edieshow(eh3, 2, 3);//花癫疯战斗死亡时图

	Enemy haimo(100, 100, 1, 1);//创建enemy haimo, 数据依次为初始x，y，视野大小，速度
	QMovie eH1("C:/Users/123/Desktop/cailiao/haimo/“偏执泡影”-默认-战斗-C1_Move-x1.gif");//导入海沫运动时gif图
	haimo.emoveshow(eH1, 2, 3);//设定海沫战斗外巡逻的状态，用enemy.cpp中Move函数
	//if()进行战斗时条件判断，进入战斗切换为战斗时图
	QMovie eH2("C:/Users/123/Desktop/cailiao/haimo/“偏执泡影”-默认-战斗-C1_Attack-x1.gif");//导入海沫战斗时gif图
	haimo.eattackshow(eH2, 2, 3);//海沫战斗时图
	QMovie eH3("C:/Users/123/Desktop/cailiao/haimo/“偏执泡影”-默认-战斗-C1_Die-x1.gif");//导入海沫死亡gif图
	haimo.edieshow(eH3, 2, 3);//海沫战斗死亡时图
	return app.exec();
}