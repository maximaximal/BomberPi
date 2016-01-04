#ifndef CLIENT_DAMAGEDEALERCOMPONENT_HPP_INCLUDED
#define CLIENT_DAMAGEDEALERCOMPONENT_HPP_INCLUDED

#include <anax/Component.hpp>

namespace Client
{
    class DamageDealerComponent : public anax::Component
    {
        public:
            DamageDealerComponent();
            DamageDealerComponent(int damage);
            virtual ~DamageDealerComponent();

            int damage = 0;
    };
}

#endif // CLIENT_DAMAGEDEALERCOMPONENT_HPP_INCLUDED
