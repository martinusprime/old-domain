#include "Game_Manager.h"

#include "Citizen.h"
#include "Random.h"

Game_Manager::Game_Manager(RenderWindow *app, View &view1, int screen_x, int screen_y)
    : m_view1(view1)
    , menu1(app, &m_view2)
    , m_grid(GRID_WIDTH, GRID_HEIGHT, &m_view1, app)
    , selection_sprite(app, "ressources/selection.png", &m_view1)
    , interface1(app, m_grid, &m_view2, screen_x, screen_y)
    , m_dialog(m_grid, app, &m_view2, screen_x, screen_y)
    , m_builder_gui(m_grid, app, &m_view1, &m_view2)
    , m_info(app, &view1, 1920, 1080)
{
    is_menu_visible = true;
    is_building_menu = false;
    is_info = false;
    m_mouse_over_actions = false;
    is_building_selected = false;
    m_screen_x = screen_x;
    m_screen_y = screen_y;
    x_offset = 0;
    y_offset = 0;
    zoom = 1;
    zoom_rate = 10;
    open_window = true;
    rock = 0;
    wood = 0;
    iron = 0;
    zoom_change = ZOOM_NO_CHANGE;

    m_app = app;
    m_app->setView(m_view1);

    window_vec = m_app->getSize();
    cout << "x_window" << window_vec.x << "y_window " << window_vec.y << endl;

    m_view2.reset(FloatRect(0.0f, 0.0f, static_cast<float>(m_screen_x), static_cast<float>(m_screen_y)));
    m_view2.setViewport(FloatRect(0.0f, 0.0f, 1.0f, 1.0f));

    Vector2f vecsize = m_view1.getSize();
    m_h = static_cast<int>(vecsize.y);
    m_w = static_cast<int>(vecsize.x);


    for (int i = 0; i < 2; i++)
    {
        selection_text[i].init(app, "rien", 12, 1);
        selection_text[i].change_font("ressources/font2.ttf");
    }

    create_map(GRID_WIDTH, GRID_HEIGHT);

    for (int i = 0; i < 3; i++) {
        m_units.push_back(shared_ptr<Unit>(new Citizen(m_grid, app, &m_view1, &m_view2, *this)));
        interface1.set_citizen_number(m_units.size());
        interface1.set_citizen("paul", 14); //I put false values because I 've got problem with get_name()

    }
    m_grid(0, 0).citizen_id = 0;

    m_buildings.push_back(Building{ app, &m_view1, 0 });

    //now that m_view1 has been reseted we can load tile files
    m_grid.loadFiles();
    tile_info.init(app, "lieu vierge", 10, 1);
}

void Game_Manager::execute_action(Action action)
{
    switch (action)
    {
    case ACT_GO_UP:
        y_offset -= 50;
        break;
    case ACT_GO_RIGHT:
        x_offset += 50;
        break;
    case ACT_GO_DOWN:
        y_offset += 50;
        break;
    case ACT_GO_LEFT:
        x_offset -= 50;
        break;
    case ACT_ZOOM_IN:
        zoom_change = ZOOM_ADD;
        break;
    case ACT_ZOOM_OUT:
        zoom_change = ZOOM_LESS;
        break;
    case ACT_CLOSE_APP:
        cout << "close app\n";
        m_app->close();
        break;
    case ACT_ROTATE_RIGHT:
        m_grid.rotateRight(m_units);
        draw();
        break;
    case ACT_ROTATE_LEFT:
        m_grid.rotateLeft(m_units);
        draw();
        break;
    default:
        break;
    }
}

/* x_mouse, y_mouse are in window coordinate (pixels)
x_cursor, y_cursor are in m_grid coordinate */
void Game_Manager::handle_mouse_at_window_border(int x_mouse, int y_mouse)
{
    static sf::Clock mouse_move_clock;
    sf::Time mouse_move_time = mouse_move_clock.getElapsedTime();
    if (mouse_move_time.asSeconds() > 0.05) {
        mouse_move_clock.restart();
        Vector2u windowSize = m_app->getSize();
        const int margin = 10;
        if (m_x_cursor < -margin || m_x_cursor > GRID_WIDTH + margin || m_y_cursor < -margin || m_y_cursor > GRID_HEIGHT + margin) {
            //we are already too far outside the m_grid, do nothing
            return;
        }
        if (x_mouse < 15)
        {
            execute_action(ACT_GO_LEFT);
        }
        else if (x_mouse > static_cast<int>(windowSize.x - 15))
        {
            execute_action(ACT_GO_RIGHT);
        }

        if (y_mouse < 15) {
            execute_action(ACT_GO_UP);
        }
        else if (y_mouse > static_cast<int>(windowSize.y - 35))
        {
            execute_action(ACT_GO_DOWN);
        }

    }
}

