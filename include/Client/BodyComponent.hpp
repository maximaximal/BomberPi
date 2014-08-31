#ifndef CLIENT_BODYCOMPONENT_HPP_INCLUDED
#define CLIENT_BODYCOMPONENT_HPP_INCLUDED

#include <anax/Component.hpp>

namespace Client
{
    class BodyComponent : public anax::Component<BodyComponent>
    {
        public:
            BodyComponent();
            BodyComponent(float x, float y, float w, float h);

            virtual ~BodyComponent();

            //X & Y are relative to the position of the entity.
				float x = 0;
				float y = 0;

            float w = 0;
            float h = 0;

            float drag = 0;
    };
}

#endif
