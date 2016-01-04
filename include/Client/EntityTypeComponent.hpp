#ifndef CLIENT_ENTITYTYPECOMPONENT_HPP_INCLUDED
#define CLIENT_ENTITYTYPECOMPONENT_HPP_INCLUDED

#include <anax/Component.hpp>

namespace Client
{
    enum class Type
    {
        Player,
        Bomb,
        Explosion,
        Powerup,

        NOT_SET,
        _COUNT
    };

    class EntityTypeComponent : public anax::Component
    {
    	public:
            EntityTypeComponent(Client::Type type = Type::NOT_SET);
            virtual ~EntityTypeComponent();

            Type type;
    };
}

#endif
