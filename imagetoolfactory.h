#ifndef IMAGETOOLFACTORY_H
#define IMAGETOOLFACTORY_H

#include <QWidget>

class ImageToolBase;

class ImageToolFactory
{

public:
    explicit ImageToolFactory(QWidget *parent = nullptr);
    ~ImageToolFactory();

public:
    enum TOOLS {SCREENSHOT, MAGNIFYINGGLASS, SPOTLIGHT};//定义“截图”，“放大镜”和“聚光灯”三种功能

    ImageToolBase* NewTool(TOOLS);//?

private:
    QWidget *m_pParent;

};

#endif // IMAGETOOLFACTORY_H
