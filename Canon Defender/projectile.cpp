#include "projectile.h"

Projectile::Projectile() :
	canBeRemoved_(true),
	boundingBox_(sf::FloatRect()),
	angle_(0.0f),
	speed_(0.0f),
	speed2_(0.0f),
	check(true),
	direct(true)
{
}

Projectile::Projectile(const sf::Vector2f pos, const float angle, const bool direction) {
	canBeRemoved_ = false;
	boundingBox_ = sf::FloatRect(pos, sf::Vector2f(10.0f, 10.0f));
	angle_ = angle;
	speed_ = 0.5f;
	speed2_ = 0.5f;
	check = false;
	direct = direction;

	shape_.setPosition(sf::Vector2f(boundingBox_.left, boundingBox_.top));
	shape_.setSize(sf::Vector2f(boundingBox_.width, boundingBox_.height));
	shape_.setFillColor(sf::Color(255, 255, 255));
}

Projectile::~Projectile() {
}

const bool& Projectile::getCanBeRemoved() const {
	return canBeRemoved_;
}

const sf::FloatRect& Projectile::getBoundingBox() const {
	return boundingBox_;
}

void Projectile::destroy() {
	canBeRemoved_ = true;
}

void Projectile::update(const sf::Time dt) {
	if (direct == 0) {
		if (cos(angle_) < 0)
			boundingBox_.left -= static_cast<float>(std::cos(angle_) * speed_ * dt.asMilliseconds());
		else
			boundingBox_.left += static_cast<float>(std::cos(angle_) * speed_ * dt.asMilliseconds()); 
	}
	else {
		if (cos(angle_) < 0)
			boundingBox_.left += static_cast<float>(std::cos(angle_) * speed_ * dt.asMilliseconds());
		else
			boundingBox_.left -= static_cast<float>(std::cos(angle_) * speed_ * dt.asMilliseconds());
	}

	if (check == true) boundingBox_.top += static_cast<float>(speed2_ * dt.asMilliseconds());
	else boundingBox_.top += static_cast<float>(std::sin(angle_) * speed2_ * dt.asMilliseconds());

	shape_.setPosition(boundingBox_.left, boundingBox_.top);
	if (speed2_ <= 0) check = true;
	if (check == false) speed2_ -= 0.0098;
	else speed2_ += 0.0098;
}

void Projectile::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const {
	renderTarget.draw(shape_);
}