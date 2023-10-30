#ifndef GAMEMAP_H
#define GAMEMAP_H

#include <QObject>

enum MapElement
{
    Grass,//0
    Tree,//1
    Mushroom,//2
    Road,//3
    Shallow,//4
    Body,//5
    Left,//6
    UpLeft,//7
    UpRight,//8
    Down//9
};

class GameMap : public QObject
{
    Q_OBJECT
public:
    explicit GameMap(QObject *parent = nullptr);
    ~GameMap();

    bool InitByFile(QString fileName);
    void Clear();

    int mRow;
    int mCol;
    int** mPArr;//用于开辟二维数组地图元素

signals:

};

#endif // GAMEMAP_H
