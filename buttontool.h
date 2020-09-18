#ifndef BUTTONTOOL_H
#define BUTTONTOOL_H

#include <QWidget>

//定义了三个类
class QVBoxLayout;
class QHBoxLayout;
class QPushButton;

class ButtonTool : public QWidget
{
    Q_OBJECT
public:
    explicit ButtonTool(QWidget *parent = nullptr);
    ~ButtonTool();

public:
    enum STATE {CUT, LAMP, SAVE, CLOSE};//枚举

    void InitButtons(QStringList buttons = {"CutButton", "LampButton", "SaveButton", "CloseButton"});//按钮

    void SetLampToolTip(bool lamp);//灯光提示

private:
    void InitUi( void );//初始界面
    void InitProperty( void );//初始属性

    void SetCutToolTip();//裁剪部件提示
    void SetSaveToolTip();//保存部件提示
    void SetCloseToolTip();//关闭部件提示

protected:

signals:
    void clicked(STATE);

private:
    QVBoxLayout *m_pRootLayout;
    QWidget *m_pRootWidget;
    QHBoxLayout *m_pRootWidgetLayout;
    QList<QPushButton*> m_qButtons;
    QStringList m_qButtonList;

};

#endif // BUTTONTOOL_H
