#include <Client/KillEntityTypeSystem.hpp>

namespace Client
{
    KillEntityTypeSystem::KillEntityTypeSystem()
    {

    }
    KillEntityTypeSystem::~KillEntityTypeSystem()
    {

    }
    void KillEntityTypeSystem::killType(Type type)
    {
        for(auto &entity : getEntities())
        {
            auto &entityType = entity.getComponent<EntityTypeComponent>();

            if(entityType.type == type)
            {
                entity.kill();
            }
        }
    }
}
