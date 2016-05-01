#include "game.h"

#include <SFML/Audio.hpp>

int
main()
{
    srand(time(NULL));

    Game game;
    game.run();

    return 0;
}
