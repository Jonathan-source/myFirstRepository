#include "Game.h"
#include <iostream>
#include "State.h"

Game::Game(sf::RenderWindow &window)
	:GameState(), circle(50.f)
{
	this->window = &window;
	srand(time(NULL));
	// Circle
	circle.setFillColor(sf::Color::Blue);
	circle.setPosition(10.f, 250.f);

	elapsedTimeSinceLastUpdate = sf::Time::Zero;
	timePerFrame = sf::seconds(1 / 60.f);

	//INIT
	camera.initView(window, world);
	initTextures();

	world.loadMap("map.txt", &textureManager);
}

Game::~Game()
{

}

State Game::update()
{
	
	elapsedTimeSinceLastUpdate += clock.restart();
	
	while (elapsedTimeSinceLastUpdate > timePerFrame)
	{
		elapsedTimeSinceLastUpdate -= timePerFrame;

		//VILLAGERS LOGIC
		villagerHandler.selectVillager(*window);
		villagerHandler.setVillagerMoveToTarget(*window);
		//villagerHandler.collideWithVillagers();
		//circle.move(4.f, 0);
		camera.move(*window);
		villagerHandler.showVillagersProfil(camera);
		villagerHandler.moveAllVillagers();
	}
		
	return State::NO_CHANGE;
}

void Game::render()
{
	window->clear();

	//window->draw(circle);
	//world.drawMap(*window);
	camera.drawMap(*window);

	villagerHandler.drawAllVillagers(*window);

	window->display();
}

void Game::handleEvents()
{
	sf::Event event;
	bool resizeDone = false;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window->close();
			
		}
		if(event.type == sf::Event::MouseWheelMoved)
		{
			camera.scroll(*window,(int)event.mouseWheel.delta);
		}
		if(event.type == sf::Event::Resized)
		{
			//Do noting TODO
		}
		else
		{

			camera.maintainAspectRatio(*window);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window->close();
		}
		if (event.type == sf::Event::KeyPressed)
		{
			villagerHandler.spawnAVillager();
		}

	}
}

void Game::initTextures()
{
	//FARMERS
	textureManager.loadResource(TextureID::Farmer, "assets/Farmer.png");
	textureManager.loadResource(TextureID::FarmerSelected, "assets/FarmerSelected.png");

	//TILES
	textureManager.loadResource(TextureID::Grass, "assets/tile_green.png");
	textureManager.loadResource(TextureID::Water, "assets/tile_blue.png");
}






