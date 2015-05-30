#include <SFML/Graphics.hpp>
#include "Game_Manager.h"
#include <iostream>

using namespace sf;







int main()
{
    try
    {
        RenderWindow app(VideoMode(1920, 1080), "SFML window" );
        //app.setFramerateLimit(60);
        Game_Manager game_manager1(&app);

        // Create the main window
        //app.setMouseCursorVisible(false);

        // Start the game loop
        while (app.isOpen() )
        {
            game_manager1.update();
            game_manager1.draw();
        }
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Terminate program with exception " << ex.what();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
