#include "mainscene.h"
#include "ui_mainscene.h"
#include "mypushbutton.h"
#include<QTimer>
#include<QPainter>
#include<QDebug>
#include<QSound>//多媒体模块 音效
MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    //配置主场景

     //设定固定大小
    setFixedSize(320,588);

    //设定图标
    setWindowIcon(QIcon(":/res/Coin0001.png"));

    //设置标题
    setWindowTitle("翻金币");

    //退出按钮实现
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });

    //准备开始按钮音效
    QSound *startsound=new QSound(":/res/TapButtonSound.wav");

    //开始按钮
    Mypushbutton *startbtn=new Mypushbutton(":/res/MenuSceneStartButton.png");//通过自定义封装的Mypushbutton类实现对开始按钮特殊图片加载
    startbtn->setParent(this);//设置开始按钮继承当前类mainwidget,放在当前窗口
    startbtn->move(this->width()*0.5 - startbtn->width()*0.5,this->height()*0.7);//设置将其左右居中

    //实例化选择关卡场景
    choosescene=new ChooselevelScene;

    //加入对选择场景返回主场景监听信号
    connect(choosescene,&ChooselevelScene::chooseSceneBack,[=](){
        //从选关场景返回主场景依然保持位置相同//位置优化
        this->setGeometry(choosescene->geometry());
        choosescene->hide();//关卡场景隐藏
        this->show();//主场景显示
    });
    connect(startbtn,&Mypushbutton::clicked,[=](){
        qDebug()<<"点击开始";
        startsound->play();//播放音效
        startbtn->zoom1();//下跳动画
        startbtn->zoom2();//上跳动画

        //延时进入到选择关卡场景
        QTimer::singleShot(500,this,[=](){
            //设置选关场景位置与当前主窗口位置相同//位置优化
            choosescene->setGeometry(this->geometry());

            //主场景隐藏
            this->hide();
            //显示选择关卡场景
            choosescene->show();
        });

    });
}
void MainScene::paintEvent(QPaintEvent *)//创建绘图事件
{
    //设置背景图片
   QPainter painter(this);
   QPixmap pix;
   pix.load(":/res/PlayLevelSceneBg.png");
   painter.drawPixmap(0,0,this->width(),this->height(),pix);
   //画背景图标
   pix.load(":/res/Title.png");
   pix.scaled(pix.width()*0.5,pix.height()*0.5);
   painter.drawPixmap(0,0,pix);
}


MainScene::~MainScene()
{
    delete ui;
}

