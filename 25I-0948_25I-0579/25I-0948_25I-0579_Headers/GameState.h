#pragma once
#include "SFML/Graphics.hpp"

//class Event;

class GameState {
public:
	virtual ~GameState() = default;//without this virtual, only gameState's own destructor will run, and memory will be leaked
	//default for just default destructor
	virtual  void update(float dt) = 0;
	virtual void draw(sf::RenderWindow& win) = 0;

};

//class PlayState :public GameState {
//
//};
//
//
//class Menu :public GameState {
//	Event ev;
//	//press enter to move to the PlayState or later to any state either play or self play or whatever
//	while (window.isOpen()) {
//		while(window.pollEvent(ev))//add ev object here
//			if (ev.type == isKeyPressed::Enter) {
//				GameStateManager::changeState(playState);
//		}
//	}
//};