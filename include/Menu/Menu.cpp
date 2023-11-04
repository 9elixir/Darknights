
#include"Menu.hpp"

#include"../../QtHello.hpp"
class QtHello;
void Menu::keyPressEvent(QKeyEvent* event) {//监听按键

    if (event->key() == Qt::Key_Escape)
    {
        qDebug()<<"quit";
        this->qthello->show();
        this->qthello->check_alive(1);
    }
}
void Menu::windowquit(){

    //window->setAttribute(Qt::WA_DeleteOnClose);
    //window->close();
    this->qthello->show();//主窗口隐藏的话视为不活跃，必须先活跃，否则整个程序寄了
    //还是不行。换方法
   this->setAttribute(Qt::WA_DeleteOnClose,true);
   this->close();
    //this->deleteLater();
}
Menu::Menu(QWidget* parent,QtHello* father,QSize size){
    // 创建左侧的 QLabel 显示图片
      qDebug()<<"in menu";
   this->setWindowFlags(Qt::WindowMinimizeButtonHint);
    this->qthello=father;

    this->setFixedSize(size);
      leftLabel = new QLabel(this);

    this->leftLabel->setFixedSize(this->width()/2,this->height());
    QPixmap characpix=QPixmap("imgs\\Chongyue\\ChongYue.png").scaled(this->leftLabel->size());
    this->leftLabel->setPixmap(characpix);
    this->leftLabel->move(0,0);

    qDebug()<<"menusize::"<<leftLabel->size();
    // 创建右侧的 QLabel 显示文字
    QFont font;
    font.setPointSize(16); // 设置字体大小为 16
    std::string labelTexts[] = {"hp:", "mp:", "攻击力:", "防御力:", "经验:","等级:"};
    std::string str[6];


    str[5]="";
    str[5]=std::to_string(father->getman()->getLevel());

    str[0]="";
    str[0]=std::to_string(father->getman()->getHp())+"/"+std::to_string(father->getman()->getHpMax());

    str[1]="";
    str[1]=std::to_string(father->getman()->getMp())+"/"+std::to_string(father->getman()->getMpMax());

    str[2]="";
    str[2]=std::to_string(father->getman()->getAttack());

    str[3]="";
    str[3]=std::to_string(father->getman()->getDefence());

    str[4]="";
    str[4]=std::to_string(father->getman()->getNowExp())+"/"+std::to_string(father->getman()->getLevelup_Exp());

    this->rightBase=new QLabel(this);
    this->rightBase->setFixedSize(this->leftLabel->size());
    this->rightBase->move(this->width()/2,0);
    QPixmap basepix=QPixmap("imgs\\tabimg.png").scaled(this->rightBase->size());
    this->rightBase->setPixmap(basepix);

    //this->rightLabels=new QLabel[5];
    this->rightLabel0=new QLabel(this);
    this->rightLabel1=new QLabel(this);
    this->rightLabel2=new QLabel(this);
    this->rightLabel3=new QLabel(this);
    this->rightLabel4=new QLabel(this);
    this->rightLabel5=new QLabel(this);

    //for(int i=0;i<5;i++)
        //(rightLabels+i)->setParent(this);


    /*for (int i=0;i<5;i++)
    {
        std::string ShowContent=labelTexts[i] + str[i];
        //QLabel* label = new QLabel(this);
        (rightLabels+i)->setText(QString(ShowContent.data()));
        (rightLabels+i)->setFont(font);
        (rightLabels+i)->setFixedSize(this->width()/2-50,this->height()/8);
        (rightLabels+i)->move(this->width()/2+25,(this->height()/8+20)*i+50);
    }*/
    std::string tempstr;

    tempstr=labelTexts[5]+str[5];
    this->rightLabel5->setText(QString(tempstr.data()));
    this->rightLabel5->setFont(font);
    this->rightLabel5->setFixedSize(this->width()/2-50,this->height()/8);
    this->rightLabel5->move(this->width()/2+25,(this->height()/8+20)*0+20);


    tempstr=labelTexts[0]+str[0];
    this->rightLabel0->setText(QString(tempstr.data()));
    this->rightLabel0->setFont(font);
    this->rightLabel0->setFixedSize(this->width()/2-50,this->height()/8);
    this->rightLabel0->move(this->width()/2+25,(this->height()/8+20)*1+20);


    tempstr=labelTexts[1]+str[1];
    this->rightLabel1->setText(QString(tempstr.data()));
    this->rightLabel1->setFont(font);
    this->rightLabel1->setFixedSize(this->width()/2-50,this->height()/8);
    this->rightLabel1->move(this->width()/2+25,(this->height()/8+20)*2+20);


    tempstr=labelTexts[2]+str[2];
    this->rightLabel2->setText(QString(tempstr.data()));
    this->rightLabel2->setFont(font);
    this->rightLabel2->setFixedSize(this->width()/2-50,this->height()/8);
    this->rightLabel2->move(this->width()/2+25,(this->height()/8+20)*3+20);

    tempstr=labelTexts[3]+str[3];
    this->rightLabel3->setText(QString(tempstr.data()));
    this->rightLabel3->setFont(font);
    this->rightLabel3->setFixedSize(this->width()/2-50,this->height()/8);
    this->rightLabel3->move(this->width()/2+25,(this->height()/8+20)*4+20);

    tempstr=labelTexts[4]+str[4];
    this->rightLabel4->setText(QString(tempstr.data()));
    this->rightLabel4->setFont(font);
    this->rightLabel4->setFixedSize(this->width()/2-50,this->height()/8);
    this->rightLabel4->move(this->width()/2+25,(this->height()/8+20)*5+20);



    this->show();
}
