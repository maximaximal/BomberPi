#pragma once

#include <string>
#include <pihud/Widget.hpp>
#include <pihud/ParticleSource.hpp>
#include <pihud/Label.hpp>
#include <pihud/Image.hpp>

namespace PiH
{
    class WeHaveAWinnerWidget : public Widget
    {
        public:
            WeHaveAWinnerWidget();
            virtual ~WeHaveAWinnerWidget();

            virtual void onUpdate(float frametime);
            virtual void onEvent(const Event &e);
            virtual void onRender(SDL_Renderer *renderer, const FloatRect &offset);

            void setWinnerName(std::string name);
        private:
            std::unique_ptr<ParticleSource> m_particleSource;
            std::unique_ptr<Image> m_victoryImage;
            std::unique_ptr<Label> m_playerNameLabel;
            std::unique_ptr<Label> m_playerNameDisplayLabel;
    };
}
