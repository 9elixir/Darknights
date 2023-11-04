#ifndef ENEMY_H
#define ENEMY_H

#include"Dijk.hpp"
#include"../init/init.hpp"
#include<stack>

#include <QElapsedTimer>
class QtHello;
class Enemy
{
private:
    int state;//0为消失了 1为(x1,y1)巡逻 2为向(x2,y2)巡逻 3为向主角急速奔跑 4为正在战斗中
    int x1,y1,x2,y2;//注意！这是像素！
    bool working;
    bool map_check(int x, int y);
    int map_x, map_y;//这是该角色的左下角的那个像素块的左上角的坐标
    int level;
    QString defences_name;
    int Health, Attack, Defent;//当前的体力、攻击力、防御力
    int Magic;//当前魔力值
    int Health_max,Magic_max;//体力最大值,魔力最大值
    int size_x,size_y;
    int toward;//1 朝下 2左 3右 4上
    int WalkPace,RunPace;
    QtHello* qthello;
    Dijk* dijk;
   // PATH posmap;
public:
    void setFather(QtHello* hello);
    bool eye_contact(int Cx,int Cy);
    int getstate();
    int getHp();
    int getHpMax();
    int getMp();
    int getMpMax();
    int getAttack();
    int getDefence();
    bool getworking();
    int getlevel();
    void setsize(int x,int y);
    void setstate(int index);
    void setworking(bool a);
    void setHp(int Hp);
    void setMp(int Mp);
    void setlevel(int Lv);
    void setdetail();
    void set_x1_and_y1(int X1,int Y1);
    void set_x2_and_y2(int X2,int Y2);
    void state_action(int index,int Cx,int Cy);
    void setWalKPace(int pace);
    void setRunPace(int pace);
    void Defence_Move(int delta_x, int delta_y);
    void ChangePic(int PERSON_ID, int PICTYPE, int SHOWIDNOW);
    int person_id;
    int picType;
    int show_id_now;

    //bool samePos(int Cx,int Cy);
    void get_x_and_y(int& X, int& Y);
    void setname(QString name);
    QString getname();
    Enemy(int x,int y,Mapmsg* map);
};

#endif // ENEMY_H
