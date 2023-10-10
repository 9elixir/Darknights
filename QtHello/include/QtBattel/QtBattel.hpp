#pragma once
#include "ui_QtHello.h"
#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include<qpushbutton.h>
#include <QCommandLinkButton>
#include<qpropertyanimation.h>
#include <QPixmap>
#include <QScrollArea>
#include <Qmovie>
#include<qscrollbar.h>
#include<qvariantanimation.h>
class SkillButton;
class ShowLabel;
class AttributeLabel;

//QtBattel是用来显示战斗界面的
class QtBattel :public QWidget {
public:
	QtBattel(QWidget* parent = nullptr, std::string BattelBackPath = "BaseImages\\battleback.jpg", std::string littleimgPath = "BaseImages\\little_head.jpg");
private:
	QPropertyAnimation* animation;
	int blood1_now = 500, blood1_max = 10000;//之后接入角色类（Defence后直接对Defence进行修改）
	QWidget* window;
	void BloodChange(QLabel* &ChangeLabel,int new_blood1_now);
	void button_clicked_new();
	QVBoxLayout* mainLayout;

	//上方的血条布局&蓝条布局
	QLabel* bloodLabel1;
	QLabel* bloodImg1;
	QLabel* bloodLabel2;
	QLabel* bloodImg2;
	QLabel* magicLabel1;
	QLabel* magicLabel2;
	//QPixmap* bloodpixmap1;
	//QPixmap* bloodpixmap2;
	// 中间二分之一的图片部分(人物)
	QLabel* characterLabel1;
	QLabel* characterLabel2;
	QMovie* charactermov1;
	QMovie* charactermov2;


	// 左侧四分之一的小图片
	QLabel* smallImageLabel;
	// 中间二分之一的按钮布局

	SkillButton* button1;
	SkillButton* button2;
	SkillButton* button3;
	SkillButton* button4;



	// 右侧四分之一的标签布局
	//QVBoxLayout* labelLayout;
	ShowLabel* label;
	/*
	ShowLabel* label1;
	ShowLabel* label2;
	ShowLabel* label3;
	ShowLabel* label4;
	*/
	QScrollArea* scrollArea;

	//判断战斗是否结束
	bool if_fight_over = false;
};
//MyLabel是用来显示战斗信息的
class ShowLabel :public QLabel
{
	Q_OBJECT

public	slots:
	void button_clicked();

public:
	ShowLabel(QWidget* parent = nullptr);
	ShowLabel(const QString& text, QWidget* parent = nullptr);
	void setText(const QString& discription);
	void setNext(ShowLabel* next);
	void wrap(bool b = true,int last_count=0); //换行
	void setbutton(SkillButton* b);
	void readinskill(SkillButton* skill);
	void setFont_height(int FONT_HEIGHT);
	void setMyWidth(int WIDTH);
	void setMyHeight(int Height);
	/*完成链表的插入、获取等基本操作
	void ListInsert(ShowLabel* m,int index);
	void ListAppend(ShowLabel* m);
	ShowLabel* getNext();
	ShowLabel* ListGet(int index);
	void ListDelete(int index);
	void ListClear();
	*/
	~ShowLabel();
private:
	const int swidth = 50;
	const int nwidth = 1;
	const int cwidth = 2;
	int width = 420;
	int height = 70;
	int contents_rows = 1;
	int font_height=30;
	
	int originx = 1020;
	int originy = 610;
	int Length = 0;//记录当前label的长度
	bool if_use_button = false;



	QString cname = "主角名", ename = "敌人名", sname = "技能名";
	QString hurt = QString("114514");
	QString discription;
	QString show = "";
	ShowLabel* next;
	SkillButton* button;//用来接收技能按钮的
};
//AttributeLabel是用来显示属性的
class AttributeLabel :public QLabel
{

};
//SkillButton是用来显示技能信息的
class SkillButton :public QCommandLinkButton
{
	Q_OBJECT
public:
	SkillButton(QWidget* parent = nullptr);
	SkillButton(const QString& text, const QString& text2, QWidget* parent = nullptr);
	void setSkillName(const QString& name);
	void setSkillHurt(const int& hurt);
	void setSkillAttribute(const QString& attribute);
	void setSkillCost(const int& cost);
	void setSkillType(const QString& type);
	void setSkillLevel(const QString& level);
	void setSkillRange(const QString& range);
	void setSkillEffect(const QString& effect);
	QString getSkillName();
	QString getSkillAttribute();
	QString getSkillType();
	QString getSkillRange();
	QString getSkillEffect();
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
	QString skilleffect;

};

void setlabelframe(QLabel* q, bool t = true);