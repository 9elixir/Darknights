#include"QtBattel.hpp"
//QtBattel是用来显示战斗界面的
QtBattel::QtBattel(QWidget* parent, std::string BattelBackPath, std::string littleimgPath) {
	
	turn_num = 0;
	window = new QWidget(nullptr);
	window->setFixedSize(QSize(960, 768));
	
	window->setWindowFlags(Qt::WindowMinimizeButtonHint);//只允许最小化

	scrollArea = nullptr;

	double PercentHeight = window->height() / 810.0;
	double PercentWidth = window->width() / 1440.0;

	//回合数
	turnLabel = new QLabel(window);
	
	std::string turn_string = std::to_string(turn_num);
	turnLabel->setText(turn_string.data());
	turnLabel->setFont(QFont("宋体", 18, 100, true));
	QSize turnLabelSize(QFontMetrics(QFont("宋体", 18, 100)).boundingRect(turn_string.data()).width()+20, QFontMetrics(QFont("宋体", 12, 100)).height()+20);
	turnLabel->setFixedSize(turnLabelSize);
	turnLabel->move(690*PercentWidth,45*PercentHeight);

	//上方的血条蓝条布局

	bloodLabel1 = new QLabel("HP: ", window);	
	bloodLabel1->setFixedSize(QSize(540*PercentWidth, 90*PercentHeight));
	bloodLabel1->move(0, 0);
	
	std::string bloodpix_path= "BaseImages\\blood.png";
	bloodImg1 = new QLabel(window);
	QPixmap bloodpix(bloodpix_path.data());
	if (bloodpix.isNull())bloodLabel1->setText("HPLOAD WRONG");
	QSize qsizeblood(440 * PercentWidth*(this->blood1_now * 1.0 / this->blood1_max), 90*PercentHeight);//label总共540，前100不用
	bloodImg1->setPixmap(bloodpix.scaled(qsizeblood));
	bloodImg1->setFixedSize(qsizeblood);
	bloodImg1->move(100*PercentWidth, 0*PercentHeight);

	magicLabel1 = new QLabel("MP: ", window);
	magicLabel1->setFixedSize(QSize(540*PercentWidth, 90*PercentHeight));
	magicLabel1->move(0*PercentWidth, 90*PercentHeight);
	bloodLabel2 = new QLabel("HP: ", window);
	bloodLabel2->setFixedSize(QSize(540 * PercentWidth, 90 * PercentHeight));
	bloodLabel2->move(900*PercentWidth, 0*PercentHeight);
	magicLabel2 = new QLabel("MP: ", window);
	magicLabel2->setFixedSize(QSize(540 * PercentWidth, 90 * PercentHeight));
	magicLabel2->move(900*PercentWidth, 90*PercentHeight);

	//设置字体形式大小和对齐方式
	bloodLabel1->setFont(QFont("宋体", 14, 100, true));
	bloodLabel2->setFont(QFont("宋体", 14, 100, true));
	magicLabel1->setFont(QFont("宋体", 14, 100, true));
	magicLabel2->setFont(QFont("宋体", 14, 100, true));

	bloodLabel1->setContentsMargins(40*PercentWidth, 10*PercentHeight, 0*PercentWidth, 0*PercentHeight);
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

	characterLabel1->setFixedSize(QSize(300*PercentWidth, 400*PercentHeight));
	characterLabel1->move(150*PercentWidth, 200*PercentHeight);
	characterLabel2->setFixedSize(QSize(300 * PercentWidth, 400 * PercentHeight));
	characterLabel2->move(990*PercentWidth, 200*PercentHeight);
	//设置图片
	charactermov1 = new QMovie("imgs\\Skadi1.gif");
	charactermov2 = new QMovie("imgs\\Tom.gif");
	charactermov1->resized(QSize(300 * PercentWidth, 400 * PercentHeight));
	charactermov2->resized(QSize(300 * PercentWidth, 400 * PercentHeight));
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
	QPixmap smallImage(littleimgPath.data()); // 更换为你的图片路径
	smallImageLabel->setFixedSize(QSize(360*PercentWidth, 200*PercentHeight));//确定框的大小，图片只会载入相应位置的内容
	smallImageLabel->move(45*PercentWidth, 610*PercentHeight);
	
	//smallImageLabel->setPixmap(smallImage.scaledToWidth(360));
	//smallImageLabel->setPixmap(smallImage.scaledToHeight(200));
	smallImageLabel->setPixmap(smallImage.scaled(360*PercentWidth,200*PercentHeight));


	// 中间二分之一的按钮布局

	button1 = new SkillButton("技能 1", "MP : 1", window);
	button2 = new SkillButton("技能 2", "Mp : 2", window);
	button3 = new SkillButton("技能 3", "Mp : 3", window);
	button4 = new SkillButton("技能 4", "Mp : 4", window);

	//设置按钮大小和位置
	button1->setFixedSize(QSize(270*PercentWidth, 90*PercentHeight));
	button1->move(405*PercentWidth, 617 * PercentHeight);
	button2->setFixedSize(QSize(270 * PercentWidth, 90 * PercentHeight));
	button2->move(720*PercentWidth, 617 * PercentHeight);
	button3->setFixedSize(QSize(270 * PercentWidth, 90 * PercentHeight));
	button3->move(405* PercentWidth, 713*PercentHeight);
	button4->setFixedSize(QSize(270 * PercentWidth, 90 * PercentHeight));
	button4->move(720* PercentWidth, 713*PercentHeight);

	//取消button自带的“->"箭头
	button1->setIcon(QIcon());
	button2->setIcon(QIcon());
	button3->setIcon(QIcon());
	button4->setIcon(QIcon());

	// 取消焦点，否则按键监听无法使用
	button1->setFocusPolicy(Qt::NoFocus);
	button2->setFocusPolicy(Qt::NoFocus);
	button3->setFocusPolicy(Qt::NoFocus);
	button4->setFocusPolicy(Qt::NoFocus);


	//右侧四分之一的标签布局
	label = new ShowLabel("战斗开始！", window);

	//label = new MyLabel("111111111122222222223333333333444444444455555555556666666666");
	/*
	label1 = new ShowLabel("1", window);
	label2 = new ShowLabel(" 2", window);
	label3 = new ShowLabel("  3", window);
	label4 = new ShowLabel("   4", window);

	label1->readinskill(button1);
	label2->readinskill(button2);
	label3->readinskill(button3);
	label4->readinskill(button4);
	*/
	//label->setText("2");
	label->setFont(QFont("宋体", 12, 100));//12号字体汉字，刚好能在420的宽度下显示25个；14号字体数字，加粗刚好能在420的宽度下显示50个
	label->setAlignment(Qt::AlignTop | Qt::AlignLeft);//设置文字对齐方式
	label->setFont_height (QFontMetrics(QFont("宋体", 12, 100)).height());
	label->setMyHeight(200 * PercentHeight);
	label->setMyWidth(400 * PercentWidth);
	//int usetime = 0;
	connect(button1, &SkillButton::clicked, this, &QtBattel::button_clicked_new);
	connect(button1, &SkillButton::clicked, label, &ShowLabel::button_clicked);
	connect(button2, &SkillButton::clicked, this, &QtBattel::button_clicked_new);
	connect(button2, &SkillButton::clicked, label, &ShowLabel::button_clicked);
	connect(button3, &SkillButton::clicked, this, &QtBattel::button_clicked_new);
	connect(button3, &SkillButton::clicked, label, &ShowLabel::button_clicked);
	connect(button4, &SkillButton::clicked, this, &QtBattel::button_clicked_new);
	connect(button4, &SkillButton::clicked, label, &ShowLabel::button_clicked);


	//int i = 0;//一个简陋计时器
	/*while (!if_fight_over) {

		connect(button1, &SkillButton::clicked, label, &ShowLabel::button_clicked);
		connect(button2, &SkillButton::clicked, label, &ShowLabel::button_clicked);
		connect(button3, &SkillButton::clicked, label, &ShowLabel::button_clicked);
		connect(button4, &SkillButton::clicked, label, &ShowLabel::button_clicked);
		//temp->ListAppend(temp->getNext());
		//temp = temp->getNext();
		i++;
		if (i == 5) {
			if_fight_over = true;
		}
	}*/

	//右侧四分之一的滚动区域布局
	QScrollArea* scrollArea = new QScrollArea{ window };
	scrollArea->setBackgroundRole(QPalette::Dark);
	scrollArea->setWidgetResizable(false);
	scrollArea->setFixedSize(QSize(420*PercentWidth, 200*PercentHeight));
	scrollArea->move(1020*PercentWidth, 610*PercentHeight);
	scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
	int barheight = scrollArea->verticalScrollBar()->height();
	qDebug() << "VBar:" << scrollArea->verticalScrollBar()->width() << " " << scrollArea->verticalScrollBar()->height();
	qDebug() << "HBar:" << scrollArea->horizontalScrollBar()->width() << " " << scrollArea->horizontalScrollBar()->height();
	label->setMyWidth(scrollArea->width() - barheight +10);//无论怎样跳绳大小，水平和垂直都是100宽 30高。为什么垂直的滚条宽比高大? 加10是因为实际应用中label还是没占满剩余位置
	scrollArea->setWidget(label);
	//this->bloodImg1->show();
	window->show();
}
void QtBattel::turnIn() {
	button1->setEnabled(false);//禁止再点击按钮
	button2->setEnabled(false);
	button3->setEnabled(false);
	button4->setEnabled(false);
}

