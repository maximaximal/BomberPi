#ifndef CLIENT_PLAYERINPUTCOMPONENT_HPP_INCLUDED
#define CLIENT_PLAYERINPUTCOMPONENT_HPP_INCLUDED

#include <map>
#include <anax/Component.hpp>
#include <PlayerInput.hpp>

namespace Client
{
    struct PlayerInputComponent : anax::Component<PlayerInputComponent>
    {
		PlayerInputComponent();

        std::map<PlayerInputEnum, bool> inputs;
    };
}

#endif
