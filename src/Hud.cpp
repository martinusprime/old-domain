#include "Hud.h"

Hud::Hud(RenderWindow *app, View *view, int screen_width, int screen_height)
    : m_view1(view)    
    , wood_sprite(app, "ressources/wood.png", m_view1)
    , iron_sprite(app, "ressources/iron.png", m_view1)
    , rock_sprite(app, "ressources/rock.png", m_view1)
    , glass_sprite(app, "ressources/wood.png", m_view1) //TODO
    , sand_sprite(app, "ressources/wood.png", m_view1) //TODO
{
    wood_number = 0;
    current_season = 0;
    current_year = -4000;
    year_lenght = 16;

    m_app = app;
    m_screen_width = screen_width;

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
}

void Hud::draw_ressources()
{
    wood_sprite.draw( (m_screen_width / 2 )- 40, 0 );
    wood_text.draw(m_screen_width / 2, 0, 22 );
}

void Hud::draw()
{
    draw_ressources();

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

    year_text.draw( m_screen_width - 110, 0 , 22);
}
