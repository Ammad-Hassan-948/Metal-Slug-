#include "HUD.h"
#include"ScoreManager.h"
#include"PlayerSoldier.h"
#include"Weapon.h"

void HUD::appendString(const char* toAppend, char* buffer, int& i)
{

	for (int j = 0; toAppend[j] != '\0'; j++) {
		buffer[i++] = toAppend[j];
	}
	buffer[i] = '\0';

}

void HUD::appendInt(int num, char* buffer, int& i)
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

HUD::HUD()
{
	// first load the font from our files
	font.loadFromFile("25I-0948_25I-0579/25I-0948_25I-0579_misc/font.ttf");

	// for top display
	topDisplay.setFont(font);
	topDisplay.setCharacterSize(24);
	// set this on the top left corner of screen
	topDisplay.setPosition(20, 20);



	devMode.setFont(font);
	devMode.setCharacterSize(24);
	devMode.setPosition(600, 20);


	// for bottom display
	bottomDisplay.setFont(font);
	bottomDisplay.setCharacterSize(24);
	bottomDisplay.setPosition(1150, 20); // top right
}

void HUD::render(sf::RenderWindow& window, PlayerSoldier* player)
{

	int score = ScoreManager::getTotalScore();
	int ammo = player->getCurrentWeapon()->getAmmo();
 

	// now i will set these strings according to requirements
	char top[100];
	int i = 0;
	appendString("SCORE: ", top, i);
	appendInt(score, top, i);
	appendString("     LIVES: ", top, i);
	appendInt(player->getLives(), top, i);


	char middle[50] = { '\0' };
	i = 0;

	if (player->getDevMode())
		appendString("DEVELOPER MODE", middle, i);




	i = 0;
	char bottom[100];

	appendString("WEAPON: ", bottom, i);
	appendString(player->getCurrentWeapon()->getName(), bottom, i);
	appendString("     AMMO: ", bottom, i);

	if (ammo == -1)
		appendString("INF: ", bottom, i);

	else
		appendInt(ammo, bottom, i);

	

	// 3. Update Text objects
	topDisplay.setString(top);
	bottomDisplay.setString(bottom);

	// 4. Draw (The HUD doesn't move with the camera!)
	window.draw(topDisplay);
	window.draw(devMode);
	window.draw(bottomDisplay);
}

