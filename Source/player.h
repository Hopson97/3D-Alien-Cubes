#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "mousecontroller.h"


class Player : public Entity
{
    public:
        Player( const int x, const int z ) { setPosition( { x, height, z } ); }

        void
        update          ( glm::mat4& view, glm::mat4& proj, sf::RenderWindow& window, const float time, const float dt  );

    private:
        void
        input           ( sf::RenderWindow& window, const float dt );

        void
        mouseInput      ( sf::RenderWindow& window );

        void
        walkInput       ( const float dt );

        void
        jumpInput       ( const float dt);

        void
        fovInput        ();

        void
        checkVelocity   ();

    private:
        MouseController mMouseController;

        float mSpeedChange      { 1  };
        float mMaxSpeed         { 20 };

        float mJumpSpeed        { 25  };
        float mFallSpeed        { 0.2 };

        int     FOV_CHANGE      { 2 };

        const
        float   BASE_FOV        { 90.0f };
        float   FOV             { BASE_FOV };

        const int height        { -3 };

};

#endif // PLAYER_H
