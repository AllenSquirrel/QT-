#include "mypushbutton.h"
#include<QDebug>
#include<QPropertyAnimation>
Mypushbutton::Mypushbutton(QString normalImg,QString pressImg)
{
        //传参  初始化成员变量
        this->normalImgpath=normalImg;
        this->pressImgpath=pressImg;
        QPixmap pix;
       bool ret= pix.load(normalImg);
       if(!ret)
       {
           qDebug("按钮图片加载失败");
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
}
void Mypushbutton::zoom1()//向下跳
{
    //创建动画对象animation
    QPropertyAnimation * animation=new QPropertyAnimation(this,"geometry");//geometry为特定动画效果“弹跳”

    //设置动画时间间隔
    animation->setDuration(200);

    //起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //结束位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //设置弹跳震荡曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //启动执行
    animation->start();
}
void Mypushbutton::zoom2()//向上跳
{
    //创建动画对象animation
    QPropertyAnimation * animation=new QPropertyAnimation(this,"geometry");//geometry为特定动画效果“弹跳”

    //设置动画时间间隔
    animation->setDuration(200);

    //起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    //结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    //设置弹跳震荡曲线
    animation->setEasingCurve(QEasingCurve::OutBounce);

    //启动执行
    animation->start();
}

void Mypushbutton::mousePressEvent(QMouseEvent *e)
{
    if(this->pressImgpath!="")//传入图片不为空，说明需要有按下的状态  切换成初始图片
    {
        QPixmap pix;
       bool ret= pix.load(pressImgpath);
       if(!ret)
       {
           qDebug("按钮图片加载失败");
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
    }
    //让父类执行其他内容
    return QPushButton::mousePressEvent(e);
}
void Mypushbutton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->pressImgpath!="")//传入图片不为空，说明需要有按下的状态  切换成初始图片
    {
        QPixmap pix;
       bool ret= pix.load(normalImgpath);
       if(!ret)
       {
           qDebug("按钮图片加载失败");
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
    }
    //让父类执行其他内容
    return QPushButton::mouseReleaseEvent(e);
}
