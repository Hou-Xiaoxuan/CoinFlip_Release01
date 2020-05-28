#ifndef PLAYPLACE_H
#define PLAYPLACE_H

#include <QMainWindow>
#include<QMenuBar>
#include<QAction>
#include<QPainter>
#include<QPixmap>
#include"mypushbutton.h"
#include<QTimer>
#include<QLabel>
#include<QPropertyAnimation>
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    int levelIndex;
    PlayScene(int a,QWidget *parent = nullptr);
    void paintEvent(QPaintEvent*);
    const static QString DefaultData[21];
    bool isWin;
    bool checked;
signals:

};

#endif // PLAYPLACE_H
