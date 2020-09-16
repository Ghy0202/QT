#include "imagetoolfactory.h"
#include "magnifyingglass.h"
#include "spotlight.h"
#include "screenshot.h"

ImageToolFactory::ImageToolFactory(QWidget *parent)
    : m_pParent(parent)
{

}

ImageToolFactory::~ImageToolFactory()
{

}

ImageToolBase *ImageToolFactory::NewTool(ImageToolFactory::TOOLS tool)
{
    switch (tool) {
        case TOOLS::SCREENSHOT: {
            return new ScreenShot(m_pParent);
        }
        case TOOLS::MAGNIFYINGGLASS: {
            return new MagnifyingGlass(m_pParent);
        }
        case TOOLS::SPOTLIGHT: {
            return new SpotLight(m_pParent);
        }
    }
    return nullptr;
}
