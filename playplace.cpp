#include "playplace.h"
#include"mychess.h"
#include<QDebug>
#include<iostream>
#include<QFile>
#include<QSound>
const QString PlayScene::DefaultData[21]={
    "",
    ":/fault/01.txt",
    ":/fault/02.data",
    ":/fault/03.data",
    ":/fault/04.data",
    ":/fault/05.data",
    ":/fault/06.data",
    ":/fault/07.data",
    ":/fault/08.data",
    ":/fault/09.data",
    ":/fault/10.data",
    ":/fault/11.data",
    ":/fault/12.data",
    ":/fault/13.data",
    ":/fault/14.data",
    ":/fault/15.data",
    ":/fault/16.data",
    ":/fault/17.data",
    ":/fault/18.data",
    ":/fault/19.data",
    ":/fault/20.data",

};

PlayScene::PlayScene(int a,QWidget *parent) : QMainWindow(parent)
{
    levelIndex=a;

    this->isWin=false;
    this->checked=false;
    setFixedSize(600,800);//固定窗口大小
    this->setWindowIcon(QIcon(":/Coin0001.png"));
    setWindowTitle("加油!");

    QMenuBar * bar= new QMenuBar();
    QMenu * menue_start= new QMenu("开始");
    QAction *action_close= new QAction("退出");
     QAction *action_back= new QAction("返回");
    this->setMenuBar(bar);
    bar->addMenu(menue_start);
    menue_start->addAction(action_back);
    menue_start->addAction(action_close);
    connect(action_close,&QAction::triggered,[=](){
        this->close();
    });
    connect(action_back,&QAction::triggered,[=](){
        QTimer::singleShot(300,this,[=](){
            this->hide();
            parent->show();
        });
    });

    //返回按钮
    MyPushbutton *btn_back=new MyPushbutton(":/BackButton.png",":/BackButtonSelected.png");
     QSound *BackSound=new QSound(":/TapButtonSound.wav") ;
    btn_back->setParent((this));// /忘了这一步……
    btn_back->move(this->width()-btn_back->width(),this->height()-btn_back->height());
    connect(btn_back,&QPushButton::clicked,[=](){
        BackSound->play();
        QTimer::singleShot(200,this,[=](){
            parent->setGeometry(this->geometry());
            this->hide();//本窗口隐藏
            parent->show();//展示选择窗口
        });
    });

    //显示关卡数目
    QLabel *label=new QLabel(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(21);
    label->setFont(font);
    QString  str=QString("关卡数目:  %1 ").arg(QString::number(this->levelIndex));
   qDebug()<<str;
    label->setText(str);
    label->setGeometry(QRect(30,this->height()-50,250,50));

    //胜利的图片
    QLabel *winLabel=new QLabel(this);
    QPixmap pix_win;
    pix_win.load(":/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,pix_win.width(),pix_win.height());
    winLabel->move((this->width()-pix_win.width())/2,-pix_win.height());
    winLabel->setPixmap(pix_win);

    //显示金币的图片
//    int state[5][5];
//    std::freopen(PlayScene::DefaultData[this->levelIndex].toStdString().c_str(),"r",stdin);
//   qDebug()<<DefaultData[this->levelIndex];
//    for(int i=1;i<=4;i++)
//        for(int j=1;j<=4;j++){
//            std::cin>>state[i][j];
//           qDebug()<<state[i][j];
//        }
//    std::fclose(stdin);

    MyChess *chess[5][5];
    QString state;
    QString path=(DefaultData[this->levelIndex]);
    qDebug()<<path;
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    state=file.readLine();
    for(int i=0;i<state.size();i++)
          qDebug()<<state[i];
    file.close();
    for(int i=1;i<=4;i++)
        for(int j=1;j<=4;j++)
        {
            QLabel* label=new QLabel(this);
            QPixmap pixmap(":/BoardNode(1).png");
            label->setPixmap(pixmap);
            label->setGeometry(0,0,pixmap.width(),pixmap.height());
            label->move(70+i*80,200+j*80);

            //创建金币
            chess[i][j]=new MyChess(state[(i-1)*4+j-1]=='1'?true:false,this);
            chess[i][j]->move(72+i*80,203+j*80);
            chess[i][j]->posx=i;
            chess[i][j]->posy=j;
        }
    QSound *fipeSound=new QSound(":/ConFlipSound.wav");
    QSound *winSound=new QSound(":/LevelWinSound.wav");
    for(int i=1;i<=4;i++)
        for(int j=1;j<=4;j++)
        {
            connect(chess[i][j],&QPushButton::clicked,[=]()
            {
                if(this->isWin==true or checked==true) return;
                checked=true;
                fipeSound->play();
                chess[i][j]->change();
                int x=chess[i][j]->posx;
                int y=chess[i][j]->posy;
//                qDebug()<<"点击了"<<x<<" "<<y;
                QTimer::singleShot(100,this,[=](){
                    if(x>1) chess[x-1][y]->change();    /*qDebug()<<"正常1";*/
                    if(x<4) chess[x+1][y]->change();   /* qDebug()<<"正常2";*/
                    if(y>1) chess[x][y-1]->change();    /*qDebug()<<"正常3";*/
                    if(y<4) chess[x][y+1]->change();    /*qDebug()<<"正常4";*/

                });


                QTimer::singleShot(350,this,[&](){
//                    for(int i=1;i<=4;i++)
//                    for(int j=1;j<=4;j++)
//                        qDebug()<<chess[i][j]->str_now;
//                    //判断是否胜利
                    bool flag=true;
                    for(int i=1;i<=4;i++)
                        for(int j=1;j<=4;j++)
                            if(chess[i][j]->str_now!=MyChess:: str[1]){
//                                qDebug()<<chess[i][j]->posx<<" "<<chess[i][j]->posy<<chess[i][j]->str_now<<" and "<< MyChess::str[1];
                                flag=false;
                            }
//                    qDebug()<<flag<<":::"<<MyChess::str[1];;
                    if(flag==true)
                    {
//                        qDebug()<<flag<<"胜利了";
                        winSound->play();
                        this->isWin=true;
                        //使得点击失效
                        for(int i=1;i<=4;i++)
                        for(int j=1;j<=4;j++)
                            chess[i][j]->isOver=true;
                        //落下标志
                        QPropertyAnimation *animation=new QPropertyAnimation(winLabel,"geometry");
                        animation->setDuration(1000);//下落事件
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+200,winLabel->width(),winLabel->height()));
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        animation->start();
                    }
                    QTimer::singleShot(350,this,[=](){//0.35秒捏只能进行一次操作
                        checked=false;
                    });
                });

            });
        }










}
void PlayScene::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pixmap;
    pixmap.load(":/OtherSceneBg.png");
    painter.drawPixmap(0,0,600,800,pixmap);

    pixmap.load(":/Title.png");
    painter.drawPixmap(40,30,pixmap.width(),pixmap.height(),pixmap);
}
