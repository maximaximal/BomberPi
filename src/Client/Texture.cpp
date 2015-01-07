#include <Client/Texture.hpp>
#include <SDL2/SDL_image.h>
#include <easylogging++.h>

namespace Client
{
    Texture::Texture(Window *window)
    {
        m_window = window;
        m_texture = nullptr;
    }
    Texture::~Texture()
    {
        destroy();
    }
    int Texture::load(const std::string &path)
    {
		destroy();
		m_path = path;

		m_texture = IMG_LoadTexture(m_window->getSDLRenderer(), path.c_str());
        if(m_texture == nullptr)
        {
			LOG(FATAL) << "Could not load texture \"" << path << "\"! Error: " << IMG_GetError();
            return 1;
        }
        return 0;
    }
    void Texture::destroy()
    {
        if(m_texture != nullptr)
        {
            SDL_DestroyTexture(m_texture);
            m_texture = nullptr;
        }
    }
    const std::string &Texture::getPath()
    {
        return m_path;
    }
    SDL_Texture *Texture::getSDLTexture()
    {
        return m_texture;
    }
}
