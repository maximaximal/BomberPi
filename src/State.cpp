#include <State.hpp>
#include <SDLEventHandler.hpp>

std::shared_ptr<SDLEventHandler> State::getSDLEventHandler()
{
    if(!m_sdlEventHandler)
        m_sdlEventHandler = std::make_shared<SDLEventHandler>();
    return m_sdlEventHandler;
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

void State::render(Client::Window *window)
{

}

void State::update(float frameTime)
{

}
