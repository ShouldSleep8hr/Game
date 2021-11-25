#include "enemy.h"
Enemy::Enemy() :
	Speedenemy_(0.f),
	Posenemy_(0.f,0.f),
	hp_(0),
	scoreHP(0),
	Tenemy_(sf::Texture()),
	checkfly(true),
	Senemy_(HitboxSprite())
{
}
Enemy::~Enemy() {}

void Enemy::init(std::string textureName, sf::Vector2f position, float speed, int hp) {
	Speedenemy_ = speed;
	Posenemy_ = position;
	hp_ = hp;
	enemyType = textureName;
	if (textureName == "images/enemy1-1.png" || textureName == "images/enemy2-1.png" || textureName == "images/fly-enemy1-1.png" || textureName == "images/fly-enemy2-1.png" || textureName == "images/enemy3-1.png" || textureName == "images/enemy3-2.png" || textureName == "images/fly-enemy3-1.png" || textureName == "images/fly-enemy3-2.png") scoreHP = 1;
	else if(textureName == "images/enemy1-2.png" || textureName == "images/enemy2-2.png" || textureName == "images/fly-enemy2-1.png") scoreHP = 2;
	else if (textureName == "images/enemy1-3.png" || textureName == "images/enemy3-3.png" || textureName == "images/enemy3-4.png") scoreHP = 3;
	else if (textureName == "images/enemy2-3.png" || textureName == "images/enemy3-5.png" || textureName == "images/enemy3-6.png") scoreHP = 5;
	Tenemy_.loadFromFile(textureName.c_str());
	if (textureName == "images/fly-enemy1-1.png" || textureName == "images/fly-enemy2-1.png" || textureName == "images/fly-enemy3-1.png" || textureName == "images/fly-enemy3-2.png") checkfly = true;
	else checkfly = false;
	Senemy_.setTexture(Tenemy_);
	Senemy_.setPosition(Posenemy_);
	if (Speedenemy_ < 0) Senemy_.setScale(-0.3f, 0.3f);
	else Senemy_.setScale(0.3f, 0.3f);
	if (textureName == "images/fly-enemy1-1.png") Senemy_.setHitbox({ 0.f,0.f,248.f,209.f });
	else if(textureName == "images/fly-enemy2-1.png") Senemy_.setHitbox({ 0.f,0.f,460.f,316.f });
	else if (textureName == "images/enemy2-3.png") Senemy_.setHitbox({ 0.f,0.f,510.f,329.f });
	else Senemy_.setHitbox({ 0.f,0.f,203.f,277.f });
	if (Speedenemy_ < 0) {
		if (textureName == "images/enemy3-1.png" || textureName == "images/enemy3-2.png") { Senemy_.setHitbox({ 0.f,0.f,150.f,273.f }); Senemy_.setScale(-0.4f, 0.4f); }
		else if (textureName == "images/enemy3-3.png" || textureName == "images/enemy3-4.png") { Senemy_.setHitbox({ 0.f,0.f,186.f,216.f }); Senemy_.setScale(-0.4f, 0.4f); }
		else if (textureName == "images/enemy3-5.png" || textureName == "images/enemy3-6.png") { Senemy_.setHitbox({ 0.f,0.f,170.f,273.f }); Senemy_.setScale(-0.4f, 0.4f); }
		else if (textureName == "images/fly-enemy3-1.png" || textureName == "images/fly-enemy3-2.png") { Senemy_.setHitbox({ 0.f,0.f,89.f,96.f }); Senemy_.setScale(-0.4f, 0.4f); }
	}
	else {
		if (textureName == "images/enemy3-1.png" || textureName == "images/enemy3-2.png") { Senemy_.setHitbox({ 0.f,0.f,150.f,273.f }); Senemy_.setScale(0.4f, 0.4f); }
		else if (textureName == "images/enemy3-3.png" || textureName == "images/enemy3-4.png") { Senemy_.setHitbox({ 0.f,0.f,186.f,216.f }); Senemy_.setScale(0.4f, 0.4f); }
		else if (textureName == "images/enemy3-5.png" || textureName == "images/enemy3-6.png") { Senemy_.setHitbox({ 0.f,0.f,170.f,273.f }); Senemy_.setScale(0.4f, 0.4f); }
		else if (textureName == "images/fly-enemy3-1.png" || textureName == "images/fly-enemy3-2.png") { Senemy_.setHitbox({ 0.f,0.f,89.f,96.f }); Senemy_.setScale(0.4f, 0.4f); }
	}
}
void Enemy::update2(const sf::Time dt) {
	if (checkfly == true) {
		if (Speedenemy_ < 0)
			Senemy_.move(Speedenemy_ * dt.asMilliseconds(), 0.001 * (495.f - Posenemy_.y) * -1 * Speedenemy_ * dt.asMilliseconds());
		else
			Senemy_.move(Speedenemy_ * dt.asMilliseconds(), 0.001 * (495.f - Posenemy_.y) * Speedenemy_ * dt.asMilliseconds());
	}
	else {
		if (Speedenemy_ < 0)
			Senemy_.move(Speedenemy_ * dt.asMilliseconds(), 0.001 * -1 * Speedenemy_ * dt.asMilliseconds());
		else
			Senemy_.move(Speedenemy_ * dt.asMilliseconds(), 0.001 * Speedenemy_ * dt.asMilliseconds());
	}
}
sf::Sprite Enemy::getSprite() {
	return Senemy_;
}
std::string Enemy::getEnemyType() {
	return enemyType;
}
sf::FloatRect Enemy::getHitbox() {
	return Senemy_.getGlobalHitbox();
}
float Enemy::getSpeed() {
	return Speedenemy_;
}
void Enemy::SlowEnemy() {
	Speedenemy_ *= 0.1;
}
void Enemy::minusHP(int currentHP) {
	hp_ = currentHP;
}
int Enemy::getHP() {
	return hp_;
}
int Enemy::getscoreHP() {
	return scoreHP;
}