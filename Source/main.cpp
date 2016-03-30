#include "game.h"

#include <SFML/Audio.hpp>

int
main()
{
    srand(time(NULL));

    sf::Music xFiles;
    xFiles.openFromFile ( "Music/x files.ogg" );
    xFiles.play();


    Game game;
    game.run();

    return 0;
}
