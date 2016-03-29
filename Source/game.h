#ifndef GAME_H
#define GAME_H

#include "cube.h"
#include "rand.h"
#include "window.h"
#include "player.h"
#include "fps_counter.h"
#include "model.h"


class Game
{
    public:
        Game        ();

        void
        run         ();

    private:
        void
        addCubes    ();

    private:
        constexpr static
        int                 m_numCubes { 100 };

        std::vector<Cube>   m_cubes;

        Window              m_window;
        Player              m_player  { -m_numCubes / 2, -50, -m_numCubes / 2 };

        Model cubeModel;

};

#endif // GAME_H
