#ifndef CLIENT_INVINCIBLESYSTEM_HPP_INCLUDED
#define CLIENT_INVINCIBLESYSTEM_HPP_INCLUDED

#include <anax/System.hpp>
#include <Client/HealthComponent.hpp>

namespace Client
{
    class HealthSystem : public anax::System<anax::Requires<HealthComponent>>
    {
        public:
            HealthSystem();
            virtual ~HealthSystem();

            void update(float frametime);
    };
}

#endif
