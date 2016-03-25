#ifndef FPS_COUNTER_H_INCLUDED
#define FPS_COUNTER_H_INCLUDED

#include <SFML/Graphics.hpp>

class FPS_Counter
{
    public:
        void
        update ()
        {
            frameTimes += getFPS( fpsClock.restart() );
            fpsCount ++;

            if ( fpsClock2.getElapsedTime().asSeconds() >= 1 ) {
                std::cout << frameTimes / fpsCount << std::endl;
                frameTimes  = 0;
                fpsCount    = 0;
                fpsClock2.restart();
            }
        }

    private:
        sf::Clock fpsClock;
        sf::Clock fpsClock2;
        int     fpsCount    = 0;
        float   frameTimes  = 0;

        float getFPS(const sf::Time& time)
        {
            return (1000000.0f / time.asMicroseconds());
        }
};

#endif // FPS_COUNTER_H_INCLUDED
