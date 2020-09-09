#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include"chooselevelscene.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainScene; }
QT_END_NAMESPACE

class MainScene : public QMainWindow
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();
    // 重写paintevent事件 画主场景背景图
    void paintEvent(QPaintEvent *);
    //定义 选择关卡场景类的对象
    ChooselevelScene * choosescene=NULL;
private:
    Ui::MainScene *ui;
};
#endif // MAINSCENE_H
