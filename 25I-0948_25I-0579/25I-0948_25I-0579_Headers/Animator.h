#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>

using namespace sf;

class Animator {
private:
	Sprite* sprite;
	int numStates;
	int* numFrames;
	float* stateTimer;
	int currentState;
	int currentFrame;
	float currentTime;
	int gridSize;
	// also to flip direction
	bool flipDir;
	void updateTextureRect();
public:
	Animator(Sprite* targetSprite, int states, int* framesPerState, float* timers, int gridSize);
	~Animator();
	void setState(int s);
	void setFlipDir(bool f);
	bool isLastFrame()const;
	// I am passing the passed time since last update call here so that animations change perfectly regardeless of how fast the 
	// game loop runs they will depend on the passed time from the computer
	void update(float passedTime);
	
};

