#pragma once
#include <stdio.h>  
#include <stdlib.h>  
#include"Enemy.h"
#include"Character.h"
#include"move.h"
//A*算法，用以计算怪物追击玩家时最短路径
#define MAX_X 100  // Map的最大宽度  
#define MAX_Y 100  // Map的最大长度  
#define MAX_OBSTACLES 100  // 最大障碍物数  
#define MAX_PATH_LENGTH 100  // 最大路径长度  
#define MOVE_COST 1  // 移动一个单位的代价  
#define OBSTACLE_COST 1000  // 遇到障碍物的惩罚  

typedef struct
{
    double x;
    double y;
    double cost;  // 到起点的距离  
    long long parent_index;  // 在路径中，该点的父节点的下标  
} Node;

Node map[MAX_X][MAX_Y];  // 地形图，每个点有一个x,y坐标、一个cost值和一个parent_index值  
int obstacle_list[MAX_OBSTACLES][2];  // 障碍物列表，每个障碍物由其左上角的x,y坐标表示  
Node start;  // 起点和终点
Node End;
long long path[MAX_PATH_LENGTH];  // 保存搜索到的最短路径  
int path_length = 0;  // 当前最短路径的长度  

// 曼哈顿距离计算函数，用于A*算法的启发式函数  
double manhattan_distance(Node* node1, Node* node2)
{
    double dx = fabs(node1->x - node2->x);
    double dy = fabs(node1->y - node2->y);
    return dx + dy;
}

//distance函数
double distanceA(double x1, double y1, double x2, double y2)
{
    double dx = fabs(x1 - x2);
    double dy = fabs(y1 - y2);
    return dx + dy;
}

//相邻邻居dxdy表示
int dx[8] = { -1,0,1,-1,1,-1,1,0 };
int dy[8] = { -1,-1,-1,0,0,1,1,1 };

// A*搜索函数  
void astar(Enemy& e,Character c)
{
//    start.x = end.x = 0;
//    start.y = end.y = 0;
    start.cost = 0;
    End.cost = INT_MAX;
    memset(map, 0x3f, sizeof(map));  // 将所有点的cost初始化为一个大的值  

    Node* current = &start;
    while (1)
    {
        // 在当前节点的邻居中寻找下一个节点  
        for (int i = 0; i < 8; i++)
        {
            int next_x = (int)(current->x + dx[i]);
            int next_y = (int)(current->y + dy[i]);
            if (next_x >= 0 && next_x < MAX_X && next_y >= 0 && next_y < MAX_Y) // 如果邻居在地图范围内 
            { 
                Node* next = &map[next_x][next_y];
                double g = current->cost + distanceA(current->x, current->y, next_x, next_y);  // 计算从起点到该点的实际距离  
                if (g < next->cost)  // 如果找到一条更短的路径，更新该点的cost值和parent_index值 
                {
                    next->cost = g;
                    next->parent_index = current - *map;
                }
                else if (g == next->cost)  // 如果找到一条相同长度的路径，加入到备选路径中
                {  
                    path[path_length++] = next - *map;
                }
            }
        }
        move(e, c.cx, c.cy, path_length / e.speed);//怪物移动过去
        if (current == &End) break;  // 如果到达终点，结束搜索  
        current = map[current->parent_index];  // 回溯到上一个节点，继续搜索  
    }
}