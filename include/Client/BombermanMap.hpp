#ifndef CLIENT_BOMBERMANMAP_HPP_INCLUDED
#define CLIENT_BOMBERMANMAP_HPP_INCLUDED

#include <vector>
#include <memory>
#include <Client/BombermanMapTile.hpp>
#include <glm/vec2.hpp>
#include <Client/Window.hpp>
#include <Client/Texture.hpp>

namespace Client
{
    class BombermanMap
    {
        public:
            BombermanMap();
            virtual ~BombermanMap();

            void init(glm::ivec2 mapSize);
            void clear();

            void setTexture(std::shared_ptr<Texture> texture);

            void render(std::shared_ptr<Window> window);

            void createOuterWall();
            void createInnerStamps();
        private:
            std::vector<std::vector<std::unique_ptr<BombermanMapTile>>> m_tiles;
            glm::ivec2 m_mapSize;

            std::shared_ptr<Texture> m_texture;
    };
}

#endif
