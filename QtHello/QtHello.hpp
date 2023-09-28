#pragma once
#include<iostream>
#include <QtWidgets/QWidget>
#include<QtWidgets/qlabel.h>
#include<QtWidgets/qmessagebox.h>
#include<QtWidgets/qboxlayout.h>
#include<QtWidgets/qpushbutton.h>
#include<qevent.h>//Qkeyevent
#include<map>
#include"include/init/init.hpp"
#include"include/Defences/Defences.hpp"
#include"include/QtBattel/QtBattel.hpp"
#include "ui_QtHello.h"

class QtHello : public QWidget
{
    Q_OBJECT
protected:
    void keyPressEvent(QKeyEvent* event);
public:
    QtHello(QWidget *parent = nullptr);
    bool mySetBackPicture(std::string s);
    bool mySetBackPicture();
    bool mySetPictures(std::string s,int x,int y);
    void myMessage(std::string title, std::string message);
    void setpicpaths(std::vector<RolePic>PicList);
    ~QtHello();

private:
    bool updateMan();
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
