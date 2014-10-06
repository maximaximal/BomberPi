#pragma once

#include <string>
#include <map>
#include <pihud/Widget.hpp>

namespace PiH
{
    class HudContainer : public Widget
    {
        public:
            HudContainer();
            virtual ~HudContainer();
            void clear();

            virtual void onEvent(const Event &e);
            virtual void onUpdate(float frametime);
            virtual void onRender(SDL_Renderer *renderer, const FloatRect &offset);

            Widget* getWidget(const std::string &name);
            void addWidget(Widget *widget, std::string name = "");
        private:
            std::map<std::string, Widget*> m_widgets;
    };
}