#include <pihud/HealthAndNameDisplay.hpp>

namespace PiH
{
    HealthAndNameDisplay::HealthAndNameDisplay(Widget *parent)
    	: Widget(parent)
    {
        m_label = new Label(this);
        m_iconHealthIndicator = new IconHealthIndicator(this);
    }
    HealthAndNameDisplay::~HealthAndNameDisplay()
    {
		delete m_label;
        delete m_iconHealthIndicator;
    }
    void HealthAndNameDisplay::setTexture(std::shared_ptr<Texture> texture)
    {
		m_iconHealthIndicator->setTexture(texture);
    }
    void HealthAndNameDisplay::setFont(std::shared_ptr<Font> font)
    {
		m_label->setFont(font);
    }
    void HealthAndNameDisplay::setName(std::string text)
    {
        m_label->setText(text);
    }
    void HealthAndNameDisplay::setDistance(int distance)
    {
        m_distance = distance;
        updateBoundingBox();
    }
    IconHealthIndicator *HealthAndNameDisplay::getHealthIndicator()
    {
		return m_iconHealthIndicator;
    }
    Label *HealthAndNameDisplay::getLabel()
    {
        return m_label;
    }
    void HealthAndNameDisplay::onRender(SDL_Renderer *renderer, const FloatRect &offset)
    {
        m_label->onRender(renderer, offset);
        m_iconHealthIndicator->onRender(renderer, offset);
    }
    void HealthAndNameDisplay::updateRectFromBeneath()
    {
        FloatRect boundingBox = getBoundingBox();

        boundingBox.w = std::max(m_label->getBoundingBox().w,
                                 m_iconHealthIndicator->getBoundingBox().w);
        boundingBox.h = m_label->getBoundingBox().h + m_distance
                + m_iconHealthIndicator->getBoundingBox().h;


        if(boundingBox != getBoundingBox())
        {
            setBoundingBox(boundingBox);
        }
    }
    void HealthAndNameDisplay::updateBoundingBox()
    {
		m_label->setPosition(m_boundingBox.x / 2 - m_label->getBoundingBox().w / 2,
                             m_boundingBox.y);
        m_iconHealthIndicator->setPosition(m_boundingBox.x,
                                           m_boundingBox.y + m_label->getBoundingBox().h + m_distance);
    }
}
