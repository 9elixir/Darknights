#pragma once
#include<iostream>
//#include"include/init/init.hpp" //在battle中已经引用
//#include"include/Defences/Defences.hpp" 引发了类型重定义
//#include"include/init/init.hpp"
#include "ui_QtHello.h"


#include <qobject.h>
#include <QtWidgets/QWidget>
#include<QtWidgets/qlabel.h>
#include<QtWidgets/qmessagebox.h>
#include<QtWidgets/qboxlayout.h>
#include<QtWidgets/qpushbutton.h>
#include<qtimer.h>
#include<qpainter.h>
#include<qevent.h>//Qkeyevent
#include<map>

#include <QtWidgets/QApplication>
#include<qapplication.h>
#include <QtWidgets/qgridlayout.h>
#include <QCommandLinkButton>
#include<qpropertyanimation.h>

#include <QPixmap>
#include <QScrollArea>
#include <Qmovie>
#include<qscrollbar.h>
#include<qvariantanimation.h>

#include "../Defences/Defences.hpp"

class QtHello : public QWidget
{
    Q_OBJECT
protected:
    void keyPressEvent(QKeyEvent* event);
public:
    inline QtHello(QWidget* parent = nullptr);
    void gameover();
    void check_alive();
    void check_alive(int statu);
    bool mySetBackPicture(std::string s);
    bool mySetBackPicture();
    bool mySetPictures(std::string s, int x, int y);
    void myMessage(std::string title, std::string message);
    inline void setpicpaths(std::vector<RolePic>PicList);
    inline void setMaptools(transmap tools);
    inline void setMap(Mapmsg map);
    void windowquit();
    void buildmap();
private:
    transmap tools;
    Mapmsg map;
    QtBattle* my_battle;
    int main_alive;
    bool updateView2();
    bool updateMan();
    bool updateViewMap();
    QPixmap BackPix;
    QLabel* BackPicture_Label;
    QLabel* QLMan;
    QVBoxLayout* BackPicture_layout;
    int len;
    Defences* man;
    QLabel* Pictures_Label;
    QVBoxLayout* Pictures_layout;
    Ui::QtHelloClass ui;
    std::vector<RolePic>RolesPicList;
    void OpenBattle();
};



//QtBattel是用来显示战斗界面的
class QtBattle :public QWidget {
	Q_OBJECT
public slots:
	void button1_clicked();
	void button2_clicked();
	void button3_clicked();
	void button4_clicked();
	void button_clicked_new();
public:
	void windowquit();
	QtBattle(QWidget* parent = nullptr, std::string BattelBackPath = "BaseImages\\battleback.jpg", std::string littleimgPath = "BaseImages\\little_head.jpg");
	//设置人物
	void setdefence(Defences* defence);
	void setFather(QtHello* father);//设置父窗口
	void BloodChange(QLabel*& ChangeLabel, int now, int max);
private:
	QtHello* father_window;
	QPropertyAnimation* animation;//行动动画

	bool if_my_turn = true;//判断是否是我方回合
	int blood1_now = 1000, blood1_max = 1000;//之后接入角色类（Defence后直接对Defence进行修改）
	int blood2_now = 1070, blood2_max = 1070;//之后接入敌人类（Enemy后直接对Enemy进行修改）
	int magic1_now = 300, magic1_max = 300;
	int magic2_now = 300, magic2_max = 300;
	QWidget* window;
	Defences* defence;

	//上方的血条布局&蓝条布局
	QLabel* bloodLabel1;
	QLabel* bloodImg1;
	QLabel* bloodLabel2;
	QLabel* bloodImg2;
	QLabel* magicLabel1;
	QLabel* magicImg1;
	QLabel* magicLabel2;
	QLabel* magicImg2;

	// 中间二分之一的图片部分(人物)
	QLabel* characterLabel1;
	QLabel* characterLabel2;
	QMovie* charactermov1;
	QMovie* charactermov2;


	// 左侧四分之一的小图片
	QLabel* smallImageLabel;
	// 中间二分之一的按钮布局
	//QMediaPlayer* player;
	SkillButton* button1;
	SkillButton* button2;
	SkillButton* button3;
	SkillButton* button4;

	// 右侧四分之一的标签布局

	ShowLabel* label;
	QScrollArea* scrollArea;

	//回合显示以及判断战斗是否结束
	int turn_num;
	QLabel* turnLabel;
	void turnIn();
	void turnBegin();
	void turnEnd();
	bool if_fight_over = false;
	void checkwin();
};
//MyLabel是用来显示战斗信息的
class ShowLabel :public QLabel
{
	Q_OBJECT

public	slots:
	void button_clicked();
	void enemyturn();
public:
	ShowLabel(QWidget* parent = nullptr);
	ShowLabel(const QString& text, QWidget* parent = nullptr);
	void setbutton(SkillButton* s);
	void setcname(const QString& cname);
	void setename(const QString& ename);
	void setText(const QString& discription);
	void setNext(ShowLabel* next);
	void wrap(bool b = true, int last_count = 0); //换行
	int getsize();//获得discription的大小
	void readinskill(SkillButton* skill);
	void setFont_height(int FONT_HEIGHT);
	void setMyWidth(int WIDTH);
	void setMyHeight(int Height);
	void setSkillEffect(const QString& effect);
	QString getSkillEffect();

	~ShowLabel();
private:
	const int swidth = 50;
	const int nwidth = 1;
	const int cwidth = 2;
	int width = 420;
	int height = 70;
	int contents_rows = 1;
	int font_height = 30;
	int originx = 1020;
	int originy = 610;
	int Length = 0;//记录当前label的长度
	bool if_use_button = false;
	QString cname = "主角名", ename = "敌人名", sname = "技能名";
	QString hurt = QString("114514");
	QString discription = "";
	QString show = "";
	QString skilleffect = "null";

	ShowLabel* next;
	SkillButton* button = nullptr;

};
//SkillButton是用来显示技能信息的
class SkillButton :public QCommandLinkButton
{
	Q_OBJECT

public:
	SkillButton(QWidget* parent = nullptr);
	SkillButton(const QString& text, const QString& text2, QWidget* parent = nullptr);
	SkillButton(Skill* s, QWidget* parent = nullptr);
	void setSkillName(const QString& name);
	void setSkillHurt(const int& hurt);
	void setSkillAttribute(const QString& attribute);
	void setSkillCost(const int& cost);
	void setSkillType(const QString& type);
	void setSkillLevel(const QString& level);
	void setSkillRange(const QString& range);
	QString getSkillName();
	QString getSkillAttribute();
	QString getSkillType();
	QString getSkillRange();
	int getSkillCost();
	int getSkillHurt();
	int getSkillLevel();

private:
	int skillcost;
	int skilllevel;
	int skillhurt;
	QString skillname;
	QString skillattribute;
	QString skilltype;
	QString skillrange;

signals:
	void myclicked(int i = 0);
};
void setlabelframe(QLabel* q, bool t = true);