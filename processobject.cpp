#include "processobject.h"                              //对放大镜与聚光灯窗口的限定

ProcessObject::ProcessObject(QObject *parent)
    : QObject(parent)                                   //默认构造函数
    , m_qstate(STATE::SELECT)                           //设置最初的状态：被选中
    , MinWidth(10)                                     //最小宽度10
    , MinHeight(10)                                    //最小高度10
    , MaxWidth(9999)                                    //最大宽度：9999
    , MaxHeight(9999)                                   //最大高度：9999
    , MaxParentWidth(9999)                              //在父类对象活动范围的最大宽度为9999
    , MaxParentHeight(9999)                             //在父类对象活动范围的最大高度为9999
    , m_qStartPos(QPoint(-1,-1))                       //默认初始坐标位置为（-1，-1）
    , m_qEndPos(m_qStartPos)                            //默认结束位置为初始坐标位置（-1，-1）

                                                         //默认左上右下左下右上四个角初始坐标均为初始坐标位置（-1，-1）
    , m_qLeftTopPos(m_qStartPos)
    , m_qRightBottomPos(m_qStartPos)
    , m_qRightTopPos(m_qStartPos)
    , m_qLeftBottomPos(m_qStartPos)
{

}

ProcessObject::~ProcessObject()
{

}


//设置图形样式函数的实现
void ProcessObject::SetGeometry(int x, int y, int width, int height)
{

    //开始默认宽=最小默认宽度，默认高=最小默认高度
    int my_width = MinWidth, my_height = MinHeight;

    //最终获取的my_width=(鼠标拖拽后的获取宽度：如果获取宽度大于最大限制宽度，则取最大限制宽度；如果获取宽度小于最小限制宽度，则取最小限制宽度)
    //最终获取的my_height同上
    my_width = qMax(width, MinWidth);
    my_width = qMin(my_width, MaxWidth);
    my_height = qMax(height, MinHeight);
    my_height = qMin(my_height, MaxHeight);

    //最终获取的左上角的点坐标为鼠标开始截屏时候选中的点，左下角的点坐标=左上角的点坐标里y坐标+my_height
    m_qLeftTopPos = QPoint(x,y);
    m_qLeftBottomPos = QPoint(x, y + my_height);

    //最终获取的右上角的点坐标为为左上角的点坐标x坐标+my_width,左下角的点坐标=左上角的点坐标x+my_width,y+my_height
    m_qRightTopPos = QPoint(x + my_width, y);
    m_qRightBottomPos = QPoint(x + my_width, y + my_height);

    //比较左上和右下两点的位置
    ComparePoint(m_qLeftTopPos, m_qRightBottomPos);
}


//设置最小的宽度
void ProcessObject::SetMinWidth(int width)
{
    MinWidth = width;
}

//返回最小的宽度
int ProcessObject::GetMinWidth() const
{
    return MinWidth;
}

//设置最小的高度
void ProcessObject::SetMinHeight(int height)
{
    MinHeight = height;
}

//返回最小高度
int ProcessObject::GetMinHeight() const
{
    return MinHeight;
}


//设置最小高度
void ProcessObject::SetMinSize(QSize size)
{
    MinWidth = size.width();
    MinHeight = size.height();
}

//得到最小尺寸
QSize ProcessObject::GetMinSize() const
{
    return QSize(MinWidth, MinHeight);
}


//返回最大宽度
void ProcessObject::SetMaxWidth(int width)
{
    MaxWidth = width;
}

//返回最大宽度
int ProcessObject::GetMaxWidth() const
{
    return MaxWidth;
}

//设置最大高度
void ProcessObject::SetMaxHeight(int height)
{
    MaxHeight = height;
}

//返回最大高度
int ProcessObject::GetMaxHeight() const
{
    return MaxHeight;
}

//设置最大尺寸
void ProcessObject::SetMaxSize(QSize size)
{
    MaxWidth = size.width();
    MaxHeight = size.height();
}

//返回最大尺寸
QSize ProcessObject::GetMaxSize() const
{
    return QSize(MaxWidth, MaxHeight);
}

//设置父类最大尺寸
void ProcessObject::SetMaxParentSize(QSize maxparentsize)
{
   MaxParentWidth = maxparentsize.width();
   MaxParentHeight = maxparentsize.height();
}

