#include <SFML/Graphics.hpp>
#include <cmath> // For sqrt

int main()
{
    sf::RenderWindow window(sf::VideoMode(400, 400), "Tree Drawing");

    sf::RectangleShape trunk(sf::Vector2f(30.f, 100.f));
    trunk.setFillColor(sf::Color(139, 69, 19));
    trunk.setPosition(185.f, 250.f);

    sf::RectangleShape ground(sf::Vector2f(400.f, 50.f));
    ground.setFillColor(sf::Color(0, 128, 0));
    ground.setPosition(0.f, 350.f);

    sf::CircleShape leaves1(60.f);
    leaves1.setFillColor(sf::Color::Green);
    leaves1.setPosition(140.f, 180.f);

    sf::CircleShape leaves2(50.f);
    leaves2.setFillColor(sf::Color::Green);
    leaves2.setPosition(100.f, 190.f);

    sf::CircleShape leaves3(50.f);
    leaves3.setFillColor(sf::Color::Green);
    leaves3.setPosition(200.f, 190.f);

    sf::CircleShape leaves4(60.f);
    leaves4.setFillColor(sf::Color::Green);
    leaves4.setPosition(140.f, 150.f);

    sf::CircleShape sun(50.f);
    sun.setFillColor(sf::Color::Yellow);
    sun.setPosition(10.f, 10.f);

    bool sunIsYellow = true;
    bool backgroundIsCyan = true;

    sf::Vector2f cloudBasePosition(200.f, 50.f);

    sf::CircleShape cloud1(40.f);
    cloud1.setFillColor(sf::Color::White);
    cloud1.setPosition(cloudBasePosition.x, cloudBasePosition.y);

    sf::CircleShape cloud2(30.f);
    cloud2.setFillColor(sf::Color::White);
    cloud2.setPosition(cloudBasePosition.x - 40.f, cloudBasePosition.y + 10.f);

    sf::CircleShape cloud3(30.f);
    cloud3.setFillColor(sf::Color::White);
    cloud3.setPosition(cloudBasePosition.x + 60.f, cloudBasePosition.y + 10.f);

    sf::CircleShape cloud4(40.f);
    cloud4.setFillColor(sf::Color::White);
    cloud4.setPosition(cloudBasePosition.x, cloudBasePosition.y - 30.f);

    // Function to move the cloud towards a target
    auto moveTowards = [](sf::Vector2f current, sf::Vector2f target, float speed) {
        sf::Vector2f direction = target - current;
        float magnitude = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        if (magnitude > 0.f) {
            direction /= magnitude; // Normalize the direction vector
        }

        return current + direction * speed;
        };

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

                if (sun.getGlobalBounds().contains(mousePos))
                {
                    if (sunIsYellow)
                    {
                        sun.setFillColor(sf::Color::Red);
                    }
                    else
                    {
                        sun.setFillColor(sf::Color::Yellow);
                    }
                    sunIsYellow = !sunIsYellow;
                    backgroundIsCyan = !backgroundIsCyan;
                }
            }
        }

        sf::Vector2i mousePosition = sf::Mouse::getPosition(window); // Get the mouse position
        sf::Vector2f targetPosition(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

        float speed = 0.05f; // Control how fast the cloud moves
        cloudBasePosition = moveTowards(cloudBasePosition, targetPosition, speed);

        // Update individual cloud parts' positions
        cloud1.setPosition(cloudBasePosition.x, cloudBasePosition.y);
        cloud2.setPosition(cloudBasePosition.x - 40.f, cloudBasePosition.y + 10.f);
        cloud3.setPosition(cloudBasePosition.x + 60.f, cloudBasePosition.y + 10.f);
        cloud4.setPosition(cloudBasePosition.x, cloudBasePosition.y - 30.f);

        if (backgroundIsCyan)
            window.clear(sf::Color::Cyan);
        else
            window.clear(sf::Color(0, 0, 139));

        window.draw(trunk);
        window.draw(ground);
        window.draw(leaves1);
        window.draw(leaves2);
        window.draw(leaves3);
        window.draw(leaves4);
        window.draw(sun);
        window.draw(cloud1);
        window.draw(cloud2);
        window.draw(cloud3);
        window.draw(cloud4);

        window.display();
    }

    return 0;
}
