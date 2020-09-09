#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H


#include <QPushButton>

class Mypushbutton : public QPushButton
{
    Q_OBJECT
public:
    explicit Mypushbutton(QWidget *parent = nullptr);

    //构造函数 参数1 正常显示图片路径 参数2 按下后显示图片路径
    Mypushbutton(QString normalImg,QString pressImg="");

    //成员属性 保存用户传入的默认显示路径以及按下显示图片的路径
    QString normalImgpath;
    QString pressImgpath;

    //按钮弹跳特效封装
    void zoom1();//向下弹跳
    void zoom2();//向上弹跳

    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
signals:

};

#endif // MYPUSHBUTTON_H
