#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_screenshot_btn_clicked();

    void on_magnify_btn_clicked();

    void on_spotlight_btn_clicked();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
