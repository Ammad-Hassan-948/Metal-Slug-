#include"ScoreManager.h"
#include<fstream>
#include<iostream>

using namespace std;

int ScoreManager::totalScore = 0;

bool ScoreManager::flawlessVictory = false;

int ScoreManager::highScores[5] = { 0, 0, 0, 0, 0 };

void ScoreManager::addScore(int amount)
{
	totalScore += amount;

}

int ScoreManager::getTotalScore()
{
	return totalScore;
}

void ScoreManager::recordFlawlessVictory()
{
	flawlessVictory = true;
}

bool ScoreManager::hasFlawlessVictory()
{
	return flawlessVictory;
}

void ScoreManager::resetVictory()
{
	flawlessVictory = false;
}

void ScoreManager::loadHighScores()
{

	ifstream file("25I-0948_25I-0579/25I-0948_25I-0579_misc/highScores.txt");

	if (file.is_open()) {
		
		for (int i = 0; i < 5; i++) {

			// read each high score seperately
			if (!(file >> highScores[i])) 
				break; 

		}
		file.close();

	}
}

void ScoreManager::saveHighScores()
{

	ofstream file("25I-0948_25I-0579/25I-0948_25I-0579_misc/highscores.txt");
	for (int i = 0; i < 5; i++) {
		file << highScores[i] << "\n";

	}
	file.close();

}

void ScoreManager::updateHighScores()
{
	// get the current score
	int current = totalScore;

	for (int i = 0; i < 5; i++) {

		// check if current is greater than any highScore
		if (current > highScores[i]) {

			// loop ahead and adjust this
			for (int j = 4; j > i; j--) {
				highScores[j] = highScores[j - 1];
			}

			// save the current high score
			highScores[i] = current;
			break;

		}
	}

	saveHighScores();
	
}

int ScoreManager::getHighScore(int index)
{
	return highScores[index];
}

