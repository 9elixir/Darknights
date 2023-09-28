#include "QtHello.hpp"
#include <QtWidgets/QApplication>


int main(int argc, char *argv[])
{
    //注意,(x,y)是原点在左上角
    init myinit=init("hello_world.txt");
    QApplication a(argc, argv);
    QtHello w;
    w.setpicpaths(myinit.RolesPicList);
    //w.mySetBackPicture("F:\\C++编程\\QtHello\\imgs\\b331ecd651b2c8650852c965ca65b4de.jpeg");
    w.show();
    return a.exec();
}
