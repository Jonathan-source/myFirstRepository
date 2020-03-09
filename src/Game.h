#ifndef GAME_H
#define GAME_H

#include "GameState.h"
#include <SFML/Graphics.hpp>
#include "Map.h"
#include "Camera.h"
#include "Entity.h"
#include "VillagerHandler.h"
#include "Villager.h"
#include "ResourceManager.h"
#include "ResourceHandler.h"
#include "enumTextures.h"
#include "GUI.h"
#include "Tile.h"
#include "BuildingHandler.h"

class Game : public GameState
{
private:
	sf::RenderWindow *window;
	Map world;
	ResourceManager<sf::Texture, TextureID> textureManager;

	sf::Clock clock;
	sf::Time timePerFrame;
	sf::Time timeResourceCall;
	sf::Time elapsedTimeSinceLastUpdate;
	
	Camera* camera;
	VillagerHandler* villagerHandler;
	ResourceHandler resourceHandler;
	GUI* gui;
	BuildingHandler *buildingHandler;

public:

	Game(sf::RenderWindow &window);
	virtual ~Game();

	// Inherited via GameState
	virtual State update() override;
	virtual void render() override;
	virtual void handleEvents() override;

	void checkAction();

	//- INITALIZE ALL THE TEXTURES -
	void initTextures();

};

#endif
