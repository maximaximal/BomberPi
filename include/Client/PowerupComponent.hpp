#ifndef CLIENT_POWERUPCOMPONENT_HPP_INCLUDED
#define CLIENT_POWERUPCOMPONENT_HPP_INCLUDED

#include <memory>
#include <anax/Component.hpp>
#include <Client/Powerup.hpp>

namespace Client
{
    class PowerupComponent : public anax::Component
    {
    	public:
            PowerupComponent(Powerup::Predefined definition = Powerup::NOT_DEFINED);
            virtual ~PowerupComponent();

            std::shared_ptr<Powerup> powerup;
    };
}

#endif
