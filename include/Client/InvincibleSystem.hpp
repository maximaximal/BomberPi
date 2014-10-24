#ifndef CLIENT_HEALTHSYSTEM_HPP_INCLUDED
#define CLIENT_HEALTHSYSTEM_HPP_INCLUDED

#include <anax/System.hpp>

namespace Client
{
    class HealthSystem : public anax::System<HealthSystem>
    {
        public:
            HealthSystem();
            virtual ~HealthSystem();

            void update(float frametime);
    };
}

#endif