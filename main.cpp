
#include"include/QtWelcome/QtWelcome.hpp"
#include<QDir>
//测试git
void CDBACK(QString target){
    QString currentPath = QDir::currentPath();
    qDebug()<<"currentPath="<<currentPath;
    // 定义目标文件夹名称
    QString targetFolderName = target;

    // 检查当前路径下是否存在目标文件夹
    QDir targetFolder(currentPath);
    if (targetFolder.exists(targetFolderName)) {
        // 目标文件夹存在，切换到目标文件夹
        QString targetFolderPath = targetFolder.absoluteFilePath(targetFolderName);
        if (QDir::setCurrent(targetFolderPath)) {
            qDebug() << "Successfully switched to target folder:" << targetFolderPath;
        } else {
            qDebug() << "Failed to switch to target folder:" << targetFolderPath;
        }
    } else {
        // 目标文件夹不存在，不断向上级目录切换，直到根目录

        if (targetFolder.isRoot()) {
            qDebug() << "Target folder not found in the parent directories.";
        }else{
            targetFolder.cdUp();
            QDir::setCurrent(targetFolder.absolutePath());
            CDBACK(target);
        }
}
    return ;
}

int main(int argc, char *argv[])
{//加入开始界面 加入等级、升级机制 加入bgm 实装战斗载入人物与机制 导入战斗的攻击力、防御力机制
  //加入tab键 查看状态
    CDBACK(QString("QtHello"));//vs和qt执行路径不同

    //注意,(x,y)是原点在左上角
    //注意指针悬空问题。
    QApplication a(argc, argv);
    /*    init myinit=init("hello_world.txt");
    myinit.setMaptool("maptools.txt");//必须先获得tool
    myinit.setMap("maptxt\\Map.txt", "maptxt\\MapAttribute.txt");
QtHello w;
    w.setpicpaths(myinit.RolesPicList);
    w.setMaptools(myinit.maptool);
    w.setMap(myinit.map);
    //w.mySetBackPicture("F:\\C++编程\\QtHello\\imgs\\b331ecd651b2c8650852c965ca65b4de.jpeg");
    w.buildmap();
    w.show();*/

    //label图片显示，需要1、设置父亲 2、设置pixmap以及pixmap的大小 3、设置fixedsize 4、move 5、show（）
    QtWelcome* welcome = new QtWelcome(nullptr);
    welcome->show();
    return a.exec();
}


/*
//注意头文件格式
#include <QtWidgets/qapplication.h>
#include <QtWidgets/qwidget.h>
#include "ui_Qtgame.h"

#include<QtWidgets/qlabel.h>
#include<QtWidgets/qmessagebox.h>
#include<QtWidgets/qboxlayout.h>
#include<QtWidgets/qpushbutton.h>
#include<qtimer.h>

#include<qpainter.h>
#include<qevent.h>//Qkeyevent

#include <QtWidgets/qgridlayout.h>
#include<QtWidgets/qcommandlinkbutton.h>
#include<qpropertyanimation.h>
#include<qpixmap.h>
#include<QtWidgets/qscrollarea.h>
#include"qmovie.h"
#include<qscrollbar.h>
#include<qvariantanimation.h>
#include<qstring.h>
//#include <QtWidgets/qapplication.h>
//#include <QtWidgets/qwidget.h>

//#include "yourmainwindow.h" // 包含您的主窗口头文件

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    // 创建您的主窗口对象
    QWidget mainWindow(nullptr);
    mainWindow.show();

    // 启动应用程序事件循环
    return app.exec();
}*/
/*
#include<iostream>
using namespace std;
int main(int argc, char* argv[]) {
    return 0;
}*/
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
