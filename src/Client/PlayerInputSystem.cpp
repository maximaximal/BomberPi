#include <Client/PlayerInputSystem.hpp>

#include <Client/PlayerInputComponent.hpp>

#include <easylogging++.h>

namespace Client
{
    PlayerInputSystem::PlayerInputSystem()
    	: Base(anax::ComponentFilter().requires<PlayerInputComponent>())
    {

    }
    PlayerInputSystem::~PlayerInputSystem()
    {
        m_keyDownConnection.disconnect();
    }
    void PlayerInputSystem::setSDLEventHandler(std::shared_ptr<SDLEventHandler> sdlEventHandler)
    {
        m_sdlEventHandler = sdlEventHandler;
        m_keyDownConnection = sdlEventHandler->getSignal(static_cast<uint8_t>(SDL_KEYDOWN)).connect(
                    sigc::mem_fun(this, &PlayerInputSystem::onKeyDown));
        m_keyUpConnection = sdlEventHandler->getSignal(static_cast<uint8_t>(SDL_KEYUP)).connect(
                    sigc::mem_fun(this, &PlayerInputSystem::onKeyUp));
    }
    void PlayerInputSystem::update()
    {
        if(m_sdlEventHandler)
        {
			for(auto &entity : getEntities())
            {
				auto playerInput = entity.getComponent<PlayerInputComponent>();

				//Deactivate inputs which are only momentarly.
                playerInput.inputs[PlayerInputEnum::ACTION] = false;
            }
        }
    }

    void PlayerInputSystem::onKeyDown(const SDL_Event &e, float frameTime)
    {
		if(m_inputComponents.count(e.key.keysym.scancode) > 0)
        {
            PlayerInputComponent *component = m_inputComponents[e.key.keysym.scancode];
            PlayerInputEnum playerInput = component->inputMap.get(e.key.keysym.scancode);
            component->inputs[playerInput] = true;
        }
    }

    void PlayerInputSystem::onKeyUp(const SDL_Event &e, float frameTime)
    {
		if(m_inputComponents.count(e.key.keysym.scancode) > 0)
        {
            PlayerInputComponent *component = m_inputComponents[e.key.keysym.scancode];
            PlayerInputEnum playerInput = component->inputMap.get(e.key.keysym.scancode);
            component->inputs[playerInput] = false;
        }
    }

    void PlayerInputSystem::onEntityAdded(anax::Entity &entity)
    {
        auto playerInput = &entity.getComponent<PlayerInputComponent>();
        for(auto &mapping : playerInput->inputMap.getMaps())
        {
            m_inputComponents[mapping.first] = playerInput;
        }
    }

    void PlayerInputSystem::onEntityRemoved(anax::Entity &entity)
    {
        auto playerInput = &entity.getComponent<PlayerInputComponent>();
        for(auto &mapping : playerInput->inputMap.getMaps())
        {
            m_inputComponents.erase(mapping.first);
        }
    }
}
