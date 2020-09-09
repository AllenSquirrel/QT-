#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>
#include"mycoin.h"
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);

    //重写构造函数  参数为int类型的关卡序号
    PlayScene(int levelNum);

    // 重写paintevent事件 画关卡背景图
    void paintEvent(QPaintEvent *);

    int levelindex;//成员变量  记录所选的关卡序号

    //创建一个二维数组，维护每关数据
    int gamearray[4][4];

    Mycoin *coinarray[4][4];//创建二维数组，方便金币周围翻转维护

    //是否胜利标志
    bool iswin=false;

signals:
    //自定义信号，告诉选关场景 点击返回
    void playSceneBack();
};

#endif // PLAYSCENE_H
