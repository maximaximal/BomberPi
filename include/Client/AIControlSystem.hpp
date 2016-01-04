#ifndef CLIENT_AICONTROLSYSTEM_HPP_INCLUDED
#define CLIENT_AICONTROLSYSTEM_HPP_INCLUDED

#include <anax/System.hpp>
#include <Client/SpeedComponent.hpp>
#include <Client/BodyComponent.hpp>
#include <Client/AIComponent.hpp>
#include <Client/HealthComponent.hpp>

namespace Client
{
class BombermanMap;
class CollisionSystem;

class AIControlSystem : public anax::System<anax::Requires<AIComponent, SpeedComponent, HealthComponent>>
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

