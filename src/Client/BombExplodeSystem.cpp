#include <Client/BombExplodeSystem.hpp>

#include <Client/BombComponent.hpp>
#include <Client/PositionComponent.hpp>
#include <Client/BombLayerComponent.hpp>
#include <Client/TimerComponent.hpp>

#include <easylogging++.h>

namespace Client
{
    BombExplodeSystem::BombExplodeSystem(std::shared_ptr<BombermanMap> bombermanMap)
    	: Base(anax::ComponentFilter().requires<PositionComponent,
               BombComponent,
               TimerComponent>())
    {
		m_bombermanMap = bombermanMap;
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
                    layer.bombsRemaining += 1;
				}
				entity.kill();
            }
        }
    }
}
