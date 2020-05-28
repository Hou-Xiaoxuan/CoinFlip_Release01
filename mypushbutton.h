#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H
//继承QWidget，用于创建 开始 和 返回 按钮
#include <QPushButton>
#include<QPainter>
#include<QPropertyAnimation>
#include<QMouseEvent>
class MyPushbutton : public QPushButton
{
    Q_OBJECT

public:
    explicit MyPushbutton(QWidget *parent = nullptr);
    MyPushbutton(const QString &a,const QString b=" ");

    QString  normalImg,pressImg;
    //特效：弹跳函数
    void bounce1(int len=10);
    void bounce2(int len=10);
    //重写鼠标的点击和按下事件
   void mousePressEvent(QMouseEvent*e);
   void mouseReleaseEvent(QMouseEvent*e);
signals:

};

#endif // MYPUSHBUTTON_H
