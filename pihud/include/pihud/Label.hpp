#pragma once

#include <pihud/Widget.hpp>
#include <SDL2/SDL_ttf.h>
#include <string>

namespace PiH
{
    class Label : public Widget
    {
        public:
            Label(Widget *parent);
            virtual ~Label();

            virtual void onEvent(const Event &e);
            virtual void onUpdate(float frametime);
            virtual void onRender(SDL_Renderer *renderer, const FloatRect &offset);

            void setText(const std::string &text);
            void setFont(const std::string &font)
        private:
            std::string m_text;
    };
}
