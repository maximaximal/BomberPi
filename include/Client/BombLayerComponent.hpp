#ifndef CLIENT_BOMBLAYERCOMPONENT_HPP_INCLUDED
#define CLIENT_BOMBLAYERCOMPONENT_HPP_INCLUDED

#include <glm/vec2.hpp>
#include <anax/Component.hpp>
#include <Client/PowerupQueue.hpp>

namespace Client
{
    class BombLayerComponent : public anax::Component<BombLayerComponent>
    {
        public:
            BombLayerComponent();
            BombLayerComponent(float cooldown);
            virtual ~BombLayerComponent();
            void reset();

            short bombsRemaining = 1;
            short bombsRemainingMax = 1;
            float speedMultiplicator = 1;
            float lastPlacedBomb = 0;

            short getBombsRemaining();
            float getSpeedMultiplicator();
            int getBombTurns();
            int getBombTiles();

            PowerupQueue powerupQueue;

            int bombTurns = 0;
            int bombTiles = 1;

            glm::ivec2 placePos;

            bool canPlace();
			bool positionOkay = false;

            float cooldown = 0.3;
    };
}

#endif
