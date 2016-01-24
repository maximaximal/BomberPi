#include <Client/EntityFactory.hpp>

#include <Client/PowerupCollisionResolver.hpp>
#include <memory>
#include <Client/PositionComponent.hpp>
#include <Client/SpriteComponent.hpp>
#include <Client/PlayerInputComponent.hpp>
#include <Client/BodyComponent.hpp>
#include <Client/PlayerComponent.hpp>
#include <Client/TimerComponent.hpp>
#include <Client/BombLayerComponent.hpp>
#include <Client/BombComponent.hpp>
#include <Client/SpreadingComponent.hpp>
#include <Client/AnimationComponent.hpp>
#include <Client/PlayerMovementSystem.hpp>
#include <Client/DamageDealerComponent.hpp>
#include <Client/HealthComponent.hpp>
#include <Client/PowerupComponent.hpp>
#include <Client/SpeedComponent.hpp>
#include <Client/EntityTypeComponent.hpp>
#include <easylogging++.h>

namespace Client
{

    EntityFactory::EntityFactory(anax::World *world,
                                 TextureManager *textureManager,
                                 Config *config)
    {
        m_world = world;
        m_textureManager = textureManager;
        m_config = config;
    }
    EntityFactory::~EntityFactory()
    {

    }

    anax::Entity EntityFactory::createPlayer(const glm::ivec2 &pos,
                                             PlayerMovementSystem *playerMovementSystem,
                                             PiH::HealthAndNameDisplay *healthAndNameDisplay,
                                             std::shared_ptr<Player> player,
                                             float cooldown)
    {
        anax::Entity entity = m_world->createEntity();
        m_world->refresh();
        entity.addComponent<PositionComponent>(pos.x, pos.y);
        SpriteComponent *spriteComponent = &entity.addComponent<SpriteComponent>();
        spriteComponent->texture = m_textureManager->get(m_config->getStringValue(Config::DATA_DIRECTORY) + "/player_proto.png");
		spriteComponent->srcRect.w = 32;
        spriteComponent->srcRect.h = 32;
        spriteComponent->srcRect.x = 0;
        switch(player->getPlayerID())
        {
            case 0:
                spriteComponent->srcRect.y = 0;
                break;
            case 1:
                spriteComponent->srcRect.y = 32;
                break;
        }

        entity.addComponent<PlayerInputComponent>();
        entity.addComponent<BombLayerComponent>(cooldown);
        BodyComponent *body = &entity.addComponent<BodyComponent>(4, 7, 28, 22);
        body->collisionSignal.connect(sigc::mem_fun(playerMovementSystem, &PlayerMovementSystem::onPlayerCollision));
        entity.addComponent<PlayerComponent>(pos, player);
        HealthComponent *healthComponent = &entity.addComponent<HealthComponent>(3, healthAndNameDisplay);
        healthComponent->damageOccured.connect(sigc::mem_fun(player.get(), &Player::damageReceived));
        entity.addComponent<SpeedComponent>();
        entity.addComponent<EntityTypeComponent>(Type::Player);
        entity.activate();

        return entity;
    }

    anax::Entity EntityFactory::createBomb(const glm::ivec2 &pos, anax::Entity thrower, int tiles, int turns)
    {
        auto entity = m_world->createEntity();
        m_world->refresh();
        entity.addComponent<PositionComponent>(pos.x, pos.y);
        SpriteComponent *spriteComponent = &entity.addComponent<SpriteComponent>();
        spriteComponent->texture = m_textureManager->get(m_config->getStringValue(Config::DATA_DIRECTORY) + "/bomb_proto.png");
        spriteComponent->srcRect.y = 160;
		spriteComponent->srcRect.w = 32;
		spriteComponent->srcRect.h = 32;
        entity.addComponent<BodyComponent>(0, 0, 32, 32);
        TimerComponent *timer = &entity.addComponent<TimerComponent>();
        timer->timeToPass = 1.3;
        entity.addComponent<BombComponent>(thrower, tiles, turns);
        std::shared_ptr<Animation> anim = std::make_shared<Animation>();
        anim->loadDefinition(m_config->getStringValue(Config::DATA_DIRECTORY) + "/bombAnimation.yml");
        entity.addComponent<AnimationComponent>(anim);
        entity.addComponent<EntityTypeComponent>(Type::Bomb);
        entity.activate();

        return entity;
    }

    anax::Entity EntityFactory::createExplosion(const glm::ivec2 &pos, int powerLeft, int turnsLeft,
                                                SpreadingComponent::SpreadingFrom from)
    {
        auto entity = m_world->createEntity();
        m_world->refresh();
        entity.addComponent<PositionComponent>(pos.x, pos.y);
        SpriteComponent *spriteComponent = &entity.addComponent<SpriteComponent>();
        spriteComponent->texture = m_textureManager->get(m_config->getStringValue(Config::DATA_DIRECTORY) + "/bomb_proto.png");
        spriteComponent->srcRect.y = 0;
		spriteComponent->srcRect.w = 32;
		spriteComponent->srcRect.h = 32;
        entity.addComponent<BodyComponent>(0, 0, 32, 32);
        entity.addComponent<SpreadingComponent>(powerLeft, turnsLeft, from);
        std::shared_ptr<Animation> anim = std::make_shared<Animation>();
        anim->loadDefinition(m_config->getStringValue(Config::DATA_DIRECTORY) + "/explosionAnimation.yml");
        anim->setRoot(0, 0);
        entity.addComponent<AnimationComponent>(anim, true);
        entity.addComponent<DamageDealerComponent>(1);
        entity.addComponent<EntityTypeComponent>(Type::Explosion);
        entity.activate();

        return entity;
    }

    anax::Entity EntityFactory::createPowerup(const glm::ivec2 &pos, Powerup::Predefined powerupDef, const std::string &texture)
    {
        auto entity = m_world->createEntity();
        m_world->refresh();
        entity.addComponent<PositionComponent>(pos.x, pos.y);
        SpriteComponent *spriteComponent = &entity.addComponent<SpriteComponent>();
        PowerupComponent *powerupComponent = &entity.addComponent<PowerupComponent>(powerupDef);
        spriteComponent->texture = m_textureManager->get(texture);
        spriteComponent->srcRect = powerupComponent->powerup->getRect();
        BodyComponent *body = &entity.addComponent<BodyComponent>(0, 0, 32, 32);
        body->collisionSignal.connect(sigc::ptr_fun(&Resolver::OnPowerupCollison));

        //Generate animation.
        std::shared_ptr<Animation> anim = std::make_shared<Animation>();
        SDL_Rect animRect = powerupComponent->powerup->getRect();
        anim->addStep(animRect);
        anim->setStepDuration(2);

        entity.addComponent<AnimationComponent>(anim, true);
        entity.addComponent<EntityTypeComponent>(Type::Powerup);
        entity.activate();

        return entity;
    }
}
