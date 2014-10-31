#include <Client/EntityFactory.hpp>

#include <Client/PowerupCollisionResolver.hpp>

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
#include <Client/EntityTypeComponent.hpp>
#include <easylogging++.h>

namespace Client
{

    EntityFactory::EntityFactory(anax::World *world,
                                 TextureManager *textureManager)
    {
        m_world = world;
        m_textureManager = textureManager;
    }
    EntityFactory::~EntityFactory()
    {

    }

    anax::Entity EntityFactory::createPlayer(const glm::ivec2 &pos,
                                             const InputMap &inputMap,
                                             PlayerMovementSystem *playerMovementSystem,
                                             PiH::HealthAndNameDisplay *healthAndNameDisplay,
                                             std::shared_ptr<Player> player,
                                             float cooldown)
    {
        anax::Entity entity = m_world->createEntity();
        entity.addComponent(new PositionComponent(pos.x, pos.y));
        SpriteComponent *spriteComponent = new SpriteComponent();
        spriteComponent->texture = m_textureManager->get("player_proto.png");
		spriteComponent->srcRect.w = 32;
		spriteComponent->srcRect.h = 32;
        entity.addComponent(spriteComponent);
        PlayerInputComponent *inputComponent = new PlayerInputComponent();
        inputComponent->inputMap = inputMap;
        entity.addComponent(inputComponent);
        entity.addComponent(new BombLayerComponent(cooldown));
        BodyComponent *body = new BodyComponent(10, 10, 10, 10);
        body->collisionSignal.connect(sigc::mem_fun(playerMovementSystem, &PlayerMovementSystem::onPlayerCollision));
        entity.addComponent(body);
        entity.addComponent(new PlayerComponent(150, pos, player));
        HealthComponent *healthComponent = new HealthComponent(3, healthAndNameDisplay);
        healthComponent->damageOccured.connect(sigc::mem_fun(player.get(), &Player::damageReceived));
        entity.addComponent(healthComponent);
        entity.addComponent(new EntityTypeComponent(Type::Player));
        entity.activate();

        return entity;
    }

    anax::Entity EntityFactory::createBomb(const glm::ivec2 &pos, anax::Entity thrower)
    {
        auto entity = m_world->createEntity();
        entity.addComponent(new PositionComponent(pos.x, pos.y));
        SpriteComponent *spriteComponent = new SpriteComponent();
        spriteComponent->texture = m_textureManager->get("bomb_proto.png");
        spriteComponent->srcRect.y = 160;
		spriteComponent->srcRect.w = 32;
		spriteComponent->srcRect.h = 32;
        entity.addComponent(spriteComponent);
        entity.addComponent(new BodyComponent(0, 0, 32, 32));
        TimerComponent *timer = new TimerComponent();
        timer->timeToPass = 1.3;
        entity.addComponent(timer);
        entity.addComponent(new BombComponent(thrower));
        std::shared_ptr<Animation> anim = std::make_shared<Animation>();
        anim->loadDefinition("bombAnimation.yml");
        entity.addComponent(new AnimationComponent(anim));
        entity.addComponent(new EntityTypeComponent(Type::Bomb));
        entity.activate();

        return entity;
    }

    anax::Entity EntityFactory::createExplosion(const glm::ivec2 &pos, int powerLeft, int turnsLeft,
                                                SpreadingComponent::SpreadingFrom from)
    {
        auto entity = m_world->createEntity();
        entity.addComponent(new PositionComponent(pos.x, pos.y));
        SpriteComponent *spriteComponent = new SpriteComponent();
        spriteComponent->texture = m_textureManager->get("bomb_proto.png");
        spriteComponent->srcRect.y = 0;
		spriteComponent->srcRect.w = 32;
		spriteComponent->srcRect.h = 32;
        entity.addComponent(spriteComponent);
        entity.addComponent(new BodyComponent(0, 0, 32, 32));
        entity.addComponent(new SpreadingComponent(powerLeft, turnsLeft, from));
        std::shared_ptr<Animation> anim = std::make_shared<Animation>();
        anim->loadDefinition("explosionAnimation.yml");
        anim->setRoot(0, 0);
        entity.addComponent(new AnimationComponent(anim, true));
        entity.addComponent(new DamageDealerComponent(1));
        entity.addComponent(new EntityTypeComponent(Type::Explosion));
        entity.activate();

        return entity;
    }

    anax::Entity EntityFactory::createPowerup(const glm::ivec2 &pos, PowerupComponent *powerupComponent, const std::string &texture, const SDL_Rect &rect)
    {
        auto entity = m_world->createEntity();
        entity.addComponent(new PositionComponent(pos.x, pos.y));
        SpriteComponent *spriteComponent = new SpriteComponent();
        spriteComponent->texture = m_textureManager->get(texture);
        spriteComponent->srcRect.x = rect.x;
        spriteComponent->srcRect.y = rect.y;
		spriteComponent->srcRect.w = rect.w;
		spriteComponent->srcRect.h = rect.h;
        entity.addComponent(spriteComponent);
        BodyComponent *body = new BodyComponent(0, 0, 32, 32);
        body->collisionSignal.connect(sigc::ptr_fun(&Resolver::OnPowerupCollison));
        entity.addComponent(body);

        //Generate animation.
        std::shared_ptr<Animation> anim = std::make_shared<Animation>();
        SDL_Rect animRect = PowerupComponent::computeRectFor(powerupComponent);
        anim->addStep(animRect);
        anim->setStepDuration(2);

        entity.addComponent(new AnimationComponent(anim, true));
        entity.addComponent(new EntityTypeComponent(Type::Powerup));
        entity.addComponent(powerupComponent);
        entity.activate();

        return entity;
    }
}
