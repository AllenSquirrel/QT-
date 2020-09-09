#include "mycoin.h"
#include<QDebug>
Mycoin::Mycoin(QString btnimg)
{
   QPixmap pix;
   bool ret= pix.load(btnimg);
   if(!ret)
   {
       QString str=QString("图片 %1 加载失败").arg(btnimg);
       qDebug()<<str;
       return;
   }
   //设置图片固定大小
   this->setFixedSize(pix.width(),pix.height());

   //设置不规则图片样式
   this->setStyleSheet("QPushButton{border:0px;}");

   //设置图标
   this->setIcon(pix);

   //设置图标大小
   this->setIconSize(QSize(pix.width(),pix.height()));

   timer1=new QTimer(this);
   timer2=new QTimer(this);
   //监听正面翻反面的信号  并且执行翻转动画
   connect(timer1,&QTimer::timeout,[=](){
       QPixmap pix;
       QString str=QString(":/res/Coin000%1.png").arg(this->min++);
       pix.load(str);

       //设置图片固定大小
       this->setFixedSize(pix.width(),pix.height());

       //设置不规则图片样式
       this->setStyleSheet("QPushButton{border:0px;}");

       //设置图标
       this->setIcon(pix);

       //设置图标大小
       this->setIconSize(QSize(pix.width(),pix.height()));

       //若翻转结束 min重置1，并且停止计时器
       if(this->min>this->max)
       {
           min=1;
           timer1->stop();
       }
   });

   connect(timer2,&QTimer::timeout,[=](){
       QPixmap pix;
       QString str=QString(":/res/Coin000%1.png").arg(this->max--);
       pix.load(str);

       //设置图片固定大小
       this->setFixedSize(pix.width(),pix.height());

       //设置不规则图片样式
       this->setStyleSheet("QPushButton{border:0px;}");

       //设置图标
       this->setIcon(pix);

       //设置图标大小
       this->setIconSize(QSize(pix.width(),pix.height()));

       //若翻转结束 min重置1，并且停止计时器
       if(this->max<this->min)
       {
           max=8;
           timer2->stop();
       }
   });
}

//改变标志的方法
void Mycoin::changeflag()
{
    if(this->flag)
    {
        timer1->start(30);
        this->flag=false;
    }
    else
    {
        timer2->start(30);
        this->flag=true;
    }
}


//为了屏蔽胜利后点击 重写mousepressevent
void Mycoin::mousePressEvent(QMouseEvent *e)
{
    if(this->win)
    {
        return;
    }
    else
    {
        QPushButton::mousePressEvent(e);
    }
}
