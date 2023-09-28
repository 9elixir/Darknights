#include<iostream>
#include<fstream>
#include<cstdio>
#include<string>
#include<cstring>
#include<vector>
using namespace std;
struct PicMsg {
	int Pic_type;
	std::vector<std::string>pic_paths;
};
struct RolePic {
	int RoleID;
	std::vector<PicMsg>PicList;
};
class init {
public:
	std::vector<RolePic>RolesPicList;
	//RolesPicList[i]->RolePic;RolePic->RunPicList and StandPicList and AttackPicList ……;xxxPicList->pic_path1 and pic_path2 and pic_path3 ……;
	void checkPicList();
	init(std::string imgs_path_txt);
private:
	int lastRoleID = -1, lastPicType = -1;
	bool read_success;
	bool debug = true;
	bool getEachMsg(int& intRoleID, int& intPicType, string& strPicPath, const string EachMsg);
	void dealwithEachMsg(int& intRoleID, int& intPicType, string& strPicPath);
	void getPersontxt(std::string paths_txt);
};