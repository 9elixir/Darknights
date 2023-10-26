#include"QtBattel.hpp"

//QtBattel是用来显示战斗界面的
QtBattle::QtBattle(QWidget* parent, std::string BattelBackPath, std::string littleimgPath) {
	//初始化变量
	turn_num = 0;

	animation = nullptr;
	bloodImg2 = nullptr;

	window = new QWidget(nullptr);
	window->setFixedSize(QSize(960, 768));
	window->setWindowFlags(Qt::WindowMinimizeButtonHint);//只允许最小化

	scrollArea = nullptr;

	double PercentHeight = window->height() / 810.0;//0.84
	double PercentWidth = window->width() / 1440.0;//0.67

	//回合显示
	turnLabel = new QLabel(window);
	QString turn_string = QString::number(turn_num);
	turnLabel->setText(turn_string);
	turnLabel->setFont(QFont("宋体", 18, 100, true));
	QSize turnLabelSize(QFontMetrics(QFont("宋体", 18, 100)).boundingRect(turn_string).width() + 20, QFontMetrics(QFont("宋体", 12, 100)).height() + 20);
	turnLabel->setFixedSize(turnLabelSize);
	turnLabel->move(690 * PercentWidth, 45 * PercentHeight);

	//模拟传入人物的指针
	this->defence = new Defences{};
	Skill* s1 = new Skill{ 0 , 30 ,QString("几手") };
	Skill* s2 = new Skill{ 20, 80, QString("冲盈") };
	Skill* s3 = new Skill{ 40, 150, QString("我无") };
	Skill* s4 = new Skill{ 80, 300, QString("拂尘") };
	this->defence->setskill(s1, 1);
	this->defence->setskill(s2, 2);
	this->defence->setskill(s3, 3);
	this->defence->setskill(s4, 4);
	this->defence->setname("重岳");
	//上方的血条布局
	bloodLabel1 = new QLabel("HP: ", window);
	bloodLabel1->setFixedSize(QSize(540 * PercentWidth, 90 * PercentHeight));
	bloodLabel1->move(0, 0);
	bloodLabel2 = new QLabel("HP: ", window);
	bloodLabel2->setFixedSize(QSize(540 * PercentWidth, 90 * PercentHeight));
	bloodLabel2->move(900 * PercentWidth, 0 * PercentHeight);
	std::string bloodpix_path1 = "BaseImages\\blood1.png";
	std::string bloodpix_path2 = "BaseImages\\blood2.png";
	bloodImg1 = new QLabel(window);
	bloodImg2 = new QLabel(window);
	QPixmap bloodpix1(bloodpix_path1.data());
	QPixmap bloodpix2(bloodpix_path2.data());
	if (bloodpix1.isNull())bloodLabel1->setText("HPLOAD WRONG");
	if (bloodpix2.isNull())bloodLabel2->setText("HPLOAD WRONG");
	QSize qsizeblood1(440 * PercentWidth * (this->blood1_now * 1.0 / this->blood1_max), 90 * PercentHeight);//label总共540，前100不用
	QSize qsizeblood2(440 * PercentWidth * (this->blood2_now * 1.0 / this->blood2_max), 90 * PercentHeight);//label总共540，前100不用
	bloodImg1->setPixmap(bloodpix1.scaled(qsizeblood1));
	bloodImg1->setFixedSize(qsizeblood1);
	bloodImg1->move(100 * PercentWidth, 0 * PercentHeight);
	bloodImg2->setPixmap(bloodpix2.scaled(qsizeblood2));
	bloodImg2->setFixedSize(qsizeblood2);
	bloodImg2->move(1000 * PercentWidth, 0 * PercentHeight);

	//上方蓝条布局
	magicLabel1 = new QLabel("MP: ", window);
	magicLabel1->setFixedSize(QSize(540 * PercentWidth, 90 * PercentHeight));
	magicLabel1->move(0 * PercentWidth, 90 * PercentHeight);
	magicLabel2 = new QLabel("MP: ", window);
	magicLabel2->setFixedSize(QSize(540 * PercentWidth, 90 * PercentHeight));
	magicLabel2->move(900 * PercentWidth, 90 * PercentHeight);
	QString magicpix_path1 = QString("BaseImages\\magic1.png");
	QString magicpix_path2 = QString("BaseImages\\magic2.png");
	magicImg1 = new QLabel(window);
	magicImg2 = new QLabel(window);
	QPixmap magicpix1(magicpix_path1);
	QPixmap magicpix2(magicpix_path2);
	if (magicpix1.isNull())magicLabel1->setText("MPLOAD WRONG");
	if (magicpix2.isNull())magicLabel2->setText("MPLOAD WRONG");
	QSize qsizemagic1(440 * PercentWidth * (this->magic1_now * 1.0 / this->magic1_max), 90 * PercentHeight);//label总共540，前100不用
	QSize qsizemagic2(440 * PercentWidth * (this->magic2_now * 1.0 / this->magic2_max), 90 * PercentHeight);//label总共540，前100不用
	magicImg1->setPixmap(magicpix1.scaled(qsizemagic1));
	magicImg1->setFixedSize(qsizemagic1);
	magicImg1->move(100 * PercentWidth, 90 * PercentHeight);
	magicImg2->setPixmap(magicpix2.scaled(qsizemagic2));
	magicImg2->setFixedSize(qsizemagic2);
	magicImg2->move(1000 * PercentWidth, 90 * PercentHeight);

	//设置字体形式大小和对齐方式
	bloodLabel1->setFont(QFont("宋体", 14, 100, true));
	bloodLabel2->setFont(QFont("宋体", 14, 100, true));
	magicLabel1->setFont(QFont("宋体", 14, 100, true));
	magicLabel2->setFont(QFont("宋体", 14, 100, true));

	bloodLabel1->setContentsMargins(40 * PercentWidth, 10 * PercentHeight, 0 * PercentWidth, 0 * PercentHeight);
	bloodLabel2->setContentsMargins(40 * PercentWidth, 10 * PercentHeight, 0 * PercentWidth, 0 * PercentHeight);
	magicLabel1->setContentsMargins(40 * PercentWidth, 10 * PercentHeight, 0 * PercentWidth, 0 * PercentHeight);
	magicLabel2->setContentsMargins(40 * PercentWidth, 10 * PercentHeight, 0 * PercentWidth, 0 * PercentHeight);


	//显示血条和蓝条的边框
	setlabelframe(bloodLabel1);
	setlabelframe(bloodLabel2);
	setlabelframe(magicLabel1);
	setlabelframe(magicLabel2);
	// 中间人物的图片布局
	characterLabel1 = new QLabel{ window };
	characterLabel2 = new QLabel{ window };

	characterLabel1->setFixedSize(QSize(300 * PercentWidth, 400 * PercentHeight));
	characterLabel1->move(150 * PercentWidth, 200 * PercentHeight);
	characterLabel2->setFixedSize(QSize(300 * PercentWidth, 400 * PercentHeight));
	characterLabel2->move(990 * PercentWidth, 200 * PercentHeight);
	//设置图片
	charactermov1 = new QMovie("imgs\\Chongyue\\CY-Idle.gif");
	charactermov2 = new QMovie("imgs\\Tom.gif");

	charactermov1->start();
	charactermov2->start();
	characterLabel1->setMovie(charactermov1);
	characterLabel2->setMovie(charactermov2);

	QPalette palette;
	//设置主窗口背景颜色
	palette.setColor(QPalette::Window, QColor(255, 255, 255));
	window->setPalette(palette);

	// 左侧四分之一的小图片
	smallImageLabel = new QLabel{ window };
	QPixmap smallImage("imgs\\Chongyue\\Chongyue.png"); // 更换为你的图片路径
	smallImageLabel->setFixedSize(QSize(360 * PercentWidth, 200 * PercentHeight));//确定框的大小240x168，图片只会载入相应位置的内容
	smallImageLabel->move(45 * PercentWidth, 610 * PercentHeight);
	smallImageLabel->setPixmap(smallImage.scaled(360 * PercentWidth, 360 * PercentWidth * 9 / 16));//16：9


	// 中间二分之一的按钮布局

	button1 = new SkillButton(this->defence->getskill(1), window);
	button2 = new SkillButton(this->defence->getskill(2), window);
	button3 = new SkillButton(this->defence->getskill(3), window);
	button4 = new SkillButton(this->defence->getskill(4), window);


	//设置按钮大小和位置
	button1->setFixedSize(QSize(270 * PercentWidth, 90 * PercentHeight));
	button1->move(405 * PercentWidth, 617 * PercentHeight);
	button2->setFixedSize(QSize(270 * PercentWidth, 90 * PercentHeight));
	button2->move(720 * PercentWidth, 617 * PercentHeight);
	button3->setFixedSize(QSize(270 * PercentWidth, 90 * PercentHeight));
	button3->move(405 * PercentWidth, 713 * PercentHeight);
	button4->setFixedSize(QSize(270 * PercentWidth, 90 * PercentHeight));
	button4->move(720 * PercentWidth, 713 * PercentHeight);

	//取消button自带的“->"箭头
	button1->setIcon(QIcon("imgs\\Chongyue\\普攻.png"));
	button2->setIcon(QIcon("imgs\\Chongyue\\技能_冲盈.png"));
	button3->setIcon(QIcon("imgs\\Chongyue\\技能_我无.png"));
	button4->setIcon(QIcon("imgs\\Chongyue\\技能_拂尘.png"));

	// 取消焦点，否则按键监听无法使用
	button1->setFocusPolicy(Qt::NoFocus);
	button2->setFocusPolicy(Qt::NoFocus);
	button3->setFocusPolicy(Qt::NoFocus);
	button4->setFocusPolicy(Qt::NoFocus);


	//右侧四分之一的标签布局
	label = new ShowLabel("战斗开始！", window);
	label->setFont(QFont("宋体", 12, 100));//12号字体汉字，刚好能在420的宽度下显示25个；14号字体数字，加粗刚好能在420的宽度下显示50个
	label->setAlignment(Qt::AlignTop | Qt::AlignLeft);//设置文字对齐方式
	label->setFont_height(QFontMetrics(QFont("宋体", 12, 100)).height());
	label->setMyHeight(200 * PercentHeight);
	label->setMyWidth(400 * PercentWidth);

	//获取按下的Skillbutton

	connect(button1, &SkillButton::clicked, this, &QtBattle::button1_clicked);
	connect(button1, &SkillButton::clicked, label, &ShowLabel::button_clicked);


	connect(button2, &SkillButton::clicked, this, &QtBattle::button2_clicked);
	connect(button2, &SkillButton::clicked, label, &ShowLabel::button_clicked);


	connect(button3, &SkillButton::clicked, this, &QtBattle::button3_clicked);
	connect(button3, &SkillButton::clicked, label, &ShowLabel::button_clicked);


	connect(button4, &SkillButton::clicked, this, &QtBattle::button4_clicked);
	connect(button4, &SkillButton::clicked, label, &ShowLabel::button_clicked);



	//右侧四分之一的滚动区域布局
	QScrollArea* scrollArea = new QScrollArea{ window };
	scrollArea->setBackgroundRole(QPalette::Dark);
	scrollArea->setWidgetResizable(false);
	scrollArea->setFixedSize(QSize(420 * PercentWidth, 200 * PercentHeight));
	scrollArea->move(1020 * PercentWidth, 610 * PercentHeight);
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	int barheight = scrollArea->verticalScrollBar()->height();
	qDebug() << "VBar:" << scrollArea->verticalScrollBar()->width() << " " << scrollArea->verticalScrollBar()->height();
	qDebug() << "HBar:" << scrollArea->horizontalScrollBar()->width() << " " << scrollArea->horizontalScrollBar()->height();
	label->setMyWidth(scrollArea->width() - barheight + 10);//无论怎样跳绳大小，水平和垂直都是100宽 30高。为什么垂直的滚条宽比高大? 加10是因为实际应用中label还是没占满剩余位置
	scrollArea->setWidget(label);

	window->show();
}
void QtBattle::setdefence(Defences* defence) {
	this->defence = defence;
}
void QtBattle::BloodChange(QLabel*& ChangeLabel, int now, int max) {

	double PercentHeight = window->height() / 810.0;
	double PercentWidth = window->width() / 1440.0;
	QSize size1 = ChangeLabel->size();
	QSize size2 = size1;
	int new_width = 440 * PercentWidth * (now * 1.0 / max);
	size2.setWidth(new_width);

	//创建属性动画，将 QLabel 的 pixmap 属性从起始图片渐变到目标图片
	//注意，pixmap不能作为动画的属性
	//使用geometry只改变geometry，size不会变化，text和pixmap不会随之变化,必须重新手写
	//若率先使用了fixedSize,geometry则无法改变,因此使用value百分比
	//size作为属性其实是合法的。
	//使用size时，value的tosize是变化的
	animation = new QPropertyAnimation(ChangeLabel, "size");
	animation->setDuration(600);  // 动画持续时间为 600 毫秒
	animation->setStartValue(size1);
	animation->setEndValue(size2);
	animation->setEasingCurve(QEasingCurve::InOutQuad);  // 使用平滑的缓动曲线
	// 启动动画
	ChangeLabel->show();

	connect(animation, &QPropertyAnimation::valueChanged, [&ChangeLabel, new_width](const QVariant& value) {
		//double Percent = value.toInt() / 100.0;
		qDebug() << value.toSize();
		//int now_width = Percent * (new_width - geo1.width()) + geo1.width();
		//QPixmap pixmap = ChangeLabel->pixmap().scaledToWidth(now_width);//这里不能单独改变width,会导致height变化
		int now_width = value.toSize().width();
		QPixmap pixmap = ChangeLabel->pixmap().scaled(value.toSize());
		ChangeLabel->setFixedWidth(now_width);
		ChangeLabel->setFixedHeight(value.toSize().height());
		ChangeLabel->setPixmap(pixmap);
		});

	connect(animation, &QPropertyAnimation::finished, [&ChangeLabel, new_width, now, PercentHeight, this]() {
		delete (this->animation);
		this->animation = nullptr;
		});
	animation->start();
}
void QtBattle::button1_clicked()
{
	label->setbutton(this->button1);
	//根据当前技能对敌人伤害的不同确定skilleffct
	double hurtrate = double(this->button1->getSkillHurt()) / double(this->blood2_max);

	if (hurtrate >= 0.3) {
		this->label->setSkillEffect("效果拔群！");
	}
	else if (hurtrate >= 0.15 && hurtrate < 0.3) {
		this->label->setSkillEffect("效果显著");
	}
	else {
		this->label->setSkillEffect("效果轻微");
	}
	this->magic1_now = this->magic1_now - this->button1->getSkillCost();
	this->BloodChange(this->magicImg1, this->magic1_now,this->magic1_max);

	QMovie *attack = new QMovie("imgs\\Chongyue\\CY-Attack_A.gif");
	this->characterLabel1->setMovie(attack);

	this->button_clicked_new();

	//当动画播放完毕后，删除动画
	connect(attack, &QMovie::frameChanged, [this, attack] {

		//判断是否是最后一帧
		if (attack->currentFrameNumber() == attack->frameCount() - 1) {

			this->characterLabel1->setMovie(this->charactermov1);
			this->charactermov1->start();

			this->blood2_now = this->blood2_now - this->button1->getSkillHurt();
			this->BloodChange(this->bloodImg2, this->blood2_now,this->blood2_max);

			this->turnEnd();

			attack->stop();

		}
		});

	attack->start();
	
}
void QtBattle::button2_clicked()
{
	label->setbutton(this->button2);
	//根据当前技能对敌人伤害的不同确定skilleffct
	double hurtrate = double(this->button2->getSkillHurt()) / double(this->blood2_max);

	if (hurtrate >= 0.3) {
		this->label->setSkillEffect("效果拔群！");
	}
	else if (hurtrate >= 0.15 && hurtrate < 0.3) {
		this->label->setSkillEffect("效果显著");
	}
	else {
		this->label->setSkillEffect("效果轻微");
	}
	this->magic1_now = this->magic1_now - this->button2->getSkillCost();
	this->BloodChange(this->magicImg1, this->magic1_now,this->magic1_max);

	QMovie* skill1 = new QMovie("imgs\\Chongyue\\CY-Skill_1.gif");
	this->characterLabel1->setMovie(skill1);

	this->button_clicked_new();

	//当动画播放完毕后，删除动画
	connect(skill1, &QMovie::frameChanged, [this, skill1] {

		//判断是否是最后一帧
		if (skill1->currentFrameNumber() == skill1->frameCount() - 1) {

			this->characterLabel1->setMovie(this->charactermov1);
			this->charactermov1->start();

			this->blood2_now = this->blood2_now - this->button2->getSkillHurt();
			this->BloodChange(this->bloodImg2, this->blood2_now,this->blood2_max);

			this->turnEnd();

			skill1->stop();

		}
		});

	skill1->start();
}

