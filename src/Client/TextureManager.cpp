#include <Client/TextureManager.hpp>

namespace Client
{
    TextureManager::TextureManager(std::shared_ptr<Window> window)
    {
		m_window = window;
    }
    TextureManager::~TextureManager()
    {
        clear();
    }

    void TextureManager::clear()
    {
		m_textures.clear();
    }

    bool TextureManager::has(const std::string &path)
    {
        if(m_textures.count(path) > 0)
        {
            return true;
        }
        return false;
    }

    std::shared_ptr<Texture> TextureManager::get(const std::string &path)
    {
        std::shared_ptr<Texture> texture;
       	if(!has(path))
        {
            texture = std::make_shared<Texture>(m_window);
            texture->load(path);
            m_textures[path] = texture;
        }
        else
        {
			texture = m_textures[path].lock();
        }
        return texture;
    }

    std::shared_ptr<Texture> TextureManager::operator[](std::string index)
    {
		return get(index);
    }
}
