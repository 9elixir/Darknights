#ifndef QTHELLO_HPP
#define QTHELLO_HPP

#include"include/QtBattel/QtBattel.hpp"
#include"include/QtWelcome/QtWelcome.hpp"
#include"include/Menu/Menu.hpp"
#include <QRandomGenerator>
class QtWelcome;
class Menu;
class QtHello : public QWidget
{
	Q_OBJECT
protected:
	void keyPressEvent(QKeyEvent* event);
public:
	QtHello(QWidget* parent = nullptr);
    void createman();
    void createEneme();
	void gameover();
	void check_alive();
	void check_alive(int statu);
	bool mySetBackPicture(std::string s);
	bool mySetBackPicture();
	bool mySetPictures(std::string s, int x, int y);
	void myMessage(std::string title, std::string message);
	void setpicpaths(std::vector<RolePic>PicList);
	void setMaptools(transmap tools);
	void setMap(Mapmsg map);
    void setFather(QtWelcome* WELCOME);
	void windowquit();
	void buildmap();
    void getRandomXY(int &X,int &Y);
    void setChongyue(Defences* character);
    void updateenemey();
    Defences* getman();
signals:
    void updateenemeyfinshed();

    private slots:
            bool updateView2();

private:
    int music_id;
    QMediaPlayer* player;
    QAudioOutput* audio;
    int timecount;
    QTimer* timer;
    QtWelcome* welcome;
	transmap tools;
	Mapmsg map;
    Menu* menu;
	QtBattle* my_battle;
	int main_alive;

	bool updateMan();
	bool updateViewMap();
	QPixmap BackPix;
	QLabel* BackPicture_Label;
	QLabel* QLMan;
	QVBoxLayout* BackPicture_layout;
	int len;
    Defences* man;//有时候得删
    Enemy* eneme;
	QLabel* Pictures_Label;
	QVBoxLayout* Pictures_layout;
	Ui::QtHelloClass ui;
	std::vector<RolePic>RolesPicList;
	void OpenBattle();
};
#endif
