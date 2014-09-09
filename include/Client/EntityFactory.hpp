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
            EntityFactory(std::shared_ptr<anax::World> world,
                          std::shared_ptr<TextureManager> textureManager);
            virtual ~EntityFactory();

            anax::Entity createPlayer(const glm::ivec2 &pos, const InputMap &inputMap);

            anax::Entity createBomb(const glm::ivec2 &pos, anax::Entity thrower);
        private:
            std::shared_ptr<TextureManager> m_textureManager;
            std::shared_ptr<anax::World> m_world;
    };
}

#endif
