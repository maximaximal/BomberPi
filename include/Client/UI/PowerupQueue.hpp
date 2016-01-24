#ifndef CLIENT_UI_POWERUPQUEUE_HPP_INCLUDED
#define CLIENT_UI_POWERUPQUEUE_HPP_INCLUDED

#include <pihud/Widget.hpp>
#include <pihud/QueueDisplayWidget.hpp>
#include <Client/Powerup.hpp>
#include <Client/TextureManager.hpp>
#include <Client/Config.hpp>

namespace Client
{
    namespace UI
    {
        class PowerupQueue : public PiH::Widget
        {
            public:
                PowerupQueue(TextureManager *textureManager, std::size_t queueSize = 3, PiH::Widget *parent = nullptr, Config *config = nullptr);
                virtual ~PowerupQueue();
                void clearPowerups();

                virtual void onUpdate(float frametime);
                virtual void onEvent(const PiH::Event &e);
                virtual void onRender(SDL_Renderer *renderer, const PiH::FloatRect &offset);

                void pushPowerup(std::shared_ptr<Powerup> powerup);

                int getMaxWidth(int tileWidth);
            protected:
                virtual void updateBoundingBox();

                virtual void focusGained(int playerID) {}
                virtual void focusLost(int playerID) {}
            private:
                std::unique_ptr<PiH::QueueDisplayWidget> m_queueDisplayWidget;
                TextureManager *m_textureManager;
                Config *m_config;
        };
    }
}

#endif
