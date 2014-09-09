#include <Client/StateBomberman.hpp>
#include <easylogging++.h>
#include <Client/TextureManager.hpp>
#include <easylogging++.h>

#include <Client/SpriteRenderingSystem.hpp>
#include <Client/PlayerInputComponent.hpp>
#include <Client/PositionComponent.hpp>
#include <Client/SpriteComponent.hpp>
#include <Client/PlayerInputSystem.hpp>
#include <Client/TimerSystem.hpp>
#include <Client/PlayerMovementSystem.hpp>
#include <Client/BombPlaceSystem.hpp>
#include <Client/BombPlacePositionSystem.hpp>
#include <Client/AnimationSystem.hpp>
#include <Client/BombExplodeSystem.hpp>
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
        m_world.reset();
        m_spriteRenderingSystem.reset();
        m_playerInputSystem.reset();
        m_playerMovementSystem.reset();
        m_timerSystem.reset();
        m_bombPlaceSystem.reset();
        m_bombPlacePositionSystem.reset();
        m_animationSystem.reset();

        m_entityFactory.reset();
        m_map.reset();
		LOG(INFO) << "StateBomberman deleted.";
    }

    void StateBomberman::init()
    {
        LOG(INFO) << "Initializing StateBomberman.";
        m_map = std::make_shared<BombermanMap>();
        m_world = std::make_shared<anax::World>();

        m_spriteRenderingSystem = std::make_shared<SpriteRenderingSystem>();
		m_world->addSystem(*m_spriteRenderingSystem);

        m_timerSystem = std::make_shared<TimerSystem>();
        m_world->addSystem(*m_timerSystem);

        m_playerInputSystem = std::make_shared<PlayerInputSystem>();
        m_playerInputSystem->setSDLEventHandler(getSDLEventHandler());
        m_world->addSystem(*m_playerInputSystem);

        m_playerMovementSystem = std::make_shared<PlayerMovementSystem>(m_map);
        m_world->addSystem(*m_playerMovementSystem);

        m_animationSystem = std::make_shared<AnimationSystem>();
        m_world->addSystem(*m_animationSystem);

        m_entityFactory = std::make_shared<EntityFactory>(m_world, getTextureManager());

        m_bombPlaceSystem = std::make_shared<BombPlaceSystem>(m_entityFactory);
        m_world->addSystem(*m_bombPlaceSystem);

        m_bombPlacePositionSystem = std::make_shared<BombPlacePositionSystem>(m_map);
        m_world->addSystem(*m_bombPlacePositionSystem);

        m_bombExplodeSystem = std::make_shared<BombExplodeSystem>(m_entityFactory);
        m_world->addSystem(*m_bombExplodeSystem);

        m_map->setTexture(getTextureManager()->get("tilemap_proto.png"));

        m_map->init(glm::ivec2(17, 15));

        m_map->createOuterWall(0);
        m_map->createOuterWall(1);
        m_map->createInnerStamps();
        m_map->createFillerWalls();

        std::vector<glm::ivec2> playerPositions;
        glm::ivec2 playerPos(0, 0);

       	InputMap inputMap;
        inputMap.set(SDL_SCANCODE_W, PlayerInputEnum::UP);
       	inputMap.set(SDL_SCANCODE_A, PlayerInputEnum::LEFT);
        inputMap.set(SDL_SCANCODE_S, PlayerInputEnum::DOWN);
        inputMap.set(SDL_SCANCODE_D, PlayerInputEnum::RIGHT);
        inputMap.set(SDL_SCANCODE_SPACE, PlayerInputEnum::ACTION);
        playerPos.x = 32; playerPos.y = 32;
		m_entityFactory->createPlayer(playerPos, inputMap);
        playerPositions.push_back(playerPos / 32);

        inputMap.clear();

        inputMap.set(SDL_SCANCODE_UP, PlayerInputEnum::UP);
       	inputMap.set(SDL_SCANCODE_LEFT, PlayerInputEnum::LEFT);
        inputMap.set(SDL_SCANCODE_DOWN, PlayerInputEnum::DOWN);
        inputMap.set(SDL_SCANCODE_RIGHT, PlayerInputEnum::RIGHT);
        inputMap.set(SDL_SCANCODE_L, PlayerInputEnum::ACTION);
        playerPos.x = 15 * 32; playerPos.y = 13 * 32;
		m_entityFactory->createPlayer(playerPos, inputMap);
        playerPositions.push_back(playerPos / 32);

        m_map->createPlayerSpace(playerPositions);

        m_world->refresh();
        LOG(INFO) << "StateBomberman initialized.";
    }

    void StateBomberman::update(float frameTime)
    {
        m_world->refresh();
        m_timerSystem->update(frameTime);
        m_animationSystem->update(frameTime);

        m_playerInputSystem->update();
        m_playerMovementSystem->update(frameTime);
        m_bombExplodeSystem->update();

        m_bombPlacePositionSystem->update();
        m_bombPlaceSystem->update();
    }

    void StateBomberman::render(std::shared_ptr<Window> window)
    {
		m_map->render(window);
        m_spriteRenderingSystem->render(window);
    }
}
