#include <Client/Player.hpp>
#include <Client/HealthComponent.hpp>
#include <Client/PositionComponent.hpp>
#include <Client/PlayerComponent.hpp>
#include <Client/BodyComponent.hpp>
#include <Client/BombLayerComponent.hpp>
#include <easylogging++.h>

namespace Client
{
    Player::Player(const std::string &name, int playerID)
        : piga::Player(name.c_str(), true, playerID)
    {

    }
    Player::~Player()
    {

    }
    void Player::setEntity(anax::Entity playerEntity)
    {
        m_entity = playerEntity;
    }
    void Player::damageReceived(int damage, anax::Entity dealer)
    {
        die();
    }
    void Player::die()
    {
        resetBombLayerComponent();
        setPosition(getStartingPosition());
    }
    bool Player::isDead()
    {
		if(getHealth() <= 0)
            return true;
        return false;
    }
    int Player::getHealth()
    {
        if(m_entity.isValid())
        {
            if(m_entity.hasComponent<HealthComponent>())
            {
                auto &health = m_entity.getComponent<HealthComponent>();
                return health.health;
            }
        }
        return 0;
    }
    void Player::setHealth(int value)
    {
        if(m_entity.isValid())
        {
            if(m_entity.hasComponent<HealthComponent>())
            {
                auto &health = m_entity.getComponent<HealthComponent>();
                health.health = value;
            }
        }
    }
    void Player::setPosition(const glm::ivec2 &pos)
    {
        if(m_entity.isValid())
        {
            if(m_entity.hasComponent<PositionComponent>())
            {
                auto &posComp = m_entity.getComponent<PositionComponent>();
                posComp.pos = pos;
            }
        }
    }

    void Player::resetBombLayerComponent()
    {
        if(m_entity.isValid())
        {
            if(m_entity.hasComponent<BombLayerComponent>())
            {
                auto &layer = m_entity.getComponent<BombLayerComponent>();
                layer.reset();
            }
        }
    }
    const glm::ivec2 &Player::getStartingPosition()
    {
        if(m_entity.isValid())
        {
            if(m_entity.hasComponent<PlayerComponent>())
            {
                auto &player = m_entity.getComponent<PlayerComponent>();
                return player.startingPos;
            }
			throw(std::out_of_range("The player component of the player's entity was not set!"));
        }
    }

    glm::ivec2 Player::getPosition()
    {
        if(m_entity.isValid())
        {
            if(m_entity.hasComponent<PositionComponent>())
            {
                auto &posComp = m_entity.getComponent<PositionComponent>();
                return posComp.pos;
            }
			throw(std::out_of_range("The position component of the player's entity was not set!"));
        }
        return glm::ivec2(32, 32);
    }
    void Player::setPowerupQueueUI(UI::PowerupQueue *powerupQueueUI)
    {
        if(m_entity.isValid())
        {
            if(m_entity.hasComponent<BombLayerComponent>())
            {
                auto &layer = m_entity.getComponent<BombLayerComponent>();
                layer.powerupQueue.setPowerupQueueUI(powerupQueueUI);
            }
        }
    }
    void Player::update(float frametime)
    {
		if(isDead())
        {
            if(m_entity.isValid())
            {
                die();
            }
        }
    }

    void Player::reset()
    {
        setPosition(getStartingPosition());
        setHealth(3);
        resetBombLayerComponent();

        auto &body = m_entity.getComponent<BodyComponent>();
        body.movementDirection = BodyComponent::NOT_MOVING;

        if(m_entity.isValid())
        {
			m_entity.activate();
        }
    }
}
