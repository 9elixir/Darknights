#pragma once

#include <QMainWindow>
#include "ui_QtWidgetsClass.h"

class QtWidgetsClass : public QMainWindow
{
	Q_OBJECT

public:
	QtWidgetsClass(QWidget *parent = nullptr);
	~QtWidgetsClass();

private:
	Ui::QtWidgetsClassClass ui;
};
