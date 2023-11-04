#include "Defences.hpp"

int Defences::getHp(){
    return this->Health;
}
int Defences::getHpMax(){
    return this->Health_max;
}
int Defences::getMp(){
    return this->Magic;
}
int Defences::getMpMax(){
    return this->Magic_max;
}
int Defences::getAttack(){
    return this->Attack;
}
int Defences::getDefence(){
    return this->Defent;
}
void Defences::setHp(int Hp){
    this->Health=Hp;
}
void Defences::setMp(int Mp){
    this->Magic=Mp;
}
int Defences::getLevel(){
    return this->level;
}
int Defences::getNowExp(){
    return this->now_exp;
}
int Defences::getLevelup_Exp(){
    return this->levelup_exp;
}
void Defences::setdetail(){
    //this->level=Lv;
    this->Health_max=this->level*100+500;//体力最大值为100倍Lv+500
    this->Magic_max=this->level*80+100;//魔力最大值为80倍Lv+100
    this->Attack=this->level*20+800;//攻击力为20倍lv+800
    this->Defent=this->level*10+200;//防御力为10倍Lv+200;


    this->levelup_exp=this->level*50+20;//升级经验值为50倍等级加20


    this->Magic=this->Magic_max;//还是加上吧
    this->Health=this->Health_max;
}
void Defences::setlevel(int Lv){
    this->level=Lv;
    this->setdetail();
    this->now_exp=0;//经验值清空
}
bool Defences::addExp(int Exp){
    this->now_exp+=Exp;
    return this->levelup();
}
bool Defences::levelup(){
    bool tag=false;
    while(this->now_exp>=this->levelup_exp){//允许连续升级
        tag=true;
        this->now_exp-=this->levelup_exp;
        this->level++;
        this->setdetail();

        this->Magic=this->Magic_max;//升级福利
        this->Health=this->Health_max;
    }
    return tag;
}
void Skill::setname(QString name) {
	this->name = name;
}
void Skill::gecontent(Skill* s) {

    cout<<"注意：该函数(Skill::gecontent(Skill* s)) 函数已失效\n";
    this->name = s->name;
	this->cost = s->cost;
	this->hurt = s->hurt;
    //该代码已废弃

}
void Defences::setMap(Mapmsg*MAP) {
	this->map = MAP;
}
Defences::Defences() {
	this->person_id = 0;
	this->picType = 0;
	this->show_id_now = 0;
	this->map_x = 0;
	this->map_y = 0;
	this->Health_max = this->Health = 0;
	this->Attack = 0;
	this->Defent = 0;
    /*Skill* nulls = new Skill{
		0,0,"--"
	};

	this->setskill(nulls, 1);
	this->setskill(nulls, 2);
	this->setskill(nulls, 3);
    this->setskill(nulls, 4);*/
}
Defences::Defences(int PERSON_ID, int PICTYPE, int SHOWIDNOW, int X, int Y, int Health_INIT, int ATTACK_INIT, int Defence_INIT) {
	this->person_id = PERSON_ID;
	this->show_id_now = SHOWIDNOW;
	this->picType = PICTYPE;
	this->map_x = X;
	this->map_y = Y;


	this->Health_max = this->Health = Health_INIT;
	this->Attack = ATTACK_INIT;
	this->Defent = Defence_INIT;
/*
 我们将技能设置分出去了
	Skill* nulls = new Skill{
		0,0,"--"
	};
	this->setskill(nulls, 1);
	this->setskill(nulls, 2);
	this->setskill(nulls, 3);
    this->setskill(nulls, 4);*/
}
Defences::~Defences() {
	delete this->skill1;
	delete this->skill2;
	delete this->skill3;
	delete this->skill4;
}
bool Defences::default_check(int x, int y) {
	if (1 <= x && x <= 520 && 1 <= y && y <= 360)
		return true;
	return false;
}
int Defences::getlevel(){
    cout<<"this time our exp="<<this->now_exp<<",and we still need "<<this->levelup_exp-this->now_exp<<" exp\n";
    return this->level;
}
bool Defences::map_check(int x, int y) {
	if (!(this->map)) {
		cout << "defence not load the map!\n";
		return false;
	}
	int widthpix = this->map->widthpix, heightpix = this->map->heightpix;
	int width = this->map->cols * widthpix, height = this->map->rows * heightpix;

	if (x<0||x+widthpix>width||y<0||y+heightpix>height)
        return false;
    int nx=x/this->map->widthpix,ny=y/this->map->heightpix;
    if (this->map->MapMartix[ny][nx].touch_type!=0)return false;
	return true;
}
void Defences::ChangePic(int PERSON_ID, int PICTYPE, int SHOWIDNOW) {
	this->person_id = PERSON_ID;
	this->picType = PICTYPE;
	this->show_id_now = SHOWIDNOW;
}
void Defences::Defence_Move(int deltax, int deltay) {
	//int init_map_x=this->map_x, init_map_y=this->map_y;
	//需要特殊判断地图边界，仍在制作中

	if (map_check(this->map_x+deltax,this->map_y+deltay)==true) 
	//if (default_check(this->map_x + deltax, this->map_y + deltay))
	{
		this->map_x += deltax;
		this->map_y += deltay;
		return;
	}

}
void Defences::get_x_and_y(int& X, int& Y) {
	X = this->map_x;
	Y = this->map_y;
	return;
}
void Defences::setskill(Skill* s, int index) {
    std::cout<<"请注意，Defence::setskill(Skill* s,int index)所传入的指针应该是new的\n";
    switch (index) {
	case 1:
        if(this->skill1)
        {
            delete this->skill1;
            this->skill1=nullptr;//避免悬挂
            }
        this->skill1=s;
		break;
	case 2:
        if(this->skill2){
            delete this->skill2;
            this->skill2=nullptr;
        }
        this->skill2=s;
		break;
	case 3:
        if(this->skill3){
            delete this->skill3;
            this->skill3=nullptr;
        }
        this->skill3=s;
		break;
	case 4:
        if(this->skill4){
            delete this->skill4;
            this->skill4=nullptr;
        }
        this->skill4=s;
		break;
	default:
		std::cout << "error" << std::endl;
		break;
	}

}
void Defences::setname(QString name) {
	this->defences_name = name;
}
QString Defences::getname() {
	return this->defences_name;
}
Skill* Defences::getskill(int index) {
	switch (index) {
	case 1:
		return this->skill1;
		break;
	case 2:
		return this->skill2;
		break;
	case 3:
		return this->skill3;
		break;
	case 4:
		return this->skill4;
		break;
	default:
		std::cout << "error" << std::endl;
		break;
	}
    return nullptr;
}
