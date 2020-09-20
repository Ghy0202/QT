#include "widget.h"
#include "ui_widget.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTime>
#include <QDebug>
#include"imagetoolbase.h"
#include"imagetoolfactory.h"
#include"config.h"
#include<QPainter>
#include<QSound>
Widget::Widget(QWidget *parent) :
    QWidget(parent),time(0), is_start(false), timeout(25 * 60), state(true),

    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(WINDOW_WIDTH,WINDOW_HEIGHT);//设置固定宽高
    this->setWindowIcon(QIcon(WINDOW_ICON));//设置图标
    this->setWindowTitle(WINDOW_TITLE);//设置应用标题
    this -> setStyleSheet("background-color: rgb(255,255,255);");//按钮背景颜色置为白色
    this -> setWindowFlags(Qt::WindowStaysOnTopHint);//窗口置顶



    //番茄钟
    //开始按钮
    Start.setParent(this);
    Start.move(220, 250);
    Start.resize(60 ,30);
    Start.setText("开始");
    Start.setStyleSheet("QPushButton {"
                        "   background-color: rgb(82,181,254);"
                        "   font-family:\"Microsoft YaHei\";"
                        "   font: bold;"
                        "   color: rgb(255,255,255);"
                        "   border-style: solid;"
                        "   border-radius: 5px;"
                        "}"
                        "QPushButton:hover {"
                        "   background-color:rgb(101,200,255);"
                        "}");

    //+按钮
    AddMin.setParent(this);
    AddMin.setText("+");
    AddMin.move(180, 200);
    AddMin.resize(20, 20);
    AddMin.setStyleSheet("QPushButton {"
                         "  background-color: rgb(255,255,255);"
                         "  font-family: \"Microsoft YaHei\";"
                         "  font: bold;"
                         "  color: rgb(82,181,254);"
                         "  border-style: solid;"
                         "  border-radius: 2px;"
                         "  border-width: 1px;"
                         "}"
                         "QPushButton:pressed {"
                         "  background-color: rgb(101,200,255);"
                         "  border-color: rgb(255,255,255);"
                         "  color: rgb(255,255,255);"
                         "}");
//-按钮
    SubMin.setParent(this);
    SubMin.setText("-");
    SubMin.move(290, 200);
    SubMin.resize(20, 20);
    SubMin.setStyleSheet("QPushButton {"
                         "  background-color: rgb(255,255,255);"
                         "  font-family: \"Microsoft YaHei\";"
                         "  font: bold;"
                         "  color: rgb(82,181,254);"
                         "  border-style: solid;"
                         "  border-radius: 2px;"
                         "  border-width: 1px;"
                         "}"
                         "QPushButton:pressed {"
                         "  background-color: rgb(101,200,255);"
                         "  border-color: rgb(255,255,255);"
                         "  color: rgb(255,255,255);"
                         "}");
//显示时间按钮
    timedisplayer.setParent(this);
    timedisplayer.move(210, 150);
    timedisplayer.resize(85, 35);
    timedisplayer.setStyleSheet("QLabel {"
                                "   color:rgb(82,181,254);"
                                "   font-family:\"Microsoft YaHei\";"
                                "   font: bold 20px;"
                                "   font-size: 30px"
                                "}");
    timedisplayer.setText("0:0");
    timedisplayer.setAlignment(Qt::AlignHCenter);

    timeoutdisplayer.setParent(this);
    timeoutdisplayer.move(240, 100);
    timeoutdisplayer.resize(20, 20);
    timeoutdisplayer.setStyleSheet("QLabel {"
                                   "   color:rgb(82,181,254);"
                                   "   font-family:\"Microsoft YaHei\";"
                                   "   font: bold 20px;"
                                   "   font-size: 15px"
                                   "}");
    timeoutdisplayer.setText(QString::number(timeout/60, 10));
    timeoutdisplayer.setAlignment(Qt::AlignHCenter);
//提示按钮1
    tip1.setParent(this);
    tip1.move(160, 80);
    tip1.resize(160, 20);
    tip1.setStyleSheet("QLabel {"
                       "   color:rgb(82,181,254);"
                       "   font-family:\"Microsoft YaHei\";"
                       "   font-size: 15px"
                       "}");
    tip1.setText("欣赏严老师时间");
    tip1.setAlignment(Qt::AlignHCenter);


    connect(&timer, &QTimer::timeout, this, &Widget::onClockTime);
    connect(&Start, &QPushButton::released, this, &Widget::startClock);

    connect(&AddMin, &QPushButton::released, this, &Widget::AddTime);
    connect(&SubMin, &QPushButton::released, this, &Widget::SubTime);


}

