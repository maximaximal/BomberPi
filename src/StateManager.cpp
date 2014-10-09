#include <StateManager.hpp>
#include <easylogging++.h>

void StateManager::push(std::shared_ptr<State> state)
{
    state->setHandlers(this);
    state->setTextureManager(m_textureManager);
    state->setFontManager(m_fontManager);
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
}

void StateManager::onSDLEvent(const SDL_Event &e, float frametime)
{
    if(m_states.size() > 0)
    {
        top()->getSDLEventHandler()->sendEvent(e, frametime);
    }
}
