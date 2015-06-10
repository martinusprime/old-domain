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
        {sf::Keyboard::G, ACT_ZOOM_OUT},
		{sf::Keyboard::C, ACT_ROTATE_RIGHT},
		{sf::Keyboard::V, ACT_ROTATE_LEFT}
    };
}

Key_event_handler::~Key_event_handler()
{
    //dtor
}


bool Key_event_handler::manage_key_event(const sf::Event &event, Action &action)
{
    switch(event.type) {
    case sf::Event::KeyPressed:
        if (key_action.count(event.key.code) == 0) {
            return false;
        }
        action = key_action[event.key.code];
        break;
    case sf::Event::Closed:
        //TODO handle escape key ?
        action = ACT_CLOSE_APP;
        break;
    case sf::Event::MouseWheelMoved:
        if (event.mouseWheel.delta < 0) {
            action = ACT_ZOOM_OUT;
        }
        else
        {
            action = ACT_ZOOM_IN;
        }
        break;
    default:
        return false;
    }

    //event handled
    return true;
}

void Key_event_handler::get_mouse_position(const sf::RenderWindow *app, sf::Vector2i &mouse_vec)
{
	mouse_vec = sf::Mouse::getPosition(*app);
}
		
bool Key_event_handler::manage_mouse_click(const sf::Event &event, enum sf::Mouse::Button &click)
{
	switch (event.type) {
	case sf::Event::MouseButtonPressed:
		click = event.mouseButton.button;
		break;
	default:
		return false;
	}

	//event handled
	return true;
}

