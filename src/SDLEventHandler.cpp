#include <SDLEventHandler.hpp>


SDLEventHandler::SDLEventHandler()
{

}
SDLEventHandler::~SDLEventHandler()
{
    for(auto signal : m_signals)
    {
        signal.second.clear();
    }
    m_signals.clear();
}
void SDLEventHandler::sendEvent(const SDL_Event &e, float frametime)
{
    onSDLEvent(e, frametime);
    if(m_signals.count(e.type) > 0)
        m_signals[e.type](e, frametime);
}

SDLEventHandler::SDLEventSignal &SDLEventHandler::getSignal(int32_t type)
{
    if(m_signals.count(type) == 0)
    {
        m_signals[type] = SDLEventSignal();
    }
    return m_signals[type];
}

void SDLEventHandler::onSDLEvent(const SDL_Event &e, float frametime)
{
    //Nothing to do here - this function can be derived from.
}
