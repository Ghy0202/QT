#include "spotlight.h"
#include "buttontool.h"
#include <QMouseEvent>
#include <QPaintEvent>
#include <QShowEvent>
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include <QDebug>
#include <QtMath>

#include "processobject.h"


SpotLight::SpotLight(QWidget *parent)
 : ImageToolBase(parent)
{
    InitUi();

    InitProperty();
}

SpotLight::~SpotLight()
{

}

void SpotLight::InitUi()
{
    showFullScreen();//Widget自带的函数，即全屏显示窗口

    m_pZoom = new QWidget(this);//新建一个控件
    m_pZoom->setObjectName("Zoom");//给控件命名

    m_pButtonTool = new ButtonTool(this);//新建按钮组
    m_pButtonTool->InitButtons({"CutButton", "LampButton", "CloseButton"});//设置按钮组件为切换、灯光、关闭
    m_pButtonTool->setVisible(false);//设置控件为不可见

}

void SpotLight::InitProperty()
{
    this->setWindowFlags(Qt::FramelessWindowHint);//setWindowFlags自带功能：将窗口的最小化、最大化与关闭统统隐藏

    //设置背景透明
    setAutoFillBackground(true);
    QPalette pal = palette();
    pal.setColor(QPalette::Background,Qt::transparent);
    setPalette(pal);
    setWindowOpacity(1);
    setAttribute(Qt::WA_TranslucentBackground);

    //添加自定义类控制
    setAttribute(Qt::WA_StyledBackground,true);

    //用自定义的.qss文件对桌面进行美化->设置出自己想要的样子（zoom图标）
    QFile resourceqss(":/ImageTools/qss/ImageToolBase.qss");
    resourceqss.open(QFile::ReadOnly);
    this->setStyleSheet(resourceqss.readAll());
    resourceqss.close();

    //初始化灯光的状态：关
    m_bLight = false;
    SetLightState("ColseLight");
    m_pButtonTool->SetLampToolTip(m_bLight);

    connect(m_pButtonTool, &ButtonTool::clicked, this, [=](ButtonTool::STATE state){//按钮组件槽函数
        switch (state) {
            case ButtonTool::STATE::CUT: {//切换
                m_bCut = !m_bCut;
                update();
                break;
            }
            case ButtonTool::STATE::LAMP: {//灯光
                m_bLight = !m_bLight;
                if(m_bLight)
                {
                    m_pButtonTool->SetLampToolTip(m_bLight);
                    SetLightState("OpenLight");
                    update();
                } else {
                    m_pButtonTool->SetLampToolTip(m_bLight);
                    SetLightState("CloseLight");
                    update();
                }

                break;
            }
            case ButtonTool::STATE::CLOSE: {//关闭
                emit clicked(STATE::CLOSE);
                this->close();
                break;
            }
        }
    });

    // 初始化 处理屏幕的对象 并初始化 可活动范围（最大尺寸为桌面尺寸，最大宽度为桌面宽度，最大高度为桌面高度）
    m_pScreen = new ProcessObject;
    m_pScreen->SetMaxParentSize(QApplication::desktop()->size());
    m_pScreen->SetMaxWidth(QApplication::desktop()->size().width());
    m_pScreen->SetMaxHeight(QApplication::desktop()->size().height());


    m_pFullScreen = new QPixmap;
    m_bInit =true;

}

//缩放判断是否在指定区域
bool SpotLight::ZoomIsInArea(QPoint pos)
{
    if(pos.x() > m_pZoom->x()
            && pos.x() < m_pZoom->x() + m_pZoom->width()
            && pos.y() > m_pZoom->y()
            && pos.y() < m_pZoom->y() + m_pZoom->height())
    {
        return true;
    }
    else{
    return false;
    }
}

// 按下事件
void SpotLight::mousePressEvent(QMouseEvent *event)
{
    if(this->ZoomIsInArea(event->pos()))//鼠标在缩放按钮上
    {
        m_pScreen->SetState(ProcessObject::STATE::ZOOM);
        m_pButtonTool->setVisible(false);//按钮组此时不可见
        this->setCursor(Qt::CrossCursor);//设置光标的图案（这里当鼠标放在缩放按钮时：十字架光标）
    }
    else if(m_pScreen->IsInArea(event->pos()))//鼠标在聚光灯窗口里
    {
        m_pScreen->SetState(ProcessObject::STATE::MOVE);
        m_pZoom->setVisible(false);//缩放按钮此时不可见
        m_pButtonTool->setVisible(false);//按钮组此时不可见
        this->setCursor(Qt::ClosedHandCursor);//设置光标图案（握紧的小拳头）
    }

    m_qMovePos = event->pos();
}

