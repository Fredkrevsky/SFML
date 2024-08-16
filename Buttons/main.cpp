#include <SFML/Graphics.hpp>
#include "Controls.h"

using namespace sf;
Font font;

int main()
{
    if (!font.loadFromFile("arialmt.ttf")) return -1;

    RenderWindow window(VideoMode(800, 800), "SFML works!");
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(150);

    TButton button;
    button.setPos(400, 500);
    button.setSize(300, 75);
    button.setColor(Color::Green);
    button.setVisible(true);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (Mouse::isButtonPressed(sf::Mouse::Left)) {
                Vector2f pos = Vector2f(Mouse::getPosition(window));
                if (button.isPressed(pos)) {
                    button.onPress();
                }
                else {
                    button.onRelease();
                }
            }
            else {
                button.onRelease();
            }
        }

        window.clear();
        button.draw(window);
        window.display();
    }

    return 0;
}