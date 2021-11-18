#ifndef PROJECTILE_H_INCLUDED
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

#endif#