void QtBattel::turnBegin() {
	
	std::string turn_string = std::to_string(turn_num);
	turnLabel->setText(turn_string.data());
	turnLabel->setFont(QFont("宋体", 18, 100, true));
	QSize turnLabelSize(QFontMetrics(QFont("宋体", 18, 100)).boundingRect(turn_string.data()).width() + 20, QFontMetrics(QFont("宋体", 12, 100)).height() + 20);
	turnLabel->setFixedSize(turnLabelSize);

	button1->setEnabled(true);
	button2->setEnabled(true);
	button3->setEnabled(true);
	button4->setEnabled(true);
}
void QtBattel::turnEnd() {
	turn_num++;
	turnBegin();
}
void setlabelframe(QLabel* q, bool t) {
	q->setFrameShape(QFrame::Box);
	q->setFrameShadow(QFrame::Sunken);
	q->setStyleSheet("border-width: 1px;border-style: solid;backgroundcolor:rgb(255,255,255);border-color: rgb(0, 0, 0);");

}

//ShowLabel是用来显示战斗信息的
ShowLabel::ShowLabel(QWidget* parent) :QLabel(parent) {
	this->next = nullptr;
	this->discription = "\0";
	this->contents_rows = 1;
	this->QLabel::setFixedSize(this->width, this->height);
	this->if_use_button = false;
}
ShowLabel::ShowLabel(const QString& text, QWidget* parent) : QLabel(text, parent) {
	this->next = nullptr;
	this->discription = text;
	this->QLabel::setFixedSize(this->width, this->height);
	this->setFont(QFont("宋体", 12, 100));//12号字体汉字，刚好能在420的宽度下显示25个；14号字体数字，加粗刚好能在420的宽度下显示50个
	this->contents_rows = 1;
	this->wrap(true,0);//自动换行
	this->setAlignment(Qt::AlignTop | Qt::AlignLeft);//设置文字对齐方式
	this->move(this->originx, this->originy);
	this->if_use_button = false;
}
ShowLabel::~ShowLabel() {
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
	this->discription = this->discription + QString("\n")+text;
	this->setFont(QFont("宋体", 12, 100));//12号字体汉字，刚好能在420的宽度下显示25个；14号字体数字，加粗刚好能在420的宽度下显示50个
	this->setAlignment(Qt::AlignTop | Qt::AlignLeft);//设置文字对齐方式
	this->QLabel::setText(this->discription);
}

