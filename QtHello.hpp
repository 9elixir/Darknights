#ifndef QTHELLO_HPP
#define QTHELLO_HPP

#include "include/Enemy/Enemy.hpp"
#include "include/Menu/Menu.hpp"
#include "include/QtBattel/QtBattel.hpp"
#include "include/QtWelcome/QtWelcome.hpp"
#include <QRandomGenerator>
class QtWelcome;
class Menu;
class Enemy;
class QtHello : public QWidget {
  Q_OBJECT
protected:
  void keyPressEvent(QKeyEvent *event);

public:
  QtHello(QWidget *parent = nullptr);
  QMediaPlayer *getplayer();
  QTimer *gettimer();
  void quitloop();
  void createman();
  void createEneme();
  void gameover();
  void check_alive();
  void check_alive(int statu);
  bool mySetBackPicture(std::string s);
  bool mySetBackPicture();
  bool mySetPictures(std::string s, int x, int y);
  void myMessage(std::string title, std::string message);
  void setpicpaths(std::vector<RolePic> PicList);
  void setMaptools(transmap tools);
  void setMap(Mapmsg map);
  void setFather(QtWelcome *WELCOME);
  void windowquit();
  void buildmap();
  void getRandomXY(int &X, int &Y);
  void getRandomXY(int &X0, int &Y0, int &X1, int &Y1, int &X2, int &Y2);
  void setChongyue(Defences *character);
  void updateenemey();
  Defences *getman();
signals:
  void updateenemeyfinshed();
  void updateview3end();
private slots:
  bool updateView2();
  bool updateView3();

private:
  void updateenemelambda();
  void timeoutlambda();
  int music_id;
  QMediaPlayer *player = nullptr;
  QAudioOutput *audio = nullptr;
  int timecount;
  QTimer *timer = nullptr;
  QtWelcome *welcome = nullptr;
  transmap tools;
  Mapmsg map;
  Menu *menu = nullptr;
  QtBattle *my_battle = nullptr;
  int main_alive;

  bool updateMan();
  bool updateViewMap();
  QPixmap BackPix;
  QLabel *BackPicture_Label = nullptr;
  QLabel *QLMan = nullptr;
  QVBoxLayout *BackPicture_layout = nullptr;
  int len;
  Defences *man = nullptr; // 有时候得删
  Enemy *eneme = nullptr;
  QLabel *Pictures_Label = nullptr;
  QVBoxLayout *Pictures_layout = nullptr;
  Ui::QtHelloClass ui;
  std::vector<RolePic> RolesPicList;
  void OpenBattle();
};
#endif
