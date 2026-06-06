#pragma once
#include<iostream>
#include<SFML/Graphics.hpp>
#include"PlayerSoldier.h"

using namespace std;

using namespace sf;


class HUD
{
private:
	// for font
	Font font;

	Text topDisplay;
	Text bottomDisplay;
	Text devMode;

	void appendString(const char* toAppend, char* buffer, int& i);
	void appendInt(int num, char* buffer, int& i);

public:
	HUD();
	void render(sf::RenderWindow& window, PlayerSoldier* player);

};


