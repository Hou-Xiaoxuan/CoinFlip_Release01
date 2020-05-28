#include "mychess.h"
#include<QDebug>
const QString MyChess::str[9]={//定义
   " ",
   ":/Coin0001.png",
   ":/Coin0002.png",
   ":/Coin0003.png",
   ":/Coin0004.png",
   ":/Coin0005.png",
   ":/Coin0006.png",
   ":/Coin0007.png",
   ":/Coin0008.png"
};

MyChess::MyChess(bool state,QWidget *parent) : QPushButton(parent)
{
    QPixmap pixmap=str[1];
    str_now= state==true?str[1]:str[8];
    qDebug()<<str_now;
    this->setFixedSize(pixmap.width(),pixmap.height());
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(QIcon(str_now));
    this->setIconSize(QSize(pixmap.width(),pixmap.height()));
    this->ii=1;
    this->jj=8;
    this->isOver=false;
    timer1=new QTimer(this);//监听正T->F的信号
    connect(timer1,&QTimer::timeout,[=]()
    {
    //不能用static，同时反转时会混淆
        //我好菜啊啊啊啊啊啊啊啊啊啊啊啊啊啊啊
        QPixmap pixmap;

            pixmap.load(str[this->ii]);
            this->setFixedSize(pixmap.width(),pixmap.height());
            this->setStyleSheet("QPushButton{border:0px}");
            this->setIcon(QIcon(pixmap));
            this->setIconSize(QSize(pixmap.width(),pixmap.height()));

        this->ii++;
        if(this->ii>8){
            this->ii=1;
            str_now=str[8];
            timer1->stop();
        }
    });
    timer2=new QTimer(this);//监听F->T的信号
    connect(timer2,&QTimer::timeout,[=](){

        QPixmap pixmap;

            pixmap.load(str[this->jj]);
            this->setFixedSize(pixmap.width(),pixmap.height());
            this->setStyleSheet("QPushButton{border:0px}");
            this->setIcon(QIcon(pixmap));
            this->setIconSize(QSize(pixmap.width(),pixmap.height()));

        this->jj--;
        if(this->jj<1){
            this->jj=8;
            str_now=str[1];
            timer2->stop();
            qDebug()<<str_now<<":"<<posx<<" "<<posy;
        }
    });

}
//翻面
void MyChess::change()
{

    if(this->str_now==str[1])//现在是金面（true）
    {
        timer1->start(20);

    }

    else if(str_now==str[8]){
        timer2->start(20);
    }

}
