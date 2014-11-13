#include <StateManager.hpp>
#include <easylogging++.h>

void StateManager::push(std::shared_ptr<State> state)
{
    state->setHandlers(this);
    state->setTextureManager(m_textureManager);
    state->setFontManager(m_fontManager);
    state->setWindow(m_window);
    state->setConfig(m_config);
    state->setInterface(m_pigaInterface);
    m_states.push_back(state);
}

void StateManager::pop()
{
    m_states.pop_back();
}

std::shared_ptr<State> StateManager::top()
{
    return m_states.back();
}

void StateManager::render(Client::Window *window)
{
    if(m_states.size() > 0)
    {
        top()->render(window);
    }
}

void StateManager::update(float frameTime)
{
    if(m_states.size() > 0)
    {
        top()->update(frameTime);
        if(top()->hasEnded())
        {
            pop();
        }
    }
}

void StateManager::setTextureManager(Client::TextureManager *textureManager)
{
    m_textureManager = textureManager;
    for(auto &state : m_states)
    {
        state->setTextureManager(textureManager);
    }
}

void StateManager::setFontManager(PiH::FontManager *fontManager)
{
    m_fontManager = fontManager;
    for(auto &state : m_states)
    {
        state->setFontManager(fontManager);
    }
}

void StateManager::setWindow(Client::Window *window)
{
    m_window = window;
    for(auto &state : m_states)
    {
        state->setWindow(window);
    }
}
void StateManager::setConfig(Client::Config *config)
{
    m_config = config;
    for(auto &state : m_states)
    {
        state->setConfig(config);
    }
}
void StateManager::setPigaInterface(piga::Interface *interface)
{
    m_pigaInterface = interface;
    for(auto &state : m_states)
    {
        state->setInterface(interface);
    }
}
Client::Window *StateManager::getWindow()
{
    return m_window;
}

void StateManager::onSDLEvent(const SDL_Event &e, float frametime)
{
    if(m_states.size() > 0)
    {
        top()->getSDLEventHandler()->sendEvent(e, frametime);
    }
}
void StateManager::onGameEvent(const piga::GameEvent &gameEvent, float frametime)
{
    if(m_states.size() > 0)
    {
        top()->getGameEventHandler()->sendGameEvent(gameEvent, frametime);
    }
}
