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
#include <Client/EntityDropGenerator.hpp>
#include <Client/EmbeddedTilemap.hpp>

namespace Client
{
    class BombermanMap
    {
        public:
            BombermanMap();
            virtual ~BombermanMap();

            void init();
            void clear();
            void clearTilemap();
            void setEntityFactory(EntityFactory *entityFactory);

            void setTexture(std::shared_ptr<Texture> texture);

            void render(Window *window, const glm::ivec2 &offset);

            void createOuterWall();
            void createFillerWalls();
            void createInnerStamps();

            void createPlayerSpace(const std::vector<glm::ivec2> &playerPositions);
            void clearSpaceForPlayer(const glm::ivec2 &pos, int layer);

            void clearTile(const glm::ivec3 &pos, bool generateDrops = true);
            void setTile(const glm::ivec3 &pos, uint8_t tile);
            void setTileBombable(const glm::ivec3 &pos, bool state);
            bool isTileBombable(const glm::ivec3 &pos);
            uint8_t getCollisionOf(const glm::ivec2 &pos);

            void setMapSize(const glm::ivec2 &size);
            const glm::ivec2& getMapSize();

            uint8_t getTileAtPixel(const glm::ivec3 &pos);
            uint8_t getTileAt(const glm::ivec3 &pos);
        private:
            std::unique_ptr<EmbeddedTilemap> m_embeddedTilemap;

            glm::ivec2 m_mapSize;
            EntityDropGenerator *m_entityDropGenerator = nullptr;
            EntityFactory *m_entityFactory;
    };
}

#endif
