#include <Client/KeyboardInputMethod.hpp>
#include <easylogging++.h>

namespace piga
{
    KeyboardInputMethod::KeyboardInputMethod(SDL_Scancode scancode, std::shared_ptr<SDLEventHandler> eventHandler)
    {
        m_scancode = scancode;
        m_eventHandler = eventHandler;
        m_eventHandler->getSignal(SDL_KEYDOWN).connect(sigc::mem_fun(this, &KeyboardInputMethod::onKeyDown));
        m_eventHandler->getSignal(SDL_KEYUP).connect(sigc::mem_fun(this, &KeyboardInputMethod::onKeyUp));
    }
    KeyboardInputMethod::~KeyboardInputMethod()
    {
        m_keyDownConnection.disconnect();
        m_keyUpConnection.disconnect();
    }
    void KeyboardInputMethod::update()
    {
        InputMethod::update();
    }
    void KeyboardInputMethod::onKeyDown(const SDL_Event &e, float frametime)
    {
        if(e.key.keysym.scancode == m_scancode)
        {
            setState(true);
        }
    }
    void KeyboardInputMethod::onKeyUp(const SDL_Event &e, float frametime)
    {
        if(e.key.keysym.scancode == m_scancode)
        {
            setState(false);
        }
    }
}
