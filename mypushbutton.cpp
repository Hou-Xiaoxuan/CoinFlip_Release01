#include "mypushbutton.h"

MyPushbutton::MyPushbutton(QWidget *parent) : QPushButton(parent)
{


}
MyPushbutton::MyPushbutton(const QString &a,const QString b)
{
    normalImg=a;
    pressImg=b;
    QPixmap Pixmap;
    Pixmap.load(normalImg);
    this->setFixedSize(Pixmap.width(),Pixmap.height() );

    this->setStyleSheet("QPushButton{border:0Px;}");// 作用：是图片周围的留白消失
    this->setIcon(Pixmap);
    this->setIconSize( QSize(Pixmap.width(),Pixmap.height()) );


}

void MyPushbutton::bounce1(int len)
{
    QPropertyAnimation * animation=new QPropertyAnimation(this,"geometry");

    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));//起始位置
    animation->setEndValue(QRect(this->x(),this->y()+len,this->width(),this->height()));//结束位置
    animation->setEasingCurve(QEasingCurve::OutBounce);//运动方式
    animation->start();
}
void MyPushbutton::bounce2(int len)
{
    QPropertyAnimation * animation=new QPropertyAnimation(this,"geometry");

    animation->setStartValue(QRect(this->x(),this->y()+len,this->width(),this->height()));//起始位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));//结束位置
    animation->setEasingCurve(QEasingCurve::OutBounce);//运动方式
    animation->start();
}


 void MyPushbutton:: mousePressEvent(QMouseEvent*e)
 {
     if(this->pressImg!=" ")
     {
         QPixmap Pixmap;
         Pixmap.load(pressImg);
         this->setFixedSize(Pixmap.width(),Pixmap.height() );
         this->setStyleSheet("QPushButton{border:0Px;}");
         this->setIcon(Pixmap);
         this->setIconSize( QSize(Pixmap.width(),Pixmap.height()) );
     }
     return QPushButton:: mousePressEvent(e);

 }
 void MyPushbutton:: mouseReleaseEvent(QMouseEvent*e)
 {
     if(this->pressImg!=" ")
     {
         QPixmap Pixmap;
         Pixmap.load(normalImg);
         this->setFixedSize(Pixmap.width(),Pixmap.height() );
         this->setStyleSheet("QPushButton{border:0Px;}");
         this->setIcon(Pixmap);
         this->setIconSize( QSize(Pixmap.width(),Pixmap.height()) );
     }
     return QPushButton:: mouseReleaseEvent(e);
 }
