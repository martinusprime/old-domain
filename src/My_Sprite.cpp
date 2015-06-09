#include "File_Loader.h"
#include "My_Sprite.h"
#include "Random.h"


My_Sprite::My_Sprite()
{
    //I'm not sure if we should leave this constructor, m_file will be empty and the object does
    //not have a valid state.
}

My_Sprite::My_Sprite(const My_Sprite &other)
{
    m_total_animation_time = other.m_total_animation_time;

    m_view1 = other.m_view1;
    m_file = other.m_file;
    m_app = other.m_app;
    m_x = other.m_x;
    m_y = other.m_y;
    m_w = other.m_w;
    m_h = other.m_h;
    m_event = other.m_event;
    m_texture = other.m_texture;

    /* sf::Sprite can not simply be copied, see "white square problem":
    http://www.sfml-dev.org/tutorials/2.1/graphics-sprite.php#the-white-square-problem */
    m_sprite = other.m_sprite;
    if (m_file != "") {
        FileLoader<sf::Texture>::loadFile(m_texture, m_file);
        m_sprite.setTexture(m_texture);
    }

    m_animation_width = other.m_animation_width;
    m_animation_length = other.m_animation_length;
    m_total_animation_time = other.m_total_animation_time;
    m_clock1 = other.m_clock1;
    m_time1 = other.m_time1;
    m_animation_rect = other.m_animation_rect;
}

My_Sprite::My_Sprite(RenderWindow *app, std::string file, View *view)
{
    m_total_animation_time =0;

    m_view1 = view;
    m_file = file;
    m_app = app;
    FileLoader<Texture>::loadFile(m_texture, m_file);
	//m_texture.setSmooth(true);
    m_sprite.setTexture(m_texture);

    FloatRect  a= m_sprite.getGlobalBounds();
    m_w = a.width;
    m_h = a.height;
}

My_Sprite::My_Sprite(RenderWindow *app, std::string file, View *view, int file_number)
{
    m_total_animation_time =0;

    m_view1 = view;
    m_app = app;
    int rand_limit = 3;
    if(file_number != 0)
    {
        rand_limit = file_number;
    }

    int random = Random::get_int(0, rand_limit);
    m_file = file + std::to_string(random) + ".png";
    //cout<< file<<endl;
    ifstream file_check(m_file);
    while(file_check.is_open() == false && rand_limit != 1 )
    {
        rand_limit--;
        random = rand() % rand_limit;
        m_file = file + std::to_string(random) + ".png";
        file_check.open(m_file);
        //cout<< "file finally chosen "<<file<<endl;
    }
    if(file_check.is_open() == false && rand_limit == 1 )
    {
        m_texture.loadFromFile("ressources/empty.png");
    }
    else
    {
        FileLoader<Texture>::loadFile(m_texture, m_file);
    }
	//m_texture.setSmooth(true);
    m_sprite.setTexture(m_texture);

    FloatRect  a = m_sprite.getGlobalBounds();
    m_w = a.width;
    m_h = a.height;

}

My_Sprite::My_Sprite(RenderWindow *app, string file, View *view, int animation_width, int animation_length, float total_animation_time)
{
    m_view1 = view;
    m_file = file;
    m_app = app;
    FileLoader<Texture>::loadFile(m_texture, m_file);
	//m_texture.setSmooth(true);
    m_sprite.setTexture(m_texture);

    m_animation_width = animation_width;
    m_animation_length = animation_length;
    m_total_animation_time = total_animation_time;
    FloatRect  a = m_sprite.getGlobalBounds();
    m_w = a.width;
    m_h = a.height;
    m_animation_rect.left = 0;
    m_animation_rect.top = 0;
    m_animation_rect.width = m_w / m_animation_length;
    m_animation_rect.height = m_h;

    m_clock1.restart();
}

void My_Sprite::set_text_rect(int x, int y, int w, int h)
{
    m_w = w;
    m_h = h;
    m_animation_rect.height = m_h;
    m_animation_rect.width = m_w;
    m_animation_rect.top = y;
    m_animation_rect.left = x;
    m_sprite.setTextureRect(m_animation_rect);
}
sf::Sprite My_Sprite::get_sprite()
{
    return m_sprite;
}

string My_Sprite::get_file()
{
    return m_file;
}

