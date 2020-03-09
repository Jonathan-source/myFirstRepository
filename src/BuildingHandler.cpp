#include "BuildingHandler.h"

BuildingHandler::BuildingHandler()
{
    this->nrOfBuildings = 0;
    for (int i = 0; i < capacity; i++)
    {
       this->buildingArray[i] = nullptr;
    }    
}
BuildingHandler::~BuildingHandler()
{
    int num = 0;
    for (int i = 0; i < capacity; i++)
    {
        if(this->buildingArray[i] != nullptr)
        {
            delete buildingArray[i];
            num++;
        }
    }
    std::cout << "[BuildingHandler]: " << num << " buildings were de-allocated.\n";
}

void BuildingHandler::createHouse(sf::Texture& texture, Tile* tile)
{

    if(!tile->getIsOccupied() && (nrOfBuildings < capacity))
    {
        this->buildingArray[nrOfBuildings] = new House(100, 1, texture);
        buildingArray[nrOfBuildings++]->setPosition(tile->getPosition());
        tile->setIsOccupied(true);
    }
}

void BuildingHandler::drawAllBuildings(sf::RenderWindow& window)
{
	for (int i = 0; i < nrOfBuildings; i++) {
		window.draw(*buildingArray[i]);
	}
}
