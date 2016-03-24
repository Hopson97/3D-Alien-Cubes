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
        walkInput   ( float& dx, float& dz );

        void
        jumpInput   ();

        void
        fovInput    ();

    private:
        MouseController mMouseController;

        float mMaxSpeed         { 0.1 };

        float mJumpSpeed        { 0.3 };
        float mFallSpeed        { 0.015 };

        int     FOV_CHANGE      { 2};
        float   FOV             { 90.0f};

};

#endif // PLAYER_H
