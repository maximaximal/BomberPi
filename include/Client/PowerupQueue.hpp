#ifndef CLIENT_POWERUPQUEUE_HPP_INCLUDED
#define CLIENT_POWERUPQUEUE_HPP_INCLUDED

#include <vector>
#include <memory>
#include <Client/Powerup.hpp>

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

            const Powerup& getCombinedPowerup();
        private:
            std::vector<std::shared_ptr<Powerup> > m_powerups;
            std::size_t m_queueSize = 3;
            Powerup m_combinedPowerup;
    };
}

#endif
