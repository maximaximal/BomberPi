#pragma once

#include <pihud/Widget.hpp>

#include <vector>
#include <memory>
#include <pihud/Particle.hpp>

namespace PiH
{
    class ParticleSource : public Widget
    {
        public:
            ParticleSource();
            virtual ~ParticleSource();

            virtual void onUpdate(float frametime);
            virtual void onEvent(const Event &e);
            virtual void onRender(SDL_Renderer *renderer, const FloatRect &offset);
        private:
            std::vector<std::unique_ptr<Particle> > m_particles;
    };
}
