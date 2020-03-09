#include "Game.h"
#include <iostream>
#include "State.h"
#include "GUI.h"

Game::Game(sf::RenderWindow &window)
	: GameState()
{
	this->window = &window;
	
	elapsedTimeSinceLastUpdate = sf::Time::Zero;
	timePerFrame = sf::seconds(1 / 60.f);

	//INIT
	this->camera = new Camera();
	initTextures();
	villagerHandler = new VillagerHandler(textureManager.getResource(TextureID::Farmer));
	camera->initView(window, world);

	this->gui = new GUI(camera);

	world.loadMap("map.txt", &textureManager);

	resourceHandler.initResources(world,textureManager.getResource(TextureID::Tree), textureManager.getResource(TextureID::TreeCutted));
	this->buildingHandler = new BuildingHandler();	
}

Game::~Game()
{
	if (camera != nullptr)
	{
		delete camera;
	}
	if (gui != nullptr)
	{
		delete gui;
	}
	if(villagerHandler != nullptr)
	{
		delete villagerHandler;
	}
}

State Game::update()
{
	elapsedTimeSinceLastUpdate += clock.restart();
	
	while (elapsedTimeSinceLastUpdate > timePerFrame)
	{
		timeResourceCall += elapsedTimeSinceLastUpdate;
		elapsedTimeSinceLastUpdate -= timePerFrame;
		
		//VILLAGERS LOGIC
		villagerHandler->setVillagerMoveToTarget(*window);
		//villagerHandler.collideWithVillagers();
		//circle.move(4.f, 0);
		camera->move(*window);
		gui->update();
		villagerHandler->showVillagersProfil(*camera);
		villagerHandler->moveAllVillagers();
		//printf("Seconds : %lf\n", timeResourceCall.asSeconds());
		if (timeResourceCall.asSeconds() > 3.0f) {
			villagerHandler->resourceTick(gui);

			timeResourceCall = sf::Time::Zero;
		}

		if(villagerHandler->checkIfSelected()){
			gui->toggleButtonVisability(true);
		} else
			gui->toggleButtonVisability(false);

		checkAction();
	}
		
	return State::NO_CHANGE;
}

void Game::render()
{
	window->clear();

	//world.drawMap(*window);
	camera->drawMap(*window);

	resourceHandler.drawAll(*window);
	villagerHandler->drawAllVillagers(*window);

	if(villagerHandler->checkIfSelected()){
		gui->toggleButtonVisability(true);
	} 
	else
		gui->toggleButtonVisability(false);

	buildingHandler->drawAllBuildings(*window);

	gui->draw(*window);


	window->display();
}



void Game::handleEvents()
{
	sf::Event event;
	bool resizeDone = false;
	while (window->pollEvent(event))
	{

		
		// MULTIPLE KEY POLLS
		gui->checkButtonAction(*window, event);

		if(event.type == sf::Event::MouseWheelMoved)
		{
			//	camera->scroll(*window,(int)event.mouseWheel.delta);
		}
		if(event.type == sf::Event::Resized)
		{
				//Do noting TODO
		}
		else
		{
			camera->maintainAspectRatio(*window);
		}



		// SINGLE KEY POLL
		switch(event.type)
		{
			// Window closed
			case sf::Event::Closed:
					window->close();
				break;

			// Key pressed
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Escape){
					window->close();
				}
				if(event.key.code == sf::Keyboard::V){
					std::cout << "V was pressed\n";
					villagerHandler->spawnAVillager();
				}
				if (event.key.code == sf::Keyboard::E) {
					std::cout << "E was pressed\n";
					int numPos = resourceHandler.gatherFromResource(villagerHandler->getVillagerList(), villagerHandler->getNrOfActive());
					if (numPos != -1)
					{
						villagerHandler->setVillagerToGather(numPos);
					}
					else {
						printf("Not close enough to a resource node\n");
					}

				}
				break;

			// Mouse pressed	
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					villagerHandler->selectVillager(*window, event, gui->getYPosButtons());
				}
				if (event.mouseButton.button == sf::Mouse::Right){
					
				}
				break;
		}
	}
}

void Game::initTextures()
{
	//FARMERS
	textureManager.loadResource(TextureID::Farmer, "assets/Farmer.png");

	//TILES
	textureManager.loadResource(TextureID::Grass, "assets/tile_green.png");
	textureManager.loadResource(TextureID::Water, "assets/tile_blue.png");

	//BUILDINGS
	textureManager.loadResource(TextureID::House, "assets/spr_house.png");

	//RESOURCES
	textureManager.loadResource(TextureID::Tree, "assets/spr_tree.png");
	textureManager.loadResource(TextureID::TreeCutted, "assets/spr_treeCut.png");

}

void Game::checkAction()
{
	int action = this->gui->getActionID();
	switch(action)
	{
		case 0:
		break;
		case 1:
		{
			sf::Vector2f villagerPos = this->villagerHandler->getPositionOfSelectedVillager();
			printf("x: %lf y: %lf\n", villagerPos.x/64, villagerPos.y/64);
			Tile *tile = this->world.getTileAt((int)villagerPos.x/64, (int)villagerPos.y/64);
			this->buildingHandler->createHouse(textureManager.getResource(TextureID::House), tile);
		}
		break;
		case 2:
		break;
		case 3:
		break;
		case 4:
		break;
		default:
		break;
	}
	this->gui->setActionID(0);
}





