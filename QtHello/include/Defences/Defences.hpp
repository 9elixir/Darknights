#include <iostream>
#include<vector>
class Defences {
public:
    Defences(int PERSON_ID, int PICTYPE, int SHOWIDNOW, int X, int Y, int Health_INIT, int ATTACK_INIT, int Defence_INIT);//设置角色ID,初始/当前的地图X、Y坐标，体力初始值，攻击力，防御力，默认体力初始值为最大体力上限
    void Defence_Move(int delta_x, int delta_y);
    void ChangePic(int PERSON_ID, int PICTYPE, int SHOWIDNOW);
    int person_id;
    int picType;
    int show_id_now;
    void get_x_and_y(int& X, int& Y);
private:
    bool default_check(int x, int y);
    int map_x, map_y;

    int Health, Attack, Defent;//当前的体力、攻击力、防御力
    int Health_max;//体力最大值
    std::vector<int>Status;
};