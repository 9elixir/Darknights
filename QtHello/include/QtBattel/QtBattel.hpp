#pragma once
#include "ui_QtHello.h"
#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
class QtBattel {
public:
	QtBattel(QWidget* parent ,std::string BattelBackPath="BaseImages\\battleback.jpg", std::string littleimgPath="BaseImages\\little_head.jpg");
private:

QWidget* window;

QVBoxLayout* mainLayout;


// 上方四分之三的图片部分
QLabel* imageLabel ;


// 下方四分之一的布局
QHBoxLayout* bottomLayout;
// 左侧四分之一的小图片
QLabel* smallImageLabel;
// 中间二分之一的按钮布局
QGridLayout* buttonLayout;

QPushButton* button1 ;
QPushButton* button2 ;
QPushButton* button3 ;
QPushButton* button4;


// 右侧四分之一的标签布局
QVBoxLayout* labelLayout;

QLabel* label1;
QLabel* label2;
QLabel* label3;
QLabel* label4;
};
