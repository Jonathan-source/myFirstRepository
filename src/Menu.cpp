#include "Menu.h"
#include <iostream>
void Menu::moveUp()
{
	if(!showSettings){
		if (selected > 0) 
		{
			selected--;
			switch (selected) {
			case 0:
				alternatives[0].setFillColor(sf::Color::Yellow);
				alternatives[1].setFillColor(sf::Color::White);
				alternatives[2].setFillColor(sf::Color::White);
				break;
			case 1:
				alternatives[0].setFillColor(sf::Color::White);
				alternatives[1].setFillColor(sf::Color::Yellow);
				alternatives[2].setFillColor(sf::Color::White);
				break;
			case 2:
				alternatives[0].setFillColor(sf::Color::White);
				alternatives[1].setFillColor(sf::Color::White);
				alternatives[2].setFillColor(sf::Color::Yellow);
				break;
			default:
				break;
			}
		}
	}
	else
	{
		if (selected > 3) {
			selected--;
			switch (selected) {
			case 3:
				alternatives[3].setFillColor(sf::Color::Yellow);
				alternatives[4].setFillColor(sf::Color::White);
				break;
			case 4:
				alternatives[3].setFillColor(sf::Color::White);
				alternatives[4].setFillColor(sf::Color::Yellow);
				break;
			default:
				break;
			}
		}
	}
}

void Menu::moveDown()
{
	if(!showSettings)
	{
		if (selected < 2) {
		selected++;
		switch (selected) {
		case 0:
			alternatives[0].setFillColor(sf::Color::Yellow);
			alternatives[1].setFillColor(sf::Color::White);
			alternatives[2].setFillColor(sf::Color::White);
			break;
		case 1:
			alternatives[0].setFillColor(sf::Color::White);
			alternatives[1].setFillColor(sf::Color::Yellow);
			alternatives[2].setFillColor(sf::Color::White);
			break;
		case 2:
			alternatives[0].setFillColor(sf::Color::White);
			alternatives[1].setFillColor(sf::Color::White);
			alternatives[2].setFillColor(sf::Color::Yellow);
			break;
		default:
			break;
		}
		}
	}
	else
	{
		if (selected < 4) {
			selected++;
			switch (selected) {
			case 3:
				alternatives[3].setFillColor(sf::Color::Yellow);
				alternatives[4].setFillColor(sf::Color::White);
				break;
			case 4:
				alternatives[3].setFillColor(sf::Color::White);
				alternatives[4].setFillColor(sf::Color::Yellow);
				break;
			default:
				break;
			}
		}
	}
}

Menu::Menu(sf::RenderWindow &window)
	: GameState(), showSettings(false)
{
	this->window = &window;

	font.loadFromFile("assets/atari.ttf");

	alternatives[0].setFont(font);
	alternatives[0].setFillColor(sf::Color::Yellow);
	alternatives[0].setCharacterSize(20);
	alternatives[0].setString("Play");
	
	alternatives[0].setPosition(this->window->getSize().x / 3.f, this->window->getSize().y / 3.f);

	alternatives[1].setFont(font);
	alternatives[1].setFillColor(sf::Color::White);
	alternatives[1].setCharacterSize(20);
	alternatives[1].setString("Settings");
	alternatives[1].setPosition(this->window->getSize().x / 3.f, this->window->getSize().y / 3.f + 50.f);

	alternatives[2].setFont(font);
	alternatives[2].setFillColor(sf::Color::White);
	alternatives[2].setCharacterSize(20);
	alternatives[2].setString("Exit");
	alternatives[2].setPosition(this->window->getSize().x / 3.f, this->window->getSize().y / 3.f + 100.f);

	//--- SETTINGS ---
	std::ifstream myFile ("settings.txt");
	if(myFile.is_open()){
		myFile >> cameraSensitivity;
		/*while(myFile >> a)
		{
			cameraSensitivity = a;
		}*/
	}
	myFile.close();
	alternatives[3].setFont(font);
	alternatives[3].setFillColor(sf::Color::White);
	alternatives[3].setCharacterSize(20);
	alternatives[3].setString("Camera sensitivity: " + std::to_string(cameraSensitivity));
	alternatives[3].setPosition(this->window->getSize().x / 3.f, this->window->getSize().y / 3.f );

	alternatives[4].setFont(font);
	alternatives[4].setFillColor(sf::Color::Yellow);
	alternatives[4].setCharacterSize(20);
	alternatives[4].setString("Back");
	alternatives[4].setPosition(this->window->getSize().x / 3.f, this->window->getSize().y / 3.f + 200.f);
	
	
	selected = 0;
	done = false;

	camera.initView(window);
}

Menu::~Menu()
{
}

State Menu::update()
{
	State currentState = State::NO_CHANGE;

	if (done) 
	{
		switch (selected) 
		{
		case 0: currentState = State::PLAY;
			break;
		case 1: 
			selected = 4;
			showSettings = true;
			done = false;
			break;
		case 2: currentState = State::EXIT;
			break;
		case 3:;
			done = false;
			break;
		case 4: 
			writeSettingsToFile();
			showSettings = false;
			selected = 1;
			done = false;
			break;
		default:
			break;
		}
	}
	return currentState;
}

void Menu::render()
{
	window->clear();

	if(!showSettings)
	{
	window->draw(this->alternatives[0]);
	window->draw(this->alternatives[1]);
	window->draw(this->alternatives[2]);
	}
	else
	{
	window->draw(this->alternatives[3]);
	window->draw(this->alternatives[4]);
	}
	window->display();
}

void Menu::writeSettingsToFile()
{
	std::ofstream myFile ("settings.txt");

	if(myFile.is_open())
	{
		myFile << cameraSensitivity;
		myFile.close();
	}
}

void Menu::handleEvents()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window->close();
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			window->close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			moveUp();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			moveDown();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
			done = true;
		}

		//Change value on camera sensitivity setting
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && selected == 3)
		{
				cameraSensitivity--;
				alternatives[3].setString("Camera sensitivity: " + std::to_string(cameraSensitivity));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && selected == 3)
		{
				cameraSensitivity++;
				alternatives[3].setString("Camera sensitivity: " + std::to_string(cameraSensitivity));
		}


		if(event.type == sf::Event::Resized)
		{
			//Do noting TODO
		}
		else
		{
			camera.maintainAspectRatio(*window);
		}
		
	}
}

