#include "chooselevelscene.h"
#include<QTimer>
#include<QMenuBar>
#include<QPainter>
#include<QDebug>
#include<QLabel>
#include"mypushbutton.h"
#include<QSound>
ChooselevelScene::ChooselevelScene(QWidget *parent) : QMainWindow(parent)
{
    //设定固定大小
   setFixedSize(320,588);

   //设定图标
   setWindowIcon(QIcon(":/res/Coin0001.png"));

   //设置标题
   setWindowTitle("关卡选择");

   //不通过UI创建，通过代码创建 菜单栏
   QMenuBar * bar = menuBar();
   setMenuBar(bar);

   //创建开始菜单
   QMenu * starMenu= bar->addMenu("开始");
    //创建退出菜单项
   QAction *quitaction=starMenu->addAction("退出");

   //点击退出  退出游戏
   connect(quitaction,&QAction::triggered,[=](){
       this->close();
   });


   //准备关卡按钮音效
   QSound *choosesound=new QSound(":/res/TapButtonSound.wav");
   //准备返回按钮音效
   QSound *backsound=new QSound(":/res/BackButtonSound.wav");



   //返回按钮
   Mypushbutton *backbtn=new Mypushbutton(":/res/BackButton.png",":/res/BackButtonSelected.png");
   backbtn->setParent(this);//放在当前窗口
   backbtn->move(this->width()- backbtn->width(),this->height()-backbtn->height());//设置将其左右居中

   //点击返回  对Mypushbutton中鼠标点击按下和释放进行重写 （进行拦截判断）
   connect(backbtn,&Mypushbutton::clicked,[=](){
       backsound->play();//播放音效
       qDebug()<<"点击返回";
       //主场景监听返回信号(延时反应)
       QTimer::singleShot(350,this,[=](){
           emit this->chooseSceneBack();
       });
   });


   //关卡按钮
   for(int i=0;i<20;i++)
   {
       Mypushbutton *menubtn=new Mypushbutton(":/res/LevelIcon.png");
       menubtn->setParent(this);//放在当前窗口
       menubtn->move(25+i%4*70,130+i/4*70);//一层for循环通过“%”，“/”构造出二维矩阵

       //监听关卡按钮的点击事件
       connect(menubtn,&Mypushbutton::clicked,[=](){

           choosesound->play();//播放音效
           QString str=QString("选择第 %1 关").arg(i+1);
           qDebug()<<str;

           //进入游戏场景

           this->hide();//隐藏当前场景（选关场景）
           play=new PlayScene(i+1);//创建游戏场景

           //设置游戏场景位置与选关场景一致  位置优化
           play->setGeometry(this->geometry());
           play->show();//显示

           //监听游戏场景中的back按钮的返回信号，监听到后显示选关场景，delete掉play场景
           connect(play,&PlayScene::playSceneBack,[=](){
               this->setGeometry(play->geometry());//位置优化
               this->show();
               delete play;
               play=NULL;
           });
       });

       //通过label控件覆盖实现关卡按钮文字显示
       QLabel *label=new QLabel;
       label->setParent(this);
       label->setFixedSize(menubtn->width(),menubtn->height());//设置与menubtn同样大小尺寸，完美覆盖
       label->setText(QString::number(i+1));
       label->move(25+i%4*70,130+i/4*70);//位置布局的移动与menubtn保持一致

       //设置label上的文字对齐方式 水平居中且垂直居中
       label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

       //label覆盖，menubtn监听受阻，需要设置鼠标点击穿透属性
       label->setAttribute(Qt::WA_TransparentForMouseEvents);
   }
}
void ChooselevelScene::paintEvent(QPaintEvent *)//创建绘图事件
{
    //设置背景图片
   QPainter painter(this);
   QPixmap pix;
   pix.load(":/res/OtherSceneBg.png");
   painter.drawPixmap(0,0,this->width(),this->height(),pix);
   //画背景图标
   pix.load(":/res/Title.png");
   pix.scaled(pix.width()*0.5,pix.height()*0.5);
   painter.drawPixmap(30,30,pix);
}
