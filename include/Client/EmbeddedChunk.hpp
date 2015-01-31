#ifndef CLIENT_EMBEDDEDCHUNK_HPP_INCLUDED
#define CLIENT_EMBEDDEDCHUNK_HPP_INCLUDED

#include <Client/Window.hpp>
#include <Client/Texture.hpp>
#include <glm/vec2.hpp>
#include <memory>

namespace Client
{
    class EmbeddedChunk
    {
        public:
            EmbeddedChunk();
            ~EmbeddedChunk();

            void reset();

            uint8_t getTile(short x, short y);
            void setTile(short x, short y, uint8_t tile);
            void setTexture(std::shared_ptr<Texture> texture);

            void setTileUserdata(short x, short y, uint8_t data);
            uint8_t getTileUserdata(short x, short y);

            void render(Window *window, int offsetX, int offsetY);

            void setTransparent(bool state = true);

            static const short width = 16;
            static const short tileWidth = 32;
        private:
            bool m_transparent = false;
            typedef union {
                uint16_t combined;
                uint8_t parts[];
            } tileType;
            inline bool checkCoords(short x, short y) const;
            inline void setTextureCoords(uint8_t tile, SDL_Rect &src);
            std::shared_ptr<Texture> m_tileTexture;
            bool m_issueRedraw = true;
            SDL_Texture *m_texture = nullptr;
            tileType m_tiles[width][width];
    };
}

#endif
