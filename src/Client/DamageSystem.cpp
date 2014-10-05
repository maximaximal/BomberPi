#include <Client/DamageSystem.hpp>

#include <Client/BodyComponent.hpp>
#include <Client/PositionComponent.hpp>
#include <Client/DamageDealerComponent.hpp>
#include <Client/HealthComponent.hpp>
#include <Client/Collision.hpp>
#include <easylogging++.h>

namespace Client 
{
    DamageSystem::DamageSystem()
        : Base(anax::ComponentFilter().requires<BodyComponent,
               DamageDealerComponent,
               PositionComponent>())
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
				health.health -= damage.damagePerSecond * m_lastFrametime;

				LOG(INFO) << "Damage: " << damage.damagePerSecond * m_lastFrametime;
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
