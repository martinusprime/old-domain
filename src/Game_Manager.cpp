#include "Game_Manager.h"

Game_Manager::Game_Manager()
{
    is_menu = true;
    x_offset = 0;
    y_offset = 0;
    zoom = 1;
    map_size_x = 0;
    map_size_y = 0;
    mouse_wheel_x = 0;
    zoom_rate = 10;
    citizen_selected = false;
    citizen_number = 1;
    city_number = 0;
    open_window = true;
    rock = 0;
    wood = 0;
    iron = 0;
    zoom_change = 0;
    selected_citizen = 0;

}
Game_Manager::~Game_Manager()
{
    //dtor
}

void Game_Manager::init(RenderWindow *app_get)
{
    app = app_get;
    view1.reset(FloatRect(0, 0, 1000, 600));
    view1.setViewport(FloatRect(0, 0, 1.0f, 1.0f));
    app->setView(view1);

    window_vec = app->getSize();
    cout<<"x_window"<<window_vec.x<<"y_window "<<window_vec.y<<endl;

    view2.reset(FloatRect(0, 0, 1000, 600));
    view2.setViewport(FloatRect(0, 0, 1.0f, 1.0f));


    Vector2f vecsize;
    vecsize = view1.getSize();
    h = vecsize.y;
    w = vecsize.x;

    if(is_menu)
    {
        menu1.init(app);
    }
    for(int i = 0; i < 6; i++)
    {
        stringstream ss;
        ss << i;
        string str = ss.str();
        string path = "ressources/tile" + str + ".png";

        tile_sprite[i].init(app, path, &view1);

        windows[i].init(app, "Map", 0.5f, 0.3f, 0, 0, &view2);
        windows[i].add_glissor(100, 100);
        windows[i].add_button(300, 100);
    }

    for(int i = 0; i < 2; i++)
    {
        selection_text[i].init(app, "rien", 12, 1);
        selection_text[i].change_font("ressources/font2.ttf");

    }
    selection_sprite.init(app, "ressources/selection.png", &view1);
    int x_tiles = 3;
    int y_tiles = 3;

    for(int i = 0; i <x_tiles; i++)
    {
        for(int j = 0; j<y_tiles; j++)
        {
            create_map(i *50,j *  50);
        }
    }

    citizen[0].init(app, &view1);
    grid[0][0].has_citizen = true;
    grid[0][0].citizen_id = 0;

    building[0].init(app, &view1, 0);

    citizen_action[0].init(app, "Fonder une ville", 0, 0, 0, 0, &view2);
    citizen_action[1].init(app, "Rentrer dans la ville", 0, 0, 0, 0, &view2);
    citizen_action[2].init(app, "Observer la ressource", 0, 0, 0, 0, &view2);
    ressource_sprite[0].init(app, "ressources/wood_ressource.png", &view1);
    tile_info.init(app, "lieu vierge", 10, 1);
//test of the sprite creator
    sprite_created_1_test.init(app, &view1, 0);

    interface1.init(app, &view1, w, h);
}

