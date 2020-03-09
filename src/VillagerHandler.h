#ifndef VILLAGERHANDLER_H
#define VILLAGERHANDLER_H
#include "Villager.h"
#include <SFML/Graphics.hpp>
#include <iostream>
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

	sf::Texture* farmerTexture;
	bool isVillagerSelected;
	Villager** villagers;

public:
	VillagerHandler(sf::Texture& _texture);
	virtual ~VillagerHandler();
	void spawnAVillager();
	bool checkIfSelected();
	void expand();
	void freeMemory();
	//CHECK ALL VILLAGERS WHO IS GATHERING FOR RESOURCE TICK
	void resourceTick(GUI* _gui);
	//GET
	int getNrOfActive();
	int getCapacity();
	Villager** getVillagerList() const;  
	void moveAllVillagers();
	void drawAllVillagers(sf::RenderWindow &window);
	void selectVillager(sf::RenderWindow& window, sf::Event& event, float yPos);
	//SET
	void setVillagerMoveToTarget(sf::RenderWindow& window);
	//SET VILLAGER ON _POSITION TO GATHERING
	void setVillagerToGather(int _position);
	void collideWithVillagers();
	void showVillagersProfil(Camera &_camera);
	void normalized (sf::Vector2f& res, const sf::Vector2f& v);
	sf::Vector2f getPositionOfSelectedVillager() const;
};

#endif
