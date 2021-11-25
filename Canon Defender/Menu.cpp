#include "Menu.h"


Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("font/Minecraftia-Regular.ttf"))
	{
		// handle error
	}
	Gamename.setFont(font);
	Gamename.setFillColor(sf::Color::White);
	Gamename.setOutlineColor(sf::Color::Black);
	Gamename.setOutlineThickness(5);
	Gamename.setString("Canon Defender");
	Gamename.setPosition(sf::Vector2f(360, 150));
	Gamename.setCharacterSize(100);

	myName.setFont(font);
	myName.setFillColor(sf::Color::White);
	Gamename.setOutlineColor(sf::Color::Black);
	myName.setOutlineThickness(5);
	myName.setString("Piraya Jangprai 64010606");
	myName.setPosition(sf::Vector2f(10, 590));
	myName.setCharacterSize(10);

	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setPosition(sf::Vector2f(800, 300));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("How to play");
	menu[1].setPosition(sf::Vector2f(740, 400));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Score");
	menu[2].setPosition(sf::Vector2f(780, 500));

	selectedItemIndex = 0;
}


Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow& window)
{
	window.draw(Gamename);
	window.draw(myName);
	for (int i = 0; i < MAX_NUMBER_OF_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::White);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}