#include <iostream>
#include <SFML/Graphics.hpp>

#include "src/engine/state_manager.hpp"
#include "src/state/main_menu_state.hpp"
#include "src/state/test_state.hpp"
#include "src/engine/time.hpp"

using namespace std;

int main()
{
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(800, 600), "Engine TEST !");
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    StateManager::get()->addState(new MainMenuState(&window));

    while (window.isOpen() && !StateManager::get()->isEmpty())
    {
        StateManager::get()->setCurrent();

        StateManager::get()->update();

        window.clear();
            StateManager::get()->draw( window );
        window.display();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            StateManager::get()->handleEvent( event );
        }

        Time::get()->update();
    }

    return 0;
}
