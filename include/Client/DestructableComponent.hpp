#ifndef CLIENT_DESTRUCTABLECOMPONENT_HPP_INCLUDED
#define CLIENT_DESTRUCTABLECOMPONENT_HPP_INCLUDED

#include <anax/Component.hpp>

namespace Client
{
    class DestructableComponent : anax::Component
    {
        public:
            DestructableComponent();
            DestructableComponent(unsigned int health);
            DestructableComponent(unsigned int health, unsigned int resistance);
            virtual ~DestructableComponent();

            /**
             * @brief The current health of the entity.
             */
			unsigned int health = 1;
            /**
             * @brief The resistance (= maximum health) the entity has.
             */
            unsigned int resistance = 1;
    };
}

#endif
