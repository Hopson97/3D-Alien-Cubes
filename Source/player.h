#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "mousecontroller.h"


class Player : public Entity
{
    public:
        void
        update      ( glm::mat4& view, glm::mat4& proj, sf::RenderWindow& window, const float time, const float dt  );

    private:
        void
        input       ( sf::RenderWindow& window, const float dt );

        void
        mouseInput  ( sf::RenderWindow& window );

        void
        walkInput   ( float& dx, float& dz, const float dt );

        void
        jumpInput   ( const float dt);

        void
        fovInput    ();

    private:
        MouseController mMouseController;

        float mMaxSpeed         { 10 };

        float mJumpSpeed        { 15 };
        float mFallSpeed        { 0.2 };

        int     FOV_CHANGE      { 2};
        float   FOV             { 90.0f};

};

#endif // PLAYER_H
