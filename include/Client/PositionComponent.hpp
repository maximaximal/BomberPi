#ifndef CLIENT_POSITIONCOMPONENT_HPP
#define CLIENT_POSITIONCOMPONENT_HPP

#include <anax/Component.hpp>
#include <glm/vec2.hpp>

namespace Client
{
   	class PositionComponent : public anax::Component<PositionComponent>
    {
        public:
			PositionComponent();
			PositionComponent(glm::dvec2 pos);
			PositionComponent(glm::ivec2 pos);
			PositionComponent(float x, float y);

            virtual ~PositionComponent();

			glm::dvec2 pos;
            glm::dvec2 orientation;

			float getXF();
			float getYF();
			int getXI();
			int getYI();
    };
}

#endif
