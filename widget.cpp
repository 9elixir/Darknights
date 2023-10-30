#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QPainter>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //初始化地图元素
    mPMap=new GameMap(this);

    QString fileName =":/Map/Map.txt";
    mPMap->InitByFile(fileName);

    mMapPainter = new QPainter(this);//创建画家

    setFixedSize(900,900);//固定窗口大小
}

Widget::~Widget()
{
    delete ui;
}

void Widget::DrawMap()
{
    for(int i=0;i< mPMap->mRow;i++)
    {
        for(int j=0;j< mPMap->mCol;j++)
        {
            QString imgUrl;
            switch(mPMap->mPArr[i][j])
            {
                case Road: imgUrl= ":/img/road.png";break;
                case Grass: imgUrl=":/img/grass.png";break;
                case Tree: imgUrl=":/img/Tree.png";break;
                case Body: imgUrl=":/img/waterBody.png";break;
                case Shallow: imgUrl=":/img/shallowGrass.png";break;
                case UpLeft: imgUrl= ":/img/waterEdgeUpLeft.png";break;
                case UpRight: imgUrl= ":/img/waterEdgeUpRight.png";break;
                case Down: imgUrl= ":/img/waterEdgeDown.png";break;
                case Mushroom: imgUrl= ":/img/mushroom.png";break;
                case Left: imgUrl= ":/img/waterEdgeLeft.png";break;
            }
                QImage img(imgUrl);
            mMapPainter->drawImage(QRect(j*img.width(),i*img.height(),img.width(),img.height()),img);
        }
    }
}
void Widget::paintEvent(QPaintEvent *event)
{
    mMapPainter->begin(this);//设置画布

    //画地图
    DrawMap();

    mMapPainter->end();//结束
}
