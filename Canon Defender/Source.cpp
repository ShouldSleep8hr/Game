#include <SFML/Graphics.hpp>
#include <time.h>
#include "projectile.h"
#include "enemy.h"
#include "item.h"
#include <vector>
using namespace sf;

const float PI = 3.141592654;
std::vector<Enemy*> enemies;
std::vector<Projectile*> projectiles;
std::vector<Item*> items;
std::string changeProj= "images/bullet1.png";
void spawnEnemy() {
    int randLoc = rand() % 2, enmType = rand() % 3;
    sf::Vector2f enemyPos;
    float speedE;
    Enemy* enemy = new Enemy();
    switch (randLoc) {
    case 0: enemyPos = sf::Vector2f(0, rand() % 600);
        speedE = 1;
        if (enmType == 0) { speedE *= 0.1; enemy->init("images/enemy1-1.png", enemyPos, speedE, 1); }
        else if (enmType == 1) { speedE *= 0.2; enemy->init("images/enemy1-2.png", enemyPos, speedE, 2); }
        else if (enmType == 2) { speedE *= 0.3; enemy->init("images/enemy1-3.png", enemyPos, speedE, 3); }
        break;
    case 1: enemyPos = sf::Vector2f(1600, rand() % 600);
        speedE = -1;
        if (enmType == 0) { speedE *= 0.1; enemy->init("images/enemy1-1.png", enemyPos, speedE, 1); }
        else if (enmType == 1) { speedE *= 0.2; enemy->init("images/enemy1-2.png", enemyPos, speedE, 2); }
        else if (enmType == 2) { speedE *= 0.3; enemy->init("images/enemy1-3.png", enemyPos, speedE, 3); }
        break;
    default: {} break;
    }
    enemies.push_back(enemy);
}
void spawnProj(sf::Vector2f projPos, float projAngle, bool direct) {
    //int projType = rand() % 3;
    //sf::Vector2f projPos;
    //float speedE;
    Projectile* projectile = new Projectile();
    /*switch (projType) {
    case 0:
        //speedE = 1;
        if (projType == 0) { speedE *= 0.1; enemy->init("images/enemy1-1.png", enemyPos, speedE, 1); }
        else if (enmType == 1) { speedE *= 0.2; enemy->init("images/enemy1-2.png", enemyPos, speedE, 2); }
        else if (enmType == 2) { speedE *= 0.3; enemy->init("images/enemy1-3.png", enemyPos, speedE, 3); }
        break;
    case 1: //projPos = sf::Vector2f(1600, rand() % 600);
        //speedE = -1;
        if (enmType == 0) { speedE *= 0.1; enemy->init("images/enemy1-1.png", enemyPos, speedE, 1); }
        else if (enmType == 1) { speedE *= 0.2; enemy->init("images/enemy1-2.png", enemyPos, speedE, 2); }
        else if (enmType == 2) { speedE *= 0.3; enemy->init("images/enemy1-3.png", enemyPos, speedE, 3); }
        break;
    default: {} break;
    }*/
    projectile->initP(changeProj, projPos, projAngle, direct);
    projectiles.push_back(projectile);
}
void spawnItem() {
    int randLocI = rand() % 2, itemType = rand() % 3;
    sf::Vector2f itemPos;
    float speedI, randSpeed = (float)(rand()%4);
    if (randSpeed == 0) randSpeed = 1;
    Item* item = new Item();
    switch (randLocI) {
    case 0: itemPos = sf::Vector2f(0, rand() % 300);
        speedI = 1;
        if (itemType == 0) { speedI *= 0.1 * randSpeed; item->initI("images/health.png", itemPos, speedI, 2); }
        else if (itemType == 1) { speedI *= 0.1 * randSpeed; item->initI("images/fire.png", itemPos, speedI, 1); }
        else if (itemType == 2) { speedI *= 0.1 * randSpeed; item->initI("images/ice.png", itemPos, speedI, 1); }
        break;
    case 1: itemPos = sf::Vector2f(1600, rand() % 300);
        speedI = -1;
        if (itemType == 0) { speedI *= 0.1 * randSpeed; item->initI("images/health.png", itemPos, speedI, 2); }
        else if (itemType == 1) { speedI *= 0.1 * randSpeed; item->initI("images/fire.png", itemPos, speedI, 1); }
        else if (itemType == 2) { speedI *= 0.1 * randSpeed; item->initI("images/ice.png", itemPos, speedI, 1); }
        break;
    default: {} break;
    }
    items.push_back(item);
}
int main()
{
    srand(time(NULL));
    const sf::FloatRect viewRect(0.0f, 0.0f, 1600.0f, 600.0f);

    sf::RenderWindow window(sf::VideoMode(1600, 600), "Canon Defender");
    sf::RectangleShape base(sf::Vector2f(100, 100));

    window.setFramerateLimit(120);
    window.setVerticalSyncEnabled(false);
    window.setKeyRepeatEnabled(false);

    base.setPosition(sf::Vector2f(825.f, 485.f));
    base.setSize(sf::Vector2f(100, 100));

    sf::Texture canon_base, canon, Tbg1;
    Tbg1.loadFromFile("images/bg1.png");
    canon_base.loadFromFile("images/canon_base.png");
    canon.loadFromFile("images/canon.png");

    sf::Sprite canon_base2, canon2, bg1;
    bg1.setTexture(Tbg1);
    canon_base2.setTexture(canon_base);
    canon_base2.setPosition(sf::Vector2f(827.f, 429.f));
    canon_base2.setScale(sf::Vector2f(0.2f, 0.2f));
    canon2.setTexture(canon);
    canon2.setPosition(sf::Vector2f(875.f, 450.f));
    canon2.setScale(sf::Vector2f(0.2f, 0.2f));

    sf::Clock deltaClock, clock;
    const sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time currenTime = sf::Time::Zero, prevTime = sf::Time::Zero, prevTimeI = sf::Time::Zero;

    //std::vector<Projectile> projectiles;

    bool di = 0; int shoot = 5;
    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += deltaClock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                case sf::Keyboard::Space:
                    //projectiles.push_back(Projectile(canon2.getPosition(), canon2.getRotation() * PI / 180, di));
                    spawnProj(canon2.getPosition(), canon2.getRotation() * PI / 180, di);
                    if (changeProj == "images/bullet-fire.png" || changeProj == "images/bullet-ice.png") shoot--;
                    if (shoot <= 0) changeProj = "images/bullet1.png";
                    break;
                default: {} break;
                }
                break;
            default: {} break;
            }
        }
        currenTime += dt;
        if (currenTime >= prevTime + sf::seconds(1.0f)) {
            spawnEnemy();
            prevTime = currenTime;
        }
        if (currenTime >= prevTimeI + sf::seconds(3.0f)) {
            spawnItem();
            prevTimeI = currenTime;
        }

        while (timeSinceLastUpdate > timePerFrame) {
            timeSinceLastUpdate -= timePerFrame;
            // update projectile
            {
                for (int i = 0; i < projectiles.size(); i++) {
                    Projectile* proj = projectiles[i];
                    proj->update(timePerFrame);
                    if (!viewRect.intersects(proj->getHitboxP())) { projectiles.erase(projectiles.begin()) + i; delete(proj); }
                }
                //projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [](Projectile const& p) { return p.getCanBeRemoved(); }), projectiles.end());
            }
            // update enemies
            {
                for (int i = 0; i < enemies.size(); i++) {
                    Enemy* enemy = enemies[i];
                    enemy->update2(timePerFrame);
                    for (int j = 0; j < projectiles.size(); j++) {
                        Projectile* proj2 = projectiles[j];
                        if (proj2->getHitboxP().intersects(enemy->getHitbox()) == true) {
                            enemy->minusHP();
                            //proj2.destroy();
                            projectiles.erase(projectiles.begin()) + j;
                            break;
                        }
                    }
                    //projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [](Projectile const& p) { return p.getCanBeRemoved(); }), projectiles.end());
                    if (enemy->getHP() <= 0) {
                        enemies.erase(enemies.begin() + i);
                        break;
                    }
                    if (enemy->getSprite().getPosition().x > 825 && enemy->getSpeed() > 0) {
                        enemies.erase(enemies.begin() + i);
                        delete(enemy);
                    }
                    else if (enemy->getSprite().getPosition().x < 925 && enemy->getSpeed() < 0) {
                        enemies.erase(enemies.begin() + i);
                        delete(enemy);
                    }
                }
            }
            // update item
            {
                for (int i = 0; i < items.size(); i++) {
                    Item* item = items[i];
                    item->update3(timePerFrame);
                    for (int j = 0; j < projectiles.size(); j++) {
                        Projectile* proj3 = projectiles[j];
                        if (proj3->getHitboxP().intersects(item->getHitboxI()) == true) {
                            item->minusHPI();
                            projectiles.erase(projectiles.begin()) + j;
                            break;
                        }
                    }
                    if (item->getHPI() <= 0) {
                        if (item->getitemName() == "images/fire.png") { changeProj = "images/bullet-fire.png"; shoot = 5; }
                        else if (item->getitemName() == "images/ice.png") { changeProj = "images/bullet-ice.png"; shoot = 5; }
                        items.erase(items.begin() + i);
                        break;
                    }
                    if (item->getSpriteI().getPosition().x > 1600 && item->getSpeedI() > 0) {
                        items.erase(items.begin() + i);
                        delete(item);
                    }
                    else if (item->getSpriteI().getPosition().x < 0 && item->getSpeedI() < 0) {
                        items.erase(items.begin() + i);
                        delete(item);
                    }
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            canon2.setScale(sf::Vector2f(0.2f, 0.2f));
            canon2.setRotation(0.f);
            di = 0;
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            canon2.setScale(sf::Vector2f(-0.2f, 0.2f));
            canon2.setRotation(0.f);
            di = 1;
        }
        if (di == 1) {
            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                //if (canon2.getRotation() >= 0 && canon2.getRotation() <= 80) 
                canon2.rotate(-0.1f);
                //if (canon2.getRotation() < 0 || canon2.getRotation() > 80) canon2.setRotation(0.f);
            }
            else if (Keyboard::isKeyPressed(Keyboard::Up)) {
                //if (canon2.getRotation() >= 0 && canon2.getRotation() <= 80) 
                canon2.rotate(0.1f);
                //if (canon2.getRotation() < 0 || canon2.getRotation() > 80) canon2.setRotation(80.f);
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
        window.draw(bg1);
        /*for (std::size_t i = 0; i < projectiles.size(); ++i) {
            window.draw(projectiles[i]);
        }*/
        for (Projectile* projectile : projectiles) window.draw(projectile->getSpriteP());
        for (Enemy* enemy : enemies) window.draw(enemy->getSprite());
        for (Item* item : items) window.draw(item->getSpriteI());
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
#include "enemy.h"
#include <vector>
using namespace sf;

const float PI = 3.141592654;
std::vector<Enemy*> enemies;
void spawnEnemy() {
    int randLoc = rand() % 2, enmType = rand()%3;
    sf::Vector2f enemyPos;
    float speedE;
    Enemy* enemy = new Enemy();
    switch (randLoc) {
    case 0: enemyPos = sf::Vector2f(0, rand() % 600);
            speedE = 1;
            if (enmType == 0) { speedE *= 0.1; enemy->init("images/enemy1-1.png", enemyPos, speedE, 1); }
            else if (enmType == 1) { speedE *= 0.2; enemy->init("images/enemy1-2.png", enemyPos, speedE, 2); }
            else if (enmType == 2) { speedE *= 0.3; enemy->init("images/enemy1-3.png", enemyPos, speedE, 3); }
            break;
    case 1: enemyPos = sf::Vector2f(1600, rand() % 600);
            speedE = -1;
            if (enmType == 0) { speedE *= 0.1; enemy->init("images/enemy1-1.png", enemyPos, speedE, 1); }
            else if (enmType == 1) { speedE *= 0.2; enemy->init("images/enemy1-2.png", enemyPos, speedE, 2); }
            else if (enmType == 2) { speedE *= 0.3; enemy->init("images/enemy1-3.png", enemyPos, speedE, 3); }
            break;
    default: {} break;
    }
    enemies.push_back(enemy);
}
int main()
{
    srand(time(NULL));
    const sf::FloatRect viewRect(0.0f, 0.0f, 1600.0f, 600.0f);

    sf::RenderWindow window(sf::VideoMode(1600, 600), "Canon Defender");
    sf::RectangleShape base(sf::Vector2f(100, 100));

    window.setFramerateLimit(120);
    window.setVerticalSyncEnabled(false);
    window.setKeyRepeatEnabled(false);

    base.setPosition(sf::Vector2f(825.f, 485.f));
    base.setSize(sf::Vector2f(100, 100));

    sf::Texture canon_base, canon, Tbg1;
    Tbg1.loadFromFile("images/bg1.png");
    canon_base.loadFromFile("images/canon_base.png");
    canon.loadFromFile("images/canon.png");

    sf::Sprite canon_base2, canon2, bg1;
    bg1.setTexture(Tbg1);
    canon_base2.setTexture(canon_base);
    canon_base2.setPosition(sf::Vector2f(827.f, 429.f));
    canon_base2.setScale(sf::Vector2f(0.2f, 0.2f));
    canon2.setTexture(canon);
    canon2.setPosition(sf::Vector2f(875.f, 450.f));
    canon2.setScale(sf::Vector2f(0.2f, 0.2f));

    sf::Clock deltaClock, clock;
    const sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time currenTime = sf::Time::Zero, prevTime = sf::Time::Zero;

    std::vector<Projectile> projectiles;

    bool di = 0;
    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += deltaClock.restart();

        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type) {
            case sf::Event::Closed: { window.close(); } break;
            case sf::Event::KeyPressed: {
                switch (event.key.code) {
                case sf::Keyboard::Space: {
                    projectiles.push_back(Projectile(canon2.getPosition(), canon2.getRotation() * PI / 180, di));
                } break; default: {} break;
                }
            } break;
            default: {} break;
            }
        }
        currenTime += dt;
        if (currenTime >= prevTime + sf::seconds(1.0f)) {
            spawnEnemy();
            prevTime = currenTime;
        }

        while (timeSinceLastUpdate > timePerFrame) {
            timeSinceLastUpdate -= timePerFrame;
            // update projectile
            {
                for (std::size_t i = 0; i < projectiles.size(); ++i) {
                    Projectile& proj = projectiles[i];
                    proj.update(timePerFrame);
                    if (!viewRect.intersects(proj.getBoundingBox())) { proj.destroy(); }
                }
                projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [](Projectile const& p) { return p.getCanBeRemoved(); }), projectiles.end());
            }
            // update enemies
            {
                for (int i = 0; i < enemies.size(); i++) {
                    Enemy* enemy = enemies[i];
                    enemy->update2(timePerFrame);
                    for (std::size_t j = 0; j < projectiles.size(); ++j) {
                        Projectile& proj2 = projectiles[j];
                        if (proj2.getBoundingBox().intersects(enemy->getHitbox()) == true) {
                            enemy->minusHP();
                            proj2.destroy();
                            break;
                        }
                    }
                    projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(), [](Projectile const& p) { return p.getCanBeRemoved(); }), projectiles.end());
                    if (enemy->getHP() <= 0) {
                        enemies.erase(enemies.begin() + i);
                        break;
                    }
                    if (enemy->getSprite().getPosition().x > 825 && enemy->getSpeed() > 0) {
                        enemies.erase(enemies.begin() + i);
                        delete(enemy);
                    }
                    else if(enemy->getSprite().getPosition().x < 925 && enemy->getSpeed() < 0){
                        enemies.erase(enemies.begin() + i);
                        delete(enemy);
                    }
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Right)) {
            canon2.setScale(sf::Vector2f(0.2f, 0.2f));
            canon2.setRotation(0.f);
            di = 0;
        }
        if (Keyboard::isKeyPressed(Keyboard::Left)) {
            canon2.setScale(sf::Vector2f(-0.2f, 0.2f));
            canon2.setRotation(0.f);
            di = 1;
        }
        if (di == 1) {
            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                //if (canon2.getRotation() >= 0 && canon2.getRotation() <= 80) 
                canon2.rotate(-0.1f);
                //if (canon2.getRotation() < 0 || canon2.getRotation() > 80) canon2.setRotation(0.f);
            }
            else if (Keyboard::isKeyPressed(Keyboard::Up)) {
                //if (canon2.getRotation() >= 0 && canon2.getRotation() <= 80) 
                canon2.rotate(0.1f);
                //if (canon2.getRotation() < 0 || canon2.getRotation() > 80) canon2.setRotation(80.f);
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
        window.draw(bg1);
        for (std::size_t i = 0; i < projectiles.size(); ++i) {
            window.draw(projectiles[i]);
        }
        for (Enemy* enemy : enemies) window.draw(enemy->getSprite());
        window.draw(canon2);
        window.draw(canon_base2);
        window.draw(base);
        window.display();
    }

    return EXIT_SUCCESS;
}*/