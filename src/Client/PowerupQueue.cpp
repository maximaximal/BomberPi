#include <Client/PowerupQueue.hpp>

namespace Client
{
    PowerupQueue::PowerupQueue()
    {

    }
    PowerupQueue::~PowerupQueue()
    {

    }
    void PowerupQueue::reset()
    {
        m_powerups.clear();
    }
    void PowerupQueue::pushPowerup(std::shared_ptr<Powerup> powerup)
    {
        m_powerups.push_back(powerup);
        if(m_powerups.size() > m_queueSize)
        {
            m_powerups.erase(m_powerups.begin());
        }
    }
    void PowerupQueue::setMaxQueueSize(std::size_t size)
    {
        m_queueSize = size;
    }
    const Powerup& PowerupQueue::getCombinedPowerup()
    {
        m_combinedPowerup.reset();
        for(auto &powerup : m_powerups)
        {
            m_combinedPowerup += *powerup;
        }
        return m_combinedPowerup;
    }
}
