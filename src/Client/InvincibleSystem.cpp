#include <Client/InvincibleSystem.hpp>

#include <Client/HealthComponent.hpp>

namespace Client
{
    InvincibleSystem::InvincibleSystem()
    	: Base(anax::ComponentFilter().requires<HealthComponent>())
    {

    }
    InvincibleSystem::~InvincibleSystem()
    {

    }
    void InvincibleSystem::update(float frametime)
    {
        for(auto &entity : getEntities())
        {
            auto &health = entity.getComponent<HealthComponent>();

            if(health.invincibleFor > 0)
            {
				health.invincibleFor -= frametime;
                if(health.invincibleFor < 0)
                {
                    health.invincibleFor = 0;
                }
            }
        }
    }
}
