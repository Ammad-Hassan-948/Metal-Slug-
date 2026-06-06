#pragma once
#include<iostream>

class Filter {
private:
	float* weights;
	int paddedSamples;
	int sampleRate;
public:
	Filter(int paddedSamples, int sampleRate);
	~Filter();
	Filter(const Filter& other);
	// getters
	float getWeight(int index);
	// functions
	void lowPass(float threshhold);
	void highPass(float threshhold);
	void bandPass(float lowerBound, float higherBound);
};