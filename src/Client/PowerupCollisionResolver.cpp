#include <Client/PowerupCollisionResolver.hpp>

#include <Client/PowerupComponent.hpp>
#include <Client/BombLayerComponent.hpp>

namespace Client
{
    namespace Resolver
    {
        void OnPowerupCollison(std::shared_ptr<Collision> collision)
        {
            if(collision->getType() == Collision::Type::EntityWithEntity)
            {
                auto &a = collision->getA();
                auto &b = collision->getB();

                if(b.hasComponent<BombLayerComponent>())
                {
                    auto &powerup = a.getComponent<PowerupComponent>();
                    auto &layer = b.getComponent<BombLayerComponent>();

                    layer.powerupQueue.pushPowerup(powerup.powerup);

                    //Destroy the powerup entity.
                    a.kill();
                }
            }
        }
    }
}
