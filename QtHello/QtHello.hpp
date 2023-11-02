#pragma once
#include<iostream>
#include <QtWidgets/QWidget>
#include<QtWidgets/qlabel.h>
#include<QtWidgets/qmessagebox.h>
#include<QtWidgets/qboxlayout.h>
#include<QtWidgets/qpushbutton.h>
#include<qtimer.h>
#include<qpainter.h>
#include<qevent.h>//Qkeyevent
#include<map>
//#include"include/init/init.hpp" 在battle中已经引用
//#include"include/Defences/Defences.hpp" 引发了类型重定义
#include"include/QtBattel/QtBattel.hpp"
#include "ui_QtHello.h"
class QtBattle;
class QtHello : public QWidget
{
    Q_OBJECT
protected:
    void keyPressEvent(QKeyEvent* event);
public:
    QtHello(QWidget *parent = nullptr);
    void gameover();
    void check_alive();
    void check_alive(int statu);
    bool mySetBackPicture(std::string s);
    bool mySetBackPicture();
    bool mySetPictures(std::string s,int x,int y);
    void myMessage(std::string title, std::string message);
    void setpicpaths(std::vector<RolePic>PicList);
    void setMaptools(transmap tools);
    void setMap(Mapmsg map);
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
