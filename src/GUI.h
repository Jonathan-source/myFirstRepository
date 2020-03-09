#ifndef GUI_H
#define GUI_H

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Camera.h"

class GUI {

public:
	GUI(Camera *camera);
	void initTextLabels();
	virtual ~GUI();

	// Methods
	void draw(sf::RenderWindow& window);
	void update();
	void checkButtonAction(sf::RenderWindow &window, sf::Event &event);
	void toggleButtonVisability(bool status);
	void addToWood(int _sum);
	int getActionID() const;
	void setActionID(int id);
	int getYPosButtons() const;
private:
	sf::RectangleShape resourceBar;

	sf::Text Label_Population;
	sf::Text Label_Food;
	sf::Text Label_Wood;
	sf::Text Label_Stone;
	sf::Text Label_Gold;
	sf::Text Label_Iron;

	int woodAmount;
	int foodAmount;
	int goldAmount;
	int ironAmount;
	sf::Font font;

	Camera *camera;
	
	int actionID;

	// Methods
	void init_buttons();
	void init_resourceBar();
	

	// Buttons
	static const int numButtons = 10;
	Button *buttonList[numButtons];
	bool buttonsVisable;
};

#endif