// 移动事件
void SpotLight::mouseMoveEvent(QMouseEvent *event)
{
    if(m_pScreen->GetState() == ProcessObject::STATE::MOVE)
    {
        QPoint pos(event->x() - m_qMovePos.x(), event->y() - m_qMovePos.y());
        m_pScreen->Move(pos);
        m_qMovePos = event->pos();
    } else if(m_pScreen->GetState() == ProcessObject::STATE::ZOOM)
    {
        QPoint pos(event->x() - m_qMovePos.x(), event->y() - m_qMovePos.y());
        int w = m_pScreen->width() + pos.x();
        int h = m_pScreen->height() + pos.y();
        m_pScreen->SetGeometry(m_pScreen->x(),
                               m_pScreen->y(),
                               w, h);
        m_qMovePos = event->pos();
    }
    update();
}

// 释放事件
void SpotLight::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    if(m_pScreen->GetState() == ProcessObject::STATE::MOVE)
    {
        m_pScreen->SetState(ProcessObject::STATE::SELECT);
        m_pZoom->setVisible(true);
        m_pButtonTool->setVisible(true);
    } if(m_pScreen->GetState() == ProcessObject::STATE::ZOOM)
    {
        m_pScreen->SetState(ProcessObject::STATE::SELECT);
        m_pButtonTool->setVisible(true);
    }
    this->setCursor(Qt::ArrowCursor);
}

void SpotLight::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::HighQualityAntialiasing);
    int x = m_pScreen->x();
    int y = m_pScreen->y();
    int w = m_pScreen->width();
    int h = m_pScreen->height();

    QPen pen;
    pen.setColor(QColor(0,0,0,0));
    painter.setPen(pen);

    QPixmap backgroundscreen(m_pScreen->GetMaxParentWidget(), m_pScreen->GetMaxParentHeight());
    //用给定的颜色填充像素图
    backgroundscreen.fill(MaskLayerColor);
    painter.drawPixmap(0,0, *m_pBackgroundScreen);
    painter.drawPixmap(0,0, backgroundscreen);

    if(w != 0 && h != 0)
    {
        if(m_bCut)
        {
            int side = qMin(w, h);
            m_pScreen->SetGeometry(m_pScreen->x(), m_pScreen->y(), side, side);
            QTransform transform;
            transform.translate(x, y);
            QPixmap pix = m_pFullScreen->copy(x, y, side, side);
            QBrush brush(pix);
            brush.setTransform(transform);
            painter.setBrush(brush);
            painter.drawEllipse(x, y, side, side);

            int circle_centerx = x + side/2;
            int circle_centery = y + side/2;
            int r = side/2;
            int x1 = static_cast<int>(double(circle_centerx) + double(r) * qCos(45.0));
            int y1 = static_cast<int>(double(circle_centery) + double(r) * qSin(45.0));
            m_pZoom->move(x1-m_pZoom->width()/2, y1-m_pZoom->height()/2);
            
        } else {
            painter.drawPixmap(x, y, m_pFullScreen->copy(x, y, w, h));
            painter.drawRect(x, y, w, h);

            m_pZoom->move(x+w-m_pZoom->width()/2, y+h-m_pZoom->height()/2);
            

        }
        // 动态变更按钮组位置
        int maxheight = m_pScreen->GetMaxParentHeight();
        int distance_y_bottom = maxheight - (y+h);
        int distance_y_top = m_pScreen->y();
        if(distance_y_bottom <= m_pButtonTool->height() + 7 && distance_y_top <= m_pButtonTool->height() + 7)
        {
            m_pButtonTool->move(x+w-m_pButtonTool->width(), y+h-m_pButtonTool->height()-7);
        } else if(distance_y_bottom<= m_pButtonTool->height() + 7)
        {
            m_pButtonTool->move(x+w-m_pButtonTool->width(), y - m_pButtonTool->height() - 7);
        } else {
            m_pButtonTool->move(x+w-m_pButtonTool->width(), y+h+7);
        }
    }

}

void SpotLight::showEvent(QShowEvent *event)
{
    Q_UNUSED(event)
    if(m_bInit)
    {
        int wide = m_pScreen->GetMaxParentHeight()/3;
        int x = (m_pScreen->GetMaxParentWidget() - wide)/2;
        int y = (m_pScreen->GetMaxParentHeight() - wide)/2;
        m_pScreen->SetStart(QPoint(x,y));
        m_pScreen->SetGeometry(x, y, wide, wide);

        // 获取主屏幕大小 - 全屏大小
        QScreen *screen = QApplication::primaryScreen();
        *m_pFullScreen = screen->grabWindow(
                                           QApplication::desktop()->winId(),
                                           0,
                                           0,
                                           m_pScreen->GetMaxParentWidget(),
                                           m_pScreen->GetMaxParentHeight()
                                       );

        m_pBackgroundScreen = new QPixmap(*m_pFullScreen);

        update();
        m_pZoom->show();
        m_pButtonTool->setVisible(true);

    }
}
