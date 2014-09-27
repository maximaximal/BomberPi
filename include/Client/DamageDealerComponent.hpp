#ifndef CLIENT_DAMAGEDEALERCOMPONENT_HPP_INCLUDED
#define CLIENT_DAMAGEDEALERCOMPONENT_HPP_INCLUDED

#include <anax/Component.hpp>

namespace Client
{
    class DamageDealerComponent : public anax::Component<DamageDealerComponent>
    {
        public:
            DamageDealerComponent();
            DamageDealerComponent(int damagePerSecond);
            virtual ~DamageDealerComponent();

            int damagePerSecond = 0;
    };
}

#endif // CLIENT_DAMAGEDEALERCOMPONENT_HPP_INCLUDED
