#include "Defences.hpp"

void Skill::setname(QString name) {
	this->name = name;
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
	Skill* nulls = new Skill{
		0,0,"--"
	};
	this->setskill(nulls, 1);
	this->setskill(nulls, 2);
	this->setskill(nulls, 3);
	this->setskill(nulls, 4);
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

	Skill* nulls = new Skill{
		0,0,"--"
	};
	this->setskill(nulls, 1);
	this->setskill(nulls, 2);
	this->setskill(nulls, 3);
	this->setskill(nulls, 4);
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
void Defences::ChangePic(int PERSON_ID, int PICTYPE, int SHOWIDNOW) {
	this->person_id = PERSON_ID;
	this->picType = PICTYPE;
	this->show_id_now = SHOWIDNOW;
}
void Defences::Defence_Move(int deltax, int deltay) {
	//int init_map_x=this->map_x, init_map_y=this->map_y;
	//需要特殊判断地图边界，仍在制作中

	//if (Map.check(this->map_x+deltax,this->map_y+deltay)==true) 
	if (default_check(this->map_x + deltax, this->map_y + deltay))
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
	switch (index) {
	case 1:
		this->skill1 = s;
		break;
	case 2:
		this->skill2 = s;
		break;
	case 3:
		this->skill3 = s;
		break;
	case 4:
		this->skill4 = s;
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
	Skill* nulls = new Skill{
		0,0,"--"
	};
	return nulls;
}