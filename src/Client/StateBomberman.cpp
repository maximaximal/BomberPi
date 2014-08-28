#include <Client/StateBomberman.hpp>
#include <easylogging++.h>
#include <Client/TextureManager.hpp>
#include <easylogging++.h>

namespace Client
{

    StateBomberman::StateBomberman()
    {

    }
    StateBomberman::~StateBomberman()
    {
		LOG(INFO) << "StateBomberman deleted.";
    }

    void StateBomberman::init()
    {
        LOG(INFO) << "Initializing StateBomberman.";
        m_map = std::make_shared<BombermanMap>();

        m_map->setTexture(getTextureManager()->get("tileset.png"));

        m_map->init(glm::ivec2(18, 16));

        LOG(INFO) << "StateBomberman initialized.";
    }

    void StateBomberman::render(std::shared_ptr<Window> window)
    {
		m_map->render(window);
    }
}
