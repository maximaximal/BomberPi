#include <pihud/Widget.hpp>

namespace PiH
{
    Widget::Widget(Widget *parent)
    {
		m_parent = parent;
    }
    Widget::~Widget()
    {

    }
    FloatRect &Widget::getBoundingBox()
    {
     	return m_boundingBox;
    }
    void Widget::setBoundingBox(const FloatRect &box)
    {
        m_boundingBox = box;
        updateParent();
    }

    void Widget::setPosition(float x, float y)
    {
        m_boundingBox.x = x;
        m_boundingBox.y = y;
        updateParent();
    }
    void Widget::onEvent(const Event &e)
    {

    }
    void Widget::onUpdate(float frametime)
    {

    }
    void Widget::onRender(SDL_Renderer *renderer, const FloatRect &offset)
    {

    }
    void Widget::updateRectFromBeneath()
    {

    }
    void Widget::updateParent()
    {
        if(m_parent != nullptr)
        {
            m_parent->updateRectFromBeneath();
        }
    }
}
