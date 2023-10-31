﻿#include "QtHello.hpp"
void QtHello::setMaptools(transmap tools) {
    this->tools = tools;
}
void QtHello::setMap(Mapmsg map) {
    this->map = map;
}
void QtHello::buildmap() {
    Mapmsg MAP = this->map;
    int width = MAP.cols, height = MAP.rows;
  

    // 计算目标 QImage 的大小
 
    // 创建目标 QImage
    QImage targetImage(width*MAP.widthpix, height*MAP.heightpix, QImage::Format_ARGB32);
    targetImage.fill(Qt::transparent);
    QPainter painter(&targetImage);
    for (int i = 0; i < height;i++) {
        for (int j = 0; j < width; j++) {
   
            QPixmap pixmap1(MAP.MapMartix[i][j].path.data());
            if (pixmap1.isNull()) {
                cout << "wrong build mappix!\n"; continue;
            }
            QPixmap temp = pixmap1.scaled(MAP.widthpix,MAP.heightpix);
       

            // 将 QPixmap 拷贝到目标 QImage
          
            painter.drawPixmap(j* MAP.widthpix, i* MAP.heightpix, temp);

      

            // 保存拼接后的 QImage
            //targetImage.save("result.png");

        }
    }
    QPixmap result;
    result=QPixmap::fromImage(targetImage);//返回类型为Qpixmap
    qDebug() << result;
    //targetImage.save("map.png");
    this->setFixedSize(width * MAP.widthpix, height * MAP.heightpix);
    this->BackPicture_Label->setFixedSize(width * MAP.widthpix, height * MAP.heightpix);
    this->BackPicture_Label->setParent(this);
    this->BackPicture_Label->setPixmap(result);
    this->BackPicture_Label->move(0, 0);
    this->BackPicture_Label->setScaledContents(true);
    this->BackPicture_Label->show();
}
void QtHello::gameover() {
   
  //  printf("hello world\n");
    if (this->my_battle) {
        this->my_battle->windowquit();
        this->my_battle = nullptr;
    } myMessage("Game Over!!!", "游戏结束，您在战斗中死亡");
 //   printf("hello world\n");
    this->windowquit();
}
void QtHello::check_alive() {
    if (this->main_alive == 1) {
        //主人公仍存活，游戏继续
        if (this->my_battle) {
            this->my_battle->windowquit();
            this->my_battle = nullptr;
        }
        this->show();

        return;
    }
    else
        if (this->main_alive == 0) {
            //主人公死亡，游戏结束
            //加载死亡界面
            gameover();
            //this->~QtHello();

        }
        else
        {
            //this->gameover();
            printf("Wrong Message! main_alive not the 0 or 1\n");
        }
}
void QtHello::windowquit() {
    myMessage(" ", "希望我们的游戏为您带来快乐");
    //QApplication::quit();
    //this->close();//报错
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->close();
    QApplication::quit();
    QTimer::singleShot(10, []() {
        QCoreApplication::quit();
        });

    //更不易异常的退出方式
}
QtHello::QtHello(QWidget* parent)
    : QWidget(parent)
{
    BackPicture_Label = new QLabel;

    BackPicture_Label->setParent(this);//new出数组
    //BackPicture_Label = new QLabel(this);
    BackPicture_layout = new QVBoxLayout;
    len = 0;

    man = nullptr;
    QLMan = nullptr;
    this->my_battle = nullptr;
    this->main_alive = 1;
    //battlebegin->setParent(this);


    ui.setupUi(this);
}
void QtHello::myMessage(std::string title, std::string message) {
    QMessageBox messageBox;
    messageBox.setWindowTitle(title.data());
    //std::string Notice = "Wrong Pic Path is:" + s;
    messageBox.setText(message.data());
    messageBox.setIcon(QMessageBox::Information);
    messageBox.addButton("yes,I have understanded", QMessageBox::AcceptRole);

    // 显示信息框
    messageBox.exec();
}
bool QtHello::mySetPictures(std::string s, int x, int y) {
    //20230919:希望不再使用指针进行声明。原因：后续需要多次添加、修改、删除窗口内各对象，如果用new指针，则不易于在后面的调用中进行这些操作。
    // 此外，函数new的指针销毁在返回时会全部销毁。
    //如何修改：目前的期望是，在类中定义map<class*,vector<>struct{vector<Label>,layout}>,使用时判断该类的指针是否存在。
    //问题：有可能一个类先被声明，然后被删除，两次的地址一样。
    //影响?:该添加的没能添加，删除的再删除尚能接受（健壮性）,修改的直接修改，似乎可以接受。
    //总结：显示内容在Class里，QT显示时读取其再显示，相当于将添加操作改为修改操作。

    //  QLabel* label = new QLabel(this);
    QLabel* label = new QLabel;
    label->setBuddy(this);//20230919：错误，无参数构造后若要绑定Widget应该用setParent


    QPixmap pixmap(s.data());//Qpix使用完可以直接销毁，但是Label、Layout不行


    if (pixmap.isNull()) {
        myMessage("mySetPictures", "pixmap is NULL!");
        //std::cout << "Wrong Pic Path!.\n"; 
        return false;
    }

    // 将图片设置为 QLabel 的内容
    label->setPixmap(pixmap);

    // 调整 QLabel 的大小以适应图片
    label->setFixedSize(this->size());
    label->setScaledContents(true);
    label->move(x, y);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(label);
    return true;
}
bool QtHello::mySetBackPicture(std::string s) {
    QLabel* label = new QLabel(this);
    QPixmap pixmap(s.data());//Qpix使用完可以直接销毁，但是Label、Layout不行
    if (pixmap.isNull()) {
        myMessage("mySetBackPicture(std::string s)", "pixmap is NULL!");

        //std::cout << "Wrong Pic Path!.\n"; 
        return false;
    }

    // 将图片设置为 QLabel 的内容
    label->setPixmap(pixmap);

    // 调整 QLabel 的大小以适应图片
    label->setFixedSize(this->size());
    label->setScaledContents(true);

    /*QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(label);*/
    //this->show();
    label->show();
    return true;
}
bool QtHello::mySetBackPicture() {
    std::string s;
    len = (len + 1) % 2;
    if (len == 1) {
        s = "imgs\\interlude_01.png";
    }
    else {
        s = "imgs\\b331ecd651b2c8650852c965ca65b4de.jpeg";
        //s = "F:\\C++编程\\QtHello\\imgs\\interlude_01.png";
    }

    QLabel* label = BackPicture_Label + 0;
    //= new QLabel(this);
    QPixmap pixmap(s.data());//Qpix使用完可以直接销毁，但是Label、Layout不行
    if (pixmap.isNull()) {
        myMessage("mySetBackPicture()", "pixmap is NULL!");
        //std::cout << "Wrong Pic Path!.\n"; 
        return false;
    }

    // 将图片设置为 QLabel 的内容
    label->setPixmap(pixmap);

    // 调整 QLabel 的大小以适应图片
    label->setFixedSize(this->size());
    label->setScaledContents(true);
    /*QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(label);*/
    return true;
}
void QtHello::keyPressEvent(QKeyEvent* event) {//监听按键
    int widthpix = this->map.widthpix, heightpix = this->map.heightpix;
    if (event->key() == Qt::Key_Space)
    {

        //myMessage("keyPressEvent", "get the Key_Space!");
        // 显示信息框
        //this->mySetBackPicture();

        //myMessage("keyPressEvent", "Creat New Man!");
        //this->buildmap();
        if (man)
        {
            qDebug()<<"man is haven and now be shutted";
            delete man;
            man = nullptr;
        }
        this->man = new Defences(0, 1, 0, 60, 60, 200, 200, 200);
        this->man->setMap(&(this->map));
        this->updateMan();
    }

    if (event->key() == Qt::Key_W) {
        if (!this->man)return;
        this->man->Defence_Move(0, -heightpix);
        if (this->man->picType == 4) {
            this->man->show_id_now++;
            this->man->show_id_now %= 4;
        }
        else {
            this->man->ChangePic(0, 4, 0);
        }
        this->updateMan();
    }
    if (event->key() == Qt::Key_S) {
        if (!this->man)return;
        this->man->Defence_Move(0, +heightpix);
        if (this->man->picType == 1) {
            this->man->show_id_now++;
            this->man->show_id_now %= 4;
        }
        else {
            this->man->ChangePic(0, 1, 0);
        }
        //this->myMessage("why not move", "why not move");
        this->updateMan();
    }
    if (event->key() == Qt::Key_A) {
        if (!this->man)return;
        this->man->Defence_Move(-widthpix, 0);
        if (this->man->picType == 2) {
            this->man->show_id_now++;
            this->man->show_id_now %= 4;
        }
        else {
            this->man->ChangePic(0, 2, 0);
        }
        this->updateMan();
    }
    if (event->key() == Qt::Key_D) {
        if (!this->man)return;
        this->man->Defence_Move(+widthpix, 0);
        if (this->man->picType == 3) {
            this->man->show_id_now++;
            this->man->show_id_now %= 4;
        }
        else {
            this->man->ChangePic(0, 3, 0);
        }
        this->updateMan();
    }
}
void QtHello::setpicpaths(std::vector<RolePic>PicList) {
    this->RolesPicList = PicList;
    QPushButton* battlebegin = new QPushButton("begin Battle!");
    battlebegin->setParent(this);
    QObject::connect(battlebegin, &QPushButton::clicked, this, &QtHello::OpenBattle);
    battlebegin->setFocusPolicy(Qt::NoFocus);//取消焦点，否则按键监听无法使用
    battlebegin->show();
    //  this->myMessage("setPiclist", "success!");
}
bool QtHello::updateMan() {
    int widthpix = this->map.widthpix, heightpix = this->map.heightpix;
    if (!QLMan)QLMan = new QLabel(this);
    cout << "this->man->person_id=" << this->man->person_id << ",this->man->picType=" << this->man->picType << ",this->man->show_id_now="<<this->man->show_id_now << "\n";
    QPixmap pixmap0((this->RolesPicList[this->man->person_id]).PicList[this->man->picType].pic_paths[this->man->show_id_now].data());//Qpix使用完可以直接销毁，但是Label、Layout不行
    QPixmap pixmap = pixmap0.scaled(widthpix,heightpix);
        if (pixmap.isNull()) {
        myMessage("updateMan", "pixmap is NULL!");

        //std::cout << "Wrong Pic Path!.\n"; 
        return false;
    }

    // 将图片设置为 QLabel 的内容
    QLMan->setPixmap(pixmap);

    // 调整 QLabel 的大小以适应图片
    QLMan->setFixedSize(pixmap.size());
    int x, y;
    man->get_x_and_y(x, y);
    QLMan->move(x, y);
    QLMan->setScaledContents(true);
    QLMan->show();
    /*QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(label);*/
    //this->show();
    return true;
}

void QtHello::OpenBattle() {
    myMessage("Open Battle", "lets Battle!");
    if (this->my_battle) { delete (this->my_battle); this->my_battle = nullptr; }
    this->my_battle = new QtBattle(this);
    this->my_battle->setFather(this);
    this->hide();
    
    //check_alive(0);
}

void QtHello::check_alive(int statu) {
    this->main_alive = statu;
    this->check_alive();
}