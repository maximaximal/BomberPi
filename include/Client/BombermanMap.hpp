#ifndef CLIENT_BOMBERMANMAP_HPP_INCLUDED
#define CLIENT_BOMBERMANMAP_HPP_INCLUDED

#include <vector>
#include <memory>
#include <map>
#include <Client/BombermanMapTile.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
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

            void render(Window *window);

            void createOuterWall(short layer);
            void createFillerWalls();
            void createInnerStamps();

            void createPlayerSpace(std::vector<glm::ivec2> playerPositions);
            void clearSpaceForPlayer(glm::ivec2 pos, int layer);

            void clearTile(glm::ivec3 pos);

            const BombermanMapTile& getTileAtPixel(glm::ivec3 pos);
        private:
            std::map<short, std::vector<std::vector<BombermanMapTile*>>> m_tiles;
            glm::ivec2 m_mapSize;

            std::shared_ptr<Texture> m_texture;
    };
}

#endif
