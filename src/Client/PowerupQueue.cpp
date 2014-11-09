#include <Client/PowerupQueue.hpp>

#include <easylogging++.h>

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
        if(m_powerupQueueUI != nullptr)
        {
            m_powerupQueueUI->clearPowerups();
        }
    }
    void PowerupQueue::pushPowerup(std::shared_ptr<Powerup> powerup)
    {
        if(m_powerups.size() + 1 > m_queueSize)
        {
            m_powerups.erase(m_powerups.begin());
        }
        m_powerups.push_back(powerup);
        if(m_powerupQueueUI != nullptr)
        {
            m_powerupQueueUI->pushPowerup(powerup);
        }
    }
    void PowerupQueue::setMaxQueueSize(std::size_t size)
    {
        m_queueSize = size;
    }
    bool PowerupQueue::removeOneOfPredefined(Powerup::Predefined predefined)
    {
        for(auto i = m_powerups.begin(); i != m_powerups.end(); ++i)
        {
            if((*i)->getDefinition() == predefined)
            {
                m_powerups.erase(i);

                if(m_powerupQueueUI != nullptr)
                {
                    m_powerupQueueUI->clearPowerups();
                    for(auto &powerup : m_powerups)
                    {
                        m_powerupQueueUI->pushPowerup(powerup);
                    }
                }
                return true;
            }
        }
        return false;
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
    void PowerupQueue::setPowerupQueueUI(UI::PowerupQueue *powerupQueueUI)
    {
        m_powerupQueueUI = powerupQueueUI;
    }
}
