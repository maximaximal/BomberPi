#ifndef CLIENT_COLLISIONSYSTEM_HPP_INCLUDED
#define CLIENT_COLLISIONSYSTEM_HPP_INCLUDED

#include <anax/System.hpp>
#include <Client/BombermanMap.hpp>
#include <Client/Collision.hpp>

namespace Client
{
    class CollisionSystem : public anax::System<CollisionSystem>
    {
        public:
            CollisionSystem(BombermanMap *bombermanMap);
            virtual ~CollisionSystem();

            void update(float frametime);
            void collideWithMapTile(const BombermanMapTile &tile, const glm::ivec3 &pos, anax::Entity &e);
        private:
            BombermanMap *m_map;
    };
}

#endif // CLIENT_COLLISIONSYSTEM_HPP_INCLUDED
