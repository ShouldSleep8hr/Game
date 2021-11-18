#include <SFML/Graphics.hpp>
#include <time.h>
#include "projectile.h"
using namespace sf;

int main()
{
    const sf::FloatRect viewRect(0.0f, 0.0f, 800.0f, 600.0f);

    sf::RenderWindow window(sf::VideoMode(1600, 600), "Canon Defender");
    sf::RectangleShape base(sf::Vector2f(100, 100));

    window.setFramerateLimit(120);
    window.setVerticalSyncEnabled(false);
    window.setKeyRepeatEnabled(false);

    base.setPosition(sf::Vector2f(825.f, 485.f));
    base.setSize(sf::Vector2f(100, 100));
    
    sf::Texture canon_base, canon, enemy;
    canon_base.loadFromFile("images/canon_base.png");
    canon.loadFromFile("images/canon.png");
    enemy.loadFromFile("images/enemy.png");
    sf::Sprite canon_base2, canon2, enemy2;
    canon_base2.setTexture(canon_base);
    canon_base2.setPosition(sf::Vector2f(827.f, 429.f));
    canon_base2.setScale(sf::Vector2f(0.2f, 0.2f));
    canon2.setTexture(canon);
    canon2.setPosition(sf::Vector2f(875.f, 450.f));
    //canon2.setRotation(-30.f);
    canon2.setScale(sf::Vector2f(0.2f, 0.2f));

    sf::Clock deltaClock;
    const sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    std::vector<Projectile> projectiles;

    bool di = 0, bul = 0; int bx, by;
    while (window.isOpen())
    {
        timeSinceLastUpdate += deltaClock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::Closed: { window.close(); } break;
            case sf::Event::KeyPressed: {
                switch (event.key.code) {
                case sf::Keyboard::Space: {
                    if (di == 0) projectiles.push_back(Projectile(canon2.getPosition(), canon2.getRotation(), di));
                    else projectiles.push_back(Projectile(canon2.getPosition(), canon2.getRotation(), di));
                    printf("%f %f\n",canon2.getRotation(), cos(canon2.getRotation()));
                } break; default: {} break;
                }
            } break;
            default: {} break;
            }
        }

        while (timeSinceLastUpdate > timePerFrame) {
            timeSinceLastUpdate -= timePerFrame;
            // update projectiles
            {
                for (std::size_t i = 0; i < projectiles.size(); ++i) {
                    Projectile& proj = projectiles[i];
                    proj.update(timePerFrame);
                    //if (!viewRect.intersects(proj.getBoundingBox())) { proj.destroy(); }
                }
                //projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [](Projectile const& p) { return p.getCanBeRemoved(); }), projectiles.end());
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            canon2.setScale(sf::Vector2f(0.2f, 0.2f));
            di = 0; 
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)) { 
            canon2.setScale(sf::Vector2f(-0.2f, 0.2f));
            //canon2.rotate(180.f);
            di = 1; 
        }
        if (di == 1) {
            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                canon2.rotate(-0.1f);
                
            }
            else if (Keyboard::isKeyPressed(Keyboard::Up)) {
                canon2.rotate(0.1f);
                
            }
        }
        else {
            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                canon2.rotate(0.1f);
                
            }
            else if (Keyboard::isKeyPressed(Keyboard::Up)) {
                canon2.rotate(-0.1f);
                
            }
        }
        window.clear(sf::Color::Black);
        for (std::size_t i = 0; i < projectiles.size(); ++i) {
            window.draw(projectiles[i]);
        }
        window.draw(canon2);
        window.draw(canon_base2);
        window.draw(base);
        window.display();
    }

    return EXIT_SUCCESS;
}

