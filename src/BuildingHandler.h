#ifndef BUILDINGHANDLER_H
#define BUILDINGHANDLER_H
#include "House.h"
#include <SFML/Graphics.hpp>
#include "Camera.h"
#include "Tile.h"
class BuildingHandler {
private:
	static const int capacity = 100;
	int nrOfBuildings;
	BuildingEntity *buildingArray[capacity];
	
public:
	BuildingHandler();
	virtual ~BuildingHandler();

	void createHouse(sf::Texture& texture, Tile* tile);
	void drawAllBuildings(sf::RenderWindow &window);
};

#endif
