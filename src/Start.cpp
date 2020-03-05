#include "Game.h"
#include "Menu.h"

#include <iostream>
#include "Camera.h"

#ifdef _DEBUG
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#pragma comment(lib, "sfml-graphics-d.lib")
#else
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-system.lib")
#pragma comment(lib, "sfml-graphics.lib")
#endif



int main()
{
	// Window
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Nocturnal Invasion");
	GameState *current = nullptr;
	State currentState = State::NO_CHANGE;
	
	current = new Menu(window);
	currentState = State::MENU;

	while (currentState != State::EXIT && window.isOpen())
	{
		current->handleEvents();
		currentState = current->update();
		
		if (currentState != State::NO_CHANGE)
		{
			
			switch (currentState)
			{
			case State::MENU:
				delete current;
				current = new Menu(window);
				break;
			case State::PLAY:
				delete current;
				current = new Game(window);
				break;
			}
		}
		current->render();
	}

	delete current;

	return 0;
}