void Game_Manager::update()
{
    zoom = 1;

    bool isEvent = app->pollEvent(event);
    time1 =  clock1.getElapsedTime();
    key_time = clock2.getElapsedTime();
    zoom_time = clock3.getElapsedTime();

    if(key_time.asSeconds() >  0.03  && !screen_moved)
    {
        clock2.restart();
        if(manage_event(false) && true)
        {
            screen_moved = true;

        }
    }
    if(zoom_time.asSeconds() >  0.05  && zoom_change != 0)
    {
        clock3.restart();
        cout<<"eoom"<<zoom<<endl;
        if(zoom_change == 1)
        {

            zoom =0.90;
            zoom_rate --;

        }
        if(zoom_change == 2)
        {
            zoom =1.1;
            zoom_rate ++;

        }

    }
    zoom_change = 0;

    if(time1.asSeconds() >  0.03f)
    {
        if(is_menu)
        {
            menu1.update();
            if(manage_event(true) == 1)
            {
                is_menu = false;
            }
        }

        if(screen_moved)
        {
            if(keys[5] == true)
            {
                y_offset-= 50;

            }
            if(keys[6] == true)
            {
                x_offset+= 50;

            }
            if(keys[7] == true)
            {
                y_offset+= 50;

            }
            if(keys[8] == true)
            {
                x_offset-= 50;
            }

            screen_moved = false;
        }


        view1.setCenter(x_offset , y_offset);
        view1.zoom(zoom);
        app->setView(view1);




        // Close window : exit
        if (isEvent && event.type == Event::Closed || manage_event(false) == 10)
        {
            cout << "close app\n";
            app->close();
        }
        for(int i = 0; i<6; i++)
        {

            if(windows[i].is_activated())
            {
                windows[i].update();
            }
        }
        citizen_update();

    }


}
void Game_Manager::citizen_update()
{

    citizen[0].update();
    grid[citizen[0].get_previous_x()][citizen[0].get_previous_y()].has_citizen = false;
    if(citizen[0].is_selected() )
    {
        citizen_action[0].update(0, h - 50);

    }
    grid[citizen[0].get_x()][citizen[0].get_y()].has_citizen = true;

    if(citizen_action[0].is_activated() && city_number == 0)
    {
        city[0].init(app, &view1, citizen[0].get_x(), citizen[0].get_y());
        city_number++;
        grid[citizen[0].get_x()][citizen[0].get_x()].is_city = true;
    }
    if(citizen_action[2].is_activated() )  //l'action sur la ressources
    {
        city[0].init(app, &view1, citizen[0].get_x(), citizen[0].get_y());
        // windows[1].init(app, "Action", 550, 400, w/2, h/2, &view1);

        grid[citizen[0].get_x()][citizen[0].get_x()].is_city = true;
    }
    if(grid[citizen[0].get_x()][citizen[0].get_y()].is_city == true)
    {
        citizen[0].on_city();
    }

}
void Game_Manager::draw()
{

    app->clear();
    if(is_menu)
    {
        menu1.draw();
    }
    else
    {
        draw_grid();
        citizen[0].draw();
        //drwing of the test created sprite
        sprite_created_1_test.draw();

        for(int i = 0; i < city_number; i++)
        {
            city[i].draw();
        }

    }
    // Update the window
    draw_gui();
    app->display();
}

