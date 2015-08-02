#ifndef CLIENT_AICONTROLSYSTEM_HPP_INCLUDED
#define CLIENT_AICONTROLSYSTEM_HPP_INCLUDED

#include <anax/System.hpp>

namespace Client
{
class BombermanMap;
class CollisionSystem;

class AIControlSystem : public anax::System<AIControlSystem>
{
    public:
        AIControlSystem(BombermanMap *map, CollisionSystem *collisionSystem);
        virtual ~AIControlSystem();

        void update();
    private:
        BombermanMap *m_map;
        CollisionSystem *m_collisionSystem;
};
}

#endif

