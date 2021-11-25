#include "ScoreBoard.h"

//The pair comparatator, uses the second var
bool sortPairBySecond(const std::pair<sf::String, int>& i, const std::pair<sf::String, int>& j);

ScoreBoard::ScoreBoard()
{

	if (!font.loadFromFile("font/Minecraftia-Regular.ttf"))
	{
		// handle error
	}
	playerPrint2.setFont(font);
	playerPrint2.setFillColor(sf::Color::White);
	playerPrint2.setCharacterSize(50);
	scorePrint2.setFont(font);
	scorePrint2.setFillColor(sf::Color::White);
	scorePrint2.setCharacterSize(50);
}

ScoreBoard::~ScoreBoard()
{
}

void ScoreBoard::Update()
{
}

void ScoreBoard::UpdateScores(std::vector<int> inputPlayerScores, std::vector<sf::String> playerNames)
{

	for (size_t i = 0; i < playerNames.size(); i++)
	{
		std::pair<sf::String, int> newPlayerPair;
		newPlayerPair.first.clear();
		newPlayerPair.first.insert(0, playerNames[i]);
		newPlayerPair.second = inputPlayerScores[i];
		playerStrings.push_back(newPlayerPair);
	}

	std::sort(playerStrings.begin(), playerStrings.end(), sortPairBySecond);
	
	for (size_t i = 0; i < playerStrings.size(); i++)
	{
		playerPrint2.setString(playerStrings[i].first);
		playerPrint.push_back(playerPrint2);
		
		std::stringstream s2;
		s2.str(std::string());
		s2 << playerStrings[i].second;
		scorePrint2.setString(s2.str());
		scorePrint.push_back(scorePrint2);
		
	}
}

void ScoreBoard::Render(sf::RenderWindow& renderWindow)
{
	//renderWindow.draw(frameSprite);
	// Draw the playerStrings
	for (size_t i = 0; i < 5; i++)
	{
		playerPrint[i].setPosition(sf::Vector2f(600, (i + 1) * 100));
		renderWindow.draw(playerPrint[i]);
		scorePrint[i].setPosition(sf::Vector2f(1000, (i + 1) * 100));
		renderWindow.draw(scorePrint[i]);
	}
	
}

// Used as a comparator for sorting a pair by its second element
bool sortPairBySecond(const std::pair<sf::String, int>& i, const std::pair<sf::String, int>& j)
{
	return (i.second > j.second);
}