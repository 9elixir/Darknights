
#include "QtHello.hpp"
#include <QtWidgets/QApplication>
//测试git
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QtHello w;
    //注意,(x,y)是原点在左上角
    init myinit=init("hello_world.txt");
    myinit.setMaptool("maptools.txt");//必须先获得tool
    myinit.setMap("maptxt\\Map.txt", "maptxt\\MapAttribute.txt");
    
    w.setpicpaths(myinit.RolesPicList);
    w.setMaptools(myinit.maptool);
    w.setMap(myinit.map);
    //w.mySetBackPicture("F:\\C++编程\\QtHello\\imgs\\b331ecd651b2c8650852c965ca65b4de.jpeg");
    w.buildmap();
    w.show();

    //label图片显示，需要1、设置父亲 2、设置pixmap以及pixmap的大小 3、设置fixedsize 4、move 5、show（）
    return a.exec();
}

/*
//测试文件输入
#include<iostream>
#include"include/init/init.hpp"

int main() {
    std::string picpath = "hello_world.txt";
   init mine(picpath);
    mine.setMaptool("maptools.txt");
   mine.setMap("maptxt\\Map.txt", "maptxt\\MapAttribute.txt");
    cout << "hello\n";
    mine.~init();
    return 0;
}
*/

/*

对Gif不能正常结束的测试：
结论：正常的mp4、avi等播放结束后，确实会产生Movie::finished。但是，Gif被qt6要求自动循环播放，因此没有自动触发finished
方案：使用frameChanged信号，根据当前播放帧来判断是否到达结尾，并触发事件。

#include <QApplication>
#include <QLabel>
#include <QMovie>



int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    // 创建QMovie对象并加载GIF文件
    QMovie movie("imgs//Tom.gif");

    // 创建QLabel用于显示动画
    QLabel label;
    label.setMovie(&movie);

    // 启动动画
    movie.start();
    // 连接finished信号到animationFinished函数
    QObject::connect(&movie, &QMovie::frameChanged, [&movie]() {
        if (movie.currentFrameNumber() == movie.frameCount() - 1) {
            qDebug() << "Animation finished";
            movie.stop();
        }
        });

    // 设置窗口属性和显示
    label.setWindowTitle("GIF Animation");
    label.show();

    return app.exec();
}*/

/*
//测试退出
#include "QtHello.hpp"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
    //注意,(x,y)是原点在左上角
    init myinit = init("hello_world.txt");
    QApplication a(argc, argv);
    QtHello w;
    w.setpicpaths(myinit.RolesPicList);
    QPushButton* quitButton = new QPushButton("Quit", &w);
    QObject::connect(quitButton, &QPushButton::clicked, [&w]() {
        w.setAttribute(Qt::WA_DeleteOnClose);
        w.close();
        QApplication::quit();
        
        });
    //w.mySetBackPicture("F:\\C++编程\\QtHello\\imgs\\b331ecd651b2c8650852c965ca65b4de.jpeg");
    w.show();

    //label图片显示，需要1、设置父亲 2、设置pixmap以及pixmap的大小 3、设置fixedsize 4、move 5、show（）
    return a.exec();
}*/