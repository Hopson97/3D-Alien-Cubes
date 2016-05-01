#ifndef GAME_H
#define GAME_H

#include "cube.h"
#include "rand.h"
#include "window.h"
#include "player.h"
#include "fps_counter.h"
#include "model.h"

#include <memory>

struct Matrices
{
    glm::mat4 view;
    glm::mat4 proj;
};


class Game
{
    public:
        Game            ();

        void
        run             ();
    private:
        void
        input           ( const float dt );

        void
        update          (  const float dt, const float time  );

        void
        calcMatrices    ( );

        void
        glDraw          ( const float dt, const float time );

        void
        sfDraw          ( const float dt );

        void
        addCubes        ();

        void
        getTimes        ( float& dt, float& time, sf::Clock& c, sf::Clock& FPSclock  );

    private:
        constexpr static
        int                 m_numCubes { 100 };

        std::vector<Cube>   m_cubes;

        Window              m_window;
        Player              m_player  { m_numCubes / 2, 50, m_numCubes / 2 };

        Model cubeModel;

        std::unique_ptr<Matrices> mats;

};

#endif // GAME_H