void Game_Manager::draw_gui()
{
    //highlight the tile
    if(!open_window)
    {
        selection();
    }
    app->setView(view2);
    open_window = false;
    if(citizen_selected)
    {
        citizen_action[0].draw();
        if(citizen[0].is_on_city())
        {
            citizen_action[1].draw();
        }
        else citizen_action[2].draw();
    }
    for(int i = 0; i<6; i++)
    {

        if(windows[i].is_activated())
        {
            open_window = true;
            windows[i].draw();
        }
    }



    draw_selection();
    interface1.draw();

    app->setView(view1);

}
void Game_Manager::create_map(int x_beg,int y_beg)
{
    srand(time(NULL));
    if(x_beg >= map_size_x)
    {
        map_size_x +=x_beg + 50;
    }
    if(y_beg >= map_size_y)
    {
        map_size_y +=y_beg + 50;
    }
    //sur 200
    water_rate = 55;
    sand_rate = 90;
    deep_sea_rate = 4;
    deep_sea_expansion_rate = 60;
    for(int i = x_beg; i <map_size_x; i++)
    {
        for(int j = y_beg; j<map_size_y; j++)
        {

            grid[i][j].type = 2;
            grid[i][j].x_pos = i;
            grid[i][j].y_pos = j;
            grid[i][j].height = 1;
            grid[i][j].zone = 1;
            grid[i][j].has_citizen = false;
            grid[i][j].passing_trought = false;
            grid[i][j].is_city = false;
            grid[i][j].ressource_type = WOOD;

        }
    }

    for(int i = x_beg; i <deep_sea_rate; i++)
    {
        int randomx = rand()%map_size_x;
        int randomy = rand()%map_size_y;
        grid[randomx][randomy].type = 4;
        grid[randomx][randomy].height = -2;
        grid[randomx][randomy].zone = 0;

        grid[randomx][randomy + 1].type = 4;
        grid[randomx][randomy +1].height = -2;
        grid[randomx][randomy +1].zone = 0;

        grid[randomx + 1][randomy + 1].type = 4;
        grid[randomx + 1][randomy +1].height = -2;
        grid[randomx + 1][randomy +1].zone = 0;

    }

    for(int k = 0; k <5; k++)
    {
        for(int i = x_beg; i <map_size_x; i++)
        {

            for(int j = y_beg; j<map_size_y; j++)
            {
                int random = rand()% 100;
                if(random < deep_sea_expansion_rate && neighbours(i, j, 0, 4, true)>=2)
                {
                    grid[i][j].type = 4;
                    grid[i][j].height = -2;
                    grid[i][j].zone = 0;

                }
            }
        }
    }


    bool is_deep_water_near, is_grass;
    //is there is deep water lot of chances of being mater if near
    for(int i = x_beg; i <map_size_x; i++)
    {

        for(int j = y_beg; j<map_size_y; j++)
        {
            is_deep_water_near = false;
            is_grass = false;
            if(i > 0 && j>0 && grid[i][j].type != 4)
            {
                if(neighbours(i, j, 0, 4, true)>=1)
                {

                    grid[i][j].type = 2;
                    grid[i][j].height = -1;
                    grid[i][j].zone = 0;

                }
            }

        }

        for(int k = 0; k <4; k++)
        {
            for(int j = y_beg; j<map_size_y; j++)
            {
                is_deep_water_near = false;
                is_grass = false;
                if(i > 0 && j>0 && grid[i][j].type != 4)
                {
                    if(neighbours(i, j, 0, 2, true) >= 3)
                    {
                        int random = rand()% 100;
                        if(random <= water_rate)
                        {
                            grid[i][j].type = 2;
                            grid[i][j].height = -1;
                            grid[i][j].zone = 0;

                        }
                    }
                }
            }

        }
    }
    for(int k = 0; k <2; k++)
    {
        //is mid water chances of being low water
        for(int i = x_beg; i <map_size_x; i++)
        {

            for(int j = y_beg; j<map_size_y; j++)
            {
                is_deep_water_near = false;
                is_grass = false;
                if(i > 0 && j>0 && grid[i][j].type != 4 && grid[i][j].type != 2 )
                {
                    if(neighbours(i, j, 0, 2, true)>= 1)
                    {
                        int random = rand()% 100;
                        if(random <= water_rate)
                        {
                            grid[i][j].type = 3;
                            grid[i][j].height = 0;
                            grid[i][j].zone = 0;
                        }
                    }
                }

            }
        }
    }
    for(int k = 0; k <4; k++)
    {
        //is mid water chances of being low water
        for(int i = x_beg; i <map_size_x; i++)
        {
            for(int j = y_beg; j<map_size_y; j++)
            {
                if(i > 0 && j>0 && grid[i][j].type != 4 && grid[i][j].type != 2 )
                {
                    if(neighbours(i, j, 0, 3, true)>=2)
                    {
                        int random = rand()% 100;
                        if(random <= water_rate)
                        {
                            grid[i][j].type = 3;
                            grid[i][j].height = 0;
                            grid[i][j].zone = 0;
                        }
                    }
                }


            }
        }
    }

//the sand

    for(int k = 0; k <11; k++)
    {
        for(int i = x_beg; i <map_size_x; i++)
        {

            for(int j = y_beg; j<map_size_y; j++)
            {
                is_deep_water_near = false;
                is_grass = false;
                int random = rand()% 100;
                if(random <= sand_rate && i > 0 && j>0 && grid[i][j].type != 4 && grid[i][j].type != 2 )
                {
                    if(neighbours(i, j, 1, 0, true) >1 || neighbours(i, j, 0, 1, true) >5  && neighbours(i, j, 0, 1, true) <=8)
                    {
                        if(neighbours(i, j, 0, 0, true) >3 || neighbours(i, j, 0, 1, true) >=3)
                        {
                            grid[i][j].type = 1;
                            grid[i][j].height = 1;

                        }
                    }
                    if(neighbours(i, j, 1, 0, true)>=3  && grid[i][j].type == 0 )
                    {
                        grid[i][j].type = 3;
                        grid[i][j].height = 1;

                    }



                }
            }
        }
    }
    for(int k = 0; k <7; k++)
    {
        for(int i = x_beg; i <map_size_x; i++)
        {

            for(int j = y_beg; j<map_size_y; j++)
            {
                is_deep_water_near = false;
                is_grass = false;
                int random = rand()% 100;
                if(random <= sand_rate && i > 0 && j>0 && grid[i][j].type != 4 && grid[i][j].type != 2 )
                {
                    if(neighbours(i, j, 0, 1, true) >=1 && neighbours(i, j, 0, 1, true) >=1  && grid[i][j].type != 1 )
                    {
                        grid[i][j].type = 5;
                        grid[i][j].height = 1;

                    }



                }
            }
        }
    }




}
void Game_Manager::draw_selection()
{

    if(x_cursor >= 0 && x_cursor < map_size_x && y_cursor >= 0 && y_cursor < map_size_y)
    {
        //show height
        stringstream ss;
        ss << grid[x_cursor][y_cursor].height;
        string str = ss.str();
        string path = "height " + str;
        selection_text[0].refill(path);
        selection_text[0].draw(0 , window_vec.y - 550 , 24);
        tile_description(x_cursor, y_cursor);
    }
}
void Game_Manager::tile_description(int tile_x, int tile_y)
{
    if(grid[tile_x][tile_y].ressource_type == WOOD)
    {
        tile_info.refill("Frêne");
    }
    else
    {
        tile_info.refill("Lieu vierge");
    }

    tile_info.draw(0 , window_vec.y - 700 , 24);
}
void Game_Manager::selection()
{
    selection_vector = app->mapPixelToCoords(mouse_vec, view1);
    if(x_cursor >= 0 && x_cursor < map_size_x && y_cursor >= 0 && y_cursor < map_size_y)
    {
        selection_sprite.draw(x_cursor* 50 ,y_cursor* 50 );
        building[0].draw(x_cursor* 50 ,y_cursor* 50 );
    }
    y_cursor = (selection_vector.y)* zoom/ 50;
    x_cursor = (selection_vector.x)* zoom/ 50;


    if(is_l_click() && x_cursor >= 0 && x_cursor < map_size_x && y_cursor >= 0 && y_cursor < map_size_y)
    {
        if(grid[x_cursor][y_cursor].has_citizen && !citizen_selected)
        {
            citizen[0].selected();
            selected_citizen = 0;
            citizen_selected = true;
            for(int i = 0; i< 100; i++)
            {
                grid[path[i][0] ][path[i][1]].passing_trought = false;
                path[i][0] = -1;
                path[i][1] = -1;
            }
        }
        if(citizen_selected )
        {
            if( x_cursor != citizen[0].get_x() ||y_cursor != citizen[0].get_y() )
            {

                citizen[0].set_goal(x_cursor, y_cursor);
                //a* homemade :)
                path[0][0] = citizen[0].get_x();
                path[0][1] = citizen[0].get_y();
                citizen_selected = false;

                for(int i = 0; i<100; i++)
                {


                    if( path [i][0] < x_cursor)
                    {
                        path[i +1][0] = path[i][0] + 1;
                    }
                    else if( path [i][0] > x_cursor)
                    {
                        path[i +1][0] = path[i][0] - 1;
                    }
                    else path[i +1][0] = path[i][0];
                    if( path[i][1] < y_cursor)
                    {
                        path[i +1][1] = path[i][1] + 1;
                    }
                    else if( path[i][1] > y_cursor)
                    {
                        path[i +1][1] = path[i][1] - 1;
                    }
                    else path[i +1][1] = path[i][1];

                    grid[path[i][0] ][path[i][1]].passing_trought = true;

                    if(path[i][0] == x_cursor && path[i][1] == y_cursor)
                    {
                        i =100;
                        for(int i = 0; i< 200; i++)
                        {
                            citizen[0].set_path( path[i][0], path[i][1], i);
                            if(path[i][0] == 0 && path[i][1] == 1)
                            {
                                i = 200;
                            }
                        }
                    }
                }


            }

        }

    }
}
int Game_Manager::neighbours(int i, int j , int typeorzoneorheight, int valor, bool diagonal)
{
    int number = 0;

    if(diagonal)
    {
        if(typeorzoneorheight == 0 && i >0 && j > 0)
        {
            if(grid[i - 1][j].type == valor)
                number++;
            if(grid[i - 1][j + 1].type == valor)
                number++;
            if(grid[i - 1][j -1].type == valor)
                number++;
            if(grid[i ][j].type == valor)
                number++;
            if(grid[i ][j + 1].type == valor)
                number++;
            if(grid[i ][j - 1].type == valor)
                number++;
            if(grid[i + 1][j].type == valor)
                number++;
            if(grid[i + 1][j + 1].type == valor)
                number++;
            if(grid[i + 1][j - 1].type == valor)
                number++;
        }
        if(typeorzoneorheight == 1 && i >0 && j > 0)
        {
            if(grid[i - 1][j].zone == valor)
                number++;
            if(grid[i - 1][j + 1].zone == valor)
                number++;
            if(grid[i - 1][j -1].zone == valor)
                number++;
            if(grid[i ][j].zone == valor)
                number++;
            if(grid[i ][j + 1].zone == valor)
                number++;
            if(grid[i ][j - 1].zone == valor)
                number++;
            if(grid[i + 1][j].zone == valor)
                number++;
            if(grid[i + 1][j + 1].zone == valor)
                number++;
            if(grid[i + 1][j - 1].zone == valor)
                number++;
        }
        if(typeorzoneorheight == 2 && i >0 && j > 0)
        {
            if(grid[i - 1][j].height == valor)
                number++;
            if(grid[i - 1][j + 1].height == valor)
                number++;
            if(grid[i - 1][j -1].height == valor)
                number++;
            if(grid[i ][j + 1].height == valor)
                number++;
            if(grid[i ][j - 1].height == valor)
                number++;
            if(grid[i + 1][j].height == valor)
                number++;
            if(grid[i + 1][j + 1].height == valor)
                number++;
            if(grid[i + 1][j - 1].height == valor)
                number++;
        }
    }
    else if(!diagonal)
    {
        if(typeorzoneorheight == 0 && i >0 && j > 0)
        {
            if(grid[i - 1][j].type == valor)
                number++;
            if(grid[i ][j + 1].type == valor)
                number++;
            if(grid[i ][j - 1].type == valor)
                number++;
            if(grid[i + 1][j].type == valor)
                number++;
        }
        if(typeorzoneorheight == 1 && i >0 && j > 0)
        {
            if(grid[i - 1][j].zone == valor)
                number++;
            if(grid[i ][j + 1].zone == valor)
                number++;
            if(grid[i ][j - 1].zone == valor)
                number++;
            if(grid[i + 1][j].zone == valor)
                number++;
        }
        if(typeorzoneorheight == 2 && i >0 && j > 0)
        {
            if(grid[i - 1][j].height == valor)
                number++;
            if(grid[i ][j + 1].height == valor)
                number++;
            if(grid[i ][j - 1].height == valor)
                number++;
            if(grid[i + 1][j].height == valor)
                number++;

            number++;
        }
    }

    return number;

}
void Game_Manager::draw_grid()
{

    for(int i = 0; i <map_size_x; i++)
    {
        for(int j = 0; j<map_size_y; j++)
        {
            if(!grid[i][j].passing_trought)
            {
                draw_tile(grid[i][j].type, grid[i][j].x_pos, grid[i][j].y_pos );
            }
            if(grid[i][j].ressource_type == WOOD && i< 5 && j < 5)
            {
                ressource_sprite[0].draw(grid[i][j].x_pos * 50, grid[i][j].y_pos * 50);
            }
        }
    }

    // Update the window
}
void Game_Manager::draw_tile(int type , int x_pos, int y_pos)
{
    tile_sprite[type].draw(x_pos * 50, y_pos * 50);
}

