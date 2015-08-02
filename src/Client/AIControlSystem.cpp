#include <Client/AIControlSystem.hpp>

#include <Client/SpeedComponent.hpp>
#include <Client/BodyComponent.hpp>
#include <Client/AIComponent.hpp>
#include <Client/BombermanMap.hpp>
#include <Client/CollisionSystem.hpp>

namespace Client
{

AIControlSystem::AIControlSystem(BombermanMap *map, CollisionSystem *collisionSystem)
    : Base(anax::ComponentFilter().requires<AIComponent,
           SpeedComponent,
           BodyComponent>())
{
    m_map = map;
    m_collisionSystem = collisionSystem;
}
AIControlSystem::~AIControlSystem()
{

}
void AIControlSystem::update()
{

}

}
