#include "BuildingEntity.h"

BuildingEntity::BuildingEntity(int hp, int level)
{
    this->hitpoints = hp;
    this->level = level;
}

BuildingEntity::~BuildingEntity()
{

}

sf::Vector2f BuildingEntity::getPosition() const
{
    return this->sprite.getPosition();
}
sf::FloatRect BuildingEntity::getGlobalBounds() const
{
    return this->sprite.getGlobalBounds();
}

int BuildingEntity::getHitpoints() const
{
    return this->hitpoints;
}

int BuildingEntity::getLevel() const
{
    return this->level;
}
	
void BuildingEntity::setPosition(sf::Vector2f pos)
{
    this->sprite.setPosition(pos);
}

void BuildingEntity::setLevel(int level)
{
    this->level = level;
}

void BuildingEntity::setHitpoints(int hp)
{
    this->hitpoints = hp;
}

void BuildingEntity::upgrade()
{
    this->level++;
}

void BuildingEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(this->sprite);
}
