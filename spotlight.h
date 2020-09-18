#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H
#include "imagetoolbase.h"

class SpotLight : public ImageToolBase
{
    Q_OBJECT
public:
    explicit SpotLight(QWidget *parent = nullptr);
    ~SpotLight();

public:


    //所有override都在重构ImageToolBase里的函数
private:

    void InitUi() override;
    void InitProperty() override;

    //缩放范围是否在主窗口内
    bool ZoomIsInArea(QPoint pos);

protected:
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void paintEvent(QPaintEvent *) override;
    void showEvent(QShowEvent *) override;

private:
    QWidget *m_pZoom;

};

#endif // SPOTLIGHT_H