void QtBattle::button3_clicked() {
	label->setbutton(this->button3);
	//根据当前技能对敌人伤害的不同确定skilleffct
	double hurtrate = double(this->button3->getSkillHurt()) / double(this->blood2_max);
	if (hurtrate >= 0.3) {
		this->label->setSkillEffect("效果拔群！");
	}
	else if (hurtrate >= 0.15 && hurtrate < 0.3) {
		this->label->setSkillEffect("效果显著");
	}
	else {
		this->label->setSkillEffect("效果轻微");
	}
	this->magic1_now = this->magic1_now - this->button3->getSkillCost();
	this->BloodChange(this->magicImg1, this->magic1_now,this->magic1_max);

	QMovie* skill3 = new QMovie("imgs\\Chongyue\\CY-Skill_3.gif");
	this->characterLabel1->setMovie(skill3);

	this->button_clicked_new();

	//当动画播放完毕后，删除动画
	connect(skill3, &QMovie::frameChanged, [this, skill3] {

		//判断是否是最后一帧
		if (skill3->currentFrameNumber() == skill3->frameCount() - 1) {

			this->characterLabel1->setMovie(this->charactermov1);
			this->charactermov1->start();

			this->blood2_now = this->blood2_now - this->button3->getSkillHurt();
			this->BloodChange(this->bloodImg2, this->blood2_now,this->blood2_max);

			this->turnEnd();

			skill3->stop();

		}
		});

	skill3->start();
	
}
void QtBattle::button4_clicked() {
	label->setbutton(this->button4);
	//根据当前技能对敌人伤害的不同确定skilleffct
	double hurtrate = double(this->button4->getSkillHurt()) /double( this->blood2_max);
	if (hurtrate >= 0.3) {
		this->label->setSkillEffect("效果拔群！");
	}
	else if (hurtrate >= 0.15 && hurtrate < 0.3) {
		this->label->setSkillEffect("效果显著");
	}
	else {
		this->label->setSkillEffect("效果轻微");
	}
	this->magic1_now = this->magic1_now - this->button4->getSkillCost();
	this->BloodChange(this->magicImg1, this->magic1_now,this->magic1_max);

	QMovie* skill2b = new QMovie("imgs\\Chongyue\\CY-Skill_2_Begin.gif");
	QMovie* skill2e = new QMovie("imgs\\Chongyue\\CY-Skill_2_End.gif");

	this->characterLabel1->setMovie(skill2b);

	this->button_clicked_new();

	//当动画播放完毕后，删除动画
	connect(skill2b, &QMovie::frameChanged, [this, skill2b, skill2e] {

		//判断是否是最后一帧
		if (skill2b->currentFrameNumber() == skill2b->frameCount() - 1) {

			this->characterLabel1->setMovie(skill2e);

			connect(skill2e, &QMovie::frameChanged, [this, skill2e] {

				//判断是否是最后一帧
				if (skill2e->currentFrameNumber() == skill2e->frameCount() - 1) {

					this->characterLabel1->setMovie(this->charactermov1);
					this->charactermov1->start();

					this->blood2_now = this->blood2_now - this->button4->getSkillHurt();
					this->BloodChange(this->bloodImg2, this->blood2_now,this->blood2_max);

					this->turnEnd();

					skill2e->stop();
				}
				});

			skill2e->start();
			skill2b->stop();
		}
		});

	skill2b->start();

}
void QtBattle::button_clicked_new()
{
	this->turnIn();
	//绑定label和defence的名称
	this->label->setcname(this->defence->getname());
	this->label->setename("Tom");
}
//在button_clicked_new中调用
void QtBattle::turnIn() {
	button1->setEnabled(false);//禁止再点击按钮
	button2->setEnabled(false);
	button3->setEnabled(false);
	button4->setEnabled(false);

}
//在turnEnd中调用
void QtBattle::turnBegin() {

	//上方显示回合数
	std::string turn_string = std::to_string(turn_num);
	turnLabel->setText(turn_string.data());
	turnLabel->setFont(QFont("宋体", 18, 100, true));
	QSize turnLabelSize(QFontMetrics(QFont("宋体", 18, 100)).boundingRect(turn_string.data()).width() + 20, QFontMetrics(QFont("宋体", 12, 100)).height() + 20);
	turnLabel->setFixedSize(turnLabelSize);
	if (if_my_turn) {
		button1->setEnabled(true);
		button2->setEnabled(true);
		button3->setEnabled(true);
		button4->setEnabled(true);

	}
	//若是敌人回合，敌人采取行动
	else {

		button1->setEnabled(false);
		button2->setEnabled(false);
		button3->setEnabled(false);
		button4->setEnabled(false);

		this->label->enemyturn();
		//根据当前技能对敌人伤害的不同确定skilleffct
		double hurtrate = double(40) / double(this->blood1_max);

		if (hurtrate >= 0.3) {
			this->label->setSkillEffect("效果拔群！");
		}
		else if (hurtrate >= 0.15 && hurtrate < 0.3) {
			this->label->setSkillEffect("效果显著");
		}
		else {
			this->label->setSkillEffect("效果轻微");
		}
		this->blood1_now = this->blood1_now - 40;
		this->BloodChange(this->bloodImg1, this->blood1_now,this->blood1_max);
		this->magic2_now = this->magic2_now - 20;
		this->BloodChange(this->magicImg2, this->magic2_now,this->magic2_max);

		turnEnd();
	}
}
//在BloodChange中调用
void QtBattle::turnEnd() {
	turn_num++;
	//根据血量判断战斗是否结束
	if_my_turn = !if_my_turn;

	if (this->blood1_now > 0 && this->blood2_now > 0) { 
			turnBegin(); 
	}
	else if (this->blood1_now <= 0 || this->blood2_now <= 0) {
		if_fight_over = true;
		if (this->blood1_now <= 0) {
			label->setText("战斗结束！你输了！");
		}
		else if (this->blood2_now <= 0) {
			label->setText("战斗结束！你赢了！");
		}
	}


}

