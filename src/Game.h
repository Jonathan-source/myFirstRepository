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
#include "enumTextures.h"

class Game : public GameState
{
private:
	sf::RenderWindow *window;
	Map world;
	sf::CircleShape circle;
	ResourceManager<sf::Texture, TextureID> textureManager;
	sf::Clock clock;
	sf::Time timePerFrame;
	sf::Time elapsedTimeSinceLastUpdate;
	
	Camera camera;
	VillagerHandler villagerHandler;

public:

	Game(sf::RenderWindow &window);
	virtual ~Game();

	// Inherited via GameState
	virtual State update() override;
	virtual void render() override;
	virtual void handleEvents() override;

	//- INITALIZE ALL THE TEXTURES -
	void initTextures();

};

#endif
