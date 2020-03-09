#include "House.h"

House::House(int hp, int level, sf::Texture& texture) 
: BuildingEntity(hp, level)
{
    this->sprite.setTexture(texture);
    this->sprite.setPosition(0.f, 0.f);
}

House::~House()
{

}