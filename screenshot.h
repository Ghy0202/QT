#ifndef SCREENSHOT_H
#define SCREENSHOT_H
#include "imagetoolbase.h"

#define AppPath qApp->applicationDirPath()
#define STRDATETIME qPrintable (QDateTime::currentDateTime().toString("yyyy-MM-dd-HH-mm-ss"))

class ScreenShot : public ImageToolBase
{
    Q_OBJECT
public:
    explicit ScreenShot(QWidget *parent = nullptr);
    ~ScreenShot();

private:
    void InitUi() override;                              //布局函数
    void InitProperty() override;
    void SetZoomVisible(bool visible);
    void SetZoomGeometry(int x, int y, int width, int height);
    bool ZoomIsInArea(QWidget *Zoom, QPoint pos);
    void Save();

protected:
    void mousePressEvent(QMouseEvent *) override;        //拖拽控件函数
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void paintEvent(QPaintEvent *) override;
    void showEvent(QShowEvent *) override;

private:
    QWidget *m_pZoom_Top;             // 上边拖拽
    QWidget *m_pZoom_Bottom;          // 下边拖拽
    QWidget *m_pZoom_Left;            // 左边拖拽
    QWidget *m_pZoom_Right;           // 右边拖拽
    QWidget *m_pZoom_Left_Top;        // 左上角拖拽
    QWidget *m_pZoom_Right_Top;       // 右上角拖拽
    QWidget *m_pZoom_Left_Bottom;     // 左下角拖拽
    QWidget *m_pZoom_Right_Bottom;    // 右下角拖拽



};

#endif // SCREENSHOT_H
