#include"init.hpp"
bool init::getEachMsg(int& intRoleID, int& intPicType, string& strPicPath, string EachMsg) {
	int i;
	bool ok[4];
	for (i = 0; i < 4; i++)ok[i] = false;


	for (i = 0; i < EachMsg.size(); i++) {
		if (EachMsg[i] == '_') {
			ok[0] = true;
			break;
		}
		//strRoleID = strRoleID + EachMsg[i];
		intRoleID = intRoleID * 10 + EachMsg[i] - '0';
	}

	for (i = i + 1; i < EachMsg.size(); i++)
	{
		if (EachMsg[i] == '(') {
			ok[1] = true;
			break;
		}
		//strPicType = strPicType + EachMsg[i];
		intPicType = intPicType * 10 + EachMsg[i] - '0';
	}


	for (; i < EachMsg.size(); i++) {
		if (EachMsg[i] == ':') {
			ok[2] = true;
			break;
		}
	}

	for (i = i + 1; i < EachMsg.size(); i++)
		strPicPath = strPicPath + EachMsg[i];
	if (strPicPath.size() > 4)
	{
		string strJudge;
		for (int j = strPicPath.size() - 4; j < strPicPath.size(); j++)strJudge = strJudge + strPicPath[j];
		if (strJudge == ".png")
			ok[3] = true;
	}


	bool final_ok = true;
	for (int j = 0; j < 4; j++)final_ok &= ok[j];

	return final_ok;

}
void init::dealwithEachMsg(int& intRoleID, int& intPicType, string& strPicPath) {
	RolePic rolepic;
	PicMsg picmsg;
	if (this->lastRoleID == intRoleID) {
		this->RolesPicList[intRoleID].RoleID = intRoleID;
		if (this->lastPicType == intPicType) {
			this->RolesPicList[intRoleID].PicList[intPicType].Pic_type = intPicType;
			this->RolesPicList[intRoleID].PicList[intPicType].pic_paths.push_back(strPicPath);
		}
		else {
			picmsg.Pic_type = intPicType;
			picmsg.pic_paths.push_back(strPicPath);
			this->RolesPicList[intRoleID].PicList.push_back(picmsg);
		}
	}
	else {
		picmsg.Pic_type = intPicType;
		picmsg.pic_paths.push_back(strPicPath);

		rolepic.RoleID = intRoleID;
		rolepic.PicList.push_back(picmsg);
		this->RolesPicList.push_back(rolepic);
	}


	/*if (this->lastRoleID == intRoleID) {

		if (this->lastPicType == intPicType) {
			picmsg.pic_paths.push_back(strPicPath);
		}
		else {
			rolepic.PicList.push_back(picmsg);
			picmsg.Pic_type = intPicType;
			picmsg.pic_paths.clear();
			picmsg.pic_paths.push_back(strPicPath);
		}
	}
	else {
		if (this->lastRoleID != -1)
		{
			rolepic.PicList.push_back(picmsg);
			this->RolesPicList.push_back(rolepic);
		}
		rolepic.RoleID = intRoleID;
		rolepic.PicList.clear();

		picmsg.Pic_type = intPicType;
		picmsg.pic_paths.clear();
		picmsg.pic_paths.push_back(strPicPath);
	}*/
	lastRoleID = intRoleID;
	lastPicType = intPicType;
}
void init::checkPicList() {
	//cout << "the txt file " << Persontxt << " has been read:\n\n";
	cout << "the rolespiclist.size()=" << this->RolesPicList.size() << "\n\n";
	for (RolePic eachrole : RolesPicList) {
		cout << "new_id:" << eachrole.RoleID << ":\n";
		for (PicMsg eachpicmsg : eachrole.PicList) {
			cout << "\t new_pic_type:" << eachpicmsg.Pic_type << ":\n";
			for (std::string eachpicpath : eachpicmsg.pic_paths) {
				cout << "\t \t new_pic_path:" << eachpicpath << '\n';
			}
		}
	}
}
void init::getPersontxt(string Persontxt) {
	ifstream inputs;
	inputs.open(Persontxt, ios::in);


	if (inputs.is_open()) {
		this->read_success = true;
		string EachMsg;
		while (getline(inputs, EachMsg)) {
			std::string strPicPath = "";
			int intRoleID = 0, intPicType = 0;
			std::cout << "EachMsg=" << EachMsg << "\n";
			bool boolTruestr = this->getEachMsg(intRoleID, intPicType, strPicPath, EachMsg);
			if (!boolTruestr)continue;
			//std::string strRoleID,strPicType;
			dealwithEachMsg(intRoleID, intPicType, strPicPath);
		}
	}
	else this->read_success = false;
	if (!this->read_success) {
		cout << "the txt file " << Persontxt << "has not been readed!\n";
	}
	if (this->debug) {

		checkPicList();
	}

}
init::init(std::string Persons_txt) {
	this->lastPicType = -1, this->lastRoleID = -1;
	this->getPersontxt(Persons_txt);
}