#ifndef CLIENT_BODYCOMPONENT_HPP_INCLUDED
#define CLIENT_BODYCOMPONENT_HPP_INCLUDED

#include <anax/Component.hpp>
#include <sigc++/sigc++.h>
#include <memory>
#include <Client/Collision.hpp>

namespace Client
{
    class BodyComponent : public anax::Component<BodyComponent>
    {
        public:
            enum MovementDirection
            {
                UP,
                DOWN,
                LEFT,
                RIGHT,
                NOT_MOVING,

                _COUNT
            };

            typedef sigc::signal<void, std::shared_ptr<Collision> > CollisionSignal;

            BodyComponent();
            BodyComponent(float x, float y, float w, float h);

            virtual ~BodyComponent();

            //X & Y are relative to the position of the entity.
				float x = 0;
				float y = 0;

            float w = 0;
            float h = 0;

            float drag = 0;

            BodyComponent::MovementDirection movementDirection = MovementDirection::NOT_MOVING;
            bool currentlyMoving();
            glm::ivec2 targetPos;

            glm::dvec2 lastMove;

            CollisionSignal collisionSignal;
    };
}

#endif
