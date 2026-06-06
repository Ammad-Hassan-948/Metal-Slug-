#include<iostream>
#include "Filter.h"

Filter::Filter(int paddedSamples, int sampleRate)
{
	this->paddedSamples = paddedSamples;
	this->sampleRate = sampleRate;
	weights = new float[paddedSamples];

	// fill with 0.0
	for (int i = 0; i < paddedSamples; i++)
		weights[i] = 0.0f;
  
}

Filter::~Filter()
{
	delete[] weights;
}

Filter::Filter(const Filter& other)
{
	this->paddedSamples = other.paddedSamples;
	this->sampleRate = other.sampleRate;
	weights = new float[paddedSamples];

	// fill with 0.0
	for (int i = 0; i < paddedSamples; i++)
		this->weights[i] = other.weights[i];
}

float Filter::getWeight(int index)
{
	return weights[index];
}

void Filter::lowPass(float threshhold)
{
	// first i will find the index until which i need to perform the operation
	// as we have the sample rate and total size, sample rate is choped evenly on whole size so frequenc per sample will be
	//      float perSample = (float)sampleRate / paddedSamples;
	// Now for index we will divide this b the total frequency we have to reach 
	//      int index = threshhold / perSample;
	// so full formula is

	int index = threshhold * paddedSamples / sampleRate;

	// i am adding a safety check so that index does not go beyond the limit of one part of mirror image
	if (index > paddedSamples / 2)
		index = paddedSamples / 2;

	// Now we have to keep frequencies till this index and above this index will be 0, as this bin is a mirror image so we will aply same logic 
	// for both left and right side
	for (int i = 0; i < index; i++)
		weights[i] = 1.0f;
	// now for frequencies after this index
	for (int i = index; i < paddedSamples / 2; i++)
		weights[i] = 0.0f;

	// as this array ill be a mirror image so for the right side
	for (int i = paddedSamples / 2; i < paddedSamples - index; i++)
		weights[i] = 0.0f;
	for (int i = paddedSamples - index; i < paddedSamples; i++)
		weights[i] = 1.0f;

}


void Filter::highPass(float threshhold)
{
	// first i will find the index until which i need to perform the operation
	// as we have the sample rate and total size, sample rate is choped evenly on whole size so frequenc per sample will be
	//     float perSample = (float)sampleRate / paddedSamples;
	// Now for index we will divide this b the total frequency we have to reach 
	//     int index = threshhold / perSample;
	// so full formula is

	int index = threshhold * paddedSamples / sampleRate;

	// i am adding a safety check so that index does not go beyond the limit of one part of mirror image
	if (index > paddedSamples / 2)
		index = paddedSamples / 2;

	// Now we have to keep frequencies till this index and above this index will be 0, as this bin is a mirror image so we will aply same logic 
	// for both left and right side
	for (int i = 0; i < index; i++)
		weights[i] = 0.0f;
	// now for frequencies after this index
	for (int i = index; i < paddedSamples / 2; i++)
		weights[i] = 1.0f;

	// as this array ill be a mirror image so for the right side
	for (int i = paddedSamples / 2; i < paddedSamples - index; i++)
		weights[i] = 1.0f;
	for (int i = paddedSamples - index; i < paddedSamples; i++)
		weights[i] = 0.0f;

}

void Filter::bandPass(float lowerBound, float higherBound)
{
	// first i will find the index until which i need to perform the operation
	// as we have the sample rate and total size, sample rate is choped evenly on whole size so frequenc per sample will be
	//     float perSample = (float)sampleRate / paddedSamples;
	// Now for index we will divide this b the total frequency we have to reach 
	//     int index = threshhold / perSample;
	// so full formula is

	int lowIndex = lowerBound * paddedSamples / sampleRate;
	int highIndex = higherBound * paddedSamples / sampleRate;

	// these are safet checks to carry out edge cases 
	if (lowIndex > paddedSamples / 2)
		lowIndex = paddedSamples / 2;
	if (highIndex > paddedSamples / 2)
		highIndex = paddedSamples / 2;
	if (lowIndex > highIndex)
		lowIndex = highIndex;

	// for left side of mirror
	for (int i = 0; i < lowIndex; i++)
		weights[i] = 0.0f;

	for (int i = lowIndex; i < highIndex; i++)
		weights[i] = 1.0f;

	for (int i = highIndex; i < paddedSamples / 2; i++)
		weights[i] = 0.0f;

	// for right side of mirror
	for (int i = paddedSamples / 2; i < paddedSamples - highIndex; i++)
		weights[i] = 0.0f;

	for (int i = paddedSamples - highIndex; i < paddedSamples - lowIndex; i++)
		weights[i] = 1.0f;

	for (int i = paddedSamples - lowIndex; i < paddedSamples; i++)
		weights[i] = 0.0f;

}

