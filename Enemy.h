#pragma once
#include<stdio.h>
#include<QApplication>
#include<QMovie>
#include<QLabel>
//������
class Enemy
{
public:
	double ex{ 0 };//λ������x
	double ey{ 0 };//λ������y
	double sight{ 1 };//������Ұ��Χ
	double speed{ 1 };//�����ٶ�
	QLabel emove;
	QLabel eset;
	QLabel edie;
	//���ﹹ�캯���������趨��ʼ����xyֵ����Ұ��Χ���ٶ�
	Enemy(double ex, double ey, double sight, double speed)
	{
		this->ex = ex;
		this->ey = ey;
		this->sight = sight;
		this->speed = speed;
	}
	//�����ƶ�ͼ������
	void emoveshow(QMovie &emovemovie,int chang,int kuan)
	{
		emovemovie.resized(QSize(chang, kuan));
		emove.setMovie(&emovemovie);
		emove.show();
		emovemovie.start();
	}
	//���﹥��ͼ������
	void eattackshow(QMovie &esetmovie,int chang,int kuan)
	{
		esetmovie.resized(QSize(chang, kuan));
		emove.setMovie(&esetmovie);
		emove.show();
		esetmovie.start();
	}
	//��������ͼ������
	void edieshow(QMovie &ediemovie,int chang,int kuan)
	{
		ediemovie.resized(QSize(chang, kuan));
		emove.setMovie(&ediemovie);
		emove.show();
		ediemovie.start();
	}
};