Widget::~Widget()
{
    delete ui;
}

//画背景图
/*void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(BACKGROUND_PATH);
    painter.drawPixmap(0,0,pix);
}*/


//与桌面番茄钟有关的四个函数
void Widget::onClockTime()
{
    if((time < timeout)&&state == true) {
        timedisplayer.setText(QString::number(time/60, 10)+":"+QString::number(time%60, 10));
        time++;
    }else {
        if(state == true) {//排除法
            time = state = 0;
            timeout2 = timeout;
            timeout = 10 * 60;
            tip1.setText("休息一下");

        }
    }

    if((time < timeout)&&state == false) {
        timedisplayer.setText(QString::number(time/60, 10)+":"+QString::number(time%60, 10));
        time++;
    }else {
        if(state == false) {
            time = 0;
            state = 1;
            timeout = timeout2;
            tip1.setText("请看大屏幕");
        }
    }
}



void Widget::startClock()
{
    timeoutdisplayer.hide();
    tip1.move(160, 80);
    tip1.resize(140, 30);
    tip1.setStyleSheet("QLabel {"
                       "   color:rgb(82,181,254);"
                       "   font-family:\"Microsoft YaHei\";"
                       "   font: bold 10px;"
                       "   font-size: 20px"
                       "}");
    tip1.setText("请看大屏幕");


    AddMin.hide();
    SubMin.hide();
    if(is_start != true) {
        timer.start(1000);
        Start.setText("停止");
        is_start=!is_start;
    }else {
        timer.stop();
        Start.setText("开始");
       is_start=!is_start;
    }
}
//+
void Widget::AddTime()
{
    timeout += 60;
    timeoutdisplayer.setText(QString::number(timeout/60, 10));
}
//-
void Widget::SubTime()
{
    if(timeout>60){
        timeout -=60;
    }else{
        timeout = 60;
    }
    timeoutdisplayer.setText(QString::number(timeout/60, 10));
}

void Widget::on_screenshot_btn_2_clicked()
{
    this->hide();
        QTimer *delay = new QTimer(this);
        connect(delay, &QTimer::timeout, this, [=](){
            ImageToolFactory factory;
            ImageToolBase* base = factory.NewTool(ImageToolFactory::TOOLS::SCREENSHOT);
            connect(base, &ImageToolBase::clicked, this, [=](ImageToolBase::STATE state){
                if(state == ImageToolBase::STATE::CLOSE){
                    this->show();
                    base->deleteLater();
                }
            });
            base->show();
            delay->deleteLater();
        });

        delay->start(300);
}

void Widget::on_magnify_btn_2_clicked()
{
    this->hide();
      QTimer *delay = new QTimer(this);
      connect(delay, &QTimer::timeout, this, [=](){
          ImageToolFactory factory;
          ImageToolBase* base = factory.NewTool(ImageToolFactory::TOOLS::MAGNIFYINGGLASS);
          connect(base, &ImageToolBase::clicked, this, [=](ImageToolBase::STATE state){
              if(state == ImageToolBase::STATE::CLOSE){
                  this->show();
                  base->deleteLater();
              }
          });
          base->show();
          delay->deleteLater();
      });

      delay->start(300);
}

void Widget::on_spotlight_btn_2_clicked()
{
    this->hide();
       QTimer *delay = new QTimer(this);
       connect(delay, &QTimer::timeout, this, [=](){
           ImageToolFactory factory;
           ImageToolBase* base = factory.NewTool(ImageToolFactory::TOOLS::SPOTLIGHT);
           connect(base, &ImageToolBase::clicked, this, [=](ImageToolBase::STATE state){
               if(state == ImageToolBase::STATE::CLOSE){
                   this->show();
                   base->deleteLater();
               }
           });
           base->show();
           delay->deleteLater();
       });

       delay->start(300);
}
void Widget::on_pushButton_clicked()
{
            static int i=0;
            ui->change->setCurrentIndex(++i%4);
}
