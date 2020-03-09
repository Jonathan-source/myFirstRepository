#ifndef FARM_H
#define FARM_H

#include <SFML/Graphics.hpp>

#include "BuildingEntity.h"

class Farm : public BuildingEntity {
private:
	

public:
	Farm(int hp, int level, sf::Texture& texture);
	virtual ~Farm();

};

#endif
