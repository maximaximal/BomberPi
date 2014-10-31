#ifndef CLIENT_KEYBOARDINPUTMETHOD_HPP_INCLUDED
#define CLIENT_KEYBOARDINPUTMETHOD_HPP_INCLUDED

#include <piga/InputMethod.hpp>
#include <SDL2/SDL.h>
#include <SDLEventHandler.hpp>

namespace piga
{
    class KeyboardInputMethod : public InputMethod
    {
        public:
            KeyboardInputMethod(SDL_Scancode scancode, std::shared_ptr<SDLEventHandler> eventHandler);
            virtual ~KeyboardInputMethod();

            virtual void update();

            void onKeyDown(const SDL_Event &e, float frametime);
            void onKeyUp(const SDL_Event &e, float frametime);
        private:
            sigc::connection m_keyUpConnection;
            sigc::connection m_keyDownConnection;
            SDL_Scancode m_scancode;
            std::shared_ptr<SDLEventHandler> m_eventHandler;
    };
}

#endif
