#ifndef CLIENT_HEALTHCOMPONENT_HPP_INCLUDED
#define CLIENT_HEALTHCOMPONENT_HPP_INCLUDED

#include <anax/Component.hpp>

namespace Client
{
    class HealthComponent : public anax::Component<HealthComponent>
    {
        public:
            HealthComponent();
            HealthComponent(int health);
            virtual ~HealthComponent();

            int health = 1;
    };
}

#endif // CLIENT_HEALTHCOMPONENT_HPP_INCLUDED
