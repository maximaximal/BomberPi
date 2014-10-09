#include <pihud/FontManager.hpp>

namespace PiH
{
    FontManager::FontManager()
    {

    }
    FontManager::~FontManager()
    {

    }
    std::shared_ptr<Font> FontManager::load(const std::string &fontPath)
    {
        std::shared_ptr<Font> font = std::make_shared<Font>();
        font->load(fontPath);

        m_fonts[fontPath] = font;

        return font;
    }
    std::shared_ptr<Font> FontManager::get(const std::string &fontPath)
    {
        std::shared_ptr<Font> font;
		if(m_fonts.count(fontPath) > 0)
        {
           	font = m_fonts[fontPath].lock();
        }
        else
        {
            font = load(fontPath);
        }
        return font;
    }
}
