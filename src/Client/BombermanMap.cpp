#include <Client/BombermanMap.hpp>
#include <easylogging++.h>

namespace Client
{
    BombermanMap::BombermanMap()
    {

    }
    BombermanMap::~BombermanMap()
    {
		clear();
    }

    void BombermanMap::init(glm::ivec2 mapSize)
    {
        clear();

		m_mapSize = mapSize;

		m_tiles[0].resize(mapSize.x);
		m_tiles[1].resize(mapSize.x);

        for(auto &layer : m_tiles)
        {
			for(auto &yTiles : layer.second)
			{
				yTiles.resize(mapSize.y);
				for(auto &tile : yTiles)
				{
					tile = new BombermanMapTile();
					tile->id = 255;
					tile->physics = BombermanMapTile::PASSABLE;
				}
			}
        }
    }

    void BombermanMap::clear()
    {
        for(auto &layer : m_tiles)
        {
            for(auto &yTiles : layer.second)
            {
                for(auto &tile : yTiles)
                {
                    delete tile;
                }
            }
        }
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
        for(auto &layer : m_tiles)
        {
			for(unsigned int x = 0; x < m_mapSize.x; ++x)
			{
				for(unsigned int y = 0; y < m_mapSize.y; ++y)
				{
					srcRect.h = 32;
					srcRect.w = 32;
					srcRect.x = layer.second[x][y]->id % (512 / 32) * 32;
					srcRect.y = layer.second[x][y]->id / (512 / 32) * 32;

					dsRect.w = 32;
					dsRect.h = 32;
					dsRect.x = x * 32;
					dsRect.y = y * 32;
					SDL_RenderCopy(window->getSDLRenderer(), m_texture->getSDLTexture(), &srcRect, &dsRect);
				}
			}
        }
    }

    void BombermanMap::createOuterWall(short layer)
    {
        for(unsigned int x = 0; x < m_mapSize.x; ++x)
        {
            m_tiles[layer][x][0]->id = 0;
            m_tiles[layer][x][0]->physics = BombermanMapTile::SOLID;
            m_tiles[layer][x][m_mapSize.y - 1]->id = 0;
            m_tiles[layer][x][m_mapSize.y - 1]->physics = BombermanMapTile::SOLID;
        }
        for(unsigned int y = 0; y < m_mapSize.y; ++y)
        {
            m_tiles[layer][0][y]->id = 0;
            m_tiles[layer][0][y]->physics = BombermanMapTile::SOLID;
            m_tiles[layer][m_mapSize.x - 1][y]->id = 0;
            m_tiles[layer][m_mapSize.x - 1][y]->physics = BombermanMapTile::SOLID;
        }
    }

    void BombermanMap::createFillerWalls()
    {
        const short layer = 1;
        for(unsigned int x = 1; x < m_mapSize.x - 1; ++x)
        {
			for(unsigned int y = 1; y < m_mapSize.y - 1; ++y)
			{
                if(m_tiles[layer][x][y]->physics != BombermanMapTile::SOLID)
                {
                    m_tiles[layer][x][y]->id = 16 + (rand() % 3);
                    m_tiles[layer][x][y]->physics = BombermanMapTile::SOLID;
                    m_tiles[layer][x][y]->bombable = true;
                }
			}
        }
    }

    void BombermanMap::createInnerStamps()
    {
        const short layer = 1;
        for(unsigned int x = 1; x < m_mapSize.x - 1; ++x)
        {
			for(unsigned int y = 1; y < m_mapSize.y - 1; ++y)
			{
				m_tiles[0][x][y]->id = 2;
				m_tiles[0][x][y]->physics = BombermanMapTile::PASSABLE;
				if(x % 2 == 0 && y % 2 == 0)
                {
                    m_tiles[layer][x][y]->id = 1;
                    m_tiles[layer][x][y]->physics = BombermanMapTile::SOLID;
                }
			}
        }
    }

    void BombermanMap::createPlayerSpace(std::vector<glm::ivec2> playerPositions)
    {
        const int layer = 1;
        for(auto &pos : playerPositions)
        {
			clearSpaceForPlayer(glm::ivec2(pos.x, pos.y), layer);
			clearSpaceForPlayer(glm::ivec2(pos.x - 1, pos.y), layer);
			clearSpaceForPlayer(glm::ivec2(pos.x, pos.y - 1), layer);
			clearSpaceForPlayer(glm::ivec2(pos.x + 1, pos.y), layer);
			clearSpaceForPlayer(glm::ivec2(pos.x, pos.y + 1), layer);
        }
    }

    void BombermanMap::clearSpaceForPlayer(glm::ivec2 pos, int layer)
    {
        if((pos.x >= 0 && pos.x < m_mapSize.x)
                && pos.y >= 0 && pos.y < m_mapSize.y)
        {
			if((pos.x != 0 && pos.x != m_mapSize.x - 1)
					&& (pos.y != 0 && pos.y != m_mapSize.y - 1))
			{
				auto *tile = m_tiles[layer][pos.x][pos.y];
				tile->physics = BombermanMapTile::PASSABLE;
				tile->id = 255;
				tile->bombable = false;
			}
        }
    }

    const BombermanMapTile& BombermanMap::getTileAtPixel(glm::ivec3 pos)
    {
       	glm::ivec3 tilePos = pos / 32;
        if(m_tiles.count(pos.z) != 0)
        {
			if(m_tiles[pos.z].size() >= tilePos.x)
			{
				if((m_tiles[pos.z][tilePos.x]).size() >= tilePos.y)
				{
					return *(m_tiles[pos.z][tilePos.x][tilePos.y]);
				}
			}
        }
    }
}
