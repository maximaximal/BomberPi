#include <pihud/HudContainer.hpp>

namespace PiH
{
    HudContainer::HudContainer()
    {

    }
    HudContainer::~HudContainer()
    {
        clear();
    }
    void HudContainer::clear()
    {
        for(auto &widget : m_widgets)
        {
            delete widget.second;
        }
        m_widgets.clear();
    }
    void HudContainer::onEvent(const Event &e)
    {
     	for(auto &widget : m_widgets)
        {
            widget.second->onEvent(e);
        }
    }
    void HudContainer::onUpdate(float frametime)
    {
        for(auto &widget : m_widgets)
        {
            widget.second->onUpdate(frametime);
        }
    }
    void HudContainer::onRender(SDL_Renderer *renderer, const FloatRect &offset)
    {
        for(auto &widget : m_widgets)
        {
            widget.second->onRender(renderer, offset);
        }
    }
    Widget *HudContainer::getWidget(const std::string &name)
    {
        return m_widgets[name];
    }
    void HudContainer::addWidget(Widget *widget, std::string name)
    {
        if(m_widgets.count(name))
        {
            if(m_widgets[name] != nullptr)
            {
                delete m_widgets[name];
            }
        }
        m_widgets[name] = widget;
    }
}
