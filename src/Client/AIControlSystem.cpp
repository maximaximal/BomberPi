#include <Client/AIControlSystem.hpp>

#include <Client/BombermanMap.hpp>
#include <Client/CollisionSystem.hpp>

namespace Client
{

AIControlSystem::AIControlSystem(BombermanMap *map, CollisionSystem *collisionSystem)
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
