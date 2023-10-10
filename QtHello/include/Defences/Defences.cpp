#include"Defences.hpp"
Defences::Defences(int PERSON_ID, int PICTYPE, int SHOWIDNOW, int X, int Y, int Health_INIT, int ATTACK_INIT, int Defence_INIT) {
	this->person_id = PERSON_ID;
	this->show_id_now = SHOWIDNOW;
	this->picType = PICTYPE;
	this->map_x = X;
	this->map_y = Y;


	this->Health_max = this->Health = Health_INIT;
	this->Attack = ATTACK_INIT;
	this->Defent = Defence_INIT;
}
bool Defences::default_check(int x, int y) {
	if (1 <= x && x <= 520 && 1 <= y && y <= 360)
		return true;
	return false;
}
void Defences::ChangePic(int PERSON_ID, int PICTYPE, int SHOWIDNOW) {
	this->person_id = PERSON_ID;
	this->picType = PICTYPE;
	this->show_id_now = SHOWIDNOW;
}
void Defences::Defence_Move(int deltax, int deltay) {
	//int init_map_x=this->map_x, init_map_y=this->map_y;
	//需要特殊判断地图边界，仍在制作中

	//if (Map.check(this->map_x+deltax,this->map_y+deltay)==true) 
	if (default_check(this->map_x+deltax,this->map_y+deltay))
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
