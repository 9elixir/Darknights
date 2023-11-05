#include"QtHello.hpp"


void QtHello::setChongyue(Defences* character){
    if(!(character)){
        qDebug()<<"Not Man so we cannot set her";
    }
    //this->defence = new Defences{};

    Skill* s1 = new Skill{ 0 , 30 ,QString("几手") };
    Skill* s2 = new Skill{ 20, 80, QString("冲盈") };
    Skill* s3 = new Skill{ 40, 150, QString("我无") };
    Skill* s4 = new Skill{ 80, 300, QString("拂尘") };//dedbug用
    character->setskill(s1, 1);
    character->setskill(s2, 2);
    character->setskill(s3, 3);
    character->setskill(s4, 4);
    character->setname(QString("重岳"));
   // qDebug()<<"We having maden Chongyue";
}
void QtHello::setMaptools(transmap tools) {
	this->tools = tools;
}
void QtHello::setMap(Mapmsg map) {
	this->map = map;
}
void QtHello::setFather(QtWelcome* WELCOME){
    this->welcome=WELCOME;
}
void QtHello::buildmap() {
	Mapmsg MAP = this->map;
	int width = MAP.cols, height = MAP.rows;


	// 计算目标 QImage 的大小

	// 创建目标 QImage
	QImage targetImage(width * MAP.widthpix, height * MAP.heightpix, QImage::Format_ARGB32);
	targetImage.fill(Qt::transparent);
	QPainter painter(&targetImage);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {

			QPixmap pixmap1(MAP.MapMartix[i][j].path.data());
			if (pixmap1.isNull()) {
				cout << "wrong build mappix!\n"; continue;
			}
			QPixmap temp = pixmap1.scaled(MAP.widthpix, MAP.heightpix);


			// 将 QPixmap 拷贝到目标 QImage

			painter.drawPixmap(j * MAP.widthpix, i * MAP.heightpix, temp);



			// 保存拼接后的 QImage
			//targetImage.save("result.png");

		}
	}
	this->BackPix = QPixmap::fromImage(targetImage);//返回类型为Qpixmap
    //qDebug() << this->BackPix;

	QPixmap viewresult = BackPix.copy(0, 0, MAP.viewcols * MAP.widthpix, MAP.viewrows * MAP.heightpix);
	//targetImage.save("map.png");
	this->setFixedSize(MAP.viewcols * MAP.widthpix, MAP.viewrows * MAP.heightpix);
	this->BackPicture_Label->setFixedSize(MAP.viewcols * MAP.widthpix, MAP.viewrows * MAP.heightpix);
	this->BackPicture_Label->setParent(this);
	this->BackPicture_Label->setPixmap(viewresult);
	this->BackPicture_Label->move(0, 0);
	//this->BackPicture_Label->setScaledContents(true);
	this->BackPicture_Label->show();
}
void QtHello::gameover() {

	//  printf("hello world\n");
	if (this->my_battle) {
		this->my_battle->windowquit();
		this->my_battle = nullptr;
    }
    myMessage("Game Over!!!", "游戏结束，您的角色已阵亡");
	//   printf("hello world\n");
	this->windowquit();
}
Defences* QtHello::getman(){
    return this->man;
}
void QtHello::check_alive() {
	if (this->main_alive == 1) {
		//主人公仍存活，游戏继续
		if (this->my_battle) {
			this->my_battle->windowquit();
			this->my_battle = nullptr;
        }
        if(true){//敌人被击败
            eneme->setstate(0);
            this->createEneme();
        }
        if (this->menu) {
            this->menu->windowquit();
           this->menu = nullptr;
        }

        this->show();
        if(this->player)this->player->play();
        if(this->timer)this->timer->start();
		return;
	}
	else
		if (this->main_alive == 0) {
			//主人公死亡，游戏结束
			//加载死亡界面
			gameover();
			//this->~QtHello();
            this->welcome->check_alive(0);

		}
		else
		{
			//this->gameover();
			printf("Wrong Message! main_alive not the 0 or 1\n");
		}
}
void QtHello::windowquit() {
	myMessage(" ", "希望我们的游戏为您带来快乐");
	//QApplication::quit();
	//this->close();//报错
	this->setAttribute(Qt::WA_DeleteOnClose);
	this->close();
    /*QApplication::quit();
	QTimer::singleShot(10, []() {
		QCoreApplication::quit();
        });*/

	//更不易异常的退出方式
}
QtHello::QtHello(QWidget* parent)
	: QWidget(parent)
{
	BackPicture_Label = new QLabel;

	BackPicture_Label->setParent(this);//new出数组
	//BackPicture_Label = new QLabel(this);
	BackPicture_layout = new QVBoxLayout;
	len = 0;
    this->setWindowFlags(Qt::WindowMinimizeButtonHint);
	man = nullptr;
    eneme=nullptr;
	QLMan = nullptr;
    timer=nullptr;
	this->my_battle = nullptr;
    this->menu=nullptr;
	this->main_alive = 1;
	//battlebegin->setParent(this);

    this->timecount=0;
    connect(this,&QtHello::updateenemeyfinshed,this,&QtHello::updateView2);


    audio = new QAudioOutput(this);
    player = new QMediaPlayer(this);
    player->setAudioOutput(audio);
    player->setSource(QUrl::fromLocalFile(QString("music\\relaxing.mp3")));
    player->setLoops(-1);
    player->play();
    this->music_id=1;


	ui.setupUi(this);
}
void QtHello::myMessage(std::string title, std::string message) {
   // qDebug()<<message;
	QMessageBox messageBox;

    messageBox.setWindowTitle(QString(title.data()));
	//std::string Notice = "Wrong Pic Path is:" + s;
    //messageBox.setText(message.data());
    QString str=QString(message.data());
    messageBox.setText(str);
	messageBox.setIcon(QMessageBox::Information);
	messageBox.addButton("yes,I have understanded", QMessageBox::AcceptRole);

	// 显示信息框
	messageBox.exec();
}
bool QtHello::mySetPictures(std::string s, int x, int y) {
	//20230919:希望不再使用指针进行声明。原因：后续需要多次添加、修改、删除窗口内各对象，如果用new指针，则不易于在后面的调用中进行这些操作。
	// 此外，函数new的指针销毁在返回时会全部销毁。
	//如何修改：目前的期望是，在类中定义map<class*,vector<>struct{vector<Label>,layout}>,使用时判断该类的指针是否存在。
	//问题：有可能一个类先被声明，然后被删除，两次的地址一样。
	//影响?:该添加的没能添加，删除的再删除尚能接受（健壮性）,修改的直接修改，似乎可以接受。
	//总结：显示内容在Class里，QT显示时读取其再显示，相当于将添加操作改为修改操作。

	//  QLabel* label = new QLabel(this);
	QLabel* label = new QLabel;
	label->setBuddy(this);//20230919：错误，无参数构造后若要绑定Widget应该用setParent


	QPixmap pixmap(s.data());//Qpix使用完可以直接销毁，但是Label、Layout不行


	if (pixmap.isNull()) {
		myMessage("mySetPictures", "pixmap is NULL!");
		//std::cout << "Wrong Pic Path!.\n"; 
		return false;
	}

	// 将图片设置为 QLabel 的内容
	label->setPixmap(pixmap);

	// 调整 QLabel 的大小以适应图片
	label->setFixedSize(this->size());
	label->setScaledContents(true);
	label->move(x, y);

	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addWidget(label);
	return true;
}
bool QtHello::mySetBackPicture(std::string s) {
	QLabel* label = new QLabel(this);
	QPixmap pixmap(s.data());//Qpix使用完可以直接销毁，但是Label、Layout不行
	if (pixmap.isNull()) {
		myMessage("mySetBackPicture(std::string s)", "pixmap is NULL!");

		//std::cout << "Wrong Pic Path!.\n"; 
		return false;
	}

	// 将图片设置为 QLabel 的内容
	label->setPixmap(pixmap);

	// 调整 QLabel 的大小以适应图片
	label->setFixedSize(this->size());
	label->setScaledContents(true);

	/*QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addWidget(label);*/
	//this->show();
	label->show();
	return true;
}
bool QtHello::mySetBackPicture() {
	std::string s;
	len = (len + 1) % 2;
	if (len == 1) {
		s = "imgs\\interlude_01.png";
	}
	else {
		s = "imgs\\b331ecd651b2c8650852c965ca65b4de.jpeg";
		//s = "F:\\C++编程\\QtHello\\imgs\\interlude_01.png";
	}

	QLabel* label = BackPicture_Label + 0;
	//= new QLabel(this);
	QPixmap pixmap(s.data());//Qpix使用完可以直接销毁，但是Label、Layout不行
	if (pixmap.isNull()) {
		myMessage("mySetBackPicture()", "pixmap is NULL!");
		//std::cout << "Wrong Pic Path!.\n"; 
		return false;
	}

	// 将图片设置为 QLabel 的内容
	label->setPixmap(pixmap);

	// 调整 QLabel 的大小以适应图片
	label->setFixedSize(this->size());
	label->setScaledContents(true);
	/*QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addWidget(label);*/
	return true;
}
void QtHello::getRandomXY(int &X,int &Y){//返回像素
    vector<int>q;
    for(int i=0;i<this->map.rows;i++)
        for(int j=0;j<this->map.cols;j++){
           if(this->map.MapMartix[i][j].touch_type==0||this->map.MapMartix[i][j].touch_type==1){
                int x,y;
                this->man->get_x_and_y(x,y);
                x/=this->map.widthpix;
                y/=this->map.heightpix;
                if(x==j&&y==i)continue;
                q.push_back(i*(this->map.cols)+j);
           }
        }
    while(1){
        int randomInt = QRandomGenerator::global()->bounded(0, (int)q.size());
        int id=q[randomInt];
        int nx=id%this->map.cols,ny=id/this->map.cols;

        int x,y;
        this->man->get_x_and_y(x,y);
        x/=this->map.widthpix;
        y/=this->map.heightpix;//地图块化
        if(x==nx&&y==ny)continue;
        X=nx,Y=ny;
        break;
    }
    q.clear();

    X*=this->map.widthpix;
    Y*=this->map.heightpix;
    qDebug()<<"X value="<<X<<",Y value="<<Y;
    return;
}
void QtHello::createman(){
    if (man)
    {
      //  qDebug() << "man is haven and now be shutted";
        delete man;
        man = nullptr;
    }
    this->man = new Defences(0, 1, 0, 60, 60, 200, 200, 200);
    this->man->setlevel(10);
    this->setChongyue(this->man);
    this->man->setMap(&(this->map));

    this->updateView2();
}
void QtHello::createEneme(){
    qDebug()<<"create the Eneme";
    if(eneme){
        delete eneme;
        eneme=nullptr;
    }
    int  X,Y;
    this->getRandomXY(X,Y);
    this->eneme=new Enemy(X,Y,&(this->map));

    this->getRandomXY(X,Y);
    this->eneme->set_x1_and_y1(X,Y);

    this->getRandomXY(X,Y);
    this->eneme->set_x2_and_y2(X,Y);

    this->eneme->setsize(1,1);
    this->eneme->setWalKPace(1);
    this->eneme->setRunPace(5);
    this->eneme->setname(QString("大鲍勃"));
    this->eneme->person_id=1;
    this->eneme->picType=2;
    this->eneme->show_id_now=0;
    this->eneme->setFather(this);
    if(!timer){
        timer=new QTimer(this);
        timer->setInterval(200);
    }
    timer->stop();
    connect(this,&QtHello::updateenemeyfinshed,[this](){
        this->timer->start();
    });
    connect(timer,&QTimer::timeout,[this](){

        //return;

        timer->stop();
        int CX,CY;
        this->man->get_x_and_y(CX,CY);
        CX/=this->map.widthpix;
        CY/=this->map.heightpix;
        if(this->eneme->eye_contact(CX,CY)){
            this->eneme->setstate(3);
        }
        //qDebug()<<"eye_contact step done";

        int NX,NY;
        this->eneme->get_x_and_y(NX,NY);
        NX/=this->map.widthpix;
        NY/=this->map.heightpix;
        if(CX==NX&&CY==NY){
             this->eneme->setstate(4);
             timer->stop();
             if(!this->my_battle)
             this->OpenBattle();
        }

        this->timecount++;
        this->timecount%=5;

        this->updateenemey();
    });
    timer->start();
    //timer->stop();
    this->updateView2();
}
void QtHello::keyPressEvent(QKeyEvent* event) {//监听按键
	int widthpix = this->map.widthpix, heightpix = this->map.heightpix;
	if (event->key() == Qt::Key_Space)
	{

		//myMessage("keyPressEvent", "get the Key_Space!");
		// 显示信息框
		//this->mySetBackPicture();

		//myMessage("keyPressEvent", "Creat New Man!");
        //this->buildmap();
        //this->createman();
        //this->updateenemey();
    }
    if(event->key()==Qt::Key_Tab){
        qDebug()<<"get the Tab";
        if((this->menu)){
             qDebug()<<"hi";

            this->menu->windowquit();
             this->menu=nullptr;
        }
         //qDebug()<<"hi2";
         this->menu=new Menu(nullptr,this,QSize(this->width()*2,this->height()*1.2));
        //this->menu->show();
      this->hide();
             if(this->timer)this->timer->stop();
    }
    if(event->key()==Qt::Key_Escape){
        qDebug()<<"In the hello,you are using the esc";
        this->welcome->check_alive(1);
    }
	if (event->key() == Qt::Key_W) {
		if (!this->man)return;
		this->man->Defence_Move(0, -heightpix);
		if (this->man->picType == 4) {
			this->man->show_id_now++;
			this->man->show_id_now %= 4;
		}
		else {
			this->man->ChangePic(0, 4, 0);
		}
		this->updateView2();
	}
	if (event->key() == Qt::Key_S) {
		if (!this->man)return;
		this->man->Defence_Move(0, +heightpix);
		if (this->man->picType == 1) {
			this->man->show_id_now++;
			this->man->show_id_now %= 4;
		}
		else {
			this->man->ChangePic(0, 1, 0);
		}
		//this->myMessage("why not move", "why not move");
		this->updateView2();
	}
	if (event->key() == Qt::Key_A) {
		if (!this->man)return;
		this->man->Defence_Move(-widthpix, 0);
		if (this->man->picType == 2) {
			this->man->show_id_now++;
			this->man->show_id_now %= 4;
		}
		else {
			this->man->ChangePic(0, 2, 0);
		}
		this->updateView2();
	}
	if (event->key() == Qt::Key_D) {
		if (!this->man)return;
		this->man->Defence_Move(+widthpix, 0);
		if (this->man->picType == 3) {
			this->man->show_id_now++;
			this->man->show_id_now %= 4;
		}
		else {
			this->man->ChangePic(0, 3, 0);
		}
		this->updateView2();
	}
}
void QtHello::setpicpaths(std::vector<RolePic>PicList) {

    this->RolesPicList = PicList;
	QPushButton* battlebegin = new QPushButton("begin Battle!");
	battlebegin->setParent(this);
	QObject::connect(battlebegin, &QPushButton::clicked, this, &QtHello::OpenBattle);
	battlebegin->setFocusPolicy(Qt::NoFocus);//取消焦点，否则按键监听无法使用
    battlebegin->show();
    battlebegin->hide();
    //  this->myMessage("setPiclist", "success!");
}
bool QtHello::updateViewMap() {
	if (!(this->man)) {
		qDebug() << "no man so we can not updateViewMap()";
		return false;
	}
	if ((this->map.MapMartix.size() <= 0)) {
		qDebug() << "no MAP so we can not updateViewMap()";
		return false;
	}
	int widthpix = this->map.widthpix, heightpix = this->map.heightpix;
	int x, y;
	this->man->get_x_and_y(x, y);
	QPixmap viewresult = this->BackPix.copy(x, y, this->map.viewcols * widthpix, this->map.viewrows * heightpix);
	this->setFixedSize(this->map.viewcols * widthpix, this->map.viewrows * heightpix);
	this->BackPicture_Label->setFixedSize(this->map.viewcols * widthpix, this->map.viewrows * heightpix);
	this->BackPicture_Label->setParent(this);
	this->BackPicture_Label->setPixmap(viewresult);
	this->BackPicture_Label->move(0, 0);
	//this->BackPicture_Label->setScaledContents(true);
	this->BackPicture_Label->show();
	return true;
}
bool QtHello::updateMan() {
	int widthpix = this->map.widthpix, heightpix = this->map.heightpix;
	if (!QLMan)QLMan = new QLabel(this);
	//cout << "this->man->person_id=" << this->man->person_id << ",this->man->picType=" << this->man->picType << ",this->man->show_id_now="<<this->man->show_id_now << "\n";
	int x, y;
	this->man->get_x_and_y(x, y);
	cout << "this->man->x=" << x / this->map.widthpix << ",this->man->y=" << y / this->map.heightpix << "\n";
	QPixmap pixmap0((this->RolesPicList[this->man->person_id]).PicList[this->man->picType].pic_paths[this->man->show_id_now].data());//Qpix使用完可以直接销毁，但是Label、Layout不行
	QPixmap pixmap = pixmap0.scaled(widthpix, heightpix);
	if (pixmap.isNull()) {
		myMessage("updateMan", "pixmap is NULL!");

		//std::cout << "Wrong Pic Path!.\n"; 
		return false;
	}

	// 将图片设置为 QLabel 的内容
	QLMan->setPixmap(pixmap);

	// 调整 QLabel 的大小以适应图片
	QLMan->setFixedSize(pixmap.size());
	QLMan->move(x, y);
	QLMan->setScaledContents(true);
	QLMan->show();
	/*QVBoxLayout* layout = new QVBoxLayout(this);
	layout->addWidget(label);*/
	//this->show();
	return true;
}
void QtHello::updateenemey(){
    if(this->eneme){
        int x3,y3;
        int x,y;
        if(true)
        {
            this->eneme->get_x_and_y(x3,y3);
            this->man->get_x_and_y(x,y);

            int state=this->eneme->getstate();
            if(state==0)state=1;
            //std::cout<<"we want to try state_action\n";
            if(true){
                if(
                    ((state==1||state==2)&&this->timecount==0)
                 //   ||((state==3)&&((this->timecount==0)||this->timecount==2||this->timecount==4))
                    ||((state==3)&&((this->timecount==0)))

                    )
                    if(this->eneme->getworking()==false)
                this->eneme->state_action(state,x,y);
            }
                emit this->updateenemeyfinshed();
        }
    }else{
        std::cout<<"Why not prinf?\n";
    }
}
bool QtHello::updateView2() {
	if (this->map.MapMartix.size() <= 0) {
		cout << "No Map and We can not update View!\n";
		return false;
	}
	if (!(this->man)) {
		cout << "No Man and We can not update View!\n";
		return false;
	}

   // QEventLoop loop;

	Mapmsg MAP = this->map;
	int r_rows = MAP.viewrows / 2 * MAP.heightpix, r_cols = MAP.viewcols / 2 * MAP.widthpix;
	// QPixmap temp1=this->BackPix;
	QImage targetImage(MAP.widthpix * MAP.cols, MAP.heightpix * MAP.rows, QImage::Format_ARGB32);
	targetImage.fill(Qt::transparent);
	QPainter painter(&targetImage);
	painter.setCompositionMode(QPainter::CompositionMode_SourceOver); //新的覆盖于旧的之上
	QPixmap pixmapt((this->RolesPicList[this->man->person_id]).PicList[this->man->picType].pic_paths[this->man->show_id_now].data());//Qpix使用完可以直接销毁，但是Label、Layout不行
	QPixmap pixmap0 = pixmapt.scaled(MAP.widthpix, MAP.heightpix);
	int x, y;
	int x0, y0;
	this->man->get_x_and_y(x, y);
	this->man->get_x_and_y(x0, y0);
	painter.drawPixmap(0, 0, this->BackPix);
    painter.drawPixmap(x, y, pixmap0);
int x3,y3;
    if(this->eneme){
    this->eneme->get_x_and_y(x3,y3);
        if(this->timecount==0)
        qDebug()<<"eneme pos:"<<x3<<" "<<y3;
      QPixmap pixmapeneme1((this->RolesPicList[this->eneme->person_id]).PicList[this->eneme->picType].pic_paths[this->eneme->show_id_now].data());
      QPixmap pixmapeneme=pixmapeneme1.scaled(MAP.widthpix, MAP.heightpix);
      painter.drawPixmap(x3,y3,pixmapeneme);
      if(this->eneme->eye_contact(x0,y0)){
            this->eneme->setstate(3);
            if(music_id!=2){
                this->player->setSource(QUrl::fromLocalFile("music\\rushing.mp3"));
                this->player->setLoops(-1);
                this->player->play();
                music_id=2;
            }
      }else{
            if(music_id!=1){
                this->player->setSource(QUrl::fromLocalFile("music\\relaxing.mp3"));
                this->player->setLoops(-1);
                this->player->play();
                music_id=1;
            }
      }
    }else{
      qDebug()<<"wow ,you not create the monster?";
    }


	QPixmap temp2 = QPixmap::fromImage(targetImage);


	if (x - r_cols < 0) {
		x = r_cols;
	}
	if (y - r_rows < 0) {
		y = r_rows;
	}
	if (x + r_cols > MAP.cols * MAP.widthpix) {
		x = MAP.cols * MAP.widthpix - r_cols;
	}
	if (y + r_rows > MAP.rows * MAP.heightpix) {
		y = MAP.rows * MAP.heightpix - r_rows;
	}
	QPixmap viewresult = temp2.copy(x - r_cols, y - r_rows, r_cols * 2, r_rows * 2);
    //qDebug() << viewresult << " " << temp2 << " " << x0 << " " << y0 << " " << x << " " << y;
	this->setFixedSize(r_cols * 2, r_rows * 2);
	this->BackPicture_Label->setFixedSize(r_cols * 2, r_rows * 2);
	this->BackPicture_Label->setParent(this);
	this->BackPicture_Label->setPixmap(viewresult);
	this->BackPicture_Label->move(0, 0);
	//this->BackPicture_Label->setScaledContents(true);
	this->BackPicture_Label->show();
    painter.end();

    //loop.quit();//太耗时了。

    return true;

}
void QtHello::OpenBattle() {
	myMessage("Open Battle", "lets Battle!");
    if (this->my_battle) { delete (this->my_battle); this->my_battle = nullptr; }
    this->my_battle = new QtBattle(nullptr,this->man,this->eneme);
	this->my_battle->setFather(this);
	this->hide();
    if(this->timer)this->timer->stop();
    if(this->player)player->stop();
	//check_alive(0);
}

void QtHello::check_alive(int statu) {
	this->main_alive = statu;
	this->check_alive();
}
