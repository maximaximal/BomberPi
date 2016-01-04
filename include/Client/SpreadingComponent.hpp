#ifndef CLIENT_SPREADINGCOMPONENT_HPP_INCLUDED
#define CLIENT_SPREADINGCOMPONENT_HPP_INCLUDED

#include <anax/Component.hpp>

namespace Client
{
    class SpreadingComponent : public anax::Component
    {
        public:
            enum SpreadingFrom {
                BOTTOM,
                LEFT,
                RIGHT,
                TOP,
                NOWHERE,

                _COUNT
            };

            SpreadingComponent(int power, int corners, SpreadingFrom from);
            SpreadingComponent();
            virtual ~SpreadingComponent();

            int power = 1;
            int corners = 0;
			SpreadingFrom from = SpreadingFrom::NOWHERE;
            bool spread = false;
    };
}

#endif
