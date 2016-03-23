#ifndef WINDOW_H
#define WINDOW_H

#include <SFML/Graphics.hpp>

constexpr float WINDOW_HEIGHT = 600.0f;
constexpr float WINDOW_WIDTH  = 1180.0f;

class Window
{
    public:
        Window  ();

        void
        update  ();

        void
        clear   ();

        sf::RenderWindow&
        get     () { return window; }

    private:
        void
        events  ();

    private:
        sf::RenderWindow window;

        sf::Clock clock;
};

#endif // WINDOW_H
