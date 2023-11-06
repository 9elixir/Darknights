#include "Enemy.hpp"
#include "../../QtHello.hpp"
class QtHello;
void Enemy::quitloop() { loop.exec(); }
int Enemy::getHp() { return this->Health; }
int Enemy::getHpMax() { return this->Health_max; }
int Enemy::getMp() { return this->Magic; }
int Enemy::getMpMax() { return this->Magic_max; }
int Enemy::getAttack() { return this->Attack; }
int Enemy::getDefence() { return this->Defent; }
void Enemy::setHp(int Hp) { this->Health = Hp; }
void Enemy::setMp(int Mp) { this->Magic = Mp; }
int Enemy::getstate() { return this->state; }
void Enemy::set_x1_and_y1(int X1, int Y1) { // 这是像素！
  this->x1 = X1;
  this->y1 = Y1;
}
void Enemy::setWalKPace(int pace) { this->WalkPace = pace; }
void Enemy::setRunPace(int pace) { this->RunPace = pace; }

void Enemy::set_x2_and_y2(int X2, int Y2) { // 这是像素！
  this->x2 = X2;
  this->y2 = Y2;
}
bool Enemy::eye_contact(int Cx, int Cy) { // 像素
  int nx = this->map_x / this->dijk->copymap.widthpix,
      ny = this->map_y / this->dijk->copymap.heightpix;
  int tx = Cx / this->dijk->copymap.widthpix,
      ty = Cy / this->dijk->copymap.heightpix;
  if (nx == tx && ny == ty)
    return true;
  /*

 c->c->c
e->c->c->c->c->c
 c->c->c

*/
  bool vis[3][3];
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      vis[i][j] = false;
  // 1 朝下 2左 3右 4上
  if (this->toward == 1) {
    for (int t = -1; t <= 1; t++) {
      int Length;
      if (t == 0)
        Length = 5;
      else
        Length = 3;
      for (int k = 1; k <= Length; k++) {
        if (nx + t < 0 || ny + k < 0 || nx + t >= this->dijk->copymap.cols ||
            ny + k >= this->dijk->copymap.rows)
          break;
        if (this->dijk->copymap.Martix[ny + k][nx + t] != 0 &&
            this->dijk->copymap.Martix[ny + k][nx + t] != 1)
          break;
        if (nx + t == tx && ny + k == ty) {
          return true;
        }
      }
    }
  }
  if (this->toward == 4) {
    for (int t = -1; t <= 1; t++) {
      int Length;
      if (t == 0)
        Length = 5;
      else
        Length = 3;
      for (int k = 1; k <= Length; k++) {
        if (nx + t < 0 || ny - k < 0 || nx + t >= this->dijk->copymap.cols ||
            ny - k >= this->dijk->copymap.rows)
          break;
        if (this->dijk->copymap.Martix[ny - k][nx + t] != 0 &&
            this->dijk->copymap.Martix[ny - k][nx + t] != 1)
          break;
        if (nx + t == tx && ny - k == ty) {
          return true;
        }
      }
    }
  }
  if (this->toward == 2) { // 左
    for (int t = -1; t <= 1; t++) {
      int Length;
      if (t == 0)
        Length = 5;
      else
        Length = 3;
      for (int k = 1; k <= Length; k++) {
        if (nx - k < 0 || ny + t < 0 || nx - k >= this->dijk->copymap.cols ||
            ny + t >= this->dijk->copymap.rows)
          break;
        if (this->dijk->copymap.Martix[ny + t][nx - k] != 0 &&
            this->dijk->copymap.Martix[ny + t][nx - k] != 1)
          break;
        if (nx - k == tx && ny + t == ty) {
          return true;
        }
      }
    }
  }
  if (this->toward == 3) { // 朝右
    for (int t = -1; t <= 1; t++) {
      int Length;
      if (t == 0)
        Length = 5;
      else
        Length = 3;
      for (int k = 1; k <= Length; k++) {
        if (nx + k < 0 || ny + t < 0 || nx + k >= this->dijk->copymap.cols ||
            ny + t >= this->dijk->copymap.rows)
          break;
        if (this->dijk->copymap.Martix[ny + t][nx + k] != 0 &&
            this->dijk->copymap.Martix[ny + t][nx + k] != 1)
          break;
        if (nx + k == tx && ny + t == ty) {
          return true;
        }
      }
    }
  }

  return false;
}
void Enemy::setstate(int index) {
  if (0 <= index && index <= 4) {
    this->state = index;
  } else {
    std::cout << "Enemy setstate over range!\n";
  }
}
void Enemy::setFather(QtHello *hello) { this->qthello = hello; }
void Enemy::setdetail() {
  // this->level=Lv;
  this->Health_max = this->level * 60 + 2000; // 体力最大值为60倍Lv+2000
  this->Magic_max = this->level * 20 + 100;   // 魔力最大值为20倍Lv+100
  this->Attack = this->level * 20 + 200;      // 攻击力为20倍lv+200
  this->Defent = this->level * 0 + 100;       // 防御力为0倍Lv+100;

  // this->levelup_exp=this->level*50+20;//升级经验值为50倍等级加20

  this->Magic = this->Magic_max; // 还是加上吧
  this->Health = this->Health_max;
}
void Enemy::setlevel(int Lv) {
  this->level = Lv;
  this->setdetail();
}

