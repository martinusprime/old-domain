#include "Game_Manager.h"

Game_Manager::Game_Manager()
{
    is_menu_visible = true;
    screen_x = 1920;
    screen_y = 1080;
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
    zoom_change = ZOOM_NO_CHANGE;
    selected_citizen = 0;
    tile_size.x = 100;
    tile_size.y = 60;

    iteration = 0;

}
Game_Manager::~Game_Manager()
{
    //dtor
}

void Game_Manager::init(RenderWindow *app_get)
{
    app = app_get;
    view1.reset(FloatRect(0, 0, screen_x, screen_y));
    view1.setViewport(FloatRect(0, 0, 1.0f, 1.0f));
    app->setView(view1);

    window_vec = app->getSize();
    cout<<"x_window"<<window_vec.x<<"y_window "<<window_vec.y<<endl;

    view2.reset(FloatRect(0, 0, screen_x, screen_y));
    view2.setViewport(FloatRect(0, 0, 1.0f, 1.0f));


    Vector2f vecsize;
    vecsize = view1.getSize();
    h = vecsize.y;
    w = vecsize.x;

    if(is_menu_visible)
    {
        menu1.init(app, & view2);
    }
    for(int i = 0; i < 10; i++)
    {
        stringstream ss;
        ss << i;
        string str = ss.str();
        string path = "ressources/tile" + str + ".png";

        tile_sprite[i].init(app, path, &view1, 100, 5, 5.0);


    }
        windows[0].init(app, "Map", 0.5f, 0.5f, 0, 0, &view2, screen_x, screen_y);
        //windows[i].desactivate();
        windows[0].add_glissor(100, 100);
        windows[0].add_glissor(100, 200);
        windows[0].add_glissor(100, 300);
        windows[0].add_glissor(100, 400);
        windows[0].add_glissor(300, 100);
        windows[0].add_glissor(300, 200);
        windows[0].add_glissor(300, 300);
        windows[0].add_glissor(300, 400);
        windows[0].add_glissor(300, 500);
        windows[0].add_button(300, 100);
        windows[0].add_button(400, 100);

    for(int i = 0; i < 2; i++)
    {
        selection_text[i].init(app, "rien", 12, 1);
        selection_text[i].change_font("ressources/font2.ttf");

    }
    selection_sprite.init(app, "ressources/selection.png", &view1);
    influence_sprite.init(app, "ressources/player_influence.png", &view1);

    int x_tiles = 1;
    int y_tiles = 1;

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
   // sprite_created_1_test.init(app, &view1);
   // sprite_created_1_test.create_character( 0);

    interface1.init(app, &view1, w, h);
}

bool Game_Manager::handle_key_events()
{
    Event event;
    bool isEvent = app->pollEvent(event);
    Action action;
    if (isEvent && key_event.manage_key_event(event, app, action, mouse_vec))
    {
        switch (action)
        {
        case ACT_GO_UP:
            y_offset-= 50;
            break;
        case ACT_GO_RIGHT:
            x_offset+= 50;
            break;
        case ACT_GO_DOWN:
            y_offset+= 50;
            break;
        case ACT_GO_LEFT:
            x_offset-= 50;
            break;
        case ACT_ZOOM_IN:
            zoom_change = ZOOM_ADD;
            break;
        case ACT_ZOOM_OUT:
            zoom_change = ZOOM_LESS;
            break;
        case ACT_CLOSE_APP:
            cout << "close app\n";
            app->close();
            break;
        default:
            break;
        }
        return true;
    }
    return false;
}

void Game_Manager::update()
{

    bool isEvent = handle_key_events();

    zoom_time = clock_zoom.getElapsedTime();
    if(zoom_time.asSeconds() >  0.05  && zoom_change != ZOOM_NO_CHANGE)
    {
        clock_zoom.restart();
        if(zoom_change == ZOOM_ADD && zoom_rate >= -30)
        {
            zoom =0.90;
            zoom_rate --;
        }
        if(zoom_change == ZOOM_LESS  && zoom_rate <= 50)
        {
            zoom =1.1;
            zoom_rate ++;
        }
        zoom_change = ZOOM_NO_CHANGE;
    }
    else
    {
        zoom = 1;
    }

    if(is_menu_visible)
    {
        menu1.update();
        if(isEvent == true)
        {
            is_menu_visible = false;
        }
    }

    view1.setCenter(x_offset , y_offset);
    view1.zoom(zoom);
    app->setView(view1);

    for(int i = 0; i<6; i++)
    {
        if(windows[i].is_activated())
        {
            windows[i].update();
            int multiplicator = windows[i].get_glissor(8) + 1;
            int divisor = windows[i].get_glissor(4) * multiplicator;
            if(divisor == 0)divisor = 1;
            amplitude = windows[i].get_glissor(0) /divisor;
            divisor = windows[i].get_glissor(5) * multiplicator;
            if(divisor == 0)divisor = 1;
            frequence = windows[i].get_glissor(1)/divisor;
            divisor = windows[i].get_glissor(6) * multiplicator;
            if(divisor == 0)divisor = 1;
            octave = windows[i].get_glissor(2)/divisor;
            divisor = windows[i].get_glissor(7) * multiplicator;
            if(divisor == 0)divisor = 1;
            persistence = windows[i].get_glissor(3)/divisor;

            iteration++;
            if(iteration >= 10)
            {
                //cout<<"createmap "<<amplitude<<endl;
                iteration = 0;
            create_map(1, 1 );

            }
        }
    }
    citizen_update();
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
        city[0].init(app, &view1, citizen[0].get_x(), citizen[0].get_y(), tile_size.x, tile_size.y );
        city_number++;
        grid[citizen[0].get_x()][citizen[0].get_x()].is_city = true;
    }
    if(citizen_action[2].is_activated() )  //l'action sur la ressources
    {
        city[0].init(app, &view1, citizen[0].get_x(), citizen[0].get_y(), tile_size.x, tile_size.y );
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
    if(! is_menu_visible)
    {
        draw_grid();
        //drwing of the test created sprite
        //sprite_created_1_test.draw();

        for(int i = 0; i < city_number; i++)
        {
            city[i].draw();
        }
        citizen[0].draw();

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
    if(is_menu_visible)
    {
        menu1.draw();
    }

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
    srand(time(0));
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
            grid[i][j].owner = YOU;

        }
    }
