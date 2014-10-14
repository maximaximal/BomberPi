#ifndef CLIENT_ENTITYFACTORY_HPP_INCLUDED
#define CLIENT_ENTITYFACTORY_HPP_INCLUDED

#include <memory>
#include <anax/World.hpp>
#include <Client/Window.hpp>
#include <glm/vec2.hpp>
#include <InputMap.hpp>
#include <Client/TextureManager.hpp>
#include <Client/SpreadingComponent.hpp>

#include <pihud/HealthAndNameDisplay.hpp>

namespace Client
{
    class PlayerMovementSystem;

    class EntityFactory
    {
        public:
            EntityFactory(anax::World *world,
                          TextureManager *textureManager);
            virtual ~EntityFactory();

            anax::Entity createPlayer(const glm::ivec2 &pos, const InputMap &inputMap,
                                      Client::PlayerMovementSystem *playerMovementSystem,
                                      PiH::HealthAndNameDisplay *healthAndNameDisplay);

            anax::Entity createBomb(const glm::ivec2 &pos, anax::Entity thrower);

            anax::Entity createExplosion(const glm::ivec2 &pos, int powerLeft, int turnsLeft, Client::SpreadingComponent::SpreadingFrom from);
        private:
            TextureManager *m_textureManager;
            anax::World *m_world;
    };
}

#endif
