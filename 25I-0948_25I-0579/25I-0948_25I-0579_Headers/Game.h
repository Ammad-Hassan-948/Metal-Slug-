#pragma once
#include <SFML/Graphics.hpp>

class GameStateManager;

class Game {
private:
	GameStateManager* stateManager; 
	sf::RenderWindow window;
	sf::Clock clock;
	void update(float dt);
	void processEvents();
	void render();
public:
	Game();
	~Game();
	void run();
};




//run the game, setup the clock open, run the while loop, in the while loop, update, render, repeat