#include <Client/PlayerInputComponent.hpp>

namespace Client
{

    PlayerInputComponent::PlayerInputComponent()
    {
        //Set all inputs to false.
        for(unsigned int i = 0; i < PlayerInputEnum::_COUNT; ++i)
        {
            PlayerInputEnum input = static_cast<PlayerInputEnum>(i);
            inputs[input] = false;
        }
    }

}
