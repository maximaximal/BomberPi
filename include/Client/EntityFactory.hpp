#ifndef CLIENT_ENTITYFACTORY_HPP_INCLUDED
#define CLIENT_ENTITYFACTORY_HPP_INCLUDED

#include <memory>
#include <anax/World.hpp>
#include <Client/Window.hpp>
#include <glm/vec2.hpp>
#include <InputMap.hpp>
#include <Client/TextureManager.hpp>

namespace Client
{
    class EntityFactory
    {
        public:
            EntityFactory(anax::World *world,
                          TextureManager *textureManager);
            virtual ~EntityFactory();

            anax::Entity createPlayer(const glm::ivec2 &pos, const InputMap &inputMap);

            anax::Entity createBomb(const glm::ivec2 &pos, anax::Entity thrower);

            anax::Entity createExplosion(const glm::ivec2 &pos, anax::Entity thrower);
        private:
            TextureManager *m_textureManager;
            anax::World *m_world;
    };
}

#endif
