#pragma once

// i am using static here so it would be accessible to all as a class not as an object
class ScoreManager
{
private:
	static int totalScore;
	static bool flawlessVictory;
	static int highScores[5];
public:
	static void addScore(int amount);
	static int getTotalScore();
	static void recordFlawlessVictory();
	static bool hasFlawlessVictory();
	static void resetVictory();

	static void loadHighScores();
	static void saveHighScores();
	static void updateHighScores();
	static int getHighScore(int index);
};