//设置父类最小尺寸
QSize ProcessObject::GetMaxParentSize() const
{
    return QSize(MaxParentWidth, MaxParentHeight);
}


//返回父类最大宽度
int ProcessObject::GetMaxParentWidget() const
{
    return MaxParentWidth;
}

//返回父类最大高度
int ProcessObject::GetMaxParentHeight() const
{
    return MaxParentHeight;
}

//返回左上角点的x坐标
int ProcessObject::x() const
{
    return m_qLeftTopPos.x();
}

//返回左上角点的y坐标
int ProcessObject::y() const
{
    return m_qLeftTopPos.y();
}

//返回窗口宽度
int ProcessObject::width() const
{
    int width = m_qRightBottomPos.x() - m_qLeftTopPos.x();
    return width;
}

//返回窗口高度
int ProcessObject::height() const
{
    int height = m_qRightBottomPos.y() - m_qLeftTopPos.y();
    return height;
}

//判断是否在选取范围内(和窗口的四个角对比)
bool ProcessObject::IsInArea(QPoint pos)
{
    if(pos.x() > m_qLeftTopPos.x()
            && pos.x() < m_qRightBottomPos.x()
            && pos.y() > m_qLeftTopPos.y()
            && pos.y() < m_qRightBottomPos.y())
    {
        return true;
    }
    return false;
}

//移动区域
void ProcessObject::Move(QPoint pos)
{
    int m_ywidth = width();
    int m_yheight = height();

    int x = m_qLeftTopPos.x() + pos.x();
    int y = m_qLeftTopPos.y() + pos.y();

    //限定移动范围在屏幕内
    if(x < 0)
    {
        x = 0;
    } else if(x + m_ywidth > MaxParentWidth)
    {
        x = MaxParentWidth - m_ywidth;
    }

    if(y < 0)
    {
        y = 0;
    } else if(y + m_yheight > MaxParentHeight)
    {
        y = MaxParentHeight - m_yheight;
    }

    m_qStartPos = QPoint(x, y);
    m_qEndPos = QPoint(x + m_ywidth, y + m_yheight);
    m_qLeftTopPos = m_qStartPos;
    m_qRightBottomPos = m_qEndPos;
}

//设定窗口状态
void ProcessObject::SetState(ProcessObject::STATE state)
{
    m_qstate = state;
}

//获取窗口状态
ProcessObject::STATE ProcessObject::GetState() const
{
    return m_qstate;
}

//设置初始位置
void ProcessObject::SetStart(QPoint pos)
{
    m_qStartPos = pos;
}

//获取出初始位置
QPoint ProcessObject::GetStart() const
{
    return m_qStartPos;
}

//设置结束位置
void ProcessObject::SetEnd(QPoint pos)
{
    m_qEndPos = pos;
    m_qLeftTopPos = m_qStartPos;
    m_qRightBottomPos = m_qEndPos;
    ComparePoint(m_qLeftTopPos, m_qRightBottomPos);
}

//获取结束位置
QPoint ProcessObject::GetEnd() const
{
    return m_qEndPos;
}

//获取左上位置
QPoint ProcessObject::GetLeftTopPos() const
{
    return m_qLeftTopPos;
}

//获取右下位置
QPoint ProcessObject::GetRightBottomPos() const
{
    return m_qRightBottomPos;
}


//对比左上和右下两个点的坐标
void ProcessObject::ComparePoint(QPoint &leftTop, QPoint &rightBottom)
{
    QPoint lefttop = leftTop;
    QPoint rightbottom = rightBottom;

    if(lefttop.x() <= rightbottom.x()) {
        // 判断end 在start右上的情况
        if(!(lefttop.y() <= rightBottom.y()))
        {
            leftTop.setY(rightbottom.y());
            rightBottom.setY(lefttop.y());
        }
        // end 在start右下的情况 不用判断
    } else {
        // 判断end 在start左下的情况
        if(lefttop.y() < rightbottom.y()) {
            leftTop.setX(rightbottom.x());
            rightBottom.setX(lefttop.x());
        } else { // 判断end 在start左上的情况
            QPoint temp;
            temp = leftTop;
            leftTop = rightBottom;
            rightBottom = temp;
        }
    }

}
