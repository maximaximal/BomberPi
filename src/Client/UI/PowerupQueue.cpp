#include <Client/UI/PowerupQueue.hpp>

namespace Client
{
    namespace UI
    {
        PowerupQueue::PowerupQueue(TextureManager *textureManager, std::size_t queueSize, Widget *parent)
            : Widget(parent)
        {
            m_textureManager = textureManager;
            m_queueDisplayWidget.reset(new PiH::QueueDisplayWidget(queueSize, this));

            std::unique_ptr<PiH::Image> backgroundImage(new PiH::Image(m_queueDisplayWidget.get()));
            backgroundImage->setTexture(textureManager->get("hud.png"));
            backgroundImage->setTextureRect(PiH::IntRect(0, 32, 32, 32));
            m_queueDisplayWidget->setBackgroundImage(std::move(backgroundImage));
        }
        PowerupQueue::~PowerupQueue()
        {

        }
        void PowerupQueue::clearPowerups()
        {
            m_queueDisplayWidget->clear();
        }
        void PowerupQueue::onUpdate(float frametime)
        {
            m_queueDisplayWidget->onUpdate(frametime);
        }
        void PowerupQueue::onEvent(const PiH::Event &e)
        {
            m_queueDisplayWidget->onEvent(e);
        }
        void PowerupQueue::onRender(SDL_Renderer *renderer, const PiH::FloatRect &offset)
        {
            m_queueDisplayWidget->onRender(renderer, offset);
        }
        void PowerupQueue::pushPowerup(std::shared_ptr<Powerup> powerup)
        {
            std::unique_ptr<PiH::Image> image(new PiH::Image(m_queueDisplayWidget.get()));
            image->setTexture(m_textureManager->get("powerups.png"));
            image->setTextureRect(powerup->getRect());
            m_queueDisplayWidget->pushImage(std::move(image));
        }
        int PowerupQueue::getMaxWidth(int tileWidth)
        {
            return m_queueDisplayWidget->getQueueSize() * tileWidth;
        }
        void PowerupQueue::updateBoundingBox()
        {
            m_queueDisplayWidget->setBoundingBox(getBoundingBox());
        }
    }
}
