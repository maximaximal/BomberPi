#ifndef CLIENT_POWERUPQUEUE_HPP_INCLUDED
#define CLIENT_POWERUPQUEUE_HPP_INCLUDED

#include <vector>
#include <memory>
#include <Client/Powerup.hpp>
#include <Client/UI/PowerupQueue.hpp>

namespace Client
{
    class PowerupQueue
    {
        public:
            PowerupQueue();
            virtual ~PowerupQueue();
            void reset();

            void pushPowerup(std::shared_ptr<Powerup> powerup);
            void setMaxQueueSize(std::size_t size);
            bool removeOneOfPredefined(Powerup::Predefined predefined);

            const Powerup& getCombinedPowerup();

            void setPowerupQueueUI(UI::PowerupQueue *powerupQueueUI);
        private:
            std::vector<std::shared_ptr<Powerup> > m_powerups;
            std::size_t m_queueSize = 3;
            Powerup m_combinedPowerup;
            UI::PowerupQueue *m_powerupQueueUI = nullptr;
    };
}

#endif
