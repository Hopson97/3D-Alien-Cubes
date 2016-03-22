#ifndef BALLTHING_H
#define BALLTHING_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "rand.h"

constexpr float WINDOW_HEIGHT = 700.0f;
constexpr float WINDOW_WIDTH  = 1280.0f;


class BallThing
{
    class Particle
    {
        public:
            Particle( sf::Vector2f pos)
            {
                mShape.setRadius((float)random::num(1, 5));
                mShape.setFillColor( {
                                    (unsigned char)random::num(0, 255),
                                    (unsigned char)random::num(0, 255),
                                    (unsigned char)random::num(0, 255)
                                    } );

                mShape.setPosition(pos);
            }

            bool
            update ( sf::RenderWindow& window )
            {
                if ( c.getElapsedTime().asSeconds() > lifeTime ) return true;

                mShape.move( mVel );

                window.draw ( mShape );
                return false;
            }

        private:
            sf::Clock c;
            sf::CircleShape mShape;

            float lifeTime  { (float)random::num(1, 4) };

            sf::Vector2f mVel { (float)random::num(-10, 10), (float)random::num(-10, 10) };
    };

    public:
        BallThing( );

        void
        update          ( sf::RenderWindow& window );

    private:
        void
        checkEdges      ();

        void
        updateParticles ( sf::RenderWindow& window );

        void
        addParticles    ();

        bool                    hitEdge     { false };
        sf::CircleShape         mShape      { 50.0f };
        sf::Vector2f            mVel        { 5, 5  };
        std::vector<Particle>   mParticles;
};

#endif // BALLTHING_H
