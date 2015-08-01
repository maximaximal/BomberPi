#include <Client/PlayerInputSystem.hpp>

#include <Client/PlayerInputComponent.hpp>
#include <Client/PlayerComponent.hpp>
#include <Client/Player.hpp>

#include <easylogging++.h>

namespace Client
{
    PlayerInputSystem::PlayerInputSystem()
        : Base(anax::ComponentFilter().requires<PlayerInputComponent,
               PlayerComponent>())
    {

    }
    PlayerInputSystem::~PlayerInputSystem()
    {
        m_gameEventConnection.disconnect();
    }
    void PlayerInputSystem::setGameEventHandler(std::shared_ptr<piga::GameEventHandler> gameEventHandler)
    {
        m_gameEventHandler = gameEventHandler;
        m_gameEventConnection = gameEventHandler->getGameEventSignal().connect(sigc::mem_fun(this, &PlayerInputSystem::onGameEvent));
    }
    void PlayerInputSystem::update()
    {
		for(auto &entity : getEntities())
		{
			auto playerInput = entity.getComponent<PlayerInputComponent>();

			//Deactivate inputs which are only momentarly.
			playerInput.inputs[PlayerInputEnum::ACTION] = false;
        }
    }
    void PlayerInputSystem::onGameEvent(const piga::GameEvent &gameEvent, float frametime)
    {
        if(gameEvent.type() == piga::GameEvent::GameInput)
        {
            if(m_inputComponents.count(gameEvent.playerID()) > 0)
            {
                m_inputComponents[gameEvent.playerID()]->inputs[getPlayerInputEnumFromPigaGameControl(gameEvent.gameInput.control())]
                        = gameEvent.gameInput.state();

                if(gameEvent.gameInput.state())
                    m_inputComponents[gameEvent.playerID()]->lastInput = getPlayerInputEnumFromPigaGameControl(gameEvent.gameInput.control());
            }
        }
    }
    void PlayerInputSystem::onEntityAdded(anax::Entity &entity)
    {
        auto &playerComp = entity.getComponent<PlayerComponent>();
        std::shared_ptr<Player> player = playerComp.player;
        m_inputComponents[player->getPlayerID()] = &entity.getComponent<PlayerInputComponent>();
    }
    void PlayerInputSystem::onEntityRemoved(anax::Entity &entity)
    {
        auto &playerComp = entity.getComponent<PlayerComponent>();
        std::shared_ptr<Player> player = playerComp.player;
        m_inputComponents.erase(player->getPlayerID());
    }
    PlayerInputEnum PlayerInputSystem::getPlayerInputEnumFromPigaGameControl(piga::GameControl control)
    {
        PlayerInputEnum inputEnum;
        switch(control)
        {
            case piga::UP:
                inputEnum = UP;
                break;
            case piga::DOWN:
                inputEnum = DOWN;
                break;
            case piga::LEFT:
                inputEnum = LEFT;
                break;
            case piga::RIGHT:
                inputEnum = RIGHT;
                break;
            case piga::ACTION:
                inputEnum = ACTION;
                break;
            case piga::BUTTON1:
                inputEnum = BUTTON1;
                break;
            case piga::BUTTON2:
                inputEnum = BUTTON2;
                break;
            case piga::BUTTON3:
                inputEnum = BUTTON3;
                break;
            case piga::BUTTON4:
                inputEnum = BUTTON4;
                break;
            case piga::BUTTON5:
                inputEnum = BUTTON5;
                break;
            case piga::BUTTON6:
                inputEnum = BUTTON6;
                break;
            default:
                //Do nothing.
                break;
        }
        return inputEnum;
    }
    piga::GameControl PlayerInputSystem::getPigaGameControlFromPlayerInputEnum(PlayerInputEnum playerInput)
    {
        piga::GameControl control;
        switch(playerInput)
        {
            case UP:
                control = piga::UP;
                break;
            case DOWN:
                control = piga::DOWN;
                break;
            case LEFT:
                control = piga::LEFT;
                break;
            case RIGHT:
                control = piga::RIGHT;
                break;
            case ACTION:
                control = piga::ACTION;
                break;
            case BUTTON1:
                control = piga::BUTTON1;
                break;
            case BUTTON2:
                control = piga::BUTTON2;
                break;
            case BUTTON3:
                control = piga::BUTTON3;
                break;
            case BUTTON4:
                control = piga::BUTTON4;
                break;
            case BUTTON5:
                control = piga::BUTTON5;
                break;
            case BUTTON6:
                control = piga::BUTTON6;
                break;
            default:
                //Do nothing.
                break;
        }
        return control;
    }
}
