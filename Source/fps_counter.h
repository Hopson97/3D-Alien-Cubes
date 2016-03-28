#ifndef FPS_COUNTER_H_INCLUDED
#define FPS_COUNTER_H_INCLUDED

#include <SFML/Graphics.hpp>

class FPS_Counter
{
    public:
        void
        update ()
        {
            float fpsThisFrame = getFPS( fpsClock.restart() );
            frameTimes      += fpsThisFrame;
            frameTimes10    += fpsThisFrame;

            fpsCount ++;

            if ( fpsClock2.getElapsedTime().asSeconds() >= 1 ) {
                std::cout << frameTimes / fpsCount << std::endl;
                frameTimes  = 0;
                fpsCount    = 0;
                fpsClock2.restart();
                frameCount ++;
            }
            /*
            if ( frameCount >= 10 )
            {
                frameCount = 0;
                std::cout << "Average FPS 10 seconds count: " << frameTimes10 / 10 << std::endl;

                frameTimes10 = 0;
            }
            */
        }

    private:
        sf::Clock fpsClock;
        sf::Clock fpsClock2;
        int     fpsCount  = 0;
        float   frameTimes  = 0;

        int     frameCount      = 0;
        float   frameTimes10    = 0; //Shows average FPS every 10 secs

        float getFPS(const sf::Time& time)
        {
            return (1000000.0f / time.asMicroseconds());
        }
};

#endif // FPS_COUNTER_H_INCLUDED
