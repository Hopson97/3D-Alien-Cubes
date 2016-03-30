#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "mousecontroller.h"

//The player is also sort of the "camera"
class Player : public Entity
{
    public:
        Player              ( const int x, const int y, const int z ) { setPosition( { x, y, z } ); }

        void
        update              ( const float time, const float dt  );


        void
        input               ( sf::RenderWindow& window, const float dt );

        inline const float
        getFOV              ()  { return FOV; }

    private:
        void
        mouseInput          ( sf::RenderWindow& window );

        void
        walkInput           ( const float dt );

        void
        jumpInput           ( const float dt);

        void
        jump                ( const float dt );

        void
        fovInput            ();

        const bool
        onGround            ();

        void
        checkIfOnGround     ( const float dt );



    private:
        MouseController mMouseController;

        const static
        int     groundHeight        { 3 },
                FOV_CHANGE          { 2 };

        float   mJumpSpeed          { 10.0f  },
                mFallSpeed          { 0.2f },
                mSpeedChange        { 1.0f  },
                mMaxSpeed           { 20.0f },
                FOV                 { 90.0f };

        bool    isJumping           { false };

};

#endif // PLAYER_H
