#ifndef CLIENT_ENTITYFACTORY_HPP_INCLUDED
#define CLIENT_ENTITYFACTORY_HPP_INCLUDED

#include <memory>
#include <anax/World.hpp>
#include <Client/Window.hpp>
#include <glm/vec2.hpp>
#include <InputMap.hpp>
#include <Client/TextureManager.hpp>
#include <Client/SpreadingComponent.hpp>
#include <Client/Player.hpp>

#include <pihud/HealthAndNameDisplay.hpp>

namespace Client
{
    class PlayerMovementSystem;
    class PowerupComponent;

    class EntityFactory
    {
        public:
            EntityFactory(anax::World *world,
                          TextureManager *textureManager);
            virtual ~EntityFactory();

            anax::Entity createPlayer(const glm::ivec2 &pos, const InputMap &inputMap,
                                      Client::PlayerMovementSystem *playerMovementSystem,
                                      PiH::HealthAndNameDisplay *healthAndNameDisplay,
                                      std::shared_ptr<Player> player);

            anax::Entity createBomb(const glm::ivec2 &pos, anax::Entity thrower);

            anax::Entity createExplosion(const glm::ivec2 &pos, int powerLeft, int turnsLeft, Client::SpreadingComponent::SpreadingFrom from);

            anax::Entity createPowerup(const glm::ivec2 &pos, PowerupComponent *powerupComponent,
                                       const std::string &texture, const SDL_Rect &rect);
        private:
            TextureManager *m_textureManager;
            anax::World *m_world;
    };
}

#endif
