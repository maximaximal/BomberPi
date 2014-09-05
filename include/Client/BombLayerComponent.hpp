#ifndef CLIENT_BOMBLAYERCOMPONENT_HPP_INCLUDED
#define CLIENT_BOMBLAYERCOMPONENT_HPP_INCLUDED

#include <glm/vec2.hpp>
#include <anax/Component.hpp>

namespace Client
{
    class BombLayerComponent : public anax::Component<BombLayerComponent>
    {
        public:
            BombLayerComponent();
            virtual ~BombLayerComponent();

            short bombsRemaining;

            glm::ivec2 placePos;

            //TODO Bomb modifiers.
    };
}

#endif
