/*#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1180, 600), "Tyoing", sf::Style::None);
    sf::Font font;
    if (!font.loadFromFile("font/Minecraftia-Regular.ttf"))
        return EXIT_FAILURE;

    sf::Event event;
    sf::String playerInput;
    sf::Text playerText("", font);
    playerText.setPosition(60, 300);
    playerText.setFillColor(sf::Color::White);
    playerText.setCharacterSize(50);

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode < 128)
                {
                    playerInput += event.text.unicode;
                    playerText.setString(playerInput);
                }
            }
            window.clear();
        }
        window.draw(playerText);
        window.display();
    }
    return 0;
}*/

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include "projectile.h"
#include "enemy.h"
#include "item.h"
#include "Menu.h"
#include "ScoreBoard.h"
#include <vector>
#include <sstream>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;
using namespace sf;
const float PI = 3.141592654;
std::vector<Enemy*> enemies;
std::vector<Projectile*> projectiles;
std::vector<Item*> items;
std::string changeProj= "images/bullet1.png";

void spawnEnemy(int level, bool redT) {
    int randLoc = rand() % 2, enmType = rand() % 4;
    sf::Vector2f enemyPos;
    float speedE, randSpeedE = (float)(rand() % 4);
    if (randSpeedE == 0) randSpeedE = 1;
    Enemy* enemy = new Enemy();
    if (level == 0) {
        switch (randLoc) {
        case 0: enemyPos = sf::Vector2f(0, (rand() % 50) + 470);
            speedE = 1;
            if (enmType == 0) { speedE *= 0.05 * randSpeedE; enemy->init("images/enemy1-1.png", enemyPos, speedE, 1); }
            else if (enmType == 1) { speedE *= 0.05 * randSpeedE; enemy->init("images/enemy1-2.png", enemyPos, speedE, 2); }
            else if (enmType == 2) { speedE *= 0.05 * randSpeedE; enemy->init("images/enemy1-3.png", enemyPos, speedE, 3); }
            else if (enmType == 3) {
                enemyPos = sf::Vector2f(0, rand() % 350);
                speedE *= 0.05 * randSpeedE; enemy->init("images/fly-enemy1-1.png", enemyPos, speedE, 1);
            }
            break;
        case 1: enemyPos = sf::Vector2f(1600, (rand() % 50) + 470);
            speedE = -1;
            if (enmType == 0) { speedE *= 0.05 * randSpeedE; enemy->init("images/enemy1-1.png", enemyPos, speedE, 1); }
            else if (enmType == 1) { speedE *= 0.05 * randSpeedE; enemy->init("images/enemy1-2.png", enemyPos, speedE, 2); }
            else if (enmType == 2) { speedE *= 0.05 * randSpeedE; enemy->init("images/enemy1-3.png", enemyPos, speedE, 3); }
            else if (enmType == 3) {
                enemyPos = sf::Vector2f(1600, rand() % 350);
                speedE *= 0.05 * randSpeedE; enemy->init("images/fly-enemy1-1.png", enemyPos, speedE, 1);
            }
            break;
        default: {} break;
        }
    }
    else if (level == 1) {
        switch (randLoc) {
        case 0: enemyPos = sf::Vector2f(0, (rand() % 50) + 470);
            speedE = 1;
            if (enmType == 0) { speedE *= 0.05 * randSpeedE; enemy->init("images/enemy2-1.png", enemyPos, speedE, 1); }
            else if (enmType == 1) { speedE *= 0.05 * randSpeedE; enemy->init("images/enemy2-2.png", enemyPos, speedE, 2); }
            else if (enmType == 2) { speedE *= 0.01 * randSpeedE; enemy->init("images/enemy2-3.png", enemyPos, speedE, 5); }
            else if (enmType == 3) {
                enemyPos = sf::Vector2f(0, rand() % 350);
                speedE *= 0.08 * randSpeedE; enemy->init("images/fly-enemy2-1.png", enemyPos, speedE, 2);
            }
            break;
        case 1: enemyPos = sf::Vector2f(1600, (rand() % 50) + 470);
            speedE = -1;
            if (enmType == 0) { speedE *= 0.05 * randSpeedE; enemy->init("images/enemy2-1.png", enemyPos, speedE, 1); }
            else if (enmType == 1) { speedE *= 0.05 * randSpeedE; enemy->init("images/enemy2-2.png", enemyPos, speedE, 2); }
            else if (enmType == 2) { speedE *= 0.01 * randSpeedE; enemy->init("images/enemy2-3.png", enemyPos, speedE, 5); }
            else if (enmType == 3) {
                enemyPos = sf::Vector2f(1600, rand() % 350);
                speedE *= 0.08 * randSpeedE; enemy->init("images/fly-enemy2-1.png", enemyPos, speedE, 2);
            }
            break;
        default: {} break;
        }
    }
    else {
        switch (randLoc) {
        case 0: enemyPos = sf::Vector2f(0, (rand() % 50) + 470);
            speedE = 1;
            if (redT == false) {
                if (enmType == 0) { speedE *= 0.05 * randSpeedE; enemy->init("images/enemy3-1.png", enemyPos, speedE, 1); }
                else if (enmType == 1) { speedE *= 0.05 * randSpeedE; enemy->init("images/enemy3-3.png", enemyPos, speedE, 3); }
                else if (enmType == 2) { speedE *= 0.01 * randSpeedE; enemy->init("images/enemy3-5.png", enemyPos, speedE, 5); }
                else if (enmType == 3) {
                    enemyPos = sf::Vector2f(0, rand() % 350);
                    speedE *= 0.2 * randSpeedE; enemy->init("images/fly-enemy3-1.png", enemyPos, speedE, 1);
                }
            }
            else {
                if (enmType == 0) { speedE *= 0.2 * randSpeedE; enemy->init("images/enemy3-2.png", enemyPos, speedE, 1); }
                else if (enmType == 1) { speedE *= 0.2 * randSpeedE; enemy->init("images/enemy3-4.png", enemyPos, speedE, 3); }
                else if (enmType == 2) { speedE *= 0.04 * randSpeedE; enemy->init("images/enemy3-6.png", enemyPos, speedE, 5); }
                else if (enmType == 3) {
                    enemyPos = sf::Vector2f(0, rand() % 350);
                    speedE *= 0.8 * randSpeedE; enemy->init("images/fly-enemy3-2.png", enemyPos, speedE, 1);
                }
            }
            break;
        case 1: enemyPos = sf::Vector2f(1600, (rand() % 50) + 470);
            speedE = -1;
            if (redT == false) {
                if (enmType == 0) { speedE *= 0.05 * randSpeedE; enemy->init("images/enemy3-1.png", enemyPos, speedE, 1); }
                else if (enmType == 1) { speedE *= 0.05 * randSpeedE; enemy->init("images/enemy3-3.png", enemyPos, speedE, 3); }
                else if (enmType == 2) { speedE *= 0.01 * randSpeedE; enemy->init("images/enemy3-5.png", enemyPos, speedE, 5); }
                else if (enmType == 3) {
                    enemyPos = sf::Vector2f(1600, rand() % 350);
                    speedE *= 0.2 * randSpeedE; enemy->init("images/fly-enemy3-1.png", enemyPos, speedE, 1);
                }
            }
            else {
                if (enmType == 0) { speedE *= 0.2 * randSpeedE; enemy->init("images/enemy3-2.png", enemyPos, speedE, 1); }
                else if (enmType == 1) { speedE *= 0.2 * randSpeedE; enemy->init("images/enemy3-4.png", enemyPos, speedE, 3); }
                else if (enmType == 2) { speedE *= 0.1 * randSpeedE; enemy->init("images/enemy3-6.png", enemyPos, speedE, 5); }
                else if (enmType == 3) {
                    enemyPos = sf::Vector2f(1600, rand() % 350);
                    speedE *= 0.5 * randSpeedE; enemy->init("images/fly-enemy3-2.png", enemyPos, speedE, 1);
                }
            }
            break;
        default: {} break;
        }
    }
    enemies.push_back(enemy);
}
void spawnProj(sf::Vector2f projPos, float projAngle, bool direct) {
    Projectile* projectile = new Projectile();
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
        if (itemType == 0) { speedI *= 0.05 * randSpeed; item->initI("images/health.png", itemPos, speedI, 2); }
        else if (itemType == 1) { speedI *= 0.05 * randSpeed; item->initI("images/fire.png", itemPos, speedI, 1); }
        else if (itemType == 2) { speedI *= 0.05 * randSpeed; item->initI("images/ice.png", itemPos, speedI, 1); }
        break;
    case 1: itemPos = sf::Vector2f(1600, rand() % 300);
        speedI = -1;
        if (itemType == 0) { speedI *= 0.05 * randSpeed; item->initI("images/health.png", itemPos, speedI, 2); }
        else if (itemType == 1) { speedI *= 0.05 * randSpeed; item->initI("images/fire.png", itemPos, speedI, 1); }
        else if (itemType == 2) { speedI *= 0.05 * randSpeed; item->initI("images/ice.png", itemPos, speedI, 1); }
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
    Menu menu(window.getSize().x, window.getSize().y);

    window.setFramerateLimit(120);
    window.setVerticalSyncEnabled(false);
    window.setKeyRepeatEnabled(false);

    base.setPosition(sf::Vector2f(825.f, 485.f));
    base.setSize(sf::Vector2f(100, 100));

    sf::Texture canon_base, canon, Tbg[3], board[3];
    Tbg[0].loadFromFile("images/bg1.png");
    Tbg[1].loadFromFile("images/bg2.png");
    Tbg[2].loadFromFile("images/bg3.png");
    canon_base.loadFromFile("images/canon_base.png");
    canon.loadFromFile("images/canon.png");
    board[0].loadFromFile("images/scoreboard.png");
    board[1].loadFromFile("images/howtoplay.png");
    board[2].loadFromFile("images/gameover.png");

    sf::Sprite canon_base2, canon2, bg[3], board2[3];
    bg[0].setTexture(Tbg[0]);
    bg[1].setTexture(Tbg[1]);
    bg[2].setTexture(Tbg[2]);
    canon_base2.setTexture(canon_base);
    canon_base2.setPosition(sf::Vector2f(827.f, 429.f));
    canon_base2.setScale(sf::Vector2f(0.2f, 0.2f));
    canon2.setTexture(canon);
    canon2.setPosition(sf::Vector2f(875.f, 450.f));
    canon2.setScale(sf::Vector2f(0.2f, 0.2f));
    board2[0].setTexture(board[0]);
    board2[1].setTexture(board[1]);
    board2[2].setTexture(board[2]);

    sf::Clock deltaClock, clock;
    const sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time currenTime = sf::Time::Zero, currenTime2 = sf::Time::Zero, currenTime3 = sf::Time::Zero, prevTime = sf::Time::Zero, prevTimeI = sf::Time::Zero, prevTimeP = sf::Time::Zero;
    sf::Time enmTime = sf::seconds(5.f);
    sf::Time bgTime = sf::Time::Zero;
    sf::Time redTime = sf::Time::Zero, redZone = sf::Time::Zero;

    sf::Font font;
    font.loadFromFile("font/Minecraftia-Regular.ttf");
    sf::Text scoreText("0", font), hpText("50", font), redZoneT(" ", font);
    scoreText.setPosition(1500,50);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setCharacterSize(50);
    hpText.setPosition(850, 535);
    hpText.setFillColor(sf::Color::Green);
    hpText.setCharacterSize(40);
    redZoneT.setPosition(15, 50);
    redZoneT.setFillColor(sf::Color::Red);
    redZoneT.setCharacterSize(50);
    std::stringstream scoreS, hpS;
    ScoreBoard SB;
    sf::Text typeName("",font);
    typeName.setPosition(500, 300);
    typeName.setFillColor(sf::Color::White);
    typeName.setCharacterSize(30);

    bool di = 0, red = false, typeFin = false;  int shoot = 5;
    int score = 0, baseHP = 50, b = 0, checkMenu = 0, lv = 0, score2 = 0;
    std::string oldName, oldScore; int oldSc;
    std::vector<int> allScore;
    std::vector<sf::String> allName;
    std::string name;

    sf::SoundBuffer redMB, beepB, shootB, hitB, dmgB, itemB[3];
    redMB.loadFromFile("audio/bg3-2.wav");
    beepB.loadFromFile("audio/beep.wav");
    shootB.loadFromFile("audio/shoot.wav");
    hitB.loadFromFile("audio/hit.wav");
    dmgB.loadFromFile("audio/damage.wav");
    itemB[0].loadFromFile("audio/health.wav");
    itemB[1].loadFromFile("audio/burn.wav");
    itemB[2].loadFromFile("audio/freeze.wav");
    sf::Sound redM, beepS, shootS, hitS, dmgS, itemS[3];
    redM.setBuffer(redMB);
    beepS.setBuffer(beepB);
    shootS.setBuffer(shootB);
    hitS.setBuffer(hitB);
    dmgS.setBuffer(dmgB);
    itemS[0].setBuffer(itemB[0]);
    itemS[1].setBuffer(itemB[1]);
    itemS[2].setBuffer(itemB[2]);
    int bgS = 0;
    sf::Music bgm[5];
    bgm[0].openFromFile("audio/menu.wav");
    bgm[1].openFromFile("audio/bg1.wav");
    bgm[2].openFromFile("audio/bg2.wav");
    bgm[3].openFromFile("audio/bg3-1.wav");
    bgm[4].openFromFile("audio/bg3-2.wav");
    bgm[4].setVolume(30.f);
    
    bool checkplay = false;
    while (window.isOpen())
    {
        if (checkMenu == 0) bgS = 0;
        else if (lv == 0) bgS = 1;
        else if (lv == 1) bgS = 2;
        else if (lv == 2) {
            if (red == false) bgS = 3;
            else bgS = 4;
        }
        bgm[bgS].play();
        while (bgm[bgS].getStatus() == sf::Music::Playing) {
            sf::sleep(sf::milliseconds(1));
            sf::Time dt = clock.restart();
            timeSinceLastUpdate += deltaClock.restart();
            currenTime3 += dt;
            sf::Event event;
            while (window.pollEvent(event))
            {
                currenTime2 += dt;
                switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    switch (event.key.code) {
                    case sf::Keyboard::Space:
                        if (checkMenu == 1) {
                            if (currenTime2 >= prevTimeP + seconds(0.05f)) {
                                shootS.play();
                                spawnProj(canon2.getPosition(), canon2.getRotation() * PI / 180, di);
                                prevTimeP = currenTime2;
                                if (changeProj == "images/bullet-fire.png" || changeProj == "images/bullet-ice.png") shoot--;
                                if (shoot <= 0) changeProj = "images/bullet1.png";
                            }
                        }
                        break;
                    case sf::Keyboard::Escape:
                        window.close();
                        break;
                    default: {} break;
                    }
                    break;
                case sf::Event::TextEntered:
                    if (baseHP <= 0) {
                        name += event.text.unicode;
                        typeName.setString(name);
                        if (Keyboard::isKeyPressed(Keyboard::Enter)) typeFin = true;
                    }
                    window.draw(typeName);
                    break;
                case sf::Event::KeyReleased:
                    switch (event.key.code)
                    {
                    case sf::Keyboard::Up:
                        menu.MoveUp();
                        break;

                    case sf::Keyboard::Down:
                        menu.MoveDown();
                        break;
                    case sf::Keyboard::LShift:
                        switch (menu.GetPressedItem())
                        {
                        case 0:
                            checkMenu = 1;
                            beepS.play();
                            break;
                        case 1:
                            checkMenu = 2;
                            beepS.play();
                            break;
                        case 2:
                            checkMenu = 3;
                            beepS.play();
                            break;
                        }
                        break;
                    }
                    break;
                default: {} break;
                }
            }
            if (checkMenu != 1) {
                window.clear();
                if (currenTime3 >= bgTime + sf::seconds(5.0f)) {
                    bgTime = currenTime3;
                    b++;
                }
                if (b > 2) b = 0;
                window.draw(bg[b]);
                if (checkMenu == 0) {
                    if (bgS == 1 || bgS == 2 || bgS == 3 || bgS == 4) bgm[bgS].stop();
                    baseHP = 50;
                    currenTime = sf::Time::Zero;
                    score = 0;
                    name.clear();
                    menu.draw(window);
                }
                else if (checkMenu == 2) {
                    window.draw(board2[1]);
                    if (Keyboard::isKeyPressed(Keyboard::BackSpace)) checkMenu = 0;
                }
                else if (checkMenu == 3) {
                    window.draw(board2[0]);
                    //allName.clear(); allScore.clear();
                    if (checkplay == false) {
                        ifstream oldData("PlayerName2.txt");
                        if (oldData.is_open()) {
                            while (std::getline(oldData, oldName)) {
                                allName.push_back(oldName);
                                //cout << oldName << " ";
                            }
                            oldData.close();
                        }
                        ifstream oldData2("PlayerScore.txt");
                        if (oldData2.is_open()) {
                            while (std::getline(oldData2, oldScore)) {
                                std::stringstream stringtoint(oldScore);
                                stringtoint >> oldSc;
                                allScore.push_back(oldSc);
                            }
                            oldData2.close();
                        }
                        SB.UpdateScores(allScore, allName);
                    }
                    SB.Render(window);
                    if (Keyboard::isKeyPressed(Keyboard::BackSpace)) checkMenu = 0;
                }
            }
            else if (checkMenu == 1) {
                bgm[0].stop();
                if (baseHP <= 0) {
                    if (typeFin == true) {
                        name[name.size() - 1] = '\0';
                        oldName.clear(); oldScore.clear();
                        allScore.clear(); allName.clear();
                        ifstream oldData("PlayerName2.txt");
                        if (oldData.is_open()) {
                            while (std::getline(oldData, oldName)) {
                                allName.push_back(oldName);
                            }
                            oldData.close();
                        }
                        ifstream oldData2("PlayerScore.txt");
                        if (oldData2.is_open()) {
                            while (std::getline(oldData2, oldScore)) {
                                std::stringstream stringtoint(oldScore);
                                stringtoint >> oldSc;
                                allScore.push_back(oldSc);
                            }
                            oldData2.close();
                        }
                        allScore.push_back(score); allName.push_back(name);
                        ofstream newData, newData2;
                        newData.open("PlayerName2.txt");
                        if (newData.is_open()) {
                            for (auto i = allName.begin(); i != allName.end(); ++i) {
                                oldName.clear();
                                oldName = *i;
                                newData << oldName << "\n";
                            }
                            newData.close();
                        }
                        newData2.open("PlayerScore.txt");
                        if (newData2.is_open()) {
                            for (auto i = allScore.begin(); i != allScore.end(); ++i) {
                                newData2 << *i << "\n";
                            }
                            newData2.close();
                        }
                        SB.UpdateScores(allScore, allName);
                        checkMenu = 0;
                        typeFin = false;
                    }
                }
                else {
                    currenTime += dt;
                    if (currenTime >= prevTime + enmTime) {
                        spawnEnemy(lv, red);
                        if (score2 == 0) {
                            //cout << currenTime.asSeconds() << " " << enmTime.asSeconds() << " " << red << endl;
                            enmTime = sf::seconds(5.f - (currenTime.asSeconds()) / 1000);
                        }
                        if (enmTime > seconds(0.5f))  enmTime -= seconds(0.15f);
                        else enmTime = seconds(0.5f);
                        prevTime = currenTime;
                    }
                    if (currenTime >= prevTimeI + sf::seconds((rand() % 5) + 10)) {
                        spawnItem();
                        prevTimeI = currenTime;
                    }
                    if (lv == 2) {
                        if (currenTime >= redTime + sf::seconds(30.f)) {
                            redZoneT.setString("Red Zone");
                            redTime = currenTime;
                            red = true;
                            bgm[3].pause();
                        }
                        if (currenTime >= redZone + sf::seconds(60.f)) {
                            redZoneT.setString(" ");
                            redZone = currenTime;
                            red = false;
                            bgm[4].pause();
                        }
                    }

                    while (timeSinceLastUpdate > timePerFrame) {
                        timeSinceLastUpdate -= timePerFrame;
                        // update projectile
                        {
                            for (int i = 0; i < projectiles.size(); i++) {
                                Projectile* proj = projectiles[i];
                                proj->update(timePerFrame);
                                if (!viewRect.intersects(proj->getHitboxP())) projectiles.erase(projectiles.begin()) + i;
                            }
                        }
                        // update enemies
                        {
                            for (int i = 0; i < enemies.size(); i++) {
                                Enemy* enemy = enemies[i];
                                enemy->update2(timePerFrame);
                                int currentHP = enemy->getHP();
                                for (int j = 0; j < projectiles.size(); j++) {
                                    Projectile* proj2 = projectiles[j];
                                    if (proj2->getHitboxP().intersects(enemy->getHitbox()) == true) {
                                        hitS.play();
                                        currentHP -= proj2->getDamage();
                                        enemy->minusHP(currentHP);
                                        if (changeProj == "images/bullet-ice.png") enemy->SlowEnemy();
                                        projectiles.erase(projectiles.begin()) + j;
                                        break;
                                    }
                                }
                                if (enemy->getHP() <= 0) {
                                    checkplay = true;
                                    score += enemy->getscoreHP();
                                    score2 += enemy->getscoreHP();
                                    scoreS.str(std::string());
                                    scoreS << score;
                                    scoreText.setString(scoreS.str());
                                    enemies.erase(enemies.begin() + i);
                                    break;
                                }
                                if (enemy->getSprite().getPosition().x > 825 && enemy->getSpeed() > 0) {
                                    dmgS.play();
                                    baseHP -= enemy->getscoreHP();
                                    if (baseHP < 0) baseHP = 0;
                                    hpS.str(std::string());
                                    hpS << baseHP;
                                    hpText.setString(hpS.str());
                                    enemies.erase(enemies.begin() + i);
                                    delete(enemy);
                                }
                                else if (enemy->getSprite().getPosition().x < 925 && enemy->getSpeed() < 0) {
                                    dmgS.play();
                                    baseHP -= enemy->getscoreHP();
                                    if (baseHP < 0) baseHP = 0;
                                    hpS.str(std::string());
                                    hpS << baseHP;
                                    hpText.setString(hpS.str());
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
                                int currentHPI = item->getHPI();
                                for (int j = 0; j < projectiles.size(); j++) {
                                    Projectile* proj3 = projectiles[j];
                                    if (proj3->getHitboxP().intersects(item->getHitboxI()) == true) {
                                        currentHPI -= proj3->getDamage();
                                        item->minusHPI(currentHPI);
                                        projectiles.erase(projectiles.begin()) + j;
                                        break;
                                    }
                                }
                                if (item->getHPI() <= 0) {
                                    if (item->getitemName() == "images/fire.png") { changeProj = "images/bullet-fire.png"; shoot = 5; itemS[1].play(); }
                                    else if (item->getitemName() == "images/ice.png") { changeProj = "images/bullet-ice.png"; shoot = 5; itemS[2].play(); }
                                    else if (item->getitemName() == "images/health.png" && baseHP < 50) {
                                        itemS[0].play();
                                        baseHP++;
                                        hpS.str(std::string());
                                        hpS << baseHP;
                                        hpText.setString(hpS.str());
                                    }
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
                            canon2.rotate(-0.3f);
                        }
                        else if (Keyboard::isKeyPressed(Keyboard::Up)) {
                            canon2.rotate(0.3f);
                        }
                    }
                    else {
                        if (Keyboard::isKeyPressed(Keyboard::Down)) {
                            canon2.rotate(0.3f);
                        }
                        else if (Keyboard::isKeyPressed(Keyboard::Up)) {
                            canon2.rotate(-0.3f);
                        }
                    }
                    window.clear();
                }
                if (score2 / 50 >= 1) {
                    if (bgS == 1 || bgS == 2 || bgS == 3 || bgS == 4) bgm[bgS].stop();
                    redZoneT.setString(" ");
                    lv++;
                    if (lv > 2) lv = 0;
                    score2 = 0;
                }
                window.draw(bg[lv]);
                for (Projectile* projectile : projectiles) window.draw(projectile->getSpriteP());
                for (Enemy* enemy : enemies) window.draw(enemy->getSprite());
                for (Item* item : items) window.draw(item->getSpriteI());
                window.draw(redZoneT);
                window.draw(canon2);
                window.draw(canon_base2);
                window.draw(base);
                window.draw(hpText);
                window.draw(scoreText);
                if(baseHP<=0) window.draw(board2[2]);
                window.draw(typeName);
            }
            window.display();
        }
    }

    return EXIT_SUCCESS;
}