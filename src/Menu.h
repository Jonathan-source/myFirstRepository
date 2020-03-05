#ifndef MENU_H
#define MENU_H

#include"GameState.h"
#include "Camera.h"
#include <fstream>
#include <iostream>

class Menu :public GameState
{
private:
	sf::RenderWindow *window;


	static const int nrOfOptions = 5;
	sf::Text alternatives[nrOfOptions];
	sf::Font font;

	Camera camera;
	int selected; 
	bool done;
	bool showSettings;

	//SETTINGS
	int cameraSensitivity;
	void writeSettingsToFile();

	void moveUp();
	void moveDown();
public:
	Menu(sf::RenderWindow &window);
	virtual ~Menu();

	// Inherited via GameState
	virtual State update() override;

	virtual void render() override;

	virtual void handleEvents() override;
};

#endif
