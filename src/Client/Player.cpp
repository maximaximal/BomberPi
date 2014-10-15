#include <Client/Player.hpp>
#include <Client/HealthComponent.hpp>
#include <easylogging++.h>

namespace Client
{
    Player::Player(const std::string &name, anax::Entity entity)
    {
        m_name = name;
        m_entity = entity;
    }
    Player::~Player()
    {
        if(m_entity.isValid())
			m_entity.kill();
    }
    void Player::setEntity(anax::Entity playerEntity)
    {
        m_entity = playerEntity;
    }
    void Player::damageReceived(int damage, anax::Entity dealer)
    {
		if(isDead())
        {
            LOG(INFO) << "The player is dead!!";
        }
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
}
