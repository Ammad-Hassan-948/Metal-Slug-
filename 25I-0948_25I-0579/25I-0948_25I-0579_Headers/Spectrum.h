#pragma once
#include<iostream>
#include"Complex.h"
#include"Filter.h"
#include"WavHeader.h"


class Whisper;

class Spectrum {
private:
	WavHeader header;
	Complex* frequencyBins;
	int originalSamples;
	int paddedSamples;
public:
	// constructor
	Spectrum(const WavHeader& header, int originalSize, int paddedSize, Complex* bins);
	// copy constructor
	Spectrum(const Spectrum& other);
	// destructor
	~Spectrum();
	// getters
	int getPaddedSamples();
	int getSampleRate();
	// functions
	Whisper inverseFFT();
	void applyFilter(Filter& weights);
};