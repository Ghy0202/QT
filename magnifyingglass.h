#ifndef MAGNIFYINGGLASS_H
#define MAGNIFYINGGLASS_H
#include "imagetoolbase.h"

class MagnifyingGlass : public ImageToolBase
{
    Q_OBJECT
public:
    explicit MagnifyingGlass(QWidget *parent = nullptr);
    ~MagnifyingGlass();

public:

private:
    void InitUi() override;
    void InitProperty() override;

    bool ZoomIsInArea(QPoint pos);//缩放

protected:
    void mousePressEvent(QMouseEvent *) override;//按下鼠标
    void mouseMoveEvent(QMouseEvent *) override;//移动鼠标
    void mouseReleaseEvent(QMouseEvent *) override;//释放鼠标
    void paintEvent(QPaintEvent *) override;//颜色填充
    void showEvent(QShowEvent *) override;//显示

private:
    QWidget *m_pZoom;
    qreal m_qZoomRatio;
};

#endif // MAGNIFYINGGLASS_H
