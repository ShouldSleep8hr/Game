#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>
#include <sstream>

class ScoreBoard
{
public:
	ScoreBoard();
	~ScoreBoard();

	void Update();
	void Render(sf::RenderWindow& renderWindow);
	void UpdateScores(std::vector<int> inputPlayerScores, std::vector<sf::String> playerNames);

private:
	sf::Texture frameImage;
	sf::Sprite frameSprite;
	std::vector<std::pair<sf::String, int>> playerStrings;

	sf::Vector2f playerNamesStartOffset;
	float playerNamesHorizontalOffset;
	float horizontalScoreOffset;
	sf::Font font;
	std::vector<sf::Text> playerPrint;
	sf::Text playerPrint2;
	std::vector<sf::Text> scorePrint;
	sf::Text scorePrint2;
};