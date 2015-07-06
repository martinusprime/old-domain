#include "Hud.h"

Hud::Hud(RenderWindow *app, Grid &grid, View *view, int screen_width, int screen_height)
    : m_view1(view)    
    , m_grid(grid)
    , task_box(app, "ressources/task_box.png", m_view1)
    , citizen_sprite(app, "ressources/head1.png", m_view1)
    , wood_sprite(app, "ressources/wood.png", m_view1)
    , iron_sprite(app, "ressources/iron.png", m_view1)
    , rock_sprite(app, "ressources/rock.png", m_view1)
    , glass_sprite(app, "ressources/wood.png", m_view1) //TODO
    , sand_sprite(app, "ressources/wood.png", m_view1) //TODO
    , m_resources_window(app, "ressources", 0.5, 0.5, 0, 0, m_view1, 1920, 1080)
    , m_resource_button(app, "ressources ", 0, 0, 0, 0, m_view1)
{
    wood_number = 0;
    current_season = 0;
    current_year = -4000;
    year_lenght = 16;
    m_citizen_number = 0;
    m_app = app;
    m_screen_width = screen_width;
    m_screen_height = screen_height;


   //seasons icons
    season_sprites.push_back(My_Sprite{ app, "ressources/summer.png", m_view1 });
    season_sprites.push_back(My_Sprite{ app, "ressources/autumn.png", m_view1 });
    season_sprites.push_back(My_Sprite{ app, "ressources/winter.png", m_view1 });
    season_sprites.push_back(My_Sprite{ app, "ressources/spring.png", m_view1 });

    season_clock.restart();
    year_clock.restart();
    //make woodnumber int to string
    wood_text.init(app, std::to_string(wood_number), 12, 1 );

    year_text.init(app, "-4000" , 12, 1 );
    citizen_text.init(app, std::to_string(m_citizen_number), 12, 1);
    //resources info panel initialization
    m_resources_window.add_text(50, 50, "Ressources ");
    m_resources_window.add_text(230, 100, "Bois");
    m_resources_window.add_text(100, 100, std::to_string(wood_number));
    m_resources_window.add_text(230, 150, " 0");
    m_resources_window.add_text(230, 200, " 1");
    m_resources_window.add_image(50, 100, "ressources/wood.png");


}

void Hud::draw_ressources()
{
    citizen_sprite.draw((m_screen_width / 2) - 200, 0);
    citizen_text.draw((m_screen_width / 2) - 200 + citizen_sprite.get_w(), 0, 22);

    wood_sprite.draw((m_screen_width / 2) - 40, 0);
    wood_text.draw(m_screen_width / 2, 0, 22);
    if (m_resources_window.is_activated())
    {
        m_resources_window.draw();
    }
}

int Hud::get_resource(Ressources_type_enum resource_type)
{
    if (resource_type == RSC_WOOD)
    {
        return wood_number;
    }
}

void Hud::set_citizen_number(int citizen_number)
{
    m_citizen_number = citizen_number;
    citizen_text.refill(std::to_string(m_citizen_number));

}

void Hud::draw()
{

    //drawing of seasons icons and time for seasons
    season_time = season_clock.getElapsedTime();
    if(season_time.asSeconds() > year_lenght / 4)
    {
        current_season++;
        if( current_season > 3)
        {
            current_season = 0;
        }
        season_clock.restart();
    }
    season_sprites[current_season].draw( m_screen_width - 40, 0);

    //displaying the year
    year_text.refill(std::to_string(current_year));

    year_time = year_clock.getElapsedTime();

    if(year_time.asSeconds() > year_lenght)
    {
        current_year++;
        if( current_season > 3)
        {
            current_season = 0;
        }
        year_clock.restart();
    }

    m_resource_button.update(m_screen_width - 400, 0);
    if (m_resource_button.is_activated())
    {
        m_resource_button.desactivate();
        m_resources_window.activate();
    }
    
    if (m_resources_window.is_activated())
    { 
        m_resources_window.refill_text(1, m_grid.get_ressource().name);
        m_resources_window.refill_text(2, std::to_string(wood_number));
        m_resources_window.refill_text(3, "flexibilité : " + std::to_string(m_grid.get_ressource().flexibility) );
        m_resources_window.refill_text(4, "solidité : " + std::to_string(m_grid.get_ressource().solidity) );
        m_resources_window.update();
    }
  

    year_text.draw( m_screen_width - 110, 0 , 22);

    m_resource_button.draw();
    draw_ressources();

    

}
void Hud::set_resource(Ressources_type_enum resource_type, float number)
{
    if (resource_type == RSC_WOOD)
    {
        wood_number += number;
        wood_text.refill( std::to_string(wood_number));

    }
}