/*#include <SFML/Graphics.hpp>
#include <time.h>
#include "projectile.h"
using namespace sf;

int main()
{
    const sf::FloatRect viewRect(0.0f, 0.0f, 800.0f, 600.0f);

    sf::RenderWindow window(sf::VideoMode(1600, 600), "Canon Defender");
    sf::RectangleShape base(sf::Vector2f(100, 100));
    sf::CircleShape bullet(10);

    window.setFramerateLimit(120);
    window.setVerticalSyncEnabled(false);
    window.setKeyRepeatEnabled(false);

    base.setPosition(sf::Vector2f(825.f, 485.f));
    base.setSize(sf::Vector2f(100, 100));
    bullet.setPosition(sf::Vector2f(850.f, 420.f));
    sf::Texture canon[2], enemy;
    canon[0].loadFromFile("images/canon_r.png");
    canon[1].loadFromFile("images/canon_l.png");
    enemy.loadFromFile("images/enemy.png");
    sf::Sprite canon2[2], enemy2;
    canon2[0].setTexture(canon[0]);
    canon2[0].setPosition(sf::Vector2f(800.f, 400.f));
    canon2[0].setScale(sf::Vector2f(0.2f, 0.2f));
    canon2[1].setTexture(canon[1]);
    canon2[1].setPosition(sf::Vector2f(800.f, 400.f));
    canon2[1].setScale(sf::Vector2f(0.2f, 0.2f));

    sf::Clock deltaClock;
    const sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    std::vector<Projectile> projectiles;

    bool di = 1, bul = 0; int bx, by;
    while (window.isOpen())
    {
        timeSinceLastUpdate += deltaClock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            //if (event.type == sf::Event::Closed) window.close();

            switch (event.type) {
                case sf::Event::Closed: { window.close(); } break;
                case sf::Event::KeyPressed: { 
                    switch (event.key.code) {
                    case sf::Keyboard::Space: {
                            const float angle = atan2(canon2[di].getRotation() - canon2[di].getPosition().y, canon2[di].getRotation() - canon2[di].getPosition().x);
                            /*const sf::Vector2f center(viewRect.left + viewRect.width / 2, viewRect.top + viewRect.height / 2);
                            const sf::Vector2f mousePos(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
                            const float angle = atan2(mousePos.y - center.y, mousePos.x - center.x);
                            projectiles.push_back(Projectile(canon2[di].getPosition(), angle));
                        } break; default: {} break;
                    } 
                } break;
                default: {} break;
            }
        }

        while (timeSinceLastUpdate > timePerFrame) {
            timeSinceLastUpdate -= timePerFrame;
            // update projectiles
            {
                for (std::size_t i = 0; i < projectiles.size(); ++i) {
                    Projectile& proj = projectiles[i];
                    proj.update(timePerFrame);
                    if (!viewRect.intersects(proj.getBoundingBox())) { proj.destroy(); }
                }
                projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [](Projectile const& p) { return p.getCanBeRemoved(); }), projectiles.end());
            }
        }

        window.clear(sf::Color::Black);
        
        if(di == 1) window.draw(canon2[1]);
        else window.draw(canon2[0]);

        if (Keyboard::isKeyPressed(Keyboard::Right))  di = 0;
        if (Keyboard::isKeyPressed(Keyboard::Left)) di = 1;
        if (di == 1) { 
            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                canon2[1].rotate(-0.1f); 
                canon2[1].move(sf::Vector2f(0.f, 0.15f));
            }
            else if (Keyboard::isKeyPressed(Keyboard::Up)) { 
                canon2[1].rotate(0.1f); 
                canon2[1].move(sf::Vector2f(0.f, -0.15f));
            }
        }
        else {
            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                canon2[0].rotate(0.1f);
                canon2[0].move(sf::Vector2f(0.1f, -0.02f));
            }
            else if (Keyboard::isKeyPressed(Keyboard::Up)) {
                canon2[0].rotate(-0.1f);
                canon2[0].move(sf::Vector2f(-0.1f, 0.02f));
            }
        }
        /*if (Keyboard::isKeyPressed(Keyboard::Space)) {
            bul = 1;
            bullet.setPosition(canon2[0].getPosition());
        }
        if (bul == 1 && di == 1) { 
            window.draw(bullet); 
            bullet.move(sf::Vector2f(-0.1f, +0.1f));
        }
        else if (bul == 1 && di == 0) {
            window.draw(bullet);
            bullet.move(sf::Vector2f(+0.1f, +0.1f));
        }
        window.draw(base);
        //window.clear();
        for (std::size_t i = 0; i < projectiles.size(); ++i) {
            window.draw(projectiles[i]);
        }
        window.display();
    }

    return EXIT_SUCCESS;
}*/

/*int main() {
    const sf::FloatRect viewRect(0.0f, 0.0f, 800.0f, 600.0f);

    sf::RenderWindow window(sf::VideoMode(viewRect.width, viewRect.height), "Test");
    window.setFramerateLimit(120);
    window.setVerticalSyncEnabled(false);
    window.setKeyRepeatEnabled(false);

    sf::Clock deltaClock;
    const sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    std::vector<Projectile> projectiles;

    while (window.isOpen()) {

        timeSinceLastUpdate += deltaClock.restart();

        // process events
        {
            sf::Event evt;
            while (window.pollEvent(evt)) {
                switch (evt.type) {
                case sf::Event::Closed: { window.close(); } break;
                    // shoot with left mouse button
                case sf::Event::MouseButtonPressed: { switch (evt.mouseButton.button) {
                case sf::Mouse::Button::Left: {
                    const sf::Vector2f center(viewRect.left + viewRect.width / 2, viewRect.top + viewRect.height / 2);
                    const sf::Vector2f mousePos(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
                    const float angle = atan2(mousePos.y - center.y, mousePos.x - center.x);
                    projectiles.push_back(Projectile(center, angle));
                } break; default: {} break;
                } } break;
                default: {} break;
                }
            }
        }

        // update
        {
            while (timeSinceLastUpdate > timePerFrame) {
                timeSinceLastUpdate -= timePerFrame;
                // update projectiles
                {
                    for (std::size_t i = 0; i < projectiles.size(); ++i) {
                        Projectile& proj = projectiles[i];
                        proj.update(timePerFrame);
                        if (!viewRect.intersects(proj.getBoundingBox())) { proj.destroy(); }
                    }
                    projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [](Projectile const& p) { return p.getCanBeRemoved(); }), projectiles.end());
                }
            }
        }

        // render
        {
            window.clear();
            for (std::size_t i = 0; i < projectiles.size(); ++i) {
                window.draw(projectiles[i]);
            }
            window.display();
        }

    }

    return EXIT_SUCCESS;
}*/