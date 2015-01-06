#include <Client/TextureManager.hpp>

namespace Client
{
    TextureManager::TextureManager(Window *window)
    {
		m_window = window;
    }
    TextureManager::~TextureManager()
    {
        destroy();
    }
    void TextureManager::destroy()
    {
        for(auto texture : m_textures)
        {
            if(!texture.second.expired())
            {
                auto sharedTexture = texture.second.lock();
                sharedTexture->destroy();
                sharedTexture.reset();
            }
        }
        m_textures.clear();
    }
    bool TextureManager::has(const std::string &path)
    {
        if(m_textures.count(path) > 0)
        {
            if(!m_textures[path].expired())
            {
                return true;
            }
            else
            {
                m_textures.erase(path);
            }
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
