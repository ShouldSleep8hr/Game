#include "item.h"
Item::Item() {}
Item::~Item() {}

void Item::initI(std::string textureName, sf::Vector2f position, float speed, int hp) {
	Speeditem_ = speed;
	Poseitem_ = position;
	hpI_ = hp;

	Titem_.loadFromFile(textureName.c_str());
	itemName = textureName.c_str();

	Sitem_.setTexture(Titem_);
	Sitem_.setPosition(Poseitem_);
	Sitem_.setHitboxI({ 0.f,0.f,203.f,277.f });
	Sitem_.setScale(sf::Vector2f(0.2f, 0.2f));
}
void Item::update3(const sf::Time dt) {
	if (Speeditem_ < 0)
		Sitem_.move(Speeditem_ * dt.asMilliseconds(), 0.001 * -1 * Speeditem_ * dt.asMilliseconds());
	else
		Sitem_.move(Speeditem_ * dt.asMilliseconds(), 0.001 * Speeditem_ * dt.asMilliseconds());
}
sf::Sprite Item::getSpriteI() {
	return Sitem_;
}
sf::FloatRect Item::getHitboxI() {
	return Sitem_.getGlobalHitboxI();
}
float Item::getSpeedI() {
	return Speeditem_;
}
void Item::minusHPI() {
	hpI_--;
}
int Item::getHPI() {
	return hpI_;
}
std::string Item::getitemName() {
	return itemName;
}