bool Game_Manager::manage_event(bool anykey)
{
    mouse_vec = Mouse::getPosition(*app);

    //Vector2i mouse_vec = Mouse::getPosition(*app);
    if(anykey)
    {
        switch(event.type)
        {
        case Event::KeyPressed:
            return 1;
            break;
        }
    }
    else
    {
        keys[5] = false;
        keys[6] = false;
        keys[7] = false;
        keys[8] = false;



        if(Event::KeyPressed)
        {
            if(sf::Keyboard::isKeyPressed(Keyboard::Z))
            {
                keys[5] = true;
            }
            else keys[5] = false;
            if(sf::Keyboard::isKeyPressed(Keyboard::D))
            {
                keys[6] = true;
            }
            else keys[6] = false;
            if(sf::Keyboard::isKeyPressed(Keyboard::S))
            {
                keys[7] = true;
            }
            else keys[7] = false;
            if(sf::Keyboard::isKeyPressed(Keyboard::Q))
            {
                keys[8] = true;
            }
            else keys[8] = false;
            if(sf::Keyboard::isKeyPressed(Keyboard::T) & zoom_rate >= -30)
            {
                zoom_change = 1;
            }
            if(sf::Keyboard::isKeyPressed(Keyboard::G) && zoom_rate <= 50)
            {
                zoom_change = 2;
            }
            return true;

        }

        return false;


    }
    mouse_wheel_x = event.mouseWheel.x;

}
bool Game_Manager::is_l_click()
{
    if(Mouse::isButtonPressed(Mouse::Left))
    {
        return true;
    }
    else return false;

}
