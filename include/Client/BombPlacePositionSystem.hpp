#ifndef CLIENT_BOMBPLACEPOSITIONSYSTEM_HPP_INCLUDED
#define CLIENT_BOMBPLACEPOSITIONSYSTEM_HPP_INCLUDED

#include <anax/System.hpp>
#include <Client/BombermanMap.hpp>

namespace Client
{
    class CollisionSystem;

    class BombPlacePositionSystem : public anax::System<BombPlacePositionSystem>
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
