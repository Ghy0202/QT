#include "widget.h"
#include "ui_widget.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTime>
#include <QDebug>
#include"imagetoolbase.h"
#include"imagetoolfactory.h"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_screenshot_btn_clicked()
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

void Widget::on_magnify_btn_clicked()
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

void Widget::on_spotlight_btn_clicked()
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