bool Enemy::map_check(int x, int y) {
  if (!(this->dijk)) {
    cout << "defence not load the map!\n";
    return false;
  }

  int width = this->dijk->copymap.cols * this->dijk->copymap.widthpix,
      height = this->dijk->copymap.rows * this->dijk->copymap.heightpix;
  int nx = x / this->dijk->copymap.widthpix,
      ny = y / this->dijk->copymap.heightpix;
  if (x < 0 || x + this->dijk->copymap.widthpix > width || y < 0 ||
      y + this->dijk->copymap.heightpix > height)
    return false;
  if (this->dijk->copymap.Martix[ny][nx] != 0 &&
      this->dijk->copymap.Martix[ny][nx] != 1)
    return false;

  return true;
}
void Enemy::ChangePic(int PERSON_ID, int PICTYPE, int SHOWIDNOW) {
  this->person_id = PERSON_ID;
  this->picType = PICTYPE;
  this->show_id_now = SHOWIDNOW;
}
int Enemy::getlevel() {
  // cout<<"this time our exp="<<this->now_exp<<",and we still need
  // "<<this->levelup_exp-this->now_exp<<" exp\n";
  return this->level;
}
void Enemy::setworking(bool a) { this->working = a; }
void Enemy::state_action(int index, int Cx, int Cy) { // 传入像素
  // cout<<"index="<<index<<",and we are doing\n";
  // qDebug()<<"index="<<index<<",and we are doing";
  this->working = true;
  // this->working=false;
  //  return;
  if (index <= 4 && index >= 0)
    this->state = index;
  if (index == 0) {
    this->working = true;
    this->working = false;
    return;
  } else if (index == 1) {
    this->working = true;
    int nx = this->map_x, ny = this->map_y; // 像素到地图
    nx = nx / this->dijk->copymap.widthpix;
    ny = ny / this->dijk->copymap.heightpix;
    //  qDebug()<<"ready to calculate::nx"<<nx<<",ny="<<ny;
    //  qDebug()<<"try to calculate……";
    //  QElapsedTimer ftimer;
    // ftimer.start(); // 启动计时器
    PATH path = this->dijk->calculatemap(nx, ny);
    // qDebug()<<"calculate done……";
    // qint64 elapsed = ftimer.elapsed(); // 获取经过的时间（毫秒）
    //  qDebug() << "函数运行时间：" << elapsed << "毫秒";
    stack<int> q;
    int nid = ny * this->dijk->copymap.cols + nx;
    int tid =
        this->y1 / this->dijk->copymap.heightpix * this->dijk->copymap.cols +
        this->x1 / this->dijk->copymap.widthpix;
    while (tid != nid && path.PRE[tid] != -1) {
      //   qDebug()<<"tid="<<tid<<",tid_x="<<tid%this->dijk->copymap.cols<<",y="<<tid/this->dijk->copymap.cols;
      if (tid == nid)
        break;
      q.push(tid);
      tid = path.PRE[tid];
    }
    for (int i = 1; i <= this->WalkPace && !q.empty(); i++) {
      tid = q.top();
      q.pop();

      nx = this->map_x, ny = this->map_y; // 像素到地图 更新当前坐标
      nx = nx / this->dijk->copymap.widthpix;
      ny = ny / this->dijk->copymap.heightpix;

      int nnx = tid % this->dijk->copymap.cols,
          nny = tid / this->dijk->copymap.cols;
      this->Defence_Move((nnx - nx) * this->dijk->copymap.widthpix,
                         (nny - ny) *
                             this->dijk->copymap.heightpix); // 地图块到像素化
      emit this->qthello->updateenemeyfinshed();
      // emit this->qthello->updateenemey();
      loop.exec();
      if (eye_contact(Cx, Cy)) {
        qDebug() << "Eneme have Found You!";
        this->state = 3;
        break;
      }
    }

    while (!q.empty()) {
      q.pop();
    }
    if (this->state != 3) {
      nx = this->map_x, ny = this->map_y; // 像素到地图
      nx = nx / this->dijk->copymap.widthpix;
      ny = ny / this->dijk->copymap.heightpix;

      if (nx == this->x1 / this->dijk->copymap.widthpix &&
          ny == this->y1 / this->dijk->copymap.heightpix) {
        this->state = 2;
      }
    }
    this->working = false;
  } else if (index == 2) {
    this->working = true;
    int nx = this->map_x, ny = this->map_y; // 像素到地图
    nx = nx / this->dijk->copymap.widthpix;
    ny = ny / this->dijk->copymap.heightpix;
    PATH path = this->dijk->calculatemap(nx, ny);
    stack<int> q;
    int nid = ny * this->dijk->copymap.cols + nx;
    int tid =
        this->y2 / this->dijk->copymap.heightpix * this->dijk->copymap.cols +
        this->x2 / this->dijk->copymap.widthpix;
    while (tid != nid && path.PRE[tid] != -1) {
      if (tid == nid)
        break;
      q.push(tid);
      tid = path.PRE[tid];
    }
    for (int i = 1; i <= this->WalkPace && !q.empty(); i++) {
      tid = q.top();
      q.pop();

      nx = this->map_x, ny = this->map_y; // 像素到地图
      nx = nx / this->dijk->copymap.widthpix;
      ny = ny / this->dijk->copymap.heightpix;

      int nnx = tid % this->dijk->copymap.cols,
          nny = tid / this->dijk->copymap.cols;
      this->Defence_Move((nnx - nx) * this->dijk->copymap.widthpix,
                         (nny - ny) *
                             this->dijk->copymap.heightpix); // 地图块到像素化
      emit this->qthello->updateenemeyfinshed();
      loop.exec();
      if (eye_contact(Cx, Cy)) {
        std::cout << "Eneme have Found You!\n";
        this->state = 3;
        break;
      }
    }
    while (!q.empty()) {
      q.pop();
    }
    if (this->state != 3) {
      nx = this->map_x, ny = this->map_y; // 像素到地图
      nx = nx / this->dijk->copymap.widthpix;
      ny = ny / this->dijk->copymap.heightpix;

      if (nx == this->x2 / this->dijk->copymap.widthpix &&
          ny == this->y2 / this->dijk->copymap.heightpix) {
        this->state = 1;
      }
    }
    this->working = false;
  } else if (index == 3) {
    this->working = true;
    int nx = this->map_x, ny = this->map_y;
    nx = nx / this->dijk->copymap.widthpix;
    ny = ny / this->dijk->copymap.heightpix; // 从像素到地图块
    PATH path = this->dijk->calculatemap(nx, ny);
    stack<int> q;
    int nid = ny * this->dijk->copymap.cols + nx;
    int ccx = Cx / this->dijk->copymap.widthpix;
    int ccy = Cy / this->dijk->copymap.heightpix;

    int tid = ccy * this->dijk->copymap.cols + ccx;
    while (tid != nid && path.PRE[tid] != -1) {
      if (tid == nid)
        break;
      q.push(tid);
      tid = path.PRE[tid];
    }
    for (int i = 1; i <= this->RunPace && !q.empty(); i++) {
      tid = q.top();
      q.pop();

      nx = this->map_x, ny = this->map_y; // 像素到地图
      nx = nx / this->dijk->copymap.widthpix;
      ny = ny / this->dijk->copymap.heightpix;

      int nnx = tid % this->dijk->copymap.cols,
          nny = tid / this->dijk->copymap.cols;
      this->Defence_Move((nnx - nx) * this->dijk->copymap.widthpix,
                         (nny - ny) *
                             this->dijk->copymap.heightpix); // 地图块到像素化

      emit this->qthello->updateenemeyfinshed();
      this->qthello->connect(this->qthello, &QtHello::updateenemeyfinshed,
                             &this->loop, &QEventLoop::quit);
      // emit this->qthello->updateenemey();
      // loop.exec();
      try {
        // 可能会引发异常的代码
        loop.exec();
      } catch (const std::exception &e) {
        // 处理标准异常
        qDebug() << "Caught exception:" << e.what();
      }
      /*if(!eye_contact(Cx,Cy)){//一个扭头就失效了
          std::cout<<"Eneme Cannot See You!\n";
          this->state=1;
          break;
      }*/
    }

    while (!q.empty()) {
      q.pop();
    }

    this->working = false;
  } else if (index == 4) {
    this->working = true;
    this->working = false;
    return;
  } else {
    this->working = true;
    cout << "Oh no,the Enemey get a wrong state_index\n";
    this->working = false;
    return;
  }

  this->working = false;
  return;
}
void Enemy::Defence_Move(int deltax, int deltay) { // 像素
  // int init_map_x=this->map_x, init_map_y=this->map_y;
  // 需要特殊判断地图边界，仍在制作中
  if (deltay > 0) {
    this->toward = 1; // 朝下
    if (this->picType == 1) {
      this->show_id_now++;
      this->show_id_now %= 4;
    } else {
      this->ChangePic(this->person_id, 1, 0);
    }
  }

  if (deltax < 0) {
    this->toward = 2; // 朝左

    if (this->picType == 2) {
      this->show_id_now++;
      this->show_id_now %= 4;
    } else {
      this->ChangePic(this->person_id, 2, 0);
    }
  }
  if (deltax > 0) {
    this->toward = 3; // 朝右

    if (this->picType == 3) {
      this->show_id_now++;
      this->show_id_now %= 4;
    } else {
      this->ChangePic(this->person_id, 3, 0);
    }
  }
  if (deltay < 0) {
    this->toward = 4; // 朝上

    if (this->picType == 4) {
      this->show_id_now++;
      this->show_id_now %= 4;
    } else {
      this->ChangePic(this->person_id, 4, 0);
    }
  }
  if (map_check(this->map_x + deltax, this->map_y + deltay) == true)
  // if (default_check(this->map_x + deltax, this->map_y + deltay))
  {
    this->map_x += deltax;
    this->map_y += deltay;
    return;
  }
}
void Enemy::get_x_and_y(int &X, int &Y) {
  X = this->map_x;
  Y = this->map_y;
  return;
}
void Enemy::setsize(int x, int y) {
  this->size_x = x;
  this->size_y = y;
}
void Enemy::setname(QString name) { this->defences_name = name; }
QString Enemy::getname() { return this->defences_name; }
bool Enemy::getworking() { return this->working; }
Enemy::Enemy(int x, int y, Mapmsg *map) {
  this->working = true;
  this->dijk = new Dijk(map);
  this->map_x = x, this->map_y = y;
  this->toward = 1;
  this->state = 0;
  this->setlevel(5);
  this->qthello = nullptr;
  this->working = false;
}
