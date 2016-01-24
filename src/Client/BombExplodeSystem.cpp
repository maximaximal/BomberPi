#include <Client/BombExplodeSystem.hpp>
#include <glm/vec3.hpp>
#include <Client/BombComponent.hpp>
#include <Client/BombLayerComponent.hpp>
#include <easylogging++.h>

namespace Client
{
    BombExplodeSystem::BombExplodeSystem(EntityFactory *entityFactory, anax::World *anaxWorld)
    {
        m_entityFactory = entityFactory;
        m_world = anaxWorld;
    }
    BombExplodeSystem::~BombExplodeSystem()
    {

    }
    void BombExplodeSystem::update()
    {
		for(auto &entity : getEntities())
        {
            auto &pos = entity.getComponent<PositionComponent>();
            auto &bomb = entity.getComponent<BombComponent>();
            auto &timer = entity.getComponent<TimerComponent>();

            if(timer.complete)
            {
                //getWorld().getEntity()
				if(bomb.thrower.hasComponent<BombLayerComponent>())
				{
					auto &layer = bomb.thrower.getComponent<BombLayerComponent>();

                    //Only up the remaining bombs, if there are less than the maximum
                    //This is needed for +1 Bomb powerups (they would be overpowered)
                    if(layer.bombsRemaining < layer.bombsRemainingMax)
						layer.bombsRemaining += 1;
				}
                m_entityFactory->createExplosion(pos.pos, bomb.tiles, bomb.turns, SpreadingComponent::NOWHERE);

                anax::Entity e = const_cast<anax::Entity&>(entity);
                e.kill();
            }
        }
    }
}
