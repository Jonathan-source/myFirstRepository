#ifndef HOUSE_H
#define HOUSE_H

#include <SFML/Graphics.hpp>

#include "BuildingEntity.h"

class House : public BuildingEntity {
private:
	

public:
	House(int hp, int level, sf::Texture& texture);
	virtual ~House();

};

#endif
