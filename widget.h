#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "gamemap.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent* event);
    void DrawMap();//画地图
    ~Widget();

private:
    Ui::Widget *ui;

    GameMap* mPMap;

    QPainter* mMapPainter;
};
#endif // WIDGET_H
