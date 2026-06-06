#pragma once

#include "Game.h"
#include "GameStateManager.h"
#include "MenuState.h"

Game::Game():window(sf::VideoMode(1600, 900), "Metal Slug", sf::Style::Close) {
	//with a close button
	window.setFramerateLimit(60);

	stateManager = new GameStateManager();
	stateManager->changeState(new MenuState(stateManager, &window));
}

Game::~Game() {
	delete stateManager;
}

void Game::run() {

	while (window.isOpen()) {

		sf::Time elapsed = clock.getElapsedTime();
		clock.restart();
		float dt = elapsed.asSeconds();

		processEvents();
		update(dt);

		render();
	}
}

void Game::processEvents() {

	sf::Event ev;

	while (window.pollEvent(ev)) {

		if (ev.type == sf::Event::Closed) {
			window.close();
		}

		//stateManager->handleEvent(ev);
	}
}

void Game::update(float dt) {
	stateManager->update(dt);
}

void Game::render() {
	window.clear();
	stateManager->draw(window);
	window.display();
}

