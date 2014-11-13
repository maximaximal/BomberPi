#include <State.hpp>
#include <SDLEventHandler.hpp>
#include <piga/GameEventHandler.hpp>

std::shared_ptr<SDLEventHandler> State::getSDLEventHandler()
{
    if(!m_sdlEventHandler)
        m_sdlEventHandler = std::make_shared<SDLEventHandler>();
    return m_sdlEventHandler;
}
std::shared_ptr<piga::GameEventHandler> State::getGameEventHandler()
{
    if(!m_gameEventHandler)
        m_gameEventHandler = std::make_shared<piga::GameEventHandler>();
    return m_gameEventHandler;
}
Client::TextureManager *State::getTextureManager()
{
    return m_textureManager;
}
PiH::FontManager *State::getFontManager()
{
    return m_fontManager;
}
StateManager* State::getStateManager()
{
    return m_stateManager;
}
Client::Window *State::getWindow()
{
    return m_window;
}
Client::Config *State::getConfig()
{
    return m_config;
}
piga::Interface *State::getInterface()
{
    return m_pigaInterface;
}
void State::setHandlers(StateManager *stateManager)
{
    m_stateManager = stateManager;
}
void State::setTextureManager(Client::TextureManager *textureManager)
{
    m_textureManager = textureManager;
}

void State::setFontManager(PiH::FontManager *fontManager)
{
    m_fontManager = fontManager;
}

void State::setWindow(Client::Window *window)
{
    m_window = window;
}

void State::setConfig(Client::Config *config)
{
    m_config = config;
}
void State::setInterface(piga::Interface *interface)
{
    m_pigaInterface = interface;
}
void State::render(Client::Window *window)
{

}
void State::update(float frameTime)
{

}
bool State::hasEnded()
{
    return m_hasEnded;
}
void State::end()
{
    m_hasEnded = true;
}
