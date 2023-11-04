#ifndef QTWELCOME_HPP
#define QTWELCOME_HPP

#include"../../QtHello.hpp"
class QtHello;
class QtWelcome : public QWidget
{
    Q_OBJECT
  
protected:
    void keyPressEvent(QKeyEvent* event);
public:
    explicit QtWelcome(QWidget *parent = nullptr);
    void check_alive();
    void check_alive(int statu);
private:
    int man_alive;
    void intoGame();
    QtHello* qthello;
    int tab_swith;
    //QVBoxLayout* switchlayout;
    QLabel* switchlabel;
    QLabel* icon;
    QLabel* backimg;

    void windowquit();
    void updateicon();
signals:

};

#endif // QTWELCOME_HPP
