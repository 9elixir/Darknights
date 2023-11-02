#include"init.hpp"
init::~init() {
	RolesPicList.clear();
	map.MapMartix.clear();
	maptool.tools.clear();
}
bool init::getEachMaptoolmsg(int& Pic_type, string& mappicPath, const string EachMsg) {
	if (EachMsg.length() < 2||EachMsg[0] == '#')return false;
	int i;
	bool ok[3];
	for (i = 0; i < 3; i++)ok[i] = false;
	for (i = 0; i < EachMsg.size(); i++)
	{
		if (EachMsg[i] == '(') {
			ok[0] = true;
			break;
		}
		//strPicType = strPicType + EachMsg[i];
		Pic_type = Pic_type * 10 + EachMsg[i] - '0';
	}


	for (i=i+1; i < EachMsg.size(); i++) {
		if (EachMsg[i] == ':') {
			ok[1] = true;
			break;
		}
	}
	mappicPath = "";
	for (i = i + 1; i < EachMsg.size(); i++)
		mappicPath = mappicPath + EachMsg[i];
	if (mappicPath.size() > 4)
	{
		string strJudge;
		for (int j = mappicPath.size() - 4; j < mappicPath.size(); j++)strJudge = strJudge + mappicPath[j];
		if (strJudge == ".png")
			ok[2] = true;
	}


	bool final_ok = true;
	for (int j = 0; j < 3; j++)final_ok &= ok[j];

	return final_ok;
}
bool init::getEachMapMsg(bool work_type,int line,string EachMsg) {
	if (EachMsg.length() < 2 || EachMsg[0] == '#')return false;
	vector<int>v;
	int value = 0;
	std::string EachMsg2 = EachMsg + ',';
	for (int i = 0; i < EachMsg2.length(); i++) {
		if ('0' <= EachMsg2[i] && EachMsg2[i] <= '9')
		{
			value = value * 10 + EachMsg2[i] - '0';
		}
		else {
			v.push_back(value);
			value = 0;
		}
	}
	if (work_type == 0) {
		vector<Mappic>temp(v.size());
		for (int i = 0; i < temp.size(); i++) {
			temp[i]= this->maptool.tools[v[i]];
		}
		this->map.MapMartix.push_back(temp);
	}
	if (work_type == 1) {
		for (int i = 0; i < v.size(); i++)
			this->map.MapMartix[line][i].touch_type = v[i];
	}
	return true;
}
bool init::getEachMsg(int& intRoleID, int& intPicType, string& strPicPath, string EachMsg) {
	if (EachMsg.length() < 2||EachMsg[0] == '#')return false;
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
	inputs.open(Persontxt);

	RolesPicList.clear();
	if (inputs.is_open()) {
		this->read_success = true;
		string EachMsg="";
		while (std::getline(inputs, EachMsg,'\n')) {
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
	inputs.close();
	if (!this->read_success) {
		cout << "the txt file " << Persontxt << "has not been readed!\n";
	}
	if (this->debug) {

		checkPicList();
	}

}
init::init(std::string Persons_txt) {
	this->lastPicType = -1, this->lastRoleID = -1;
	if (this->debug)cout << "Persons_txt=" << Persons_txt << "\n";
	this->getPersontxt(Persons_txt);
	if (this->debug)cout << "init done\n";
}
void init::checkMap() {
	vector<vector<Mappic> >list=this->map.MapMartix;
	cout << "rows:" << this->map.rows<<",cols:"<<this->map.cols<<"\n";
	cout << "heightpix:" << this->map.heightpix << ",widthpix:" << this->map.widthpix << "\n";
	cout << "viewrows:" << this->map.viewrows << ",viewcols:" << this->map.viewcols<<"\n";
	for (vector<Mappic>eachline:list) {
		for (Mappic eachcol : eachline) {
			cout << eachcol.Pic_type;
			cout << "(" << eachcol.touch_type << ") ";
		}
		cout << "\n";
	}
}
void init::checkMaptoollist() {
	vector<Mappic>tools=this->maptool.tools;
	cout << "the maptools.size()=" << this->maptool.tools.size() << "\n\n";
	for (Mappic eachpic : tools) {
		cout << "new_mappic_id:" << eachpic.Pic_type<< ":\n";
		cout << "\tthe pic_type is:" << eachpic.Pic_type;
		cout << "\tthe touch level is:" << eachpic.touch_type << "\n\tpath is:"<<eachpic.path;
	}
	cout << "\n";
}
bool init::setMaptool(std::string maptool_path) {
	ifstream inputs;
	inputs.open(maptool_path, ios::in);

	maptool.tools.clear();
	if (inputs.is_open()) {
		this->read_maptool_success = true;
		string EachMsg;
		while (getline(inputs, EachMsg,'\n')) {
			std::string strMappicPath = "";
			int intPictype = 0, intTouchtype = 0;
			std::cout << "EachMsg=" << EachMsg << "\n";
			bool boolTruestr = this->getEachMaptoolmsg(intPictype, strMappicPath, EachMsg);
			if (!boolTruestr)continue;
			Mappic temp;
			temp.path = strMappicPath, temp.touch_type = intTouchtype, temp.Pic_type = intPictype;
			maptool.tools.push_back(temp);
			//std::string strRoleID,strPicType;
			
		}
	}
	else this->read_maptool_success = false;
	inputs.close();
	if (!this->read_maptool_success) {
		cout << "the txt file " << maptool_path << "has not been readed!\n";
		return false;
	}
	if (this->debug) {

		checkMaptoollist();
	}
	return true;
}
bool init::setMap(std::string map_path,std::string touch_path) {
	if (!this->read_maptool_success) {
		cout << "we must get the maptool then get the map!\n";
		return false;
	}
	ifstream inputs;
	inputs.open(map_path, ios::in);
	this->map.MapMartix.clear();
	if (inputs.is_open()) {
		this->read_map = true;
		string EachMsg;
		while (getline(inputs, EachMsg,'\n')) {
			std::cout << "EachMsg=" << EachMsg << "\n";
			bool boolTruestr = this->getEachMapMsg(0,0,EachMsg);
			if (!boolTruestr)continue;
			//std::string strRoleID,strPicType;

		}
	}
	else this->read_map = false;
	inputs.close();
	if (!this->read_map) {
		cout << "the txt file " << map_path << "has not been readed!\n";
		return false;
	}
	 
	ifstream inputs2;
	inputs2.open(touch_path, ios::in);
	if (inputs2.is_open()) {
		this->read_touch = true;
		string EachMsg;
		int countline = 0;
		while (getline(inputs2, EachMsg,'\n')) {
			
			std::cout << "EachMsg=" << EachMsg << "\n";
			bool boolTruestr = this->getEachMapMsg(1,countline,EachMsg);
			if (!boolTruestr)continue;
			countline++;
			//std::string strRoleID,strPicType;

		}
	}
	else this->read_touch = false;
	inputs2.close();
	if (!this->read_touch) {
		cout << "the txt file " << touch_path << "has not been readed!\n";
	
		return false;
	}

	this->map.rows = this->map.MapMartix.size();
	this->map.cols = this->map.MapMartix[0].size();
	this->map.heightpix = 30, this->map.widthpix = 30;
	this->map.viewrows = this->map.rows/2, this->map.viewcols = this->map.cols/2;
	//this->map.viewrows = this->map.rows, this->map.viewcols = this->map.cols;
	if (this->debug) {
		checkMaptoollist();
		checkMap();
	}

	return true;
}