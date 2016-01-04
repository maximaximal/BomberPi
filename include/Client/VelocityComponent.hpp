#ifndef CLIENT_VELOCITYCOMPONENT_HPP
#define CLIENT_VELOCITYCOMPONENT_HPP

#include <glm/vec2.hpp>
#include <anax/Component.hpp>

namespace Client
{
    class VelocityComponent : public anax::Component
    {
        public:
            VelocityComponent();
            VelocityComponent(glm::dvec2 vel);
            VelocityComponent(double x, double y);
            VelocityComponent(int x, int y);

            virtual ~VelocityComponent();
            void clear();

            glm::dvec2 velocity;
    };
}

#endif
