#include "mainscene.h"
#include "ui_mainscene.h"
#include"chooselevelscene.h"
#include<QSound>
MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    //主场景：
    setFixedSize(600,800);//固定窗口大小
    setWindowIcon(QIcon(":/Coin0001.png"));
    setWindowTitle("开心金币");
    connect(ui->action_close,&QAction::triggered,this,[=](){//推出游戏设置
        this->close();
    });




    //开始按钮
    MyPushbutton *start_btn=new MyPushbutton(":/MenuSceneStartButton.png");
    start_btn->setParent(this);
    start_btn->move(this->width()/2-start_btn->width()/2,this->height()*0.7);

    ChooseLevelScene *chooseScene =new ChooseLevelScene(this);
    connect(chooseScene,&ChooseLevelScene::ChooseBack,this,[=](){
        QTimer::singleShot(100,this,[=](){
            this->setGeometry(chooseScene->geometry());
        chooseScene->hide();
        this->show();
        });
    });
    QSound *startSound=new QSound(":/TapButtonSound.wav");//添加音效
    connect(start_btn,&QPushButton::clicked,[=](){
        startSound->play();//音效
        //点击的弹起特效
        start_btn->bounce1();
        start_btn->bounce2();
        QTimer::singleShot(300,this,[=](){
            this->hide();//本窗口隐藏
            chooseScene->setGeometry(this->geometry());
            chooseScene->show();//展示选择窗口
        });
    });


}

void MainScene::paintEvent(QPaintEvent *)
{
    //通过QPainter设置 主场景图片 和 开始 图标
    QPainter painter(this);
    QPixmap pixmap;
    pixmap.load(":/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,600,800,pixmap);

    pixmap.load(":/Title.png");
    painter.drawPixmap(0,0,pixmap);
}


MainScene::~MainScene()
{
    delete ui;
}