bool Game_Manager::handle_input_events()
{
    Event event;
    bool isEvent = m_app->pollEvent(event);
    Action action;
    sf::Mouse::Button click = {};
    Vector2i mouse_vec;

    key_event.get_mouse_position(m_app, mouse_vec);

//translate to m_grid coordinates
if (m_mouse_over_actions == false)
{
    m_selection_vector = m_app->mapPixelToCoords(mouse_vec, m_view1);
    m_x_cursor = static_cast<int>((m_selection_vector.x / (float)Tile::tile_size.m_w + m_selection_vector.y / (float)Tile::tile_size.m_h - 0.5) * zoom);
    m_y_cursor = static_cast<int>((m_selection_vector.y / (float)Tile::tile_size.m_h - m_selection_vector.x / (float)Tile::tile_size.m_w + 0.5) * zoom);
}

handle_mouse_at_window_border(mouse_vec.x, mouse_vec.y);

bool ret = false;
if (isEvent)
{
    if (key_event.manage_key_event(event, action))
    {
        execute_action(action);
        ret = true;
    }
    if (key_event.manage_mouse_click(event, click)) {
        if (!open_window) {
            handle_mouse_click(click, mouse_vec);
        }
        ret = true;
    }
}
return ret;
}

void Game_Manager::update()
{

    bool isEvent = handle_input_events();

    zoom_time = clock_zoom.getElapsedTime();
    if (zoom_time.asSeconds() > 0.05  && zoom_change != ZOOM_NO_CHANGE)
    {
        clock_zoom.restart();
        if (zoom_change == ZOOM_ADD && zoom_rate >= -30)
        {
            zoom = 0.90f;
            zoom_rate--;
        }
        if (zoom_change == ZOOM_LESS  && zoom_rate <= 50)
        {
            zoom = 1.1f;
            zoom_rate++;
        }
        zoom_change = ZOOM_NO_CHANGE;
    }
    else
    {
        zoom = 1;
    }

    if (is_menu_visible)
    {
        menu1.update();
        if (isEvent == true)
        {
            is_menu_visible = false;
        }
    }

    m_view1.setCenter(static_cast<float>(x_offset), static_cast<float>(y_offset));
    m_view1.zoom(zoom);
    m_app->setView(m_view1);

    for (My_window &window : windows)
    {
        if (window.is_activated())
        {
            window.update();
        }
    }

    if (is_info)
    {
        m_info.update();
        if (m_info.is_activated() == false)
        {
            is_info = false;
        }
    }

    if (is_building_menu)
    {
        m_builder_gui.update();
        if (m_builder_gui.is_activated() == false)
        {
            is_building_menu = false;
            is_building_selected = false;

        }
        if (m_builder_gui.is_building_selected() == true && is_building_menu)
        {
            is_building_selected = true;
         }
        if (is_building_selected )
        {
            if (Mouse::isButtonPressed(Mouse::Left) && interface1.get_resource(RSC_WOOD) >= 0.5f  &&m_x_cursor >= 0 && m_x_cursor < GRID_WIDTH && m_y_cursor >= 0 && m_y_cursor < GRID_HEIGHT
                && m_grid(m_x_cursor, m_y_cursor).is_building == false
                && m_grid(m_x_cursor, m_y_cursor).owner == YOU
                && m_grid(m_x_cursor, m_y_cursor).is_city == false)
           
            {
                m_grid(m_x_cursor, m_y_cursor).is_building = true;
                interface1.set_resource(RSC_WOOD, -0.5f);
                m_buildings.push_back(Building{ m_app, &m_view1, 0 });
                m_buildings[m_buildings.size() - 1].set_coord(m_x_cursor, m_y_cursor);
                cout << "new buildings" << endl;
            }

        }
    }

    update_units();


}

void Game_Manager::set_building_menu()
{
    is_building_menu = true;
}

void Game_Manager::update_units()
{
    m_mouse_over_actions = false;

    for (std::shared_ptr<Unit> &unit : m_units) {
        unit->update();
        if (unit->is_selected() == 1)
        {
            if (unit->is_mouse_over_actions())
            {
            //    cout << "touttouttouttouttouttouttouttouttoue" << endl;
                m_mouse_over_actions = true;
            }


        }
    }
}


