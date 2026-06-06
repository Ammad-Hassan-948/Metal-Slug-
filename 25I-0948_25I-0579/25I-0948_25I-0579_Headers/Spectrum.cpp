#include<iostream>
#include "Spectrum.h"
#include "Whisper.h"

Spectrum::Spectrum(const WavHeader& header, int originalSize, int paddedSize, Complex* bins)
{
	this->header = header;
	this->originalSamples = originalSize;
	this->paddedSamples = paddedSize;

	// Now for bins i will make a deep copy of it
	this->frequencyBins = new Complex[paddedSamples];
	for (int i = 0; i < paddedSize; i++) {
		// using my copy constructor to copy
		this->frequencyBins[i] = bins[i];
	}
}

Spectrum::~Spectrum()
{
	delete[] frequencyBins;
}

int Spectrum::getPaddedSamples()
{
	return paddedSamples;
}

int Spectrum::getSampleRate()
{
	return header.sampleRate;
}

Spectrum::Spectrum(const Spectrum& other)
{
	this->header = other.header;
	this->originalSamples = other.originalSamples;
	this->paddedSamples = other.paddedSamples;

	// Now for bins i will make a deep copy of it
	this->frequencyBins = new Complex[paddedSamples];
	for (int i = 0; i < paddedSamples; i++) {
		// using my copy constructor to copy
		this->frequencyBins[i] = other.frequencyBins[i];
	}
}



Whisper Spectrum::inverseFFT()
{
	int bits = 0;
	// first i will ensure or find the next power of 2 for padding of my numSamples
	int padding = 2;
	for (int i = 1;; i++) {
		if (padding >= originalSamples) {
			bits = i;          // i also save the power of 2 the padding is so can know the no of bits i need to rotate
			break;
		}

		padding *= 2;
	}



	// now according to the algorithm i will shift the bits
	for (int i = 0; i < padding; i++) {

		int reversed = 0;

		// to reverse the bits i will use bitwise
		for (int j = 0; j < bits; j++) {
			reversed = reversed | (((i >> j) & 1) << (bits - j - 1));
		}

		if (reversed > i) {  // according to theorem we reverse only if reversed index is greater than original
			Complex temp = frequencyBins[i];
			frequencyBins[i] = frequencyBins[reversed];
			frequencyBins[reversed] = temp;
		}

	}



	// now i will apply the algorithm and make chunks
	const float PI = 3.14159265f;



	// first loop
	for (int n = 2; n <= padding; n *= 2) {

		// second loop
		for (int i = 0; i < padding; i += n) {

			// third loop
			for (int j = 0; j < n / 2; j++) {

				// Now here i will first find angle
				float angle = 2.0f * PI * j / n;

				// Now i will create a twiddle factor using this angle. I will make a complex object twidle in which real part will be cos of 
				// that angle and imaginary part will be sin of that angle
				Complex twidle = Complex(cos(angle), sin(angle));

				// Now i will grab two elements , the top element is
				Complex topElement = frequencyBins[i + j];
				// the bottom element is half step ahead
				Complex bottomElement = frequencyBins[i + j + n / 2];

				// Now we will find the twiddle factor by multiplying the bottom element with twidle
				Complex factor = bottomElement * twidle;   // i have used the operator overloading function

				// Then the new top and bottom elements will be
				frequencyBins[i + j] = topElement + factor;
				frequencyBins[i + j + n / 2] = topElement - factor;
			}

		}
	}



	// Now i will scale down the frequencies by dividing them by padding as due to the padding the frequencies were scaled up
	for (int i = 0; i < paddedSamples; i++) {
		// first i will get the real and imaginary parts using getters
		float real = frequencyBins[i].getRealPart() / padding;
		float imag = frequencyBins[i].getImaginaryPart() / padding;

		frequencyBins[i] = Complex(real, imag);
	}



	WavHeader copy = this->header;

	// updating values on base of new sample number for safety check
	copy.subchunk2Size = originalSamples * 2;   // as every sample takes 2 bytes so size in bytes is
	copy.chunkSize = 36 + copy.subchunk2Size;  // as a head is of 44 bytes but first 8 butes are excluded from its size



	// creating a whisper object with this header and this size
	Whisper inversed(copy, originalSamples);



	for (int i = 0; i < originalSamples; i++) {
		// now we will seperate this sample and by performing hard clipping then will store it in data
		float value = frequencyBins[i].getRealPart();

		value = inversed.hardClipping(value);

		inversed.setData(i, short(value));
	}



	return inversed;


}

void Spectrum::applyFilter(Filter& weights)
{
	// i will multiply each frequency bin by its corresponding weight to both real and imaginary parts of complex objects
	for (int i = 0; i < paddedSamples; i++) {
		float sampleWeight = weights.getWeight(i);

		float realP = frequencyBins[i].getRealPart() * sampleWeight;
		float imagP = frequencyBins[i].getImaginaryPart() * sampleWeight;

		frequencyBins[i] = Complex(realP, imagP);
	}
}

