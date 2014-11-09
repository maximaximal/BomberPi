#include <Client/KillEntityTypeSystem.hpp>

namespace Client
{
    KillEntityTypeSystem::KillEntityTypeSystem()
        : Base(anax::ComponentFilter().requires<EntityTypeComponent>())
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