void Game_Manager::draw()
{
    static sf::Clock render_clock;
    if (render_clock.getElapsedTime().asMilliseconds() < 2) {
        return;
    }
    render_clock.restart();
    m_app->clear();
    if (!is_menu_visible)
    {
        m_grid.draw();

        for (Building &building : m_buildings)
        {
            building.draw();
        }
        for (City &city : m_cities)
        {
            city.draw();
        }
        for (std::shared_ptr<Unit> &unit : m_units) {
            unit->draw();
        }
    }

    if (is_building_selected == true)
    {
        draw_building_selection();
    }

    // Update the window
    draw_gui();
    m_app->display();
}
void Game_Manager::draw_building_selection()
{
    if (m_x_cursor >= 0 && m_x_cursor < GRID_WIDTH && m_y_cursor >= 0 && m_y_cursor < GRID_HEIGHT)
    {
        m_builder_gui.draw_building(m_x_cursor, m_y_cursor);
    }
}

void Game_Manager::draw_gui()
{
    highlight_selected_tile();
    m_app->setView(m_view2);
    if (is_menu_visible)
    {
        menu1.draw();
    }

    open_window = false;

    for (My_window &window : windows)
    {
        if (window.is_activated())
        {
            open_window = true;
            window.draw();
        }
    }
    m_dialog.draw();
    draw_selection();

    if (is_building_menu)
    {
        m_builder_gui.draw();
    }

    interface1.draw();

    if (is_info)
    {
        m_info.draw();
    }

    m_app->setView(m_view1);
}

