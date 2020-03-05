#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>
#include "State.h"
#include <string>

class GameState
{
public:
	GameState();
	virtual ~GameState();
	virtual State update() = 0;
	virtual void render() = 0;
	virtual void handleEvents() = 0;
};

#endif