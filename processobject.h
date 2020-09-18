#ifndef PROCESSOBJECT_H
#define PROCESSOBJECT_H

#include <QObject>
#include <QPoint>
#include <QSize>

class ProcessObject : public QObject
{
    Q_OBJECT
public:
    explicit ProcessObject(QObject *parent = nullptr);
    ~ProcessObject();

public:
    // SELECT(选择状态-设置初始大小)， MOVE(移动状态), ZOOM(修改大小状态)

    //定义鼠标移动的状态
    enum STATE {SELECT, MOVE, ZOOM, TOP_ZOOM, BOTTOM_ZOOM, LEFT_ZOOM, RIGHT_ZOOM};


    //设置图形样式
    void SetGeometry(int x, int y, int width, int height);


    //设置最小的宽度
    void SetMinWidth(int width);
    int GetMinWidth( void ) const;

    //设置最小的高度
    void SetMinHeight(int height);
    int GetMinHeight( void ) const;

    //设置最小的尺寸？
    void SetMinSize(QSize size);
    QSize GetMinSize( void ) const;

    //设置最大宽度
    void SetMaxWidth(int width);
    int GetMaxWidth( void ) const;

    //设置最大高度
    void SetMaxHeight(int height);
    int GetMaxHeight( void ) const;

    //设置最大尺寸
    void SetMaxSize(QSize size);
    QSize GetMaxSize( void ) const;

    // 父对象最大活动范围
    void SetMaxParentSize( QSize maxparentsize );
    QSize GetMaxParentSize( void ) const;
    int GetMaxParentWidget( void ) const;
    int GetMaxParentHeight( void ) const;

    //？？？？
    int x( void ) const;
    int y( void ) const;
    int width( void ) const;
    int height( void ) const;

    // 判断是否在选取区域内
    bool IsInArea(QPoint pos);

    // 移动区域
    void Move(QPoint pos);

    // 设置状态
    void SetState( STATE state );
    // 获取状态
    STATE GetState( void ) const;

    //设置起始位置
    void SetStart(QPoint pos);
    //获取起始位置的坐标
    QPoint GetStart( void ) const;

    //设定结束位置
    void SetEnd(QPoint pos);
    //获取结束位置的坐标
    QPoint GetEnd( void ) const;


    //得到左上角的坐标
    QPoint GetLeftTopPos( void ) const;

    //得到右下角的坐标
    QPoint GetRightBottomPos( void ) const;

private:
    // 比较两点位置
    void ComparePoint(QPoint &leftTop, QPoint &rightBottom);

private:
    QPoint m_qLeftTopPos, m_qRightBottomPos, m_qRightTopPos, m_qLeftBottomPos;//4个角的坐标（左上、右下、右上、左下）
    QPoint m_qStartPos, m_qEndPos;//开始的坐标和结束的坐标
    int MinWidth, MinHeight;//最大最小宽高
    int MaxWidth, MaxHeight;

    // 在父对象活动范围大小
    int MaxParentWidth, MaxParentHeight;

    STATE m_qstate;//定义一个状态枚举数据成员

};

#endif // PROCESSOBJECT_H