void Game_Manager::create_map(int map_width, int map_height)
{
    //sur 200
    cout << "Creation" << endl;
    water_rate = 55;
    sand_rate = 90;
    deep_sea_rate = 4;
    deep_sea_expansion_rate = 60;
    for (int i = 0; i <map_width; i++)
    {
        for (int j = 0; j< map_height; j++)
        {
            m_grid(i, j).m_type = 2;
            m_grid(i, j).m_x_pos = i;
            m_grid(i, j).m_y_pos = j;
            m_grid(i, j).height = 1;
            m_grid(i, j).zone = 1;
            m_grid(i, j).passing_through = false;
            m_grid(i, j).is_city = false;
            m_grid(i, j).ressource_type = RSC_NO;
            m_grid(i, j).owner = PLAYER2;
            m_grid(i, j).random_pattern = Random::get_int(0, 4);
            //test for stone
            if (i < 5 && j < 5 && i> 0 && j > 0)
            {
                m_grid(i, j).ressource_type = RSC_STONE;
                m_grid(i, j).resource_location = 0;

            }
        }
    }
    for (int i = 0; i <10; i++)
    {
        for (int j = 0; j< 10; j++)
        {
            if (m_grid(i, j).ressource_type == RSC_STONE)
            {
                if (m_grid(i + 1, j).ressource_type == RSC_STONE
                    && m_grid(i, j + 1).ressource_type == RSC_STONE
                    && m_grid(i - 1, j).ressource_type != RSC_STONE
                    && m_grid(i, j - 1).ressource_type != RSC_STONE)
                {

                    m_grid(i, j).resource_location = 0;

                }
                if (m_grid(i + 1, j).ressource_type != RSC_STONE
                    && m_grid(i, j + 1).ressource_type != RSC_STONE
                    && m_grid(i - 1, j).ressource_type == RSC_STONE
                    && m_grid(i, j - 1).ressource_type == RSC_STONE)
                {

                    m_grid(i, j).resource_location = 19;

                }
                if (m_grid(i + 1, j).ressource_type != RSC_STONE
                    && m_grid(i, j + 1).ressource_type == RSC_STONE
                    && m_grid(i - 1, j).ressource_type == RSC_STONE
                    && m_grid(i, j - 1).ressource_type != RSC_STONE)
                {

                    m_grid(i, j).resource_location = 4;

                }
                if (m_grid(i + 1, j).ressource_type == RSC_STONE
                    && m_grid(i, j + 1).ressource_type != RSC_STONE
                    && m_grid(i - 1, j).ressource_type != RSC_STONE
                    && m_grid(i, j - 1).ressource_type == RSC_STONE)
                {

                    m_grid(i, j).resource_location = 1;

                }
                if (m_grid(i + 1, j).ressource_type == RSC_STONE
                    && m_grid(i, j + 1).ressource_type == RSC_STONE
                    && m_grid(i - 1, j).ressource_type == RSC_STONE
                    && m_grid(i, j - 1).ressource_type != RSC_STONE)
                {

                    m_grid(i, j).resource_location = 1;

                }
            }

        }
    }
    //perlin noise experimentation
    PerlinNoise perlin4;
    //perlin4.Set(persistence, frequence, amplitude, octave, 20);
    double noise_value = 0;


    for (int i = 0; i < map_width; i++)
    {
        for (int j = 0; j < map_height; j++)
        {
            noise_value = floor(100 * (perlin4.GetHeight(i, j)));

            if (noise_value <= -75)
            {
                m_grid(i, j).m_type = 0;
                m_grid(i, j).m_is_walkable = false;
            }

            if (noise_value <= -50 && noise_value > -75)
            {
                m_grid(i, j).m_type = 1;
                m_grid(i, j).m_is_walkable = false;
            }

            if (noise_value <= -35 && noise_value > -50)
            {
                m_grid(i, j).m_type = 2;
                m_grid(i, j).m_is_walkable = false;

            }
            if (noise_value <= -15 && noise_value > -35)
            {
                m_grid(i, j).m_type = 3;
                m_grid(i, j).m_is_walkable = false;

            }

            if (noise_value <= 0 && noise_value > -15)
            {
                m_grid(i, j).m_type = 4;

            }



            if (noise_value > 0 && noise_value <= 35)
            {
                m_grid(i, j).m_type = 5;

            }
            if (noise_value > 35 && noise_value <= 50)
            {
                m_grid(i, j).m_type = 6;

            }
            if (noise_value > 50)
            {
                m_grid(i, j).m_type = 6;

            }
            //   cout<<noise_value<<endl;
        }
    }
    //test of rivers creation

    int river_number = 5;
    int x_start;
    int y_start;
    int x_now, y_now;
    srand(time(0));
    for (int i = 0; i < river_number; i++)
    {
        for (int k = 0; k < 10; k++)
        {
            x_start = Random::get_int(1, GRID_WIDTH - 1) * 5;
            cout << "x_start" << x_start << endl;
            y_start = Random::get_int(1, GRID_HEIGHT - 1) * 5;
            x_now = x_start;
            y_now = y_start;
            if (m_grid(x_now, y_now).m_type > 2)
            {
                k = 30;
            }
            m_grid(x_now, y_now).m_type = 0;
            m_grid(x_now, y_now).m_is_walkable = false;

        
        }

        int dir = Random::get_int(0, 4);
        for (int j = 0; j < 30; j++)
        {

            m_grid(x_now, y_now).m_type = 3;


            if (x_now >= GRID_WIDTH - 1 || y_now >= GRID_HEIGHT - 1 || x_now <= 1 || y_now <= 1)
            {
                j = 55;
            }

            if(Random::get_int(0, 2) ==1 )
            {
                dir = Random::get_int(0, 4);
            }

            if (dir == 0)
            {
                y_now++;
            }
            else if (dir == 1)
            {
                y_now--;
            }
            else if (dir == 2)
            {
                x_now++;
            }
            else if (dir == 3)
            {
                x_now--;
            }

            if (m_grid(x_now, y_now).m_type <= 2)
            {
                j = 55;
            }
        }

                

    }







    for (int i = 0; i <map_width; i++)
    {
        for (int j = 0; j< map_height; j++)
        {
            if (m_grid(i, j).m_type == 5 || m_grid(i, j).m_type == 6)
            {
                m_grid(i, j).ressource_type = RSC_WOOD;
            }
        }
    }
}

void Game_Manager::draw_selection()
{

    if (m_x_cursor >= 0 && m_x_cursor < GRID_WIDTH && m_y_cursor >= 0 && m_y_cursor < GRID_HEIGHT)
    {
        //show height
        stringstream ss;
        ss << m_grid(m_x_cursor, m_y_cursor).height;
        string str = ss.str();
        string path1 = "height " + str;
        selection_text[0].refill(path1);
        selection_text[0].draw(0, window_vec.y - 550, 24);

        stringstream ss2;
        ss2 << m_grid(m_x_cursor, m_y_cursor).m_x_pos;
        str = ss2.str();
        path1 = "x: " + str;
        selection_text[1].refill(path1);
        selection_text[1].draw(0, window_vec.y - 450, 24);


        stringstream ss3;
        ss3 << m_grid(m_x_cursor, m_y_cursor).m_y_pos;
        str = ss3.str();
        path1 = "y: " + str;
        selection_text[1].refill(path1);
        selection_text[1].draw(0, window_vec.y - 350, 24);

        tile_description(m_x_cursor, m_y_cursor);
    }
}

void Game_Manager::tile_description(int tile_x, int tile_y)
{
    if (m_grid(tile_x, tile_y).ressource_type == RSC_WOOD)
    {
        tile_info.refill("Fr�ne");
    }
    else
    {
        tile_info.refill("Lieu vierge");
    }

    tile_info.draw(0, window_vec.y - 700, 24);
}

