#include "chooselevelscene.h"
#include<QDebug>
#include<QSound>
ChooseLevelScene::ChooseLevelScene(QWidget *parent) : QMainWindow(parent)
{
    //窗口布置
    setFixedSize(600,800);//固定窗口大小
    setWindowIcon(QIcon(":/Coin0001.png"));
    setWindowTitle("选择关卡!");

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
//    qDebug()<<btn_back->normalImg;
    connect(btn_back,&QPushButton::clicked,[=](){
        QTimer::singleShot(200,this,[=](){
            BackSound->play();
//            this->hide();//本窗口隐藏
//            parent->show();//展示选择窗口
            //方法2：
            emit ChooseBack();
        });
    });


    //选择关卡
    MyPushbutton *btn_menu[20];
    QSound *Chooses=new QSound(":/TapButtonSound.wav") ;
    for(int i=0;i<20;i++)
    {
        btn_menu[i]=new MyPushbutton(":/LevelIcon.png");
        btn_menu[i]->setParent(this);
        btn_menu[i]->move(90+i%4*120,150+i/4*120);
        QLabel *label=new QLabel;
        label->setParent(this);
        label->setFixedSize(btn_menu[i]->size());
        label->setText(QString::number(i+1));
        label->move(90+i%4*120,150+i/4*120);
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        label->setAttribute(Qt::WA_TransparentForMouseEvents);//点击穿透效果
        connect(btn_menu[i],&QPushButton::clicked,[=](){
            Chooses->play();
            btn_menu[i]->bounce1(2);
            btn_menu[i]->bounce2(2);
//                qDebug()<<i+1;

            Play=new PlayScene(i+1,this);
            QTimer::singleShot(300,this,[=](){
                Play->setGeometry(this->geometry());
                this->hide();
                Play->show();
            });
        });
    }
}


void ChooseLevelScene::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    QPixmap pixmap;
    pixmap.load(":/OtherSceneBg.png");
    painter.drawPixmap(0,0,600,800,pixmap);

    pixmap.load(":/Title.png");
    painter.drawPixmap(40,30,pixmap.width(),pixmap.height(),pixmap);
}
