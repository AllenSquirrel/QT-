#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include<QTimer>
class Mycoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit Mycoin(QWidget *parent = nullptr);
    //重写自定义的构造函数
    //参数为传入金币到银币1-8翻转图片
    Mycoin(QString btnimg);

    //金币属性
    int posx;//x位置
    int poxy;//y位置
    bool flag;//正反标识

    //改变标志的方法
    void changeflag();
    QTimer *timer1;//正面翻反面的定时器
    QTimer *timer2;//反面翻正面的定时器
    int min=1;
    int max=8;


    //加入一个胜利标志位  控制游戏胜利后 金币无法点击翻转
    bool win=false;

    //为了屏蔽胜利后点击 重写mousepressevent
    void mousePressEvent(QMouseEvent *e);
signals:

};

#endif // MYCOIN_H
