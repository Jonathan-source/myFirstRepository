#ifndef VILLAGERHANDLER_H
#define VILLAGERHANDLER_H
#include "Villager.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include <complex>
#include <valarray>
#include "Camera.h"
class VillagerHandler
{
private:
	float lengthToMousePos;
	int nrOfActive;
	int capacity;
	sf::Vector2i spawnPos;

	sf::Vertex quad[8];

	sf::Vector2f distanceToMousePosition;
	sf::Vector2f firstMousePosition;	//Used for box selection
	bool hasDonefirstIteration;	 //Used for box selection.

	Villager** villagers;

	void selectionBoxUpdate(sf::RenderWindow& window, sf::Vector2f& mousePos);
public:
	VillagerHandler();
	void spawnAVillager();
	
	void expand();
	void freeMemory();
	int getNrOfActive();
	int getCapacity();
	void moveAllVillagers();
	void drawAllVillagers(sf::RenderWindow &window);
	void selectVillager(sf::RenderWindow& window);
	void setVillagerMoveToTarget(sf::RenderWindow& window);
	void collideWithVillagers();
	void showVillagersProfil(Camera &_camera);
	void normalized (sf::Vector2f& res, const sf::Vector2f& v);
};

#endif