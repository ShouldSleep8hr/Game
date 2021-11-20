#pragma once
#include <SFML/Graphics.hpp>

class HitboxSprite : public sf::Sprite {
public:
	/// sets the hitbox
	void setHitbox(const sf::FloatRect& hitbox) {
		m_hitbox = hitbox;
	}
	/// gets the hitbox (use this instead of getGlobalBounds())
	sf::FloatRect getGlobalHitbox() const {
		return getTransform().transformRect(m_hitbox);
	}
private:
	sf::FloatRect m_hitbox;
};
class Enemy {
public:
	Enemy();
	~Enemy();

	void init(std::string textureName, sf::Vector2f position, float speed, int hp);
	void update2(const sf::Time dt);
	sf::Sprite getSprite();
	sf::FloatRect getHitbox();
	float getSpeed();
	int getHP();
	void minusHP();

private:
	sf::Texture Tenemy_;
	HitboxSprite Senemy_;
	sf::Vector2f Posenemy_;
	float Speedenemy_;
	int hp_;
};