#include "ballthing.h"

BallThing :: BallThing(  )
{
    mShape.setPosition( { (float)random::num(0, WINDOW_WIDTH), (float)random::num(0, WINDOW_HEIGHT)} );

    mShape.setFillColor( {
                    (unsigned char)random::num(0, 255),
                    (unsigned char)random::num(0, 255),
                    (unsigned char)random::num(0, 255)
                    } );

    sf::FloatRect f = mShape.getLocalBounds();
    mShape.setOrigin( f.width /2, f.height /2 );
}

void
BallThing :: update ( sf::RenderWindow& window )
{
    mShape.move ( mVel );

    checkEdges();

    updateParticles(window);

    for ( int i = 0 ; i < 1 ; i++ ) {
        mParticles.emplace_back( mShape.getPosition() );
    }



    window.draw(mShape);
}


void
BallThing :: checkEdges      ()
{
    if ( mShape.getPosition().x + mShape.getRadius() > WINDOW_WIDTH  ) {
        mVel.x *= -1;
        if (!hitEdge ) {
            hitEdge = true;
            addParticles();
        }
    }
    else if ( mShape.getPosition().y + mShape.getRadius() > WINDOW_HEIGHT ) {
        mVel.y *= -1;
        if (!hitEdge ) {
            hitEdge = true;
            addParticles();
        }
    }
    else if ( mShape.getPosition().x < 0  ) {
        mVel.x *= -1;
        if (!hitEdge ) {
            hitEdge = true;
            addParticles();
        }
    }
    else if ( mShape.getPosition().y < 0 ) {
        mVel.y *= -1;
        if (!hitEdge ) {
            hitEdge = true;
            addParticles();
        }
    }
    else {
        hitEdge = false;
    }
}

void
BallThing :: updateParticles ( sf::RenderWindow& window )
{
    for ( uint32_t i = 0 ; i < mParticles.size() ; i++ ) {
        if (mParticles.at(i).update( window )) {
            mParticles.erase(mParticles.begin() + i);
        }
    }
}

void
BallThing :: addParticles    ()
{
    int numParticles = random::num(10,100);

    for ( int i = 0 ; i < numParticles ; i++ ) {
        mParticles.emplace_back( mShape.getPosition() );
    }
}
