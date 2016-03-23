#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "mousecontroller.h"


class Player : public Entity
{
    public:
        void
        update      ( glm::mat4& view, glm::mat4& proj, sf::RenderWindow& window, const float time  ) override;

    private:
        void
        input       ( sf::RenderWindow& window );

        void
        mouseInput  ( sf::RenderWindow& window );

        void
        walkInput   ();

        void
        jumpInput   ();

        void
        fovInput    ();

    private:
        MouseController mMouseController;

        float mSpeed = 0.0;
        float mMaxSpeed     = 0.2;

        float mJumpSpeed    = 0.3;
        float mFallSpeed    = 0.015;

        int     FOV_CHANGE  = 2;
        float   FOV         = 90.0f;

};

#endif // PLAYER_H
