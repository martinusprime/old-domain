#include <SFML/Graphics.hpp>
#include "Game_Manager.h"
using namespace sf;







int main()
{
    RenderWindow app(VideoMode(1600, 920), "SFML window" );


    Game_Manager game_manager1;
    // Create the main window

    //app.setMouseCursorVisible(false);
    game_manager1.init(&app);
	// Start the game loop
    while (app.isOpen() )
    {
        game_manager1.update();
        game_manager1.draw();
    }


    return EXIT_SUCCESS;
}
