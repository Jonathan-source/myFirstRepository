#include "ResourceEntity.h"

ResourceEntity::ResourceEntity()
{
}

ResourceEntity::ResourceEntity(sf::Texture& _texture, int _resourceType, int _resourceAmount, sf::Vector2f _position, sf::Texture &_textureResEmpty)
	:type(_resourceType), resourceAmount(_resourceAmount)
{
	this->sprite.setTexture(_texture);
	this->sprite.setPosition(_position.x * 64, _position.y * 64);
	resourceTexture = &_texture;
	resourceTextureEmpty = &_textureResEmpty;
	hitBox = sf::FloatRect(this->sprite.getPosition(), sf::Vector2f(128, 128));
}

ResourceEntity::~ResourceEntity()
{
}

int ResourceEntity::removeFromResource(int _sum)
{
	int amountRemoved = 0;
	if (resourceAmount > 0) {
		this->resourceAmount -= _sum;
		amountRemoved = _sum;
	}
	else {
		this->sprite.setTexture(*resourceTextureEmpty);
		amountRemoved = -1;
	}
	return amountRemoved;
}

int ResourceEntity::getResourceType() const
{
	return type;
}

int ResourceEntity::getResourceAmount() const
{
	return resourceAmount;
}

sf::Vector2f ResourceEntity::getPosition() const
{
	return this->sprite.getPosition();
}

sf::FloatRect ResourceEntity::getHitBox() const
{
	return hitBox;
}

void ResourceEntity::setPosition(sf::Vector2f _pos)
{
	this->sprite.setPosition(_pos);
}

void ResourceEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
}