#pragma once
#include "ResourceEntity.h"
#include "enumTextures.h"
#include "Villager.h"
#include "Map.h"
#include "Camera.h"

class ResourceHandler
{
private:
	int woodStored;
	int ironStored;
	int goldStored;
	int foodStored;
	int nrOfActive;
	int capacity;
	ResourceEntity** resourceObjects;
public:
	ResourceHandler();
	~ResourceHandler();
	//Initialize all resources to spawn on map
	void initResources(Map& _map, sf::Texture &_texture, sf::Texture& _texturesResourceEmpty);
	//Function to spawn a resource on list (resourceObjects)
	void spawnResource(sf::Texture& _textures, int _type, int _resourceAmount, sf::Vector2f _pos, sf::Texture& _texturesResourceEmpty);
	//RETURNS INT ON WHAT POSITION THE VILLAGER IS ON THAT IS GATHERING
	int gatherFromResource(Villager** villagerList, int _nrOfActive);
	void drawAll(sf::RenderWindow &window);
};

