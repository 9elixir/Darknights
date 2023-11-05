#include "QtWelcome.hpp"
void QtWelcome::keyPressEvent(QKeyEvent *event) { // 监听按键

  if (event->key() == Qt::Key_Return) {
    if (this->tab_swith == 1) {
      this->windowquit();
    } else if (this->tab_swith == 0) {
      qDebug() << "We are into the hello";
      this->intoGame();
    } else {
      qDebug() << "Wrong tag_Swith!";
    }
  }
  if (event->key() == Qt::Key_Up) {
    this->tab_swith--;
    this->updateicon();
  }
  if (event->key() == Qt::Key_Down) {
    this->tab_swith++;
    this->updateicon();
  }
}
void QtWelcome::intoGame() {
  // 修改逻辑
  /*if(this->qthello){
      this->qthello->windowquit();
      this->qthello=nullptr;
  }

  this->qthello=new QtHello(nullptr);

  init myinit=init("hello_world.txt");
  myinit.setMaptool("maptools.txt");//必须先获得tool
  myinit.setMap("maptxt\\Map.txt", "maptxt\\MapAttribute.txt");
  this->qthello->setpicpaths(myinit.RolesPicList);
  this->qthello->setMaptools(myinit.maptool);
  this->qthello->setMap(myinit.map);
  //w.mySetBackPicture("F:\\C++编程\\QtHello\\imgs\\b331ecd651b2c8650852c965ca65b4de.jpeg");
  this->qthello->buildmap();
  this->qthello->setFather(this);
  this->qthello->show();


  this->hide();*/

  if (!(this->qthello)) {
    // this->qthello->windowquit();
    // this->qthello=nullptr;
    qDebug() << "New helloing……";
    this->qthello = new QtHello(nullptr);
    qDebug() << "New hello done……";
    init myinit = init("hello_world.txt");
    qDebug() << "myinit have  newing";
    myinit.setMaptool("maptools.txt"); // 必须先获得tool
    myinit.setMap("maptxt\\Map.txt", "maptxt\\MapAttribute.txt");

    qDebug() << "myinit have done";
    this->qthello->setpicpaths(myinit.RolesPicList);
    this->qthello->setMaptools(myinit.maptool);
    this->qthello->setMap(myinit.map);
    // w.mySetBackPicture("F:\\C++编程\\QtHello\\imgs\\b331ecd651b2c8650852c965ca65b4de.jpeg");
    this->qthello->buildmap();
    this->qthello->setFather(this);
    qDebug() << "begin to create";
    this->qthello->createman();
    this->qthello->createEneme();
  }
  if (this->qthello->gettimer())
    this->qthello->gettimer()->start();

  if (this->qthello->getplayer())
    this->qthello->getplayer()->play();
  this->qthello->show();
  this->hide();
  return;
}
void QtWelcome::windowquit() {

  qDebug() << "Welcome also need to be done";
  if (this->qthello) {
    this->qthello->windowquit();
    this->qthello = nullptr;
  }
  this->setAttribute(Qt::WA_DeleteOnClose);
  this->close();
}
void QtWelcome::updateicon() {
  QString begin;
  if (this->qthello)
    begin = QString("继续游戏");
  else
    begin = QString("开始游戏");
  this->switchlabel1->setText(begin);
  this->tab_swith %= 2;
  this->tab_swith = (this->tab_swith + 2) % 2;

  if (this->tab_swith == 0)
    this->icon->move((this->switchlabel1)->pos().x() - this->icon->width(),
                     this->switchlabel1->pos().y());
  if (this->tab_swith == 1)
    this->icon->move((this->switchlabel2)->pos().x() - this->icon->width(),
                     this->switchlabel2->pos().y());
}
void QtWelcome::check_alive() {
  if (this->man_alive != 1 && this->man_alive != 0) {
    qDebug() << "Welcome's checkalive only receive 0 or 1";
    return;
  }
  if (this->man_alive == 1) {
    qDebug() << "we are still alive";
    this->show();
    // 20231101 我们认为esc只是隐藏。我们不把他删了
    /*  if(this->qthello){
          //this->qthello->windowquit();
          //this->qthello=nullptr;
          this->qthello->hide();
      }*/
    if (this->qthello) {
      this->qthello->hide();
      if (this->qthello->getplayer()) {

        this->qthello->getplayer()->stop();
      }

      if (this->qthello->gettimer())
        this->qthello->gettimer()->stop();
      this->updateicon();
    }
    return;
  } else {
    this->windowquit();
  }
}
void QtWelcome::check_alive(int statu) {
  if (statu == 1) {
    this->man_alive = 1;
  } else if (statu == 0) {
    this->man_alive = 0;
  } else {
    qDebug() << "Welcome's checkalive only receive 0 or 1";
  }
  this->check_alive();
}
QtWelcome::QtWelcome(QWidget *parent) : QWidget{parent} {
  this->setFixedSize(768, 512);
  this->backimg = new QLabel;
  this->backimg->setParent(this);
  this->backimg->setFixedSize(this->size());
  QPixmap backpix = QPixmap("imgs\\beginimg.png").scaled(this->size());
  this->backimg->move(0, 0);
  this->backimg->setPixmap(backpix);
  // QString qstmp("诚信考试");
  // this->backimg->setText(qstmp);
  //  (this->backimg)->setFont(QFont("宋体", 18, 100, true));
  // this->backimg->setScaledContents(true);

  this->tab_swith = 0;
  // this->switchlayout=new QVBoxLayout(this);
  this->switchlabel1 = new QLabel(this);
  this->switchlabel2 = new QLabel(this);
  switchlabel1->setFixedSize(128, 50);
  switchlabel2->setFixedSize(128, 50);

  (switchlabel1)->move(0.45 * this->width(), 512 - 50 - 50);
  (switchlabel2)->move(0.45 * this->width(), 512 - 50);
  QString begin("开始游戏");
  switchlabel1->setText(begin);
  // qDebug() << this->switchlabel->size();
  QString end("退出游戏");
  (switchlabel2)->setText(end);

  (switchlabel1)->setStyleSheet("font-size: 16px;");
  (switchlabel1)->show();
  (switchlabel2)->setStyleSheet("font-size: 16px;");
  (switchlabel2)->show();

  this->icon = new QLabel(this);
  QPixmap picon("imgs\\chooselogo.png");
  picon = picon.scaled(50, switchlabel1->height());
  this->icon->setPixmap(picon);
  this->icon->setFixedSize(50, switchlabel1->height());

  // this->icon->move(50,50);
  // this->icon->show();
  this->qthello = nullptr;
  this->man_alive = 1;
  this->updateicon();
}
