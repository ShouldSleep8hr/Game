#include "projectile.h"

Projectile::Projectile() :
	//canBeRemoved_(true),
	//boundingBox_(sf::FloatRect()),
	angle_(0.0f),
	speed_(0.0f),
	speed2_(0.0f),
	check(true),
	direct(true),
	PoseP_(0.0f,0.0f),
	typeProj(std::string()),
	Tproj_(sf::Texture()),
	Sproj_(HitboxSpriteP())
{
}
//Projectile::Projectile() {}
Projectile::~Projectile() {}

void Projectile::initP(std::string textureName, const sf::Vector2f pos, float angle, const bool direction) {
	//canBeRemoved_ = false;
	//boundingBox_ = sf::FloatRect(pos, sf::Vector2f(10.0f, 10.0f));
	angle_ = angle;
	speed_ = 0.5f;
	speed2_ = 0.5f;
	check = false;
	direct = direction;
	PoseP_ = pos;
	typeProj = textureName;

	Tproj_.loadFromFile(textureName.c_str());
	Sproj_.setTexture(Tproj_);
	Sproj_.setPosition(pos);
	Sproj_.setHitboxP({ 0.f,0.f,391.f,379.f });
	Sproj_.setScale(sf::Vector2f(0.1f, 0.1f));

	//shape_.setPosition(sf::Vector2f(boundingBox_.left, boundingBox_.top));
	//shape_.setSize(sf::Vector2f(boundingBox_.width, boundingBox_.height));
	//shape_.setFillColor(sf::Color(255, 255, 255));
}

/*const bool& Projectile::getCanBeRemoved() const {
	return canBeRemoved_;
}
const sf::FloatRect& Projectile::getBoundingBox() const {
	return boundingBox_;
}
void Projectile::destroy() {
	canBeRemoved_ = true;
}*/

void Projectile::update(const sf::Time dt) {
	if (direct == 0) {
		if (cos(angle_) < 0)
			PoseP_.x -= static_cast<float>(std::cos(angle_) * speed_ * dt.asMilliseconds());
		else
			PoseP_.x += static_cast<float>(std::cos(angle_) * speed_ * dt.asMilliseconds());
	}
	else {
		if (cos(angle_) < 0)
			PoseP_.x += static_cast<float>(std::cos(angle_) * speed_ * dt.asMilliseconds());
		else
			PoseP_.x -= static_cast<float>(std::cos(angle_) * speed_ * dt.asMilliseconds());
	}

	//if (check == true) PoseP_.y += static_cast<float>(speed2_ * dt.asMilliseconds());
	//else {
	if (direct == 1) PoseP_.y -= (std::sin(angle_) * speed_ * dt.asMilliseconds());
	else PoseP_.y += (std::sin(angle_) * speed_ * dt.asMilliseconds());
	Sproj_.setPosition(PoseP_.x, PoseP_.y);
	//shape_.setPosition(boundingBox_.left, boundingBox_.top);
	/*if (speed2_ <= 0) check = true;
	if (check == false) speed2_ -= 0.0098;
	else speed2_ += 0.0098;*/
}
sf::Sprite Projectile::getSpriteP() {
	return Sproj_;
}
sf::FloatRect Projectile::getHitboxP() {
	return Sproj_.getGlobalHitboxP();
}
int Projectile::getDamage() {
	if (typeProj == "images/bullet-fire.png") return 3;
	else return 1;
}
/*void Projectile::draw(sf::RenderTarget& renderTarget, sf::RenderStates renderStates) const {
	renderTarget.draw(shape_);
}*/