/********************************************************************************
** Form generated from reading UI file 'Qtgame.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTGAME_H
#define UI_QTGAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtHelloClass
{
public:

    void setupUi(QWidget *QtHelloClass)
    {
        if (QtHelloClass->objectName().isEmpty())
            QtHelloClass->setObjectName("QtHelloClass");
        QtHelloClass->resize(600, 400);

        retranslateUi(QtHelloClass);

        QMetaObject::connectSlotsByName(QtHelloClass);
    } // setupUi

    void retranslateUi(QWidget *QtHelloClass)
    {
        QtHelloClass->setWindowTitle(QCoreApplication::translate("QtHelloClass", "QtHello", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtHelloClass: public Ui_QtHelloClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTGAME_H
