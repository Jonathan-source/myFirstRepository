#include "Entity.h"


Entity::Entity()
	:speed(5.0f), health(100), attackDmg(10)
{
	texture.loadFromFile("assets/Farmer.png");	//TEMPORARLY UNTIL ASSETMANAGER IS DONE
	texture2.loadFromFile("assets/FarmerSelected.png");	//TEMPORARLY UNTIL ASSETMANAGER IS DONE
	sprite.setTexture(texture);
	sprite.setPosition(0, 0);
}

Entity::Entity(float _speed, int _health, int _attackDmg)
	:speed(_speed), health(_health), attackDmg(_attackDmg)
{
	texture.loadFromFile("assets/Farmer.png");	//TEMPORARLY UNTIL ASSETMANAGER IS DONE
	texture2.loadFromFile("assets/FarmerSelected.png");	//TEMPORARLY UNTIL ASSETMANAGER IS DONE
	sprite.setTexture(texture);
	sprite.setPosition(0, 0);
}

float Entity::getSpeed() const
{
	return speed;
}

int Entity::getHealth() const
{
	return health;
}

int Entity::getAttackDmg() const
{
	return attackDmg;
}

sf::Vector2f Entity::getPosition() const
{
	return this->sprite.getPosition();
}

sf::FloatRect Entity::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Entity::setSpeed(float _speed)
{
	this->speed = _speed;
}

void Entity::setHealth(int _health)
{
	this->health = _health;
}

void Entity::setAttackDmg(int _attackDmg)
{
	this->attackDmg = _attackDmg;
}

void Entity::setSelectTexture()
{
	this->sprite.setTexture(texture2);
}

void Entity::setNormalTexture()
{
	this->sprite.setTexture(texture);
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
}