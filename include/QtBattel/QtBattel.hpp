#ifndef QTBATTEL_HPP
#define QTBATTEL_HPP


#include "../Defences/Defences.hpp"
#include"../Enemy/Enemy.hpp"
#include <QtWidgets/qapplication.h>
#include <QtWidgets/qwidget.h>
#include"../../ui_Qtgame.h"
#include<qurl.h>
#include<qmediaplayer.h>
#include<QtMultimedia/qaudiooutput.h>
#include<QtWidgets/qlabel.h>
#include<QtWidgets/qmessagebox.h>
#include<QtWidgets/qboxlayout.h>
#include<QtWidgets/qpushbutton.h>
#include<qtimer.h>

#include<qpainter.h>
#include<qevent.h>//Qkeyevent

#include <QtWidgets/qgridlayout.h>
#include<QtWidgets/qcommandlinkbutton.h>
#include<qpropertyanimation.h>
#include<qpixmap.h>
#include<QtWidgets/qscrollarea.h>
#include"qmovie.h"
#include<qscrollbar.h>
#include<qvariantanimation.h>





class QtHello;
//SkillButton技能按钮
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
//MyLabel显示标签
class ShowLabel :public QLabel
{
    Q_OBJECT

public	slots:
    void button_clicked();
    void enemyturn();
public:
    void setdefence(int D);
    void setattack(int A);
    ShowLabel(QWidget* parent = nullptr);
    ShowLabel(const QString& text, QWidget* parent = nullptr);
    void setbutton(SkillButton* s);
    void setcname(const QString& cname);
    void setename(const QString& ename);
    void setText(const QString& discription);
    void setNext(ShowLabel* next);
    void wrap(bool b = true, int last_count = 0); //自动换行
    int getsize();//获取大小
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
    int Length = 0;//??????label?????
    bool if_use_button = false;
    int attack;
    int defence;
    QString cname = "重岳", ename = "Tom", sname = "撕扯";
    QString hurt = QString("114514");
    QString discription = "";
    QString show = "";
    QString skilleffect = "null";

    ShowLabel* next;
    SkillButton* button = nullptr;

};

//QtBattel战斗界面
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

    QtBattle(QWidget* parent = nullptr, Defences* HelloCharacter=nullptr,Enemy* Helloenemy=nullptr,std::string BattelBackPath = "BaseImages\\battleback.jpg", std::string littleimgPath = "BaseImages\\little_head.jpg");
    //初始化
    void setdefence(Defences* defence);
    void setEnemy(Enemy* enemy);
    void setFather(QtHello* father);//QtHello界面
    void BloodChange(QLabel*& ChangeLabel, int now, int max);
private:
    int music_id;
    QMediaPlayer* player;
    QAudioOutput* audio;
    QtHello* father_window;
    QPropertyAnimation* animation;//动画演出
    bool if_my_turn = true;//判断是否为我方回合
    int blood1_now = 1000, blood1_max = 1000;//我方血量
    int blood2_now = 10070, blood2_max = 10070;//敌人血量
    int magic1_now = 300, magic1_max = 300;
    int magic2_now = 300, magic2_max = 300;
    QWidget* window;
    Defences* defence;//这玩意别删!是别的窗口传进来的!
    Enemy* enemy;
    //血条蓝条
    QLabel* bloodLabel1;
    QLabel* bloodImg1;
    QLabel* bloodLabel2;
    QLabel* bloodImg2;
    QLabel* magicLabel1;
    QLabel* magicImg1;
    QLabel* magicLabel2;
    QLabel* magicImg2;
    QLabel*BaseImg;
    // 角色动画
    QLabel* characterLabel1;
    QLabel* characterLabel2;
    QMovie* charactermov1;
    QMovie* charactermov2;


    // 人物动画
    QLabel* smallImageLabel;
//技能
    SkillButton* button1;
    SkillButton* button2;
    SkillButton* button3;
    SkillButton* button4;

    //战斗信息
    ShowLabel* label;
    QScrollArea* scrollArea;
    int exp_caculate();
   //回合机制
    int turn_num;
    QLabel* turnLabel;
    void EnemyLogic();
    void turnIn();
    void turnBegin();
    void turnEnd();
    bool if_fight_over = false;
    void checkwin();
};
#endif

