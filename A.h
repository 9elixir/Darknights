#pragma once
#include <stdio.h>  
#include <stdlib.h>  
#include"Enemy.h"
#include"Character.h"
#include"move.h"
//A*�㷨�����Լ������׷�����ʱ���·��
#define MAX_X 100  // Map�������  
#define MAX_Y 100  // Map����󳤶�  
#define MAX_OBSTACLES 100  // ����ϰ�����  
#define MAX_PATH_LENGTH 100  // ���·������  
#define MOVE_COST 1  // �ƶ�һ����λ�Ĵ���  
#define OBSTACLE_COST 1000  // �����ϰ���ĳͷ�  

typedef struct
{
    double x;
    double y;
    double cost;  // �����ľ���  
    long long parent_index;  // ��·���У��õ�ĸ��ڵ���±�  
} Node;

Node map[MAX_X][MAX_Y];  // ����ͼ��ÿ������һ��x,y���ꡢһ��costֵ��һ��parent_indexֵ  
int obstacle_list[MAX_OBSTACLES][2];  // �ϰ����б�ÿ���ϰ����������Ͻǵ�x,y�����ʾ  
Node start;  // �����յ�
Node End;
long long path[MAX_PATH_LENGTH];  // ���������������·��  
int path_length = 0;  // ��ǰ���·���ĳ���  

// �����پ�����㺯��������A*�㷨������ʽ����  
double manhattan_distance(Node* node1, Node* node2)
{
    double dx = fabs(node1->x - node2->x);
    double dy = fabs(node1->y - node2->y);
    return dx + dy;
}

//distance����
double distanceA(double x1, double y1, double x2, double y2)
{
    double dx = fabs(x1 - x2);
    double dy = fabs(y1 - y2);
    return dx + dy;
}

//�����ھ�dxdy��ʾ
int dx[8] = { -1,0,1,-1,1,-1,1,0 };
int dy[8] = { -1,-1,-1,0,0,1,1,1 };

// A*��������  
void astar(Enemy& e,Character c)
{
//    start.x = end.x = 0;
//    start.y = end.y = 0;
    start.cost = 0;
    End.cost = INT_MAX;
    memset(map, 0x3f, sizeof(map));  // �����е��cost��ʼ��Ϊһ�����ֵ  

    Node* current = &start;
    while (1)
    {
        // �ڵ�ǰ�ڵ���ھ���Ѱ����һ���ڵ�  
        for (int i = 0; i < 8; i++)
        {
            int next_x = (int)(current->x + dx[i]);
            int next_y = (int)(current->y + dy[i]);
            if (next_x >= 0 && next_x < MAX_X && next_y >= 0 && next_y < MAX_Y) // ����ھ��ڵ�ͼ��Χ�� 
            { 
                Node* next = &map[next_x][next_y];
                double g = current->cost + distanceA(current->x, current->y, next_x, next_y);  // �������㵽�õ��ʵ�ʾ���  
                if (g < next->cost)  // ����ҵ�һ�����̵�·�������¸õ��costֵ��parent_indexֵ 
                {
                    next->cost = g;
                    next->parent_index = current - *map;
                }
                else if (g == next->cost)  // ����ҵ�һ����ͬ���ȵ�·�������뵽��ѡ·����
                {  
                    path[path_length++] = next - *map;
                }
            }
        }
        move(e, c.cx, c.cy, path_length / e.speed);//�����ƶ���ȥ
        if (current == &End) break;  // ��������յ㣬��������  
        current = map[current->parent_index];  // ���ݵ���һ���ڵ㣬��������  
    }
}