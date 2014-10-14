#ifndef CLIENT_HEALTHCOMPONENT_HPP_INCLUDED
#define CLIENT_HEALTHCOMPONENT_HPP_INCLUDED

#include <anax/Component.hpp>
#include <pihud/HealthAndNameDisplay.hpp>

namespace Client
{
    class HealthComponent : public anax::Component<HealthComponent>
    {
        public:
            HealthComponent();
            HealthComponent(int health, PiH::HealthAndNameDisplay *display = nullptr);
            virtual ~HealthComponent();

            float health = 1;
            float invincibleFor = 0;

            PiH::HealthAndNameDisplay *display = nullptr;
    };
}

#endif // CLIENT_HEALTHCOMPONENT_HPP_INCLUDED
