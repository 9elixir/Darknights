#include "gamemap.h"
#include <QFile>

GameMap::GameMap(QObject *parent)
    : QObject{parent}
{
    mRow=0;
    mCol=0;
    mPArr=nullptr;

};

GameMap::~GameMap()
{
    Clear();
}

void GameMap::Clear()
{
    if(mPArr != nullptr)
    {
        for(int i=0;i<mRow;i++)
        {
            delete[] mPArr[i];
        }
        delete[] mPArr;
    }

}

bool GameMap::InitByFile(QString fileName)
{
    QFile file(fileName);//创建文件对象
    if(!file.open(QIODevice::ReadOnly))
    {
        return false;//打开失败
    }

    //读取所有内容
    QByteArray arrAll=file.readAll();
    arrAll.replace("\r\n","\n");//替换
    QList<QByteArray> lineList =arrAll.split('\n');//分割字串
    mRow=lineList.size();//确定行
    mPArr=new int*[mRow];//开辟行

    for(int i=0;i<mRow;i++)
    {
        QList<QByteArray> colList = lineList[i].split(',');
        mCol=colList.size();//确定列
        mPArr[i]=new int[mCol];//开辟列

        for(int j=0;j<mCol;j++)
        {
            mPArr[i][j] = colList[j].toInt();
        }
    }
}
