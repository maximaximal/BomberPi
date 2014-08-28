#include <Client/BombermanMap.hpp>
#include <easylogging++.h>

namespace Client
{
    BombermanMap::BombermanMap()
    {

    }
    BombermanMap::~BombermanMap()
    {

    }

    void BombermanMap::init(glm::ivec2 mapSize)
    {
        clear();

		m_mapSize = mapSize;

		m_tiles.resize(mapSize.x);
        for(auto &yTiles : m_tiles)
        {
            yTiles.resize(mapSize.y);
            for(auto &tile : yTiles)
            {
                std::unique_ptr<BombermanMapTile> tilePtr;
                tilePtr.reset(new BombermanMapTile());
                tilePtr->id = 4;
                tilePtr->physics = BombermanMapTile::PASSABLE;
                tile = std::move(tilePtr);
            }
        }

        createOuterWall();
    }

    void BombermanMap::clear()
    {
        m_tiles.clear();
    }

    void BombermanMap::setTexture(std::shared_ptr<Texture> texture)
    {
        m_texture = texture;
    }

    void BombermanMap::render(std::shared_ptr<Window> window)
    {
        SDL_Rect srcRect;
        SDL_Rect dsRect;
        for(unsigned int x = 0; x < m_mapSize.x; ++x)
        {
            for(unsigned int y = 0; y < m_mapSize.y; ++y)
            {
                srcRect.h = 32;
                srcRect.w = 32;
                srcRect.x = m_tiles[x][y]->id / (512 / 32);
				srcRect.y = m_tiles[x][y]->id % (512 / 32);

                dsRect.w = 32;
                dsRect.h = 32;
                dsRect.x = x * 32;
                dsRect.y = y * 32;
				SDL_RenderCopy(window->getSDLRenderer(), m_texture->getSDLTexture(), &srcRect, &dsRect);
            }
        }
    }

    void BombermanMap::createOuterWall()
    {
        for(unsigned int x = 0; x < m_mapSize.x; ++x)
        {
            m_tiles[x][0]->id = 0;
            m_tiles[x][m_mapSize.y - 1]->id = 0;
        }
        for(unsigned int y = 0; y < m_mapSize.y; ++y)
        {
            m_tiles[0][y]->id = 0;
            m_tiles[m_mapSize.x - 1][y]->id = 0;
        }
    }
}
