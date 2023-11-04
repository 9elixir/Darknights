#ifndef INIT_HPP
#define INIT_HPP
#include<iostream>
#include<vector>
#include<map>
#include<fstream>
#include<cstdio>
#include<string>
#include<cstring>
#include<qstring.h>
using namespace std;
struct PicMsg {//每个动作的所有图片信息
	int Pic_type=-1;
	std::vector<std::string>pic_paths;
};
struct RolePic {//一个角色
	int RoleID=-1;
	std::vector<PicMsg>PicList;//该角色的所有动作
};


struct Mappic{
	int Pic_type=-1;
	int touch_type=-1;
	std::string path;
};
struct Mapmsg {
	vector<vector<Mappic> >MapMartix;
	int rows=-1, cols=-1;
	int widthpix=30, heightpix=30;
	int viewrows=-1, viewcols=-1;
};
struct transmap {
	vector<Mappic>tools;
};
class init {
public:
	std::vector<RolePic>RolesPicList;
	Mapmsg map;
	transmap maptool;
	//RolesPicList[i]->RolePic;RolePic->RunPicList and StandPicList and AttackPicList ……;xxxPicList->pic_path1 and pic_path2 and pic_path3 ……;
	void checkPicList();
	void checkMap();
	void checkMaptoollist();
	init(std::string imgs_path_txt);
	~init();
	bool setMaptool(std::string maptool_path);
	bool setMap(std::string map_path,std::string touch_path);
private:
	int lastRoleID = -1, lastPicType = -1;
	bool read_success;
	bool read_maptool_success=false;
	bool read_map, read_touch;
	bool debug = true;
	bool getEachMsg(int& intRoleID, int& intPicType, string& strPicPath, const string EachMsg);
	bool getEachMapMsg(bool work_type,int line,const string EachMsg);
	bool getEachMaptoolmsg(int&Pic_type,string&mappicPath,const string EachMsg);
	void dealwithEachMsg(int& intRoleID, int& intPicType, string& strPicPath);
	void getPersontxt(std::string paths_txt);
};
#endif