//perlin noise expreimentation
PerlinNoise perlin4;
perlin4.Set(persistence, frequence, amplitude, 1, 20);
            double noise_value = 0;


 for(int i = x_beg; i <map_size_x; i++)
    {
        for(int j = y_beg; j<map_size_y; j++)
        {
            noise_value = floor(10 * (perlin4.GetHeight(i, j))) ;
            if(noise_value <= 0 && noise_value > -15)
            {
                grid[i][j].type = 0;

            }
            if(noise_value <= -15 && noise_value > -35)
            {
                grid[i][j].type = 1;

            }
            if(noise_value <= -35 && noise_value > -50)
            {
                grid[i][j].type = 2;

            }
            if(noise_value <= -50 && noise_value > -75)
            {
                grid[i][j].type = 3;

            }
            if(noise_value <= -75 && noise_value > -100)
            {
                grid[i][j].type = 4;

            }
            if(noise_value > 0 && noise_value <= 35)
            {
                grid[i][j].type = 7;

            }
            if(noise_value > 35 && noise_value <= 50)
            {
                grid[i][j].type = 8;

            }

          //  cout<<noise_value<<endl;
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
        string path1 = "height " + str;
        selection_text[0].refill(path1);
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
        selection_sprite.draw( (x_cursor - y_cursor)* (tile_size.x / 2) ,(x_cursor + y_cursor)* (tile_size.y / 2) );
    }
    x_cursor = (selection_vector.x / tile_size.x + selection_vector.y/ tile_size.y - 0.5)* zoom;
    y_cursor = (selection_vector.y/ tile_size.y - selection_vector.x / tile_size.x + 0.5)* zoom;


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
int Game_Manager::count_neighbours(unsigned int i, unsigned int j , int typeorzoneorheight, int value, bool diagonal)
{
    int number = 0;


    if(typeorzoneorheight == 0)
    {
        if(grid[i - 1][j].type == value)
            number++;
        if(grid[i ][j + 1].type == value)
            number++;
        if(grid[i ][j - 1].type == value)
            number++;
        if(grid[i + 1][j].type == value)
            number++;
        if (diagonal)  //diagonal + sides
        {
            if(grid[i - 1][j + 1].type == value)
                number++;
            if(grid[i - 1][j -1].type == value)
                number++;
            if(grid[i + 1][j + 1].type == value)
                number++;
            if(grid[i + 1][j - 1].type == value)
                number++;
        }
    }
    if(typeorzoneorheight == 1)
    {
        if(grid[i - 1][j].zone == value)
            number++;
        if(grid[i ][j + 1].zone == value)
            number++;
        if(grid[i ][j - 1].zone == value)
            number++;
        if(grid[i + 1][j].zone == value)
            number++;
        if (diagonal)
        {
            if(grid[i - 1][j + 1].zone == value)
                number++;
            if(grid[i - 1][j -1].zone == value)
                number++;
            if(grid[i + 1][j + 1].zone == value)
                number++;
            if(grid[i + 1][j - 1].zone == value)
                number++;
        }
    }
    if(typeorzoneorheight == 2)
    {
        if(grid[i - 1][j].height == value)
            number++;
        if(grid[i ][j + 1].height == value)
            number++;
        if(grid[i ][j - 1].height == value)
            number++;
        if(grid[i + 1][j].height == value)
            number++;
        if (diagonal)
        {
            if(grid[i - 1][j + 1].height == value)
                number++;
            if(grid[i - 1][j -1].height == value)
                number++;
            if(grid[i + 1][j + 1].height == value)
                number++;
            if(grid[i + 1][j - 1].height == value)
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
                ressource_sprite[0].draw( (grid[i][j].x_pos - grid[i][j].y_pos)* (tile_size.x / 2), (grid[i][j].x_pos + grid[i][j].y_pos)* (tile_size.y / 2));
            }
        }
    }

    // Update the window
}
void Game_Manager::draw_tile(int type , int x_pos, int y_pos)
{
    //tile_sprite[type].draw(x_pos * 50, y_pos * 50);
    tile_sprite[type].draw( ( x_pos - y_pos) * (tile_size.x / 2), (y_pos +x_pos) * (tile_size.y / 2));

    if(grid[x_pos][y_pos].owner == YOU)
    {
    influence_sprite.draw( ( x_pos - y_pos) * (tile_size.x / 2), (y_pos +x_pos) * (tile_size.y / 2));

    }
}

bool Game_Manager::is_l_click()
{
    if(Mouse::isButtonPressed(Mouse::Left))
    {
        return true;
    }
    else return false;

}
