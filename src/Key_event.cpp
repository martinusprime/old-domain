#include "Key_event.h"

Key_event_handler::Key_event_handler()
{
    key_action = std::map<sf::Keyboard::Key, Action>
    {
        {sf::Keyboard::Z, ACT_GO_UP},
        {sf::Keyboard::Up, ACT_GO_UP},
        {sf::Keyboard::D, ACT_GO_RIGHT},
        {sf::Keyboard::Right, ACT_GO_RIGHT},
        {sf::Keyboard::S, ACT_GO_DOWN},
        {sf::Keyboard::Down, ACT_GO_DOWN},
        {sf::Keyboard::Q, ACT_GO_LEFT},
        {sf::Keyboard::Left, ACT_GO_LEFT},
        {sf::Keyboard::T, ACT_ZOOM_IN},
        {sf::Keyboard::G, ACT_ZOOM_OUT}
    };
}

Key_event_handler::~Key_event_handler()
{
    //dtor
}


bool Key_event_handler::manage_key_event(const sf::Event &event, const sf::RenderWindow *app, Action &action, sf::Vector2i &mouse_vec)
{
    mouse_vec = sf::Mouse::getPosition(*app);

    if(event.type == sf::Event::KeyPressed)
    {
        if (key_action.count(event.key.code) == 0) {
            return false;
        }
        action = key_action[event.key.code];
        return true;
    }
    else if (event.type == sf::Event::Closed)
    {
        //TODO handle escape key ?
        action = ACT_CLOSE_APP;
        return true;
    }
    return false;
}
