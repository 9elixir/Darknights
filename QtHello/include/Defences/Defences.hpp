#include <iostream>
#include<vector>
#include<QString>
//skill is used for write skill information
struct Skill {
    int cost;
    int hurt;
    QString name;
    void setname(QString name);
};
class Defences {
public:
    Defences();
    Defences(int PERSON_ID, int PICTYPE, int SHOWIDNOW, int X, int Y, int Health_INIT, int ATTACK_INIT, int Defence_INIT);//设置角色ID,初始/当前的地图X、Y坐标，体力初始值，攻击力，防御力，默认体力初始值为最大体力上限
    ~Defences();
    void Defence_Move(int delta_x, int delta_y);
    void ChangePic(int PERSON_ID, int PICTYPE, int SHOWIDNOW);
    int person_id;
    int picType;
    int show_id_now;
    void get_x_and_y(int& X, int& Y);
    void setskill(Skill* s, int index1);
    void setname(QString name);
    QString getname();
    Skill* getskill(int index);
private:
    bool default_check(int x, int y);
    int map_x, map_y;
    QString defences_name;
    int Health, Attack, Defent;//当前的体力、攻击力、防御力
    int Health_max;//体力最大值
    std::vector<int>Status;
    Skill* skill1 = new Skill{ 0,0,"1" };
    Skill* skill2 = new Skill{ 0,0,"2" };
    Skill* skill3 = new Skill{ 0,0,"3" };
    Skill* skill4 = new Skill{ 0,0,"4" };
};