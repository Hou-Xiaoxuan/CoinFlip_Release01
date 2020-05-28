#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H
//关卡选择 窗口
#include <QMainWindow>
#include<QMenuBar>
#include<QAction>
#include<QPainter>
#include<QPixmap>
#include"mypushbutton.h"
#include"playplace.h"
#include<QTimer>
#include<QLabel>
class ChooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelScene(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent*);
    PlayScene * Play= NULL;

signals:
    void ChooseBack();
};

#endif // CHOOSELEVELSCENE_H
