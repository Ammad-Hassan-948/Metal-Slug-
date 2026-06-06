#pragma once

//block is the atomic unit of the game world 
//tracking three items, its type, hp and filledByRain which will 
//distinguish between ocean watter from puddle water
//so that rain logic doesnt fill the already ocean tiles


struct Block {

	int type; //air, grass, water etc

	int hp;

	bool filledByRain;

	Block():type(0), hp(0), filledByRain(false){}

	Block(int t, int h, bool rain = false): type(t), hp(hp), filledByRain(false){}



};

