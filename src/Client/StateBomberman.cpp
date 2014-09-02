#include <Client/StateBomberman.hpp>
#include <easylogging++.h>
#include <Client/TextureManager.hpp>
#include <easylogging++.h>

#include <Client/SpriteRenderingSystem.hpp>
#include <Client/PlayerInputComponent.hpp>
#include <Client/PositionComponent.hpp>
#include <Client/SpriteComponent.hpp>
#include <Client/PlayerInputSystem.hpp>
#include <Client/PlayerMovementSystem.hpp>
#include <Client/PlayerComponent.hpp>
#include <Client/VelocityComponent.hpp>
#include <Client/BodyComponent.hpp>

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
        m_world = std::make_shared<anax::World>();

        m_spriteRenderingSystem = std::make_shared<SpriteRenderingSystem>();
		m_world->addSystem(*m_spriteRenderingSystem.get());

        m_playerInputSystem = std::make_shared<PlayerInputSystem>();
        m_playerInputSystem->setSDLEventHandler(getSDLEventHandler());
        m_world->addSystem(*m_playerInputSystem);

        m_playerMovementSystem = std::make_shared<PlayerMovementSystem>(m_map);
        m_world->addSystem(*m_playerMovementSystem);

        m_entityFactory = std::make_shared<EntityFactory>(m_world, getTextureManager());

        m_map->setTexture(getTextureManager()->get("tilemap_proto.png"));

        m_map->init(glm::ivec2(17, 15));

        m_map->createOuterWall();
        m_map->createInnerStamps();

       	InputMap inputMap;
        inputMap.set(SDL_SCANCODE_W, PlayerInputEnum::UP);
       	inputMap.set(SDL_SCANCODE_A, PlayerInputEnum::LEFT);
        inputMap.set(SDL_SCANCODE_S, PlayerInputEnum::DOWN);
        inputMap.set(SDL_SCANCODE_D, PlayerInputEnum::RIGHT);
        inputMap.set(SDL_SCANCODE_SPACE, PlayerInputEnum::ACTION);
		m_entityFactory->createPlayer(glm::ivec2(32, 32), inputMap);

        inputMap.clear();

        inputMap.set(SDL_SCANCODE_UP, PlayerInputEnum::UP);
       	inputMap.set(SDL_SCANCODE_LEFT, PlayerInputEnum::LEFT);
        inputMap.set(SDL_SCANCODE_DOWN, PlayerInputEnum::DOWN);
        inputMap.set(SDL_SCANCODE_RIGHT, PlayerInputEnum::RIGHT);
        inputMap.set(SDL_SCANCODE_MINUS, PlayerInputEnum::ACTION);
		m_entityFactory->createPlayer(glm::ivec2(288, 288), inputMap);

        inputMap.clear();

        inputMap.set(SDL_SCANCODE_U, PlayerInputEnum::UP);
       	inputMap.set(SDL_SCANCODE_H, PlayerInputEnum::LEFT);
        inputMap.set(SDL_SCANCODE_J, PlayerInputEnum::DOWN);
        inputMap.set(SDL_SCANCODE_K, PlayerInputEnum::RIGHT);
        inputMap.set(SDL_SCANCODE_Z, PlayerInputEnum::ACTION);
		m_entityFactory->createPlayer(glm::ivec2(32, 288), inputMap);

        m_world->refresh();
        LOG(INFO) << "StateBomberman initialized.";
    }

    void StateBomberman::update(float frameTime)
    {
        m_world->refresh();
        m_playerInputSystem->update();
        m_playerMovementSystem->update(frameTime);
    }

    void StateBomberman::render(std::shared_ptr<Window> window)
    {
		m_map->render(window);
        m_spriteRenderingSystem->render(window);
    }
}
