#include "playscene.h"
#include"mypushbutton.h"
#include"dataconfig.h"
#include"mycoin.h"
#include<QDebug>
#include<QMenuBar>
#include<QPainter>
#include<QTimer>
#include<QLabel>
#include<QPropertyAnimation>
#include<QSound>
/*PlayScene::PlayScene(QWidget *parent) : QMainWindow(parent)
{

}*/

PlayScene::PlayScene(int levelNum)
{
    QString str=QString("已进入第 %1 关").arg(levelNum);
    qDebug()<<str;
    this->levelindex=levelNum;//记录关卡序号

    //设定固定大小
   setFixedSize(320,588);

   //设定图标
   setWindowIcon(QIcon(":/res/Coin0001.png"));

   //设置标题
   setWindowTitle("翻金币");

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


   //准备翻转按钮音效
   QSound *flipsound=new QSound(":/res/ConFlipSound.wav");
   //准备返回按钮音效
   QSound *backsound=new QSound(":/res/BackButtonSound.wav");
   //准备胜利音效
   QSound *winsound=new QSound(":/res/LevelWinSound.wav");

   //返回按钮
   Mypushbutton *backbtn=new Mypushbutton(":/res/BackButton.png",":/res/BackButtonSelected.png");
   backbtn->setParent(this);//放在当前窗口
   backbtn->move(this->width()- backbtn->width(),this->height()-backbtn->height());//设置将其左右居中

   //点击返回  对Mypushbutton中鼠标点击按下和释放进行重写 （进行拦截判断）
   connect(backbtn,&Mypushbutton::clicked,[=](){
       backsound->play();//播放返回音效
       qDebug()<<"点击返回";
       //主场景监听返回信号(延时反应)
       QTimer::singleShot(350,this,[=](){
           emit this->playSceneBack();//playSceneBack()为一个信号槽信号
       });
   });



   //显示胜利图片(隐藏式显示)
   QLabel *winlabel=new QLabel;
   QPixmap tmppix;
   tmppix.load(":/res/LevelCompletedDialogBg.png");
   winlabel->setGeometry(0,0,tmppix.width(),tmppix.height());
   winlabel->setParent(this);
   winlabel->setPixmap(tmppix);
   winlabel->move((this->width()-tmppix.width())*0.5,-tmppix.height());//隐藏式显示

   //显示当前选择关卡数
   QLabel *label=new QLabel;
   label->setParent(this);
   QFont font;
   font.setFamily("华文新魏");
   font.setPointSize(20);
   QString str1=QString("level: %1").arg(this->levelindex);
   //将字体设置到标签控件中
   label->setFont(font);
   label->setText(str1);
   label->setGeometry(30,this->height()-50,120,50);//(x,y.w.h)

   //初始化每个关卡的二维数组
   dataConfig config;
   for(int i=0;i<4;i++)
   {
       for(int j=0;j<4;j++)
       {
           this->gamearray[i][j]=config.mData[this->levelindex][i][j];
       }
   }

   //显示金币翻转背景图
   for (int i=0;i<4;i++)
   {
       for(int j=0;j<4;j++)
       {
           //绘制背景图片
           QLabel* label=new QLabel;
           label->setGeometry(0,0,50,50);
           label->setPixmap(QPixmap(":/res/BoardNode.png"));
           label->setParent(this);
           label->move(57+i*50,200+j*50);
           label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

           //创建金币,按照dataconfig中mdata中默认初始化金银币位置
           QString str;
           if(this->gamearray[i][j]==1)
           {
               str=":/res/Coin0001.png";
           }
           else
           {
               str=":/res/Coin0008.png";
           }
           Mycoin *coin=new Mycoin(str);
           coin->setParent(this);
           coin->move(59+i*50,204+j*50);
           //金币属性
           coin->posx=i;
           coin->poxy=j;
           coin->flag=this->gamearray[i][j];//1->金币  2->银币

           coinarray[i][j]=coin;
           //翻转操作调用接口
           connect(coin,&Mycoin::clicked,[=](){
               flipsound->play();//播放金币翻转音效
               coin->changeflag();
               this->gamearray[i][j]=this->gamearray[i][j]==0?1:0;//翻转结束后的维护

               QTimer::singleShot(300,this,[=](){

                   //翻转周围金币
                   //周围右侧金币翻转条件
                   if(coin->posx+1<4)
                   {
                       coinarray[coin->posx+1][coin->poxy]->changeflag();
                       this->gamearray[coin->posx+1][coin->poxy]=this->gamearray[coin->posx+1][coin->poxy]==0?1:0;
                   }
                   //周围左侧金币翻转条件
                   if(coin->posx-1>=0)
                   {
                       coinarray[coin->posx-1][coin->poxy]->changeflag();
                       this->gamearray[coin->posx-1][coin->poxy]=this->gamearray[coin->posx-1][coin->poxy]==0?1:0;
                   }
                   //周围下侧金币翻转条件
                   if(coin->poxy+1<4)
                   {
                       coinarray[coin->posx][coin->poxy+1]->changeflag();
                       this->gamearray[coin->posx][coin->poxy+1]=this->gamearray[coin->posx][coin->poxy+1]==0?1:0;
                   }
                   //周围上侧金币翻转条件
                   if(coin->poxy-1>=0)
                   {
                       coinarray[coin->posx][coin->poxy-1]->changeflag();
                       this->gamearray[coin->posx][coin->poxy-1]=this->gamearray[coin->posx][coin->poxy-1]==0?1:0;
                   }

                   //判断是否胜利
                   this->iswin=true;
                   for(int i=0;i<4;i++)
                   {
                       for(int j=0;j<4;j++)
                       {
                           if(coinarray[i][j]->flag==false)
                           {
                               this->iswin=false;
                               break;
                           }
                       }
                   }
                   if(this->iswin==true)
                   {
                       winsound->play();//播放胜利音效
                       QString str=QString("第 %1 关游戏胜利").arg(this->levelindex);
                       qDebug()<<str;

                       for(int i=0;i<4;i++)
                       {
                           for(int j=0;j<4;j++)
                           {
                               coinarray[i][j]->win=true;//金币标志置为true，此时用于中断鼠标点击操作判断
                           }
                       }


                       //胜利动画实现
                       //创建动画对象animation
                       QPropertyAnimation * animation=new QPropertyAnimation(winlabel,"geometry");//geometry为特定动画效果“弹跳”

                       //设置动画时间间隔
                       animation->setDuration(1000);

                       //起始位置
                       animation->setStartValue(QRect(winlabel->x(),winlabel->y(),winlabel->width(),winlabel->height()));

                       //结束位置
                       animation->setEndValue(QRect(winlabel->x(),winlabel->y()+120,winlabel->width(),winlabel->height()));

                       //设置弹跳震荡曲线
                       animation->setEasingCurve(QEasingCurve::OutBounce);

                       //启动执行
                       animation->start();
                   }
               });

           });
       }
   }

}
void PlayScene::paintEvent(QPaintEvent *)//创建绘图事件
{
    //设置背景图片
   QPainter painter(this);
   QPixmap pix;
   pix.load(":/res/OtherSceneBg.png");
   painter.drawPixmap(0,0,this->width(),this->height(),pix);
   //画背景图标
   pix.load(":/res/Title.png");
   pix.scaled(pix.width()*0.5,pix.height()*0.5);
   painter.drawPixmap(10,30,pix);
}
