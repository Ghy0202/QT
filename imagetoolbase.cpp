#include "imagetoolbase.h"
#include "processobject.h"
#include <QApplication>
#include <QDebug>

ImageToolBase::ImageToolBase(QWidget *parent)//初始化各组件属性
    : QWidget(parent)
    , m_qMovePos(QPoint(-1, -1))
    , m_pScreen(nullptr)
    , m_pFullScreen(nullptr)
    , m_pBackgroundScreen(nullptr)
    , m_pButtonTool(nullptr)
    , m_bLight(true)
    , m_bCut(false)
    , m_bInit(false)
    , m_pParent(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    setAutoFillBackground(true);//自动填充背景
    QPalette pal = palette();//颜色组
    pal.setColor(QPalette::Background,Qt::transparent);//背景颜色透明
    setPalette(pal);
    setWindowOpacity(1);
    setAttribute(Qt::WA_TranslucentBackground);
    //添加自定义类控制
    setAttribute(Qt::WA_StyledBackground,true);
}

ImageToolBase::~ImageToolBase()
{

}

void ImageToolBase::SetLightState(QString state)//设置灯光范围
{
    this->setProperty("State", state);
    this->setStyle(QApplication::style());
}

void ImageToolBase::SetMaskLayerColor(QColor color)//设置遮罩层颜色
{
    MaskLayerColor = color;
}

QColor ImageToolBase::GetMaskLayerColor() const//获取遮罩层颜色
{
    return MaskLayerColor;
}
