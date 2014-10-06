#pragma once 

#include <SDL2/SDL.h>
#include <pihud/Event.hpp>
#include <pihud/Rect.hpp>

namespace PiH
{
    class Widget
    {
        public:
            Widget();
            virtual ~Widget();

            FloatRect& getBoundingBox();
            void setBoundingBox(const FloatRect &box);

            virtual void onEvent(const Event &e);
            virtual void onUpdate(float frametime);
            virtual void onRender(SDL_Renderer* renderer, const FloatRect &offset);
        protected:
            FloatRect m_boundingBox;
    };
}
