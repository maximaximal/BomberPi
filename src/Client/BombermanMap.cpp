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

        m_entityDropGenerator = new EntityDropGenerator(m_entityFactory);
        m_entityDropGenerator->setChance(1000);

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
                    tile->dropGenerator = nullptr;
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
        if(m_entityDropGenerator != nullptr)
            delete m_entityDropGenerator;
        m_entityDropGenerator = nullptr;
    }

    void BombermanMap::setEntityFactory(EntityFactory *entityFactory)
    {
        m_entityFactory = entityFactory;
    }

    void BombermanMap::setTexture(std::shared_ptr<Texture> texture)
    {
        m_texture = texture;
    }

    void BombermanMap::render(Window *window, const glm::ivec2 &offset)
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
					dsRect.x = x * 32 + offset.x;
					dsRect.y = y * 32 + offset.y;
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
            m_tiles[layer][x][m_mapSize.y - 1]->bombable = false;
        }
        for(unsigned int y = 0; y < m_mapSize.y; ++y)
        {
            m_tiles[layer][0][y]->id = 0;
            m_tiles[layer][0][y]->physics = BombermanMapTile::SOLID;
            m_tiles[layer][m_mapSize.x - 1][y]->id = 0;
            m_tiles[layer][m_mapSize.x - 1][y]->physics = BombermanMapTile::SOLID;
            m_tiles[layer][m_mapSize.x - 1][y]->bombable = false;
        }
    }

    void BombermanMap::createFillerWalls()
    {
        const short layer = 1;
        for(unsigned int x = 1; x < m_mapSize.x - 1; ++x)
        {
			for(unsigned int y = 1; y < m_mapSize.y - 1; ++y)
			{
                if(m_tiles[layer][x][y]->physics == BombermanMapTile::PASSABLE
                        || m_tiles[layer][x][y]->bombable == true)
                {
                    m_tiles[layer][x][y]->id = 16 + (rand() % 3);
                    m_tiles[layer][x][y]->physics = BombermanMapTile::SOLID;
                    m_tiles[layer][x][y]->bombable = true;
                    m_tiles[layer][x][y]->dropGenerator = m_entityDropGenerator;
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
                    m_tiles[layer][x][y]->bombable = false;
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
                clearTile(glm::ivec3(pos.x, pos.y, layer), false);
			}
        }
    }

    void BombermanMap::clearTile(glm::ivec3 pos, bool generateDrops)
    {
        if(pos.z < m_tiles.size())
        {
			if((pos.x >= 0 && pos.x < m_mapSize.x)
					&& pos.y >= 0 && pos.y < m_mapSize.y)
			{
				if((pos.x != 0 && pos.x != m_mapSize.x - 1)
						&& (pos.y != 0 && pos.y != m_mapSize.y - 1))
				{
					auto *tile = m_tiles[pos.z][pos.x][pos.y];

                    if(tile->dropGenerator != nullptr && generateDrops)
                    {
                        tile->dropGenerator->run(pos);
                    }

					tile->physics = BombermanMapTile::PASSABLE;
					tile->id = 255;
					tile->bombable = false;
                    tile->dropGenerator = nullptr;
                }
			}
        }
    }
    const glm::ivec2 &BombermanMap::getMapSize()
    {
        return m_mapSize;
    }
    const BombermanMapTile& BombermanMap::getTileAtPixel(const glm::ivec3 &pos)
    {
       	glm::ivec3 tilePos = pos / 32;
        tilePos.z = pos.z;
        return getTileAt(tilePos);
    }
    const BombermanMapTile &BombermanMap::getTileAt(const glm::ivec3 &pos)
    {
        if(m_tiles.count(pos.z) != 0)
        {
            if(m_tiles[pos.z].size() > pos.x)
			{
                if((m_tiles[pos.z][pos.x]).size() > pos.y)
				{
					return *(m_tiles[pos.z][pos.x][pos.y]);
				}
			}
        }
        throw std::out_of_range("Tile not in range!");
    }
}
