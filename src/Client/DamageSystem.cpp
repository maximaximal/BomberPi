#include <Client/DamageSystem.hpp>

#include <Client/HealthComponent.hpp>
#include <Client/Collision.hpp>
#include <easylogging++.h>

namespace Client 
{
    DamageSystem::DamageSystem()
    {

    }
    DamageSystem::~DamageSystem()
    {

    }
    void DamageSystem::update(float frametime)
    {
        m_lastFrametime = frametime;
    }
    void DamageSystem::onDamageDealerCollision(std::shared_ptr<Collision> collision)
    {
        if(collision->getType() == Collision::EntityWithEntity)
        {
			auto &dealer = collision->getA();
			auto &witness = collision->getB();

			if(witness.hasComponent<HealthComponent>())
			{
				auto &health = witness.getComponent<HealthComponent>();
				auto &damage = dealer.getComponent<DamageDealerComponent>();

                if(health.invincibleFor == 0)
                {
					health.health -= damage.damage;
					health.invincibleFor = 1;

                    //Fire the damageOccured event from the health component.
                    health.damageOccured(damage.damage, dealer);
                }
			}
        }
    }
    void DamageSystem::onEntityAdded(anax::Entity &e)
    {
        auto &body = e.getComponent<BodyComponent>();
        body.collisionSignal.connect(sigc::mem_fun(this, &DamageSystem::onDamageDealerCollision));
    }
    void DamageSystem::onEntityRemoved(anax::Entity &e)
    {

    }
}
