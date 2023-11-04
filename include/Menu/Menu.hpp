#ifndef MENU_HPP
#define MENU_HPP
#include<QWidget>
#include<QLabel>
#include<qevent.h>
class QtHello;
class Menu: public QWidget
{
 // Q_OBJECT
protected:
    void keyPressEvent(QKeyEvent* event);
public:
    Menu(QWidget* parent,QtHello* father=nullptr,QSize size=QSize(768,512));
    void windowquit();
  //  void setWindowSize(int width, int height);

private:
    QtHello* qthello;
    //QLabel* rightLabels;//为什么是new的数组就不行
    //由于new的数组销毁形式和其他的不太一样，所以一定要批量的话，可以用QList<组件>widgetlist代替，然后for循环new单个新的组件，
    //并append
    //之后在windowquit里qDeleAll(widgetlist),并widgetlist.clear()
    QLabel* rightLabel0,*rightLabel1,*rightLabel2,*rightLabel3,*rightLabel4,*rightLabel5;
    QLabel* rightBase;
    QLabel* leftLabel;
};
#endif // MENU_HPP