void ShowLabel::setNext(ShowLabel* next) {
	this->next = next;
}
void ShowLabel::wrap(bool b,int last_count) {
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
		//QString存储字符串采用的是Unicode码，每一个字符是一个16位的QChar，而不是8位的char，所以Qstring处理中文字符没有问题，而且一个汉字算作是一个字符。
		/*if (uni >= 0x4E00 && uni <= 0x9FA5)
		{
			sumwidth += this->cwidth;
			//这个字符是中文
		}
		//else if (uni >= 0x0000 && uni <= 0x0009 ) {
			//sumwidth += this->nwidth;
		//}
		else if (uni == QChar('\n').unicode()) {
			sumwidth = 0;
			contents_rows++;
			continue;
		}
		else {
			sumwidth += this->nwidth;
		}*/
		/*if (i > 1) {
			if ( sumwidth >= (this->swidth)|| ( (cha == QString("害")) && this->discription.at(i - 1) == QString("伤") ) ) {
				if (i + 1 < this->discription.size()&&this->discription.at(i+1)!='\n')
				{
					this->discription.insert(i + 1, QString("\n"));
					sumwidth = 0;
				}
				}
		}*/

		if (uni == QChar('\n').unicode()) {
			str = QString("");
			contents_rows++;
			continue;
		}
		str = str + cha;
		sumwidth = QFontMetrics(QFont("宋体", 12, 100)).boundingRect(str).width();
		if (i > 1) {
			qDebug() << str << " " << sumwidth<<" this width="<< this->width;
			if (sumwidth> (this->width) ) {
				if (i + 1 < this->discription.size() && this->discription.at(i + 1) == '\n')
				{
					continue;
				}
				this->discription.insert(i , QString("\n"));
				sumwidth = 0;
				i--;
			}
			else if ((cha == QString("害")) && this->discription.at(i - 1) == QString("伤")) {
				this->discription.insert(i+1, QString("\n"));
			}

		}
	}
	
	this->QLabel::setText(this->discription);
	this->QLabel::setFixedWidth(this->width);
	this->QLabel::setFixedHeight(contents_rows* (this->font_height+3));
}
void QtBattel::BloodChange(QLabel*&ChangeLabel,int new_blood1_now) {

	double PercentHeight = window->height() / 810.0;
	double PercentWidth = window->width() / 1440.0;
	QSize size1= ChangeLabel->size();
	QSize size2=size1;
	int new_width = 440 * PercentWidth * (new_blood1_now*1.0 / this->blood1_max);
	size2.setWidth(new_width);
	
	// 创建属性动画，将 QLabel 的 pixmap 属性从起始图片渐变到目标图片
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

	connect(animation, &QPropertyAnimation::valueChanged, [&ChangeLabel,new_width](const QVariant& value) {
		//double Percent = value.toInt() / 100.0;
		qDebug() << value.toSize();
		//int now_width = Percent * (new_width - geo1.width()) + geo1.width();
		int now_width = value.toSize().width();
		QPixmap pixmap = ChangeLabel->pixmap().scaledToWidth(now_width);
		//QPixmap pixmap("imgs//interlude_01.png");
		ChangeLabel->setFixedWidth(now_width);
		ChangeLabel->setPixmap(pixmap);
	});

	connect(animation, &QPropertyAnimation::finished, [&ChangeLabel,new_width,new_blood1_now,this]() {
		ChangeLabel->setPixmap(ChangeLabel->pixmap().scaledToWidth(new_width));
		ChangeLabel->setFixedWidth(new_width);
		this->blood1_now = new_blood1_now;
		delete (this->animation);
		this->animation = nullptr;
		this->turnEnd();
		});
	animation->start();
}
void ShowLabel::button_clicked() {
	//this->move(this->originx, this->originy);
	int last_count = this->discription.size();
	this->show = this->cname + QString("%1%2%3%4%5%6%7%8");
	this->setText(show.arg("对").arg(ename).arg("使用了").arg("韩国的虾米诺手啊奥利安菲冰卧槽冰不许爆冰既是刀冰又是解药").arg("造成了").arg(hurt).arg("点伤害").arg("效果显著"));
	this->wrap(true,last_count);
	//his->if_use_button = true;
}
void QtBattel::button_clicked_new() {
	this->turnIn();
	if (this->blood1_now >= 5000)this->BloodChange(this->bloodImg1, this->blood1_now - 2000);
	else this->BloodChange(this->bloodImg1,this->blood1_now + 1000);

	//qDebug() << "Bar:" << scrollArea->verticalScrollBar()->width() << " " << scrollArea->verticalScrollBar()->height();
}
void ShowLabel::setbutton(SkillButton* b) {
	this->button = b;
}
void ShowLabel::readinskill(SkillButton* skill) {
	this->sname = skill->getSkillName();
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
	this->skilleffect = "\0";
}
SkillButton::SkillButton(const QString& text1, const QString& text2, QWidget* parent) : QCommandLinkButton(text1, text2, parent) {
	this->skillcost = 0;
	this->skillname = text1;
	this->skillhurt = 0;
	this->skillattribute = "\0";
	this->skilltype = "\0";
	this->skilllevel = 0;
	this->skillrange = "\0";
	this->skilleffect = "\0";
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
void SkillButton::setSkillEffect(const QString& effect) {
	this->skilleffect = effect;
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
QString SkillButton::getSkillEffect() {
	return this->skilleffect;
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