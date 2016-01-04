#ifndef CLIENT_HEALTHCOMPONENT_HPP_INCLUDED
#define CLIENT_HEALTHCOMPONENT_HPP_INCLUDED

#include <anax/Component.hpp>
#include <anax/Entity.hpp>
#include <sigc++/sigc++.h>

namespace PiH
{
    class HealthAndNameDisplay;
}

namespace Client
{
    class HealthComponent : public anax::Component
    {
        public:
            HealthComponent();
            HealthComponent(int health, PiH::HealthAndNameDisplay *display = nullptr);
            virtual ~HealthComponent();

            float health = 1;
            float invincibleFor = 0;

            PiH::HealthAndNameDisplay *display = nullptr;

            sigc::signal<void, int, anax::Entity> damageOccured;
    };
}

#endif // CLIENT_HEALTHCOMPONENT_HPP_INCLUDED
