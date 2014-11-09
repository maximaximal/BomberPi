#ifndef CLIENT_KILLENTITYTYPESYSTEM_HPP_INCLUDED
#define CLIENT_KILLENTITYTYPESYSTEM_HPP_INCLUDED

#include <anax/System.hpp>
#include <Client/EntityTypeComponent.hpp>

namespace Client
{
    class KillEntityTypeSystem : public anax::System<KillEntityTypeSystem>
    {
        public:
            KillEntityTypeSystem();
            virtual ~KillEntityTypeSystem();

            void killType(Type type);
    };
}

#endif