void Game_Manager::highlight_selected_tile()
{
    if (m_x_cursor >= 0 && m_x_cursor < GRID_WIDTH && m_y_cursor >= 0 && m_y_cursor < GRID_HEIGHT)
    {
        //highlight selected tile
        selection_sprite.draw((m_x_cursor - m_y_cursor)* (Tile::tile_size.m_w / 2), (m_x_cursor + m_y_cursor)* (Tile::tile_size.m_h / 2));
    }
}

void Game_Manager::handle_mouse_click(sf::Mouse::Button click, Vector2i mouse_vec)
{
    if (m_x_cursor < 0 || m_x_cursor >= GRID_WIDTH || m_y_cursor < 0 || m_y_cursor >= GRID_HEIGHT)
    {
        return;
    }

    //TODO check all units, not only citizen 0
    for (shared_ptr<Unit> &unit : m_units) {
        if (unit->handle_mouse_click(m_selection_vector, click, m_x_cursor, m_y_cursor))
        {
            //troubles when I put get_name (the real purpose of this
            m_info.fill(std::to_string(unit->get_x()) );
        }
    }
}

int Game_Manager::count_neighbours(unsigned int i, unsigned int j, Caracteristic typeorzoneorheight, int value, bool diagonal)
{
    int number = 0;
    if (i == 0 || j == 0 || j + 1 >= GRID_HEIGHT || i + 1 >= GRID_WIDTH) {
        return 0; //TODO handle this correctly
    }

    if (typeorzoneorheight == CRC_TYPE)
    {
        if (m_grid(i - 1, j).m_type == value)
            number++;
        if (m_grid(i, j + 1).m_type == value)
            number++;
        if (m_grid(i, j - 1).m_type == value)
            number++;
        if (m_grid(i + 1, j).m_type == value)
            number++;
        if (diagonal)  //diagonal + sides
        {
            if (m_grid(i - 1, j + 1).m_type == value)
                number++;
            if (m_grid(i - 1, j - 1).m_type == value)
                number++;
            if (m_grid(i + 1, j + 1).m_type == value)
                number++;
            if (m_grid(i + 1, j - 1).m_type == value)
                number++;
        }
    }
    if (typeorzoneorheight == CRC_ZONE)
    {
        if (m_grid(i - 1, j).zone == value)
            number++;
        if (m_grid(i, j + 1).zone == value)
            number++;
        if (m_grid(i, j - 1).zone == value)
            number++;
        if (m_grid(i + 1, j).zone == value)
            number++;
        if (diagonal)
        {
            if (m_grid(i - 1, j + 1).zone == value)
                number++;
            if (m_grid(i - 1, j - 1).zone == value)
                number++;
            if (m_grid(i + 1, j + 1).zone == value)
                number++;
            if (m_grid(i + 1, j - 1).zone == value)
                number++;
        }
    }
    if (typeorzoneorheight == CRC_HEIGTH)
    {
        if (m_grid(i - 1, j).height == value)
            number++;
        if (m_grid(i, j + 1).height == value)
            number++;
        if (m_grid(i, j - 1).height == value)
            number++;
        if (m_grid(i + 1, j).height == value)
            number++;
        if (diagonal)
        {
            if (m_grid(i - 1, j + 1).height == value)
                number++;
            if (m_grid(i - 1, j - 1).height == value)
                number++;
            if (m_grid(i + 1, j + 1).height == value)
                number++;
            if (m_grid(i + 1, j - 1).height == value)
                number++;
        }
    }

    return number;
}

void Game_Manager::show_action_button(Button &button)
{
    button.update(0, m_h - 50);
}

void Game_Manager::set_info()
{
    is_info = true;
    m_info.activate();
}

void Game_Manager::create_city(int x, int y)
{
    m_cities.push_back(City{ m_app, &m_view1, x, y, Tile::tile_size.m_w, Tile::tile_size.m_h });
    m_cities[m_cities.size() - 1].create_city();
    m_grid(x, y).is_city = true;

    Tile_Box tile_box(x - 5, y - 5, x + 5, y + 5, GRID_WIDTH, GRID_HEIGHT);
    tile_box.start();
    for (int i = 0; i < 380; i++) //for the moment not to big selection
    {
        if ( ! tile_box.is_over())
        {
            m_grid(tile_box.get_x(), tile_box.get_y()).owner = YOU;
        }
        else
        {
            i = 1000;
        }
    }
}
