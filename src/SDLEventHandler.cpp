#include <SDLEventHandler.hpp>


void SDLEventHandler::sendEvent(const SDL_Event &e, float frametime)
{
    onSDLEvent(e, frametime);
    m_signals[e.type](e, frametime);
}

SDLEventHandler::SDLEventSignal SDLEventHandler::getSignal(uint8_t type)
{
    return m_signals[type];
}

void SDLEventHandler::onSDLEvent(const SDL_Event &e, float frametime)
{
    //Nothing to do here - this function can be derived from.
}
