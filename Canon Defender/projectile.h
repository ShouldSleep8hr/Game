/*#ifndef PROJECTILE_H_INCLUDED
#define PROJECTILE_H_INCLUDED*/
#pragma once
#include <SFML/Graphics.hpp>

class HitboxSpriteP : public sf::Sprite {
public:
	/// sets the hitbox
	void setHitboxP(const sf::FloatRect& hitbox) {
		p_hitbox = hitbox;
	}
	/// gets the hitbox (use this instead of getGlobalBounds())
	sf::FloatRect getGlobalHitboxP() const {
		return getTransform().transformRect(p_hitbox);
	}
private:
	sf::FloatRect p_hitbox;
};
class Projectile /* : public sf::Drawable*/ {
public:
	Projectile();
	~Projectile();
	void initP(std::string textureName, const sf::Vector2f pos, const float angle, const bool direction);
	//virtual ~Projectile();

	//const bool& getCanBeRemoved() const;
	//const sf::FloatRect& getBoundingBox() const;
	//void destroy
	sf::Sprite getSpriteP();
	sf::FloatRect getHitboxP();
	void update(const sf::Time dt);

private:
	//virtual void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const;

	//bool canBeRemoved_;
	//sf::FloatRect boundingBox_;
	float angle_;
	float speed_;
	float speed2_;
	bool check;
	bool direct;
	//sf::RectangleShape shape_;
	sf::Texture Tproj_;
	HitboxSpriteP Sproj_;
	sf::Vector2f PoseP_;

};
//#endif#

/*#ifndef PROJECTILE_H_INCLUDED
#define PROJECTILE_H_INCLUDED

#include <SFML/Graphics.hpp>

class Projectile : public sf::Drawable {
public:
	Projectile();
	Projectile(const sf::Vector2f pos, const float angle, const bool direction);
	virtual ~Projectile();

	const bool& getCanBeRemoved() const;
	const sf::FloatRect& getBoundingBox() const;

	void destroy();
	void update(const sf::Time dt);

private:
	virtual void draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const;

	bool canBeRemoved_;
	sf::FloatRect boundingBox_;
	float angle_;
	float speed_;
	float speed2_;
	bool check;
	bool direct;

	sf::RectangleShape shape_;

};
#endif#*/
