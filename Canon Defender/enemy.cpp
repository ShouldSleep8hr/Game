#include "enemy.h"
Enemy::Enemy() {}
Enemy::~Enemy() {}

void Enemy::init(std::string textureName, sf::Vector2f position, float speed, int hp) {
	Speedenemy_ = speed;
	Posenemy_ = position;
	hp_ = hp;
	
	Tenemy_.loadFromFile(textureName.c_str());

	Senemy_.setTexture(Tenemy_);
	Senemy_.setPosition(Posenemy_);
	Senemy_.setHitbox({ 0.f,0.f,203.f,277.f });
	Senemy_.setScale(sf::Vector2f(0.2f, 0.2f));
}
void Enemy::update2(const sf::Time dt) {
	if (Speedenemy_ < 0)
		Senemy_.move(Speedenemy_ * dt.asMilliseconds(), 0.001 * (485.f - Posenemy_.y) * -1 * Speedenemy_ * dt.asMilliseconds());
	else
		Senemy_.move(Speedenemy_ * dt.asMilliseconds(), 0.001 * (485.f - Posenemy_.y) * Speedenemy_ * dt.asMilliseconds());
}
sf::Sprite Enemy::getSprite() {
	return Senemy_;
}
sf::FloatRect Enemy::getHitbox() {
	return Senemy_.getGlobalHitbox();
}
float Enemy::getSpeed() {
	return Speedenemy_;
}
void Enemy::minusHP() {
	hp_--;
}
int Enemy::getHP() {
	return hp_;
}