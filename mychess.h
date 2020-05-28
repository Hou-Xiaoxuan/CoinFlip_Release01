#ifndef MYCHESS_H
#define MYCHESS_H
#include <QMainWindow>
#include<QMenuBar>
#include<QAction>
#include<QPainter>
#include<QPixmap>
#include<QTimer>
#include<QLabel>
#include<QPushButton>
class MyChess : public QPushButton
{
    Q_OBJECT
public:
    explicit MyChess(bool state,QWidget *parent = nullptr);
    const static QString str[9];//声明
    QString str_now;
    bool isOver;
    int posx,posy;
    int ii,jj;
    //翻面
    QTimer * timer1,* timer2;
    void change();

signals:

};



#endif // MYCHESS_H
