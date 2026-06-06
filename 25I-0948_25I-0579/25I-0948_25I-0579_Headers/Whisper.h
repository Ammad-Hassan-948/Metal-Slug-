#pragma once
#include<iostream>
#include"WavHeader.h"




class Spectrum;

class Whisper {
private:
	WavHeader header;
	short int* data;    // using short to go with the 16 bit requirement as short has 2 bytes,64 bits
	int numSamples;
public:
	Whisper(const char* fileName);
	// i will also write a copy constructor as i need it when i am allocating a new object to copy and not to open from file
	Whisper(const Whisper& toCopy);
	// this is custom copy constructor
	Whisper(const WavHeader& header, int numSamples);
	~Whisper();
	// setter
	void setData(int index, short int value);
	float hardClipping(float scaledValue);
	void peakNormalization();
	Whisper& operator*=(float gain);
	void reverse();
	Whisper hardSplicing(int start, int end);
	Whisper operator+(const Whisper& track2);
	Whisper operator+=(const Whisper& append);
    // for FFT
	Spectrum performFFT();
	void saveToFile(const char* fileName);

};


