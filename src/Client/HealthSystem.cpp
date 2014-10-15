#include <Client/InvincibleSystem.hpp>

#include <Client/HealthComponent.hpp>
#include <pihud/HealthAndNameDisplay.hpp>

namespace Client
{
    HealthSystem::HealthSystem()
    	: Base(anax::ComponentFilter().requires<HealthComponent>())
    {

    }
    HealthSystem::~HealthSystem()
    {

    }
    void HealthSystem::update(float frametime)
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

			if(health.display != nullptr)
				health.display->setCurrentHealth(health.health);
        }
    }
}