//ShowLabel是用来显示战斗信息的
ShowLabel::ShowLabel(QWidget* parent) :QLabel(parent) {
	this->next = nullptr;
	this->discription = "\0";
	this->contents_rows = 1;
	this->QLabel::setFixedSize(this->width, this->height);
	this->if_use_button = false;
	this->button = new SkillButton();
}
ShowLabel::ShowLabel(const QString& text, QWidget* parent) : QLabel(text, parent) {
	this->discription = text;
	this->QLabel::setFixedSize(this->width, this->height);
	this->setFont(QFont("宋体", 12, 100));//12号字体汉字，刚好能在420的宽度下显示25个；14号字体数字，加粗刚好能在420的宽度下显示50个
	this->contents_rows = 1;
	this->wrap(true, 0);//自动换行
	this->setAlignment(Qt::AlignTop | Qt::AlignLeft);//设置文字对齐方式
	this->move(this->originx, this->originy);
	this->if_use_button = false;
	this->button = new SkillButton();
}
ShowLabel::~ShowLabel() {
	delete this->button;
	delete this->next;
}
void ShowLabel::setFont_height(int FONT_HEIGHT) {
	this->font_height = FONT_HEIGHT;
}
void ShowLabel::setMyHeight(int HEIGHT) {
	this->height = HEIGHT;
}
void ShowLabel::setMyWidth(int WIDTH) {
	this->width = WIDTH;
}
void ShowLabel::setText(const QString& text) {
	this->discription = this->discription + QString("\n") + text;
	this->setFont(QFont("宋体", 12, 100));//12号字体汉字，刚好能在420的宽度下显示25个；14号字体数字，加粗刚好能在420的宽度下显示50个
	this->setAlignment(Qt::AlignTop | Qt::AlignLeft);//设置文字对齐方式
	this->QLabel::setText(this->discription);
}
void ShowLabel::setNext(ShowLabel* next) {
	this->next = next;
}
void ShowLabel::wrap(bool b, int last_count) {
	if (!b) {
		return;
	}

	int sumwidth = 0;
	QString str("");
	int nCount = this->discription.count();
	for (int i = last_count; i < discription.count(); i++)
	{
		QChar cha = this->discription.at(i);
		ushort uni = cha.unicode();

		if (uni == QChar('\n').unicode()) {
			str = QString("");
			contents_rows++;
			continue;
		}
		str = str + cha;
		sumwidth = QFontMetrics(QFont("宋体", 12, 100)).boundingRect(str).width();
		if (i > 1) {
			qDebug() << str << " " << sumwidth << " this width=" << this->width;
			if (sumwidth > (this->width)) {
				if (i + 1 < this->discription.size() && this->discription.at(i + 1) == '\n')
				{
					continue;
				}
				this->discription.insert(i, QString("\n"));
				sumwidth = 0;
				i--;
			}
			else if ((cha == QString("害")) && this->discription.at(i - 1) == QString("伤")) {
				this->discription.insert(i + 1, QString("\n"));
			}

		}
	}

	this->QLabel::setText(this->discription);
	this->QLabel::setFixedWidth(this->width);
	this->QLabel::setFixedHeight(contents_rows * (this->font_height + 3));

}
void ShowLabel::button_clicked() {

	int last_count = this->discription.size();
	this->show = this->cname + QString("%1%2%3%4%5%6%7%8");
	this->sname = this->button->getSkillName();
	this->hurt = QString::number(this->button->getSkillHurt());

	this->setText(show.arg("对").arg(ename).arg("使用了").arg(this->sname).arg("造成了").arg(hurt).arg("点伤害").arg(this->skilleffect));
	this->wrap(true, last_count);

}
void ShowLabel::enemyturn() {
	int last_count = this->discription.size();
	this->show = this->ename + QString("%1%2%3%4%5%6%7%8");
	this->sname = "撕扯";
	this->hurt = QString::number(40);
	this->setText(show.arg("对").arg(cname).arg("使用了").arg(this->sname).arg("造成了").arg(hurt).arg("点伤害").arg(this->skilleffect));
	this->wrap(true, last_count);
}
void ShowLabel::setcname(const QString& name) {
	this->cname = name;
}
void ShowLabel::setename(const QString& name) {
	this->ename = name;
}
void ShowLabel::readinskill(SkillButton* skill) {
	this->sname = skill->getSkillName();
}
void ShowLabel::setSkillEffect(const QString& effect) {
	this->skilleffect = effect;
}
QString ShowLabel::getSkillEffect() {
	return this->skilleffect;
}
//SkillButton是用来显示技能信息的
SkillButton::SkillButton(QWidget* parent) :QCommandLinkButton(parent) {
	this->skillcost = 0;
	this->skillname = "\0";
	this->skillhurt = 0;
	this->skillattribute = "\0";
	this->skilltype = "\0";
	this->skilllevel = 0;
	this->skillrange = "\0";
}
SkillButton::SkillButton(const QString& text1, const QString& text2, QWidget* parent) : QCommandLinkButton(text1, text2, parent) {
	this->skillcost = 0;
	this->skillname = text1;
	this->skillhurt = 0;
	this->skillattribute = "\0";
	this->skilltype = "\0";
	this->skilllevel = 0;
	this->skillrange = "\0";
}
SkillButton::SkillButton(Skill* s, QWidget* parent) : QCommandLinkButton((s->name + "%1%2").arg(" Hurt: ").arg(s->hurt), QString("Cost : %1").arg(s->cost), parent) {
	this->skillcost = s->cost;
	this->skillname = s->name;
	this->skillhurt = s->hurt;
	this->skillattribute = "\0";
	this->skilltype = "\0";
	this->skilllevel = 0;
	this->skillrange = "\0";
}
void ShowLabel::setbutton(SkillButton* s) {
	this->button->setSkillName(s->getSkillName());
	this->button->setSkillHurt(s->getSkillHurt());
	this->button->setSkillCost(s->getSkillCost());
}
void SkillButton::setSkillName(const QString& name) {
	this->skillname = name;
}
void SkillButton::setSkillHurt(const int& hurt) {
	this->skillhurt = hurt;
}
void SkillButton::setSkillCost(const int& cost) {
	this->skillcost = cost;
}
void SkillButton::setSkillAttribute(const QString& attribute) {
	this->skillattribute = attribute;
}
void SkillButton::setSkillType(const QString& type) {
	this->skilltype = type;
}
void SkillButton::setSkillLevel(const QString& level) {
	this->skilllevel = level.toInt();
}
void SkillButton::setSkillRange(const QString& range) {
	this->skillrange = range;
}

QString SkillButton::getSkillName() {
	return this->skillname;
}
QString SkillButton::getSkillAttribute() {
	return this->skillattribute;
}
QString SkillButton::getSkillType() {
	return this->skilltype;
}
QString SkillButton::getSkillRange() {
	return this->skillrange;
}

int SkillButton::getSkillCost() {
	return this->skillcost;
}
int SkillButton::getSkillHurt() {
	return this->skillhurt;
}
int SkillButton::getSkillLevel() {
	return this->skilllevel;
}

//设置label的边框
void setlabelframe(QLabel* q, bool t) {
	q->setFrameShape(QFrame::Box);
	q->setFrameShadow(QFrame::Sunken);
	q->setStyleSheet("border-width: 1px;border-style: solid;backgroundcolor:rgb(255,255,255);border-color: rgb(0, 0, 0);");

}