#pragma once
#include "ModeSelectState.h"
#include "SurvivalState.h"
#include "CampaignState.h"
#include "SelfPlayState.h"
#include"GameStateManager.h"

ModeSelectState::ModeSelectState(GameStateManager* mgr, sf::RenderWindow* win) {
	manager = mgr;
	window = win;
	selectedIndex = 0;
	keyDelay = 0.3f;

	bgTexture.loadFromFile("assets/Backgrounds/ModeSelect.png");
	bgSprite.setTexture(bgTexture);
	bgSprite.setScale(
		(float)win->getSize().x / bgTexture.getSize().x,
		(float)win->getSize().y / bgTexture.getSize().y
	);

	font.loadFromFile("assets/Fonts/font.ttf");

	title.setFont(font);
	title.setString("SELECT MODE");
	title.setCharacterSize(60);
	title.setFillColor(sf::Color::White);
	title.setPosition(600, 300);

	option1.setFont(font);
	option1.setString("SURVIVAL MODE");
	option1.setCharacterSize(40);
	option1.setPosition(620, 430);

	option2.setFont(font);
	option2.setString("CAMPAIGN MODE");
	option2.setCharacterSize(40);
	option2.setPosition(620, 500);

	option3.setFont(font);
	option3.setString("SELF-PLAY MODE");
	option3.setCharacterSize(40);
	option3.setPosition(620, 570);


}

void ModeSelectState::update(float dt) {
	keyDelay -= dt;

	if (keyDelay <= 0) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			selectedIndex++;
			if (selectedIndex > 2) {
				selectedIndex = 0;
			}
			keyDelay = 0.2f;
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
			selectedIndex--;
			if (selectedIndex < 0) {
				selectedIndex = 2;
			}
			keyDelay = 0.2f;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && keyDelay <= 0) {
		if (selectedIndex == 0) {
			manager->changeState(new SurvivalState(manager, window, 2));

		}
		else if (selectedIndex == 1) {
			manager->changeState(new CampaignState(manager, window));

		}
		else {
			//manager->changeState(new SelfPlayState(manager, window));
		}
		return;
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		if (window) window->close();
		return;
	}

}

void ModeSelectState::draw(sf::RenderWindow& win) {
	win.draw(bgSprite);
	win.draw(title);
	if (selectedIndex == 0) {
		option1.setFillColor(sf::Color::Yellow);
	}
	else {
		option1.setFillColor(sf::Color::White);
	}

	if (selectedIndex == 1) {
		option2.setFillColor(sf::Color::Yellow);
	}
	else {
		option2.setFillColor(sf::Color::White);
	}

	if (selectedIndex == 2) {
		option3.setFillColor(sf::Color::Yellow);
	}
	else {
		option3.setFillColor(sf::Color::White);
	}

	win.draw(option1); win.draw(option2); win.draw(option3);
}
