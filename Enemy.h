#pragma once
#include<stdio.h>
#include<QApplication>
#include<QMovie>
#include<QLabel>
//怪物类
class Enemy
{
public:
	double ex{ 0 };//位置坐标x
	double ey{ 0 };//位置坐标y
	double sight{ 1 };//怪物视野范围
	double speed{ 1 };//怪物速度
	QLabel emove;
	QLabel eset;
	QLabel edie;
	//怪物构造函数，依次设定初始坐标xy值，视野范围，速度
	Enemy(double ex, double ey, double sight, double speed)
	{
		this->ex = ex;
		this->ey = ey;
		this->sight = sight;
		this->speed = speed;
	}
	//怪物移动图像设置
	void emoveshow(QMovie &emovemovie,int chang,int kuan)
	{
		emovemovie.resized(QSize(chang, kuan));
		emove.setMovie(&emovemovie);
		emove.show();
		emovemovie.start();
	}
	//怪物攻击图像设置
	void eattackshow(QMovie &esetmovie,int chang,int kuan)
	{
		esetmovie.resized(QSize(chang, kuan));
		emove.setMovie(&esetmovie);
		emove.show();
		esetmovie.start();
	}
	//怪物死亡图像设置
	void edieshow(QMovie &ediemovie,int chang,int kuan)
	{
		ediemovie.resized(QSize(chang, kuan));
		emove.setMovie(&ediemovie);
		emove.show();
		ediemovie.start();
	}
};