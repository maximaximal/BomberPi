#include <Client/EmbeddedChunk.hpp>
#include <Client/EmbeddedTilemap.hpp>
#include <easylogging++.h>

namespace Client
{
    EmbeddedChunk::EmbeddedChunk()
    {
        reset();
    }
    EmbeddedChunk::~EmbeddedChunk()
    {
        if(m_texture != nullptr)
            SDL_DestroyTexture(m_texture);
    }
    void EmbeddedChunk::reset()
    {
        for(std::size_t x = 0; x < width; ++x)
        {
            for(std::size_t y = 0; y < width; ++y)
            {
                m_tiles[x][y].parts[0] = 0;
                m_tiles[x][y].parts[1] = 255;
            }
        }
        m_issueRedraw = true;
    }
    uint8_t EmbeddedChunk::getTile(short x, short y)
    {
        if(checkCoords(x, y))
        {
            return m_tiles[x][y].parts[1];
        }
        return 0;
    }
    void EmbeddedChunk::setTile(short x, short y, uint8_t tile)
    {
        if(checkCoords(x, y))
        {
            m_tiles[x][y].parts[1] = tile;
            m_issueRedraw = true;
        }
    }
    void EmbeddedChunk::setTexture(std::shared_ptr<Texture> texture)
    {
        m_tileTexture = texture;
        m_issueRedraw = true;
    }
    void EmbeddedChunk::setTileUserdata(short x, short y, uint8_t data)
    {
        if(checkCoords(x, y))
        {
            m_tiles[x][y].parts[0] = data;
        }
    }
    uint8_t EmbeddedChunk::getTileUserdata(short x, short y)
    {
        if(checkCoords(x, y))
        {
            return m_tiles[x][y].parts[0];
        }
    }
    void EmbeddedChunk::render(Window *window, int offsetX, int offsetY)
    {
        if(!m_tileTexture)
        {
            return;
        }
        SDL_Rect src;
        SDL_Rect dst;
        if(m_texture == nullptr)
        {
            m_texture = SDL_CreateTexture(window->getSDLRenderer(),
                                          SDL_PIXELFORMAT_RGBA8888,
                                          SDL_TEXTUREACCESS_TARGET,
                                          width * tileWidth, width * tileWidth);

            setTransparent(m_transparent);
        }
        if(m_issueRedraw)
        {
            m_issueRedraw = false;
            SDL_SetRenderTarget(window->getSDLRenderer(), m_texture);
            SDL_RenderClear(window->getSDLRenderer());
            src.w = tileWidth;
            src.h = tileWidth;
            dst.w = tileWidth;
            dst.h = tileWidth;
            for(std::size_t x = 0; x < width; ++x)
            {
                for(std::size_t y = 0; y < width; ++y)
                {
                    //Only render tiles different than 255, because that tile is bound to be empty.
                    if(getTile(x, y) != ((uint8_t) 255))
                    {
                        setTextureCoords(getTile(x, y), src);
                        dst.x = x * tileWidth;
                        dst.y = y * tileWidth;
                        SDL_RenderCopy(window->getSDLRenderer(), m_tileTexture->getSDLTexture(), &src, &dst);
                    }
                }
            }
            SDL_SetRenderTarget(window->getSDLRenderer(), nullptr);
        }
        src.w = tileWidth * width;
        src.h = tileWidth * width;
        src.x = 0;
        src.y = 0;
        dst.w = tileWidth * width;
        dst.h = tileWidth * width;
        dst.x = offsetX;
        dst.y = offsetY;
        SDL_RenderCopy(window->getSDLRenderer(), m_texture, &src, &dst);
    }
    void EmbeddedChunk::setTransparent(bool state)
    {
        m_transparent = state;
        if(m_texture != nullptr)
        {
            if(state)
                SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND);
            else
                SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_NONE);
        }
    }
    bool EmbeddedChunk::checkCoords(short x, short y) const
    {
        if(x >= 0
                && x < width
                && y >= 0
                && y < width)
            return true;
        return false;
    }
    void EmbeddedChunk::setTextureCoords(uint8_t tile, SDL_Rect &src)
    {
        src.x = (tile % width) * tileWidth;
        src.y = (tile / width) * tileWidth;
    }
}