void My_Sprite::add_sprite(My_Sprite added_sprite, string save_slot, int width)
{
    m_animation_rect.height = m_h;
    m_animation_rect.width = m_w;
    m_animation_rect.top = 0;
    m_animation_rect.left = 0;

    Image background;
    FileLoader<Image>::loadFile(background, m_file);
    Image background2;
    FileLoader<Image>::loadFile(background2, added_sprite.get_file());

    sf::Image image;
    image.create(width, m_h);

    image.copy(background, 0, 0,  IntRect(0, 0, m_w, m_h));
    image.copy(background2, 0, 0, IntRect(0, 0, m_w, m_h), true);

    image.saveToFile(save_slot);


    FileLoader<Texture>::loadFile(m_texture, save_slot);
    m_file = save_slot;
    m_sprite.setTexture(m_texture);
}

void My_Sprite::add_sprite(My_Sprite added_sprite, int sunlight_get)
{
    m_animation_rect.height = 64;
    m_animation_rect.width = 128;
    m_animation_rect.top = 0;
    m_animation_rect.left = 0;
    int sunlight = - sunlight_get* 17;

    Texture texture2;

    Image background;
    FileLoader<Image>::loadFile(background, m_file);
    Image background2;
    FileLoader<Image>::loadFile(background2, added_sprite.get_file());

    sf::Image image;
    image.create(128, 64);
    // Copy image1 on image2 at position (10, 10)
    image.copy(background, 0, 0,  IntRect(0, 0, 128, 64));
    image.copy(background2, 0, 0, IntRect(0, 0, 128, 64),true);
    Color ancient_pixel;

    for(int i = 0; i< 128; i++)
    {
        for(int j = 0; j< 64; j++)
        {
            ancient_pixel = image.getPixel(i, j );
            ancient_pixel.r += sunlight  ;
            ancient_pixel.g += sunlight ;
            ancient_pixel.b += sunlight ;

            image.setPixel(i, j, ancient_pixel );
        }
    }
    image.saveToFile("ressources/generated/character/character01.png");


    m_texture.loadFromFile("ressources/generated/character/character01.png");
    m_file ="ressources/generated/character/character01.png";
    m_sprite.setTexture(m_texture);
}

void My_Sprite::draw(int x, int y)
{
    m_x = x;
    m_y = y;
    if(m_total_animation_time != 0)
    {
        m_time1 = m_clock1.getElapsedTime();
        if(m_time1.asSeconds() > m_total_animation_time / m_animation_length)
        {
            m_clock1.restart();
            m_animation_rect.left += m_animation_width;
            if(m_animation_rect.left >= m_w)
            {
                m_animation_rect.left = 0;
            }
            m_sprite.setTextureRect(m_animation_rect);
        }


    }

    m_sprite.setPosition(m_x, m_y);
    m_app->draw(m_sprite);
}

void My_Sprite::draw_tile(int x, int y, int random)
{
    m_x = x;
    m_y = y;
    m_animation_rect.left = 128 * random;
    m_animation_rect.width = 128 ;
    m_sprite.setTextureRect(m_animation_rect);
    m_sprite.setPosition(m_x, m_y);
    m_app->draw(m_sprite);
    //cout<<" ra "<<animation_rect.left<<endl;
}

void My_Sprite::scale(float x_rate, float y_rate)
{
    m_sprite.scale(Vector2f(x_rate, y_rate));
    FloatRect  a= m_sprite.getGlobalBounds();
    m_w = a.width;
    m_h = a.height;
}

void My_Sprite::set_color(Color color_get)
{
    Image image1;
    FileLoader<Image>::loadFile(image1, m_file);

    Color ancient_pixel;
    Vector2u image_size;
    image_size= image1.getSize();
    for(unsigned int i = 0; i< image_size.x; i++)
    {
        for(unsigned int j = 0; j< image_size.y; j++)
        {
            ancient_pixel = image1.getPixel(i, j );
            if(ancient_pixel.r <= 252 && ancient_pixel.g <= 252 && ancient_pixel.b <= 252 )
            {
                ancient_pixel.r = color_get.r;
                ancient_pixel.g = color_get.g;
                ancient_pixel.b = color_get.b;
            }


            image1.setPixel(i, j, ancient_pixel );
        }
    }
    image1.saveToFile(m_file);
    m_texture.loadFromImage(image1);
    m_sprite.setTexture(m_texture);
}

void My_Sprite::add_color(int r, int g, int b, int alpha)
{
    m_sprite.setColor(Color(r, g, b, alpha));

}

bool My_Sprite::is_over()
{
    Vector2i a = Mouse::getPosition(*m_app);

    if( a.x >= m_x &&  a.x <= m_x  + m_w
            && a.y >= m_y   && a.y <= m_y  + m_h)
    {
        return true;
    }
    else return false;
}

int My_Sprite::get_w()
{
    return m_w;
}

int My_Sprite::get_h()
{
    return m_h;
}
