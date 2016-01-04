#ifndef CLIENT_BOMBPLACEPOSITIONSYSTEM_HPP_INCLUDED
#define CLIENT_BOMBPLACEPOSITIONSYSTEM_HPP_INCLUDED

#include <anax/System.hpp>
#include <Client/BombermanMap.hpp>

#include <Client/BombLayerComponent.hpp>
#include <Client/PositionComponent.hpp>

namespace Client
{
    class CollisionSystem;

    class BombPlacePositionSystem : public anax::System<anax::Requires<BombLayerComponent, PositionComponent>>
    {
        public:
            BombPlacePositionSystem(BombermanMap *bombermanMap, Client::CollisionSystem *collisionSystem);
            virtual ~BombPlacePositionSystem();

            void update(float frametime);
        private:
            BombermanMap *m_bombermanMap;
            CollisionSystem *m_collisionSystem;
    };
}

#endif
