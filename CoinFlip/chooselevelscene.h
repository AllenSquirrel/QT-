#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H

#include <QMainWindow>
#include"playscene.h"
class ChooselevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooselevelScene(QWidget *parent = nullptr);
    // 重写paintevent事件 画关卡背景图
    void paintEvent(QPaintEvent *);

    //游戏场景对象指针
    PlayScene *play=NULL;
signals:
    //自定义信号，告诉主场景 点击返回
    void chooseSceneBack();
};

#endif // CHOOSELEVELSCENE_H
