#ifndef CLIENT_COLLISIONSYSTEM_HPP_INCLUDED
#define CLIENT_COLLISIONSYSTEM_HPP_INCLUDED

#include <anax/System.hpp>
#include <Client/BombermanMap.hpp>

namespace Client
{
    class CollisionSystem : public anax::System<CollisionSystem>
    {
        public:
            CollisionSystem(BombermanMap *bombermanMap);
            virtual ~CollisionSystem();

            void update(float frametime);
        private:
            BombermanMap *m_map;
    };
}

#endif // CLIENT_COLLISIONSYSTEM_HPP_INCLUDED
