#include "Animator.h"
#include"Helpers.h"

Animator::Animator(Sprite* targetSprite, int states, int* framesPerState, float* timers, int gridSize): sprite(targetSprite), 
numStates(states), currentState(0), currentFrame(0), currentTime(0), gridSize(gridSize), 
numFrames(copyIntegars(framesPerState, numStates)), stateTimer(copyFloat(timers, numStates)), flipDir(false)
{
	// set the first state and its first frame manually as the first sprite
	updateTextureRect();
}

Animator::~Animator()
{
	delete[] numFrames;
	delete[] stateTimer;
}

void Animator::updateTextureRect()
{
	// first get x and y positions according to grid size
	int xPosition = currentFrame * gridSize;
	int yPosition = currentState * gridSize;

	// if direction is not flipped get simple frame from start to end
	if (!flipDir) {
		sprite->setTextureRect(IntRect(xPosition, yPosition, gridSize, gridSize));
	}
	else {
		// for left frame start from right and go till left side
		sprite->setTextureRect(IntRect(xPosition + gridSize, yPosition, -gridSize, gridSize));
	}
}

void Animator::setState(int s)
{
	if (s >= 0 && s < numStates) {
		if (s != currentState) {
			currentState = s;
			currentFrame = 0;
			currentTime = 0.0f;
		}
		updateTextureRect();
	}
}

void Animator::setFlipDir(bool f)
{
	if (flipDir != f) {
		flipDir = f;
		updateTextureRect();
	}
}

bool Animator::isLastFrame() const
{
	if (currentFrame == numFrames[currentState] - 1)
		return true;

	return false;
}

void Animator::update(float passedTime)
{
	// first add the time passed since last game loop
	currentTime += passedTime;

	// now i will first check if i have to change the frame if time for one frame has passed
	if (currentTime > stateTimer[currentState]) {
		// reset the timer by substracting the actual time for that state to avoid lag if timer has passed ahead already
		currentTime -= stateTimer[currentState];

		// change the frame
		currentFrame++;

		// now also check if the frames for this state have ended so we can restart this state from 1st frame again
		if (currentFrame >= numFrames[currentState]) {

			// then start again from 1st frame of this state
			currentFrame = 0;
		}

		updateTextureRect();
	}
}

