#ifndef CLIENT_BOMBEXPLODESYSTEM_HPP_INCLUDED
#define CLIENT_BOMBEXPLODESYSTEM_HPP_INCLUDED

#include <memory>
#include <anax/System.hpp>
#include <Client/BombermanMap.hpp>

#include <Client/PositionComponent.hpp>
#include <Client/BombComponent.hpp>
#include <Client/TimerComponent.hpp>

namespace Client
{
    class BombExplodeSystem : public anax::System<anax::Requires<PositionComponent, BombComponent, TimerComponent>>
    {
        public:
            BombExplodeSystem(EntityFactory *entityFactory, anax::World *anaxWorld);
            virtual ~BombExplodeSystem();

            void update();
        private:
			EntityFactory *m_entityFactory;
            anax::World *m_world;
    };
}

#endif
