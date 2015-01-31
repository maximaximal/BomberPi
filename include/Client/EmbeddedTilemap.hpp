#ifndef CLIENT_EMBEDDEDTILEMAP_HPP_INCLUDED
#define CLIENT_EMBEDDEDTILEMAP_HPP_INCLUDED

#include <map>
#include <memory>
#include <glm/vec2.hpp>
#include <Client/Window.hpp>
#include <Client/Texture.hpp>

namespace Client
{
    class EmbeddedChunk;

    class EmbeddedTilemap
    {
        public:
            enum CollisionTypes {
                NoCollision,
                CollideFully
            };

            EmbeddedTilemap();
            ~EmbeddedTilemap();

            void clear();
            void setTile(int x, int y, int z, uint8_t tile);
            uint8_t getTile(int x, int y, int z);

            void setTileUserdata(int x, int y, int z, uint8_t tile);
            uint8_t getTileUserdata(int x, int y, int z);

            void render(Window *window, const glm::ivec2 &offset);

            CollisionTypes getCollisionOf(int x, int y);
            void setCollisionOf(int x, int y, CollisionTypes collisionType);

            void setTextureForLayer(std::shared_ptr<Texture> texture, int z);

            /**
             * @brief layerCount The number of layers this map has.
             *
             * The highest layer is used for collison detection, so the visible layers are only
             * the layerCount - 1.
             */
            static const short layerCount = 3;
        private:
            inline bool chunkExists(int chunkX, int chunkY, int z);
            inline void createChunk(int chunkX, int chunkY, int z);
            std::array<std::map<int, std::map<int, std::unique_ptr<EmbeddedChunk> > >, layerCount> m_layers;
            std::array<std::shared_ptr<Texture>, layerCount - 1> m_textures;
    };
}

#endif
