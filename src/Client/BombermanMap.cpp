#include <Client/BombermanMap.hpp>
#include <Client/EmbeddedChunk.hpp>
#include <easylogging++.h>

namespace Client
{
    BombermanMap::BombermanMap()
    {
        m_embeddedTilemap.reset(new EmbeddedTilemap());
        m_mapSize.x = 17;
        m_mapSize.y = 15;
    }
    BombermanMap::~BombermanMap()
    {

    }
    void BombermanMap::init()
    {
        clear();
        m_entityDropGenerator = new EntityDropGenerator(m_entityFactory);
        m_entityDropGenerator->setChance(1000);
    }
    void BombermanMap::clear()
    {
        if(m_entityDropGenerator != nullptr)
            delete m_entityDropGenerator;
        m_entityDropGenerator = nullptr;
        m_embeddedTilemap->clear();
    }
    void BombermanMap::clearTilemap()
    {
        m_embeddedTilemap->clear();
    }
    void BombermanMap::setEntityFactory(EntityFactory *entityFactory)
    {
        m_entityFactory = entityFactory;
    }
    void BombermanMap::setTexture(std::shared_ptr<Texture> texture)
    {
        m_embeddedTilemap->setTextureForLayer(texture, 0);
        m_embeddedTilemap->setTextureForLayer(texture, 1);
    }
    void BombermanMap::render(Window *window, const glm::ivec2 &offset)
    {
        m_embeddedTilemap->render(window, offset);
    }
    void BombermanMap::createOuterWall()
    {
        for(unsigned int x = 0; x < m_mapSize.x; ++x)
        {
            m_embeddedTilemap->setTile(x, 0, 0, 0);
            m_embeddedTilemap->setTileUserdata(x, 0, 0, 0);
            m_embeddedTilemap->setCollisionOf(x, 0, EmbeddedTilemap::CollideFully);
            m_embeddedTilemap->setTile(x, m_mapSize.y - 1, 0, 0);
            m_embeddedTilemap->setTileUserdata(x, m_mapSize.y - 1, 0, 0);
            m_embeddedTilemap->setCollisionOf(x, m_mapSize.y - 1, EmbeddedTilemap::CollideFully);
        }
        for(unsigned int y = 0; y < m_mapSize.y; ++y)
        {
            m_embeddedTilemap->setTile(0, y, 0, 0);
            m_embeddedTilemap->setTileUserdata(0, y, 0, 0);
            m_embeddedTilemap->setCollisionOf(0, y, EmbeddedTilemap::CollideFully);
            m_embeddedTilemap->setTile(m_mapSize.x - 1, y, 0, 0);
            m_embeddedTilemap->setTileUserdata(m_mapSize.x - 1, y, 0, 0);
            m_embeddedTilemap->setCollisionOf(m_mapSize.x - 1, y, EmbeddedTilemap::CollideFully);
        }
    }
    void BombermanMap::createFillerWalls()
    {
        const short layer = 1;
        for(unsigned int x = 1; x < m_mapSize.x - 1; ++x)
        {
			for(unsigned int y = 1; y < m_mapSize.y - 1; ++y)
			{
                if(m_embeddedTilemap->getCollisionOf(x, y) == EmbeddedTilemap::NoCollision
                        || m_embeddedTilemap->getTileUserdata(x, y, layer) == 1)
                {
                    m_embeddedTilemap->setTile(x, y, layer, 16 + (rand() % 3));
                    m_embeddedTilemap->setCollisionOf(x, y, EmbeddedTilemap::CollideFully);
                    m_embeddedTilemap->setTileUserdata(x, y, layer, 1);
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
                m_embeddedTilemap->setTile(x, y, 0, 2);
                m_embeddedTilemap->setCollisionOf(x, y, EmbeddedTilemap::NoCollision);
                m_embeddedTilemap->setTileUserdata(x, y, 0, 0);
                if(x % 2 == 0 && y % 2 == 0)
                {
                    m_embeddedTilemap->setTile(x, y, layer, 1);
                    m_embeddedTilemap->setCollisionOf(x, y, EmbeddedTilemap::CollideFully);
                    m_embeddedTilemap->setTileUserdata(x, y, layer, 0);
                }
			}
        }
    }
    void BombermanMap::createPlayerSpace(const std::vector<glm::ivec2> &playerPositions)
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
    void BombermanMap::clearSpaceForPlayer(const glm::ivec2 &pos, int layer)
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
    void BombermanMap::clearTile(const glm::ivec3 &pos, bool generateDrops)
    {
        if((pos.x >= 0 && pos.x < m_mapSize.x)
                && pos.y >= 0 && pos.y < m_mapSize.y)
        {
            if((pos.x != 0 && pos.x != m_mapSize.x - 1)
                    && (pos.y != 0 && pos.y != m_mapSize.y - 1))
            {
                if(generateDrops)
                    m_entityDropGenerator->run(pos);
                m_embeddedTilemap->setTile(pos.x, pos.y, pos.z, 255);
                m_embeddedTilemap->setTileUserdata(pos.x, pos.y, pos.z, 0);
                m_embeddedTilemap->setCollisionOf(pos.x, pos.y, EmbeddedTilemap::NoCollision);
            }
        }
    }
    void BombermanMap::setTile(const glm::ivec3 &pos, uint8_t tile)
    {
        m_embeddedTilemap->setTile(pos.x, pos.y, pos.z, tile);
    }
    void BombermanMap::setTileBombable(const glm::ivec3 &pos, bool state)
    {
        if(state)
            m_embeddedTilemap->setTileUserdata(pos.x, pos.y, pos.z, 1);
        else
            m_embeddedTilemap->setTileUserdata(pos.x, pos.y, pos.z, 0);
    }
    bool BombermanMap::isTileBombable(const glm::ivec3 &pos)
    {
        if(m_embeddedTilemap->getTileUserdata(pos.x, pos.y, pos.z) == 1)
            return true;
        return false;
    }
    uint8_t BombermanMap::getCollisionOf(const glm::ivec2 &pos)
    {
        return m_embeddedTilemap->getCollisionOf(pos.x, pos.y);
    }
    void BombermanMap::setMapSize(const glm::ivec2 &size)
    {
        m_mapSize = size;
    }
    const glm::ivec2 &BombermanMap::getMapSize()
    {
        return m_mapSize;
    }
    uint8_t BombermanMap::getTileAtPixel(const glm::ivec3 &pos)
    {
        glm::ivec3 tilePos = pos / (int) EmbeddedChunk::tileWidth;
        tilePos.z = pos.z;
        return getTileAt(tilePos);
    }
    uint8_t BombermanMap::getTileAt(const glm::ivec3 &pos)
    {
        return m_embeddedTilemap->getTile(pos.x, pos.y, pos.z);
    }
}
