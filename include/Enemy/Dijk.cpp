#include "Dijk.hpp"

void Dijk::Dijkstra(int s){
    this->newPATHS.PRE.clear();
    this->newPATHS.PRE=vector<int>(this->copymap.cols*this->copymap.rows);
    this->newPATHS.size=this->copymap.cols*this->copymap.rows;
    for(int i=0;i<newPATHS.PRE.size();i++){
        newPATHS.PRE[i]=-1;
    }
    vector<bool>vis(this->copymap.cols*this->copymap.rows);
    vector<int>dis(this->copymap.cols*this->copymap.rows);
    for(int i=0;i<dis.size();i++)
        dis[i]=-1;
    for(int i=0;i<vis.size();i++)
        vis[i]=false;
    dis[s]=0;
    priority_queue<Dijknode>q;

    Dijknode temp1,temp2;
    temp1.id=s;
    temp1.val=0;
    q.push(temp1);
    int move[4][2]={{0,-1},{0,1},{-1,0},{1,0}};
    while(!q.empty()){
        temp1=q.top();
        q.pop();
        int u=temp1.id;
        if(vis[u])continue;
        vis[u]=true;
        for(int i=0;i<4;i++){
            int dx=move[i][0],dy=move[i][1];
            int nx=u%this->copymap.cols,ny=u/this->copymap.cols;//左上角坐标轴
          // qDebug()<<"In Calculating::nx="<<nx<<",ny="<<ny;
            nx=nx+dx,ny=ny+dy;
            if(nx<0||ny<0||nx>=this->copymap.cols||ny>=this->copymap.rows)continue;
            if(this->copymap.Martix[ny][nx]!=0&&this->copymap.Martix[ny][nx]!=1)continue;
            if(dis[ny*this->copymap.cols+nx]==-1||dis[u]+1<dis[ny*this->copymap.cols+nx]){
                dis[ny*this->copymap.cols+nx]=dis[u]+1;
                this->newPATHS.PRE[ny*this->copymap.cols+nx]=u;
                temp2.id=ny*this->copymap.cols+nx;
                temp2.val=dis[ny*this->copymap.cols+nx];
                q.push(temp2);
            }
        }
    }

    return;
}
void Dijk::setmap(Mapmsg* map){
    //若敌人可悬浮，则0 1都可走。若为地面，则只有0可走
    this->copymap.Martix.clear();
    this->newPATHS.PRE.clear();
    this->copymap.cols=map->cols;
    this->copymap.rows=map->rows;

    this->copymap.heightpix=map->heightpix;
    this->copymap.widthpix=map->widthpix;
    for(int i=0;i<copymap.rows;i++)
    {
        vector<int>q(copymap.cols);
        copymap.Martix.push_back(q);
        for(int j=0;j<copymap.cols;j++)
            copymap.Martix[i][j]=map->MapMartix[i][j].touch_type;
    }
}
PATH Dijk::calculatemap(int x,int y){
   // qDebug()<<"Dijk::calculatemap:x="<<x<<",y="<<y;
    int id=y*copymap.cols+x;
   // qDebug()<<"and in the dijk,id="<<id;
    this->Dijkstra(id);
    return this->newPATHS;
}
Dijk::~Dijk(){
    this->copymap.Martix.clear();
    this->newPATHS.PRE.clear();
}
Dijk::Dijk(Mapmsg* map)
{
    this->setmap(map);
    //this->calculatemap();
}
