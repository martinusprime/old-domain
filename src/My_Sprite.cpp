#include "My_Sprite.h"

My_Sprite::My_Sprite()
{
    total_animation_time =0;
}

My_Sprite::My_Sprite(const My_Sprite &other)
{
    total_animation_time =0;

    view1 = other.view1;
    file = other.file;
    app = other.app;
    x = other.x;
    y = other.y;
    w = other.w;
    h = other.h;
    event = other.event;
    texture = other.texture;

    /* sf::Sprite can not simply be copied, see "white square problem:
    http://www.sfml-dev.org/tutorials/2.1/graphics-sprite.php#the-white-square-problem */
    sprite = other.sprite;
    texture.loadFromFile(file.c_str());
    sprite.setTexture(texture);

    animation_width = other.animation_width;
    animation_length = other.animation_length;
    total_animation_time = other.total_animation_time;
    clock1 = other.clock1;
    time1 = other.time1;
    animation_rect = other.animation_rect;
}

My_Sprite::~My_Sprite()
{
    //dtor
}

void My_Sprite::init(RenderWindow *app_get, std::string file_get, View *view_get)
{
    total_animation_time =0;

    view1 = view_get;
    file = file_get;
    app = app_get;
    texture.loadFromFile(file.c_str());
	texture.setSmooth(true);
    sprite.setTexture(texture);

    FloatRect  a= sprite.getGlobalBounds();
    w = a.width;
    h = a.height;
}

sf::Sprite My_Sprite::get_sprite()
{
    return sprite;
}

void My_Sprite::init(RenderWindow *app_get, std::string file_get, View *view_get, int file_number)
{
    total_animation_time =0;

    view1 = view_get;
    app = app_get;
    int rand_limit = 3;
    srand(time(0));
    if(file_number != 0)
    {
        rand_limit = file_number;
    }

    int random = rand()% + rand_limit;
    stringstream ss;
    ss << random;
    file = file_get + ss.str() + ".png";
    cout<< file<<endl;
    ifstream file_check(file.c_str());
    while(file_check.is_open() == false && rand_limit != 1 )
    {
        rand_limit--;
        random = rand()% + rand_limit;
        ss.str("");
        ss.clear();
        ss << random;
        file = file_get +ss.str() + ".png";
        file_check.open(file.c_str());
        cout<< "file finally chosen "<<file<<endl;

    }
    if(file_check.is_open() == false && rand_limit == 1 )
    {
        texture.loadFromFile("ressources/empty.png");
    }
    else
    {
        texture.loadFromFile(file.c_str());
    }
	texture.setSmooth(true);
    sprite.setTexture(texture);

    FloatRect  a= sprite.getGlobalBounds();
    w = a.width;
    h = a.height;

}

void My_Sprite::init(RenderWindow *app_get, string file_get, View *view_get, int animation_width_get, int animation_length_get, float total_animation_time_get)
{
    view1 = view_get;
    file = file_get;
    app = app_get;
    texture.loadFromFile(file.c_str());
	texture.setSmooth(true);
    sprite.setTexture(texture);

    animation_width =animation_width_get;
    animation_length =animation_length_get;
    total_animation_time =total_animation_time_get;
    FloatRect  a= sprite.getGlobalBounds();
    w = a.width;
    h = a.height;
    animation_rect.left = 0;
    animation_rect.top = 0;
    animation_rect.width = w/animation_length;
    animation_rect.height = h;

    clock1.restart();

}


string My_Sprite::get_file()
{
    return file;
}

void My_Sprite::add_sprite(My_Sprite *added_sprite, string save_slot, int width)
{
    animation_rect.height = h;
    animation_rect.width = w;
    animation_rect.top = 0;
    animation_rect.left = 0;

    Image background;
    background.loadFromFile(file.c_str());
    Image background2;
    background2.loadFromFile(added_sprite->get_file().c_str());

    sf::Image image;
     image.create(width, h);

    image.copy(background, 0, 0,  IntRect(0, 0, w, h));
    image.copy(background2, 0, 0, IntRect(0, 0, w, h), true);

    image.saveToFile(save_slot.c_str());


    texture.loadFromFile(save_slot.c_str());
    file = save_slot.c_str();
    sprite.setTexture(texture);
}

void My_Sprite::add_sprite(My_Sprite *added_sprite, int sunlight_get)
{

    animation_rect.height = 64;
    animation_rect.width = 128;
    animation_rect.top = 0;
    animation_rect.left = 0;
    int sunlight = - sunlight_get* 17;

    Texture texture2;

    Image background;
    background.loadFromFile(file.c_str());
    Image background2;
    background2.loadFromFile(added_sprite->get_file().c_str());

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


    texture.loadFromFile("ressources/generated/character/character01.png");
    file ="ressources/generated/character/character01.png";
    sprite.setTexture(texture);
}

void My_Sprite::draw(int x_get, int y_get)
{
    x = x_get;
    y = y_get;
    if(total_animation_time != 0)
    {
        time1 = clock1.getElapsedTime();
        if(time1.asSeconds() > total_animation_time / animation_length)
        {
            clock1.restart();
            animation_rect.left += animation_width;
            if(animation_rect.left >= w)
            {
                animation_rect.left = 0;
            }
            sprite.setTextureRect(animation_rect);
        }


    }

    sprite.setPosition(x, y);
    app->draw(sprite);

}
void My_Sprite::draw_tile(int x_get, int y_get, int random)
{
    x = x_get;
    y = y_get;
    animation_rect.left = 128 * random;
    animation_rect.width = 128 ;
    sprite.setTextureRect(animation_rect);
    sprite.setPosition(x, y);
    app->draw(sprite);
                //cout<<" ra "<<animation_rect.left<<endl;

}

void My_Sprite::scale(float x_rate, float y_rate)
{
    sprite.scale(Vector2f(x_rate, y_rate));
    FloatRect  a= sprite.getGlobalBounds();
    w = a.width;
    h = a.height;
}
void My_Sprite::set_color(Color color_get)
{
    Image image1;
    image1.loadFromFile(file.c_str());

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
    image1.saveToFile(file.c_str());
    texture.loadFromImage(image1);
    sprite.setTexture(texture);
}

void My_Sprite::add_color(int r, int g, int b, int alpha)
{
    sprite.setColor(Color(r, g, b, alpha));

}
bool My_Sprite::is_over()
{
    Vector2i a = Mouse::getPosition(*app);

    if( a.x >= x &&  a.x <= x  + w
            && a.y >= y   && a.y <= y  + h)
    {
        return true;
    }
    else return false;
}

int My_Sprite::get_w()
{
    return w;
}

int My_Sprite::get_h()
{
    return h;
}
