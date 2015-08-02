#ifndef CLIENT_SPEEDCOMPONENT_HPP_INCLUDED
#define CLIENT_SPEEDCOMPONENT_HPP_INCLUDED

#include <anax/Component.hpp>

namespace Client
{
class SpeedComponent : public anax::Component<SpeedComponent>
{
    public:
        SpeedComponent(float speed = 150) : speed(speed) {}
        virtual ~SpeedComponent() {}

        float speed;
};
}

#endif

