#pragma once
#include<iostream>
#include "MenuState.h"

#include "GameStateManager.h"
#include "ModeSelectState.h"
#include"ScoreManager.h"

using namespace std;

void MenuState::appendString(const char* toAppend, char* buffer, int& i)
{
	for (int j = 0; toAppend[j] != '\0'; j++) {
		buffer[i++] = toAppend[j];
	}
	buffer[i] = '\0';
}

void MenuState::appendInt(int num, char* buffer, int& i)
{
	if (num == 0) {
		buffer[i++] = '0';
		buffer[i] = '\0';
	}


	// now i will convert this no into char
	char temp[20];
	int j = 0;
	while (num > 0) {
		temp[j++] = (char)(num % 10 + '0');
		num /= 10;
	}

	// now copy this in reverse to buffer
	while (j > 0) {
		buffer[i++] = temp[--j];
	}

	buffer[i] = '\0';
}

MenuState::MenuState(GameStateManager* mgr, sf::RenderWindow* win) : manager(mgr), window(win) {


	bgTexture.loadFromFile("assets/Backgrounds/start.png");
	bgSprite.setTexture(bgTexture);
	bgSprite.setScale(
		(float)win->getSize().x / bgTexture.getSize().x,
		(float)win->getSize().y / bgTexture.getSize().y
	);

	if (!font.loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_misc/font.TTF")) {
	//left for now
	cout << "Font couldn't load";

	}

		text.setFont(font);
		text.setString("PRESS ENTER TO START");
		text.setCharacterSize(50);
		text.setFillColor(sf::Color::White);
		text.setPosition(500, 450);





		ScoreManager::loadHighScores();

		leaderboardTitle.setFont(font);
		leaderboardTitle.setString("TOP 5 HIGH SCORES");
		leaderboardTitle.setPosition(50, 50);

		leaderboardContent.setFont(font);
		char scores[100] = "";
		int index = 0;
		for (int i = 0; i < 5; i++) {
			appendInt(i + 1, scores, index);
			appendString(". ", scores, index);
			appendInt(ScoreManager::getHighScore(i), scores, index);
			appendString("\n", scores, index);

		}
		leaderboardContent.setString(scores);
		leaderboardContent.setPosition(50, 100);



	}


void MenuState::update(float dt) {
	//maybe animations here; nothing else right now
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
		manager->changeState(new ModeSelectState(manager, window));
		return;
	}
}
void MenuState::draw(sf::RenderWindow& win) {
	win.draw(bgSprite);
	win.draw(leaderboardTitle);
	win.draw(leaderboardContent);
	win.draw(text);
	//win.draw(score);

}
