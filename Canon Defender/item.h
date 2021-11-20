#pragma once
#include <SFML/Graphics.hpp>

class HitboxSpriteI : public sf::Sprite {
public:
	/// sets the hitbox
	void setHitboxI(const sf::FloatRect& hitbox) {
		i_hitbox = hitbox;
	}
	/// gets the hitbox (use this instead of getGlobalBounds())
	sf::FloatRect getGlobalHitboxI() const {
		return getTransform().transformRect(i_hitbox);
	}
private:
	sf::FloatRect i_hitbox;
};
class Item {
public:
	Item();
	~Item();

	void initI(std::string textureName, sf::Vector2f position, float speed, int hp);
	void update3(const sf::Time dt);
	sf::Sprite getSpriteI();
	sf::FloatRect getHitboxI();
	float getSpeedI();
	int getHPI();
	void minusHPI();
	std::string getitemName();

private:
	sf::Texture Titem_;
	HitboxSpriteI Sitem_;
	sf::Vector2f Poseitem_;
	float Speeditem_;
	int hpI_;
	std::string itemName;
};