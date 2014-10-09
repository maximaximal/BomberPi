#include <pihud/Label.hpp>
#include <pihud/pihud.hpp>

namespace PiH
{
    Label::Label(Widget *parent)
    	: Widget(parent)
    {

    }
    Label::~Label()
    {
		if(m_renderedText != nullptr)
            SDL_DestroyTexture(m_renderedText);
    }
    void Label::onEvent(const Event &e)
    {

    }
    void Label::onUpdate(float frametime)
    {

    }
    void Label::onRender(SDL_Renderer *renderer, const FloatRect &offset)
    {
		if(m_hasToRedraw)
            redraw();

        SDL_Rect dstRect = m_boundingBox.toSDLRect();

        if(m_renderedText != nullptr)
			SDL_RenderCopy(renderer, m_renderedText, nullptr, &dstRect);
    }
    void Label::setText(const std::string &text)
    {
		m_text = text;
        m_hasToRedraw = true;
    }
    void Label::setFont(std::shared_ptr<Font> font)
    {
        m_font = font;
        m_hasToRedraw = true;
    }
    void Label::setColor(SDL_Color color)
    {
        m_color = color;
        m_hasToRedraw = true;
    }
    void Label::redraw()
    {
        SDL_Surface *rendered = TTF_RenderUTF8_Blended(m_font->getFont(), m_text.c_str(), m_color);
        m_renderedText = SDL_CreateTextureFromSurface(GlobalConfig->getSDLRenderer(), rendered);
        SDL_FreeSurface(rendered);
    }
}
