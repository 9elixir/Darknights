#ifndef DIJK_HPP
#define DIJK_HPP

#include<iostream>
#include<queue>
#include"../init/init.hpp"
#include<qwidget.h>
struct Dijkmap{
    int rows,cols;
    vector<vector<int>>Martix;
    int widthpix,heightpix;
};
struct Dijknode{
    int id;
    int val;
    bool operator<(const Dijknode& y) const {
        return val >y.val;
    }
};
struct PATH{
    int size;
    vector<int>PRE;
};
class Dijk
{
private:
    void Dijkstra(int s);
    PATH newPATHS;


    void setmap(Mapmsg* map);
public:
    Dijkmap copymap;
    Dijk(Mapmsg* map);
    PATH calculatemap(int x,int y);
    ~Dijk();
};

#endif // DIJK_HPP
