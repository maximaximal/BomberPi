#ifndef CLIENT_PLAYERINPUTCOMPONENT_HPP_INCLUDED
#define CLIENT_PLAYERINPUTCOMPONENT_HPP_INCLUDED

#include <map>
#include <anax/Component.hpp>
#include <PlayerInput.hpp>
#include <InputMap.hpp>

namespace Client
{
    class PlayerInputComponent : public anax::Component<PlayerInputComponent>
    {
        public:
			PlayerInputComponent();
            virtual ~PlayerInputComponent();

			std::map<PlayerInputEnum, bool> inputs;
			InputMap inputMap;

            bool isActive(PlayerInputEnum input);
    };
}

#endif
