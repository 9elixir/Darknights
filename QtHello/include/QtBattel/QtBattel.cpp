#include"QtBattel.hpp"
QtBattel::QtBattel(QWidget *parent, std::string BattelBackPath, std::string littleimgPath) {
    window = new QWidget(nullptr);
    window->setFixedSize(QSize(720,480));
    mainLayout = new QVBoxLayout(window);
    window->setLayout(mainLayout);

    // 上方四分之三的图片部分
    imageLabel = new QLabel;
    QPixmap image(BattelBackPath.data()); // 更换为你的图片路径
    imageLabel->setPixmap(image.scaledToHeight(window->height() * 0.75));
    imageLabel->setPixmap(image.scaledToWidth(window->width()));
    mainLayout->addWidget(imageLabel);

    // 下方四分之一的布局
    bottomLayout = new QHBoxLayout;
    mainLayout->addLayout(bottomLayout);

    // 左侧四分之一的小图片
    smallImageLabel = new QLabel;
    QPixmap smallImage(littleimgPath.data()); // 更换为你的图片路径
    smallImageLabel->setPixmap(smallImage.scaledToWidth(window->width() * 0.25));
    smallImageLabel->setPixmap(smallImage.scaledToHeight(window->height() * 0.25));
    bottomLayout->addWidget(smallImageLabel);

    // 中间二分之一的按钮布局
    buttonLayout = new QGridLayout;
    bottomLayout->addLayout(buttonLayout);

    button1 = new QPushButton("技能 1");
    button2 = new QPushButton("技能 2");
    button3 = new QPushButton("技能 3");
    button4 = new QPushButton("技能 4");
    button1->setFocusPolicy(Qt::NoFocus);//取消焦点，否则按键监听无法使用
    button2->setFocusPolicy(Qt::NoFocus);
    button3->setFocusPolicy(Qt::NoFocus);
    button4->setFocusPolicy(Qt::NoFocus);
    
    buttonLayout->addWidget(button1, 0, 0);
    buttonLayout->addWidget(button2, 0, 1);
    buttonLayout->addWidget(button3, 1, 0);
    buttonLayout->addWidget(button4, 1, 1);

    // 右侧四分之一的标签布局
    labelLayout = new QVBoxLayout;
    bottomLayout->addLayout(labelLayout);

    label1 = new QLabel("Label 1");
    label2 = new QLabel("Label 2");
    label3 = new QLabel("Label 3");
    label4 = new QLabel("Label 4");

    labelLayout->addWidget(label1);
    labelLayout->addWidget(label2);
    labelLayout->addWidget(label3);
    labelLayout->addWidget(label4);
    
    window->show();
}


