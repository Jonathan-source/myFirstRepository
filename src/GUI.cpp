#include "GUI.h"

GUI::GUI(Camera *camera) 
: buttonsVisable(false), woodAmount(0), ironAmount(0), foodAmount(0), goldAmount(0)
{	
	this->actionID = 0;
	this->camera = camera;
	init_buttons();
	init_resourceBar();

	initTextLabels();
}

void GUI::initTextLabels()
{
	font.loadFromFile("assets/atari.ttf");
	Label_Wood.setCharacterSize(20);
	Label_Wood.setFillColor(sf::Color::Yellow);
	Label_Wood.setFont(font);

	Label_Food.setCharacterSize(20);
	Label_Food.setFillColor(sf::Color::Yellow);
	Label_Food.setFont(font);

	Label_Iron.setCharacterSize(20);
	Label_Iron.setFillColor(sf::Color::Yellow);
	Label_Iron.setFont(font);

	Label_Gold.setCharacterSize(20);
	Label_Gold.setFillColor(sf::Color::Yellow);
	Label_Gold.setFont(font);
}

GUI::~GUI()
{
	int num = 0;
	for (int i = 0; i < this->numButtons; i++)
	{
		if(buttonList[i] != nullptr)
		{
			delete buttonList[i];
			num++;
		}
	}
	std::cout << "[GUI]: " << num << " buttons were de-allocated.\n";	
}

void GUI::init_buttons()
{
	int num = 0;
	for (int i = 0; i < this->numButtons; i++)
	{
		buttonList[i] = new Button();
		buttonList[i]->setSize(sf::Vector2f(100.f, 50.f));
		// Set temp position.
		buttonList[i]->setPosition(0.f, 0.f);
		num++;
	}
	buttonList[5]->setActionID(1);
	std::cout << "[GUI]: " << num << " buttons were allocated.\n";
}

void GUI::init_resourceBar()
{
	sf::Color white2 = sf::Color(255, 255, 255, 35);
	resourceBar.setFillColor(white2);
	resourceBar.setSize(sf::Vector2f(1000.f, 50.f));
	resourceBar.setPosition(0.f, 0.f);
}

void GUI::addToWood(int _sum)
{
	woodAmount += _sum;
}

void GUI::update()
{
	/* Update the position of everything based on camera movement */

	// Update the position of all buttons.  
	for (int i = 0; i < this->numButtons; i++)
	{
		buttonList[i]->setPosition(camera->getPosition().x + (i * 150.f) - 700, camera->getPosition().y + 470.0f);
	}
	// Update position of resourceBar (0, 0).
	resourceBar.setPosition(camera->getPosition().x - 960.f, camera->getPosition().y - 550.f);
	Label_Wood.setPosition(resourceBar.getPosition().x + 10, resourceBar.getPosition().y +10);
	Label_Wood.setString("Wood: " + std::to_string(woodAmount));

	Label_Food.setPosition(Label_Wood.getPosition().x + 200, resourceBar.getPosition().y + 10);
	Label_Food.setString("Food: " + std::to_string(foodAmount));

	Label_Iron.setPosition(Label_Food.getPosition().x + 200, resourceBar.getPosition().y + 10);
	Label_Iron.setString("Iron: " + std::to_string(ironAmount));

	Label_Gold.setPosition(Label_Iron.getPosition().x + 200, resourceBar.getPosition().y + 10);
	Label_Gold.setString("Gold: " + std::to_string(goldAmount));


}

void GUI::checkButtonAction(sf::RenderWindow &window, sf::Event &event)
{
	if(this->buttonsVisable)
	{
		// Notice the mapPixelToCoord to get the correct position.
		sf::Vector2f windowMousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		// Loop throught all buttons.
		for (int i = 0; i < this->numButtons; i++)
		{	
			// Check if any button contain the mouse-pointer.
			if(buttonList[i]->getGlobalBound().contains(windowMousePosition.x, windowMousePosition.y))
			{
				buttonList[i]->onMouseEntered();
				// Then check if left button is pressed.
				if(event.type == sf::Event::MouseButtonPressed &&
					event.mouseButton.button == sf::Mouse::Left) 
				{
					this->buttonList[i]->isLeftClicked();
					
					// Button is being pressed, check and perform button action.
					this->actionID = this->buttonList[i]->getActionID();
					
				}
			}
			else 
				buttonList[i]->onMouseWithdraw();	
		}
	}
}

int GUI::getActionID() const
{
	return this->actionID;
}

void GUI::setActionID(int id)
{
	this->actionID = id;
}

int GUI::getYPosButtons() const
{
	return buttonList[0]->getGlobalBound().top;
}

void GUI::toggleButtonVisability(bool status)
{
	this->buttonsVisable = status;
}


void GUI::draw(sf::RenderWindow& window)
{
	if(this->buttonsVisable)
	{
		// Draw all buttons
		for (int i = 0; i < this->numButtons; i++)
		{
				window.draw(*buttonList[i]);
		}
	}
	// Draw all resourceBar.
	window.draw(resourceBar);
	//Draw all Text
	window.draw(Label_Wood);
	window.draw(Label_Iron);
	window.draw(Label_Gold);
	window.draw(Label_Food);
}
