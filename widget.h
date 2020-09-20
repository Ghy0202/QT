#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QLabel>
#include<QTimer>
#include<QPushButton>
#include<QSound>
#include"config.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();


    //重写PaintEvent,画背景图
  //  void paintEvent(QPaintEvent *event);



    //下面是补充的番茄钟的设计

    inline void onClockTime();
    inline void startClock();
    inline void AddTime();
    inline void SubTime();


private slots:


    void on_screenshot_btn_2_clicked();

    void on_magnify_btn_2_clicked();

    void on_spotlight_btn_2_clicked();

  private:
    //下面是补充的番茄钟设计
    QPushButton AddMin,SubMin;
    QPushButton Start;

    QLabel timedisplayer,timeoutdisplayer,tip1;
    QTimer timer;

    int time,timeout,timeout2;
    bool is_start,state;



private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
