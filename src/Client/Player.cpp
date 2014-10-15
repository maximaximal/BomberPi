#include <Client/Player.hpp>
#include <Client/HealthComponent.hpp>
#include <Client/PositionComponent.hpp>
#include <Client/PlayerComponent.hpp>
#include <easylogging++.h>

namespace Client
{
    Player::Player(const std::string &name)
    {
        m_name = name;
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
        setPosition(getStartingPosition());
    }
    void Player::die()
    {
		setHealth(0);
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

    const glm::ivec2 &Player::getStartingPosition()
    {
        if(m_entity.isValid())
        {
            if(m_entity.hasComponent<PlayerComponent>())
            {
                auto &player = m_entity.getComponent<PlayerComponent>();
                return player.startingPos;
            }
        }
    }
    void Player::update(float frametime)
    {
		if(isDead())
        {
            if(m_entity.isValid())
            {
                m_entity.kill();
            }
        }
    }
}
