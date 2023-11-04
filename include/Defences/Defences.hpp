#include"../init/init.hpp"
//skill is used for write skill information
struct Skill {
    int cost;
    int hurt;
    QString name;
    void setname(QString name);
    void gecontent(Skill* s);
};
class Defences {
public:
    int getHp();
    int getHpMax();
    int getMp();
    int getMpMax();
    int getAttack();
    int getDefence();

    int getLevel();
    int getNowExp();
    int getLevelup_Exp();
    void setMap(Mapmsg*MAP);
    Defences();
    Defences(int PERSON_ID, int PICTYPE, int SHOWIDNOW, int X, int Y, int Health_INIT, int ATTACK_INIT, int Defence_INIT);//设置角色ID,初始/当前的地图X、Y坐标，体力初始值，攻击力，防御力，默认体力初始值为最大体力上限
    void setHp(int Hp);
    void setMp(int Mp);
    bool addExp(int Exp);
    void setlevel(int Lv);
    void setdetail();
    bool levelup();
    ~Defences();
    void Defence_Move(int delta_x, int delta_y);
    void ChangePic(int PERSON_ID, int PICTYPE, int SHOWIDNOW);
    int person_id;
    int picType;
    int show_id_now;
    int getlevel();
    void get_x_and_y(int& X, int& Y);
    void setskill(Skill* s, int index1);
    void setname(QString name);
    QString getname();
    Skill* getskill(int index);
private:
    int level;
    int now_exp;
    int levelup_exp;
    Mapmsg* map;
    bool default_check(int x, int y);
    bool map_check(int x, int y);
    int map_x, map_y;
    QString defences_name;
    int Health, Attack, Defent;//当前的体力、攻击力、防御力
    int Magic;//当前魔力值
    int Health_max,Magic_max;//体力最大值,魔力最大值
    std::vector<int>Status;
    Skill* skill1;
    Skill* skill2;
    Skill* skill3;
    Skill* skill4;
};
