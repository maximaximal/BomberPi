#pragma once

#include <SDL2/SDL_rect.h>

namespace PiH
{
    template<typename T>
    class Rect
    {
        public:
            Rect() {
                clear();
            }

            Rect(T x, T y) {
                clear();
                this->x = x;
                this->y = y;
            }

            Rect(T x, T y, T w, T h) {
                this->x = x;
                this->y = y;
                this->w = w;
                this->h = h;
            }

            ~Rect() {

            }

            void clear() {
                x = 0;
                y = 0;
                w = 0;
                h = 0;
            }

            SDL_Rect toSDLRect() {
                SDL_Rect rect;
                rect.x = x;
                rect.y = y;
                rect.w = w;
                rect.h = h;
                return rect;
            }

            T x;
            T y;
            T w;
            T h;
    };

    typedef Rect<float> FloatRect;
    typedef Rect<int32_t> IntRect;
}
