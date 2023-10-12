#include "QtHello.hpp"
#include <QtWidgets/QApplication>
//测试git

int main(int argc, char *argv[])
{
    //注意,(x,y)是原点在左上角
    init myinit=init("hello_world.txt");
    QApplication a(argc, argv);
    QtHello w;
    w.setpicpaths(myinit.RolesPicList);
    //w.mySetBackPicture("F:\\C++编程\\QtHello\\imgs\\b331ecd651b2c8650852c965ca65b4de.jpeg");
    w.show();

    //label图片显示，需要1、设置父亲 2、设置pixmap以及pixmap的大小 3、设置fixedsize 4、move 5、show（）
    return a.exec();
}

/*#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QPropertyAnimation>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QLabel label("Hello, World!");
    //label.setAlignment(Qt::AlignCenter);
    label.setFixedSize(200, 100);
    label.show();

    QPushButton button("Animate");
    button.show();

    QObject::connect(&button, &QPushButton::clicked, [&label]() {
        QSize startSize(label.size());
        QSize endSize(label.size().width() + 100, label.size().height() + 50);

        QPropertyAnimation* animation = new QPropertyAnimation(&label, "size");
        animation->setDuration(1000);  // 动画持续时间为 1000 毫秒
        animation->setStartValue(startSize);
        animation->setEndValue(endSize);
        animation->setEasingCurve(QEasingCurve::InOutQuad);  // 使用平滑的缓动曲线
        QObject::connect(animation, &QPropertyAnimation::valueChanged, [](const QVariant& value) {
            double Percent = value.toInt() / 100.0;
            qDebug() << value.toSize();
            });
        
        animation->start();
        });

    return app.exec();
}*/