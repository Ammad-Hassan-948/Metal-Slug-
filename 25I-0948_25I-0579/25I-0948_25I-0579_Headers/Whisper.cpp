#include<iostream>
#include<fstream>
#include<cmath>
#include "Whisper.h"
#include "Spectrum.h"

using namespace std;

Whisper::Whisper(const char* fileName)
{
	this->data = nullptr;
	this->numSamples = 0;

	ifstream audio(fileName, ios::binary);   // opening the file
	
	if (audio.is_open()) {
         
		// to read the header exactly i use read function and cast my header into char* so it is shown as stream of bits and bytes
		// Also i have used sizeof(WavHeader) to make sure that compiler exactly allocates the space for header as in the struct WavHeader it has 
		// been restricted to take up exact size and not add padding

		audio.read((char*)&header, sizeof(WavHeader));

		// Now i will check for no of bytes of the sample
		if (header.bitsPerSample == 16) {
			// As 16 bits requires two bites to store, hence every sample will use 2 bytes so number of samples will be size/2 and also we save 
			// them as short which save 2 bytes, so it will not give a problem

			numSamples = header.subchunk2Size / 2;

			// Now i allocate a short int array of this size to store these values
			data = new short int[numSamples];
			
			// as our pointer to this file has currently read the header now it will move forward and read the next data
			audio.read((char*)data, header.subchunk2Size);
		}
		else if (header.bitsPerSample == 8) {
			// if it is 8 bits it will only require 1 byte
			numSamples = header.subchunk2Size;

			// As this data is 1 byte so i will first read into char arra
			unsigned char* temp = new unsigned char[numSamples];

			audio.read((char*)temp, header.subchunk2Size);

			// As we need to convert from 8 bit to 16 bit, unsigned 8 bit ranges from 0 to 255 and silence at 128, and signed 16 bit from
			// -32768 to 32767. When we convert from unsigned 8 bit to 16 bit, we need to silence by moving centre, now our audio moves from -128 to 127
			// we substract 128 from sample to silence and to scale the audio max for 8 bit is 127 and 16 bit is 32767

			// So we find a factor on boundary by 3276/128 = 256

			// short int memory is
			data = new short int[numSamples];

			for (int i = 0; i < numSamples; i++) {
				data[i] = (temp[i] - 128) * 256;
			}

			delete[] temp;

			// As our samples are converted to 16 bit we will also change other values
			header.bitsPerSample = 16;
			header.subchunk2Size *= 2;
			// Also changing byte rate and block align according to formula given as these were also before according to 8 bit
			header.byteRate = header.sampleRate * header.numChannels * 2;
			header.blockAlign = header.numChannels * 2;
		}
		else {
			cout << "Error! Unsported bit size " << fileName << " is "<<header.bitsPerSample <<"-bit." << endl;
		}
	}
	else {
		cout << "Could not find " << fileName << ". Check your file name and try again." << endl;
	}
}


// This is my constructor to return exactly a deep copy of the object sent
Whisper::Whisper(const Whisper& toCopy)
{
	// as WavHeader has all values and not any pointer so shallow copy will also work same way deep copy does
	this->header = toCopy.header;
	this->numSamples = toCopy.numSamples;

	data = new short int[numSamples];

	// i am writing 0 in data array and it will be filled in splice function
	for (int i = 0; i < numSamples; i++)
		this->data[i] = toCopy.data[i];
}



 Whisper::Whisper(const WavHeader& header, int numSamples)
{
	this->header = header;
	this->numSamples = numSamples;
	data = new short int[numSamples];
}

Whisper::~Whisper()
{
	delete[] data;
}

void Whisper::setData(int index, short int value)
{
	data[index] = value;
}



float Whisper::hardClipping(float scaledValue) {
	
	if (scaledValue > 32767)
		scaledValue = 32767;
	else if (scaledValue < -32768)
		scaledValue = -32768;

	return scaledValue;
}

void Whisper::peakNormalization()
{
	// first i will find the max value
	short int max = 0;

	// as i also need to look for negative peaks so i add absolute
	for (int i = 0; i < numSamples; i++) {
		if (abs(data[i]) > max) {
			max = abs(data[i]);
		}
	}

	// also a safety check
	if (max == 0)
		return;

	// Now i will find a factor to scale this value to max and multiply it to the whole buffer also clamping it, as maximum value is 32767
	float factor = float(32767)/max;

	for (int i = 0; i < numSamples; i++) {
		float scaledValue = data[i] * factor;

		data[i] = hardClipping(scaledValue);
	}
}

Whisper& Whisper::operator*=(float gain)
{
	for (int i = 0; i < numSamples; i++) {
		float gainedValue = data[i] * gain;

		data[i] = hardClipping(gainedValue);
	}

	return *this;
}

void Whisper::reverse()
{
	for (int i = 0; i < numSamples / 2; i++) {
		short int temp = data[i];
		data[i] = data[numSamples - i - 1];
		data[numSamples - i - 1] = temp;
	}
}

Whisper Whisper::hardSplicing(int start, int end)
{
	// first i will get the starting and ending indexes
	// As the audios are snapshots per seconds which is called the sample rate which is the ammount of snapshots per sample, so we get start 
	// and end times. we multiply the time by sample rate and also the number of channels and mono will store 1 but stereo will store 2
	start = start * header.sampleRate * header.numChannels;
	end = end * header.sampleRate * header.numChannels;

	if (start > numSamples)
		start = numSamples;

	if (end > numSamples)
		end = numSamples;

	int updatedSamples = end - start;   // this is the new number of spliced samples

	// Now i will make a header where i will make changes and then through my custom copy constructor allocate a new copy of this object
	WavHeader copyHead = header;   // this will cop element by element

	// the changes in header will be with the number of samples and their sizes

	copyHead.subchunk2Size = updatedSamples * 2;   // as every sample takes 2 bytes so size in bytes is
	copyHead.chunkSize = 36 + copyHead.subchunk2Size;  // as a head is of 44 bytes but first 8 butes are excluded from its size

	// Now i will call constructor to make an object with this header
	Whisper spliced(copyHead, updatedSamples);

	int index = start;
	for (int i = 0; i < updatedSamples; i++)
		spliced.data[i] = this->data[index++];

	return spliced;


}

Whisper Whisper::operator+(const Whisper& track2)
{
	int maxSamples = 0;
	WavHeader tempHead;

	// Here we will mix both audios and use the longest one for length
	if ((this->numSamples) >= (track2.numSamples)) {
		maxSamples = this->numSamples;
		tempHead = this->header;
	}
		
	else {
		maxSamples = track2.numSamples;
		tempHead = track2.header;
	}

	// updating values on base of new sample number for safety check
	tempHead.subchunk2Size = maxSamples * 2;   // as every sample takes 2 bytes so size in bytes is
	tempHead.chunkSize = 36 + tempHead.subchunk2Size;  // as a head is of 44 bytes but first 8 butes are excluded from its size

	// Now passing this largest header and no of samples to create a new whisper object
	Whisper result(tempHead, maxSamples);

	for (int i = 0; i < maxSamples; i++) {
		int value1 = 0;
		int value2 = 0;

		if (i < this->numSamples) {   //  making sure that we do not read out of bound if both data are of different size
			value1 = this->data[i];
		}
		if (i < track2.numSamples) {
			value2 = track2.data[i];
		}

		result.data[i] = hardClipping(value1 + value2);           // saving value after clipping
	}

	return result;
		
}

Whisper Whisper::operator+=(const Whisper& append)
{
	int newNumSamples = this->numSamples + append.numSamples;        // finding new size which is sum of both

	short int* temp = new short int[newNumSamples];

	int index = 0;
	// first i will copy data from this
	for (int i = 0; i < this->numSamples; i++)
		temp[index++] = this->data[i];

	// then from append
	for (int i = 0; i < append.numSamples; i++)
		temp[index++] = append.data[i];

	delete[] this->data;

	this->data = temp;

	this->numSamples = newNumSamples;

	// updating values on base of new sample number for safety check
	header.subchunk2Size = newNumSamples * 2;   // as every sample takes 2 bytes so size in bytes is
	header.chunkSize = 36 + header.subchunk2Size;  // as a head is of 44 bytes but first 8 butes are excluded from its size

	return *this;
}

Spectrum Whisper::performFFT()
{
	int bits = 0;
	// first i will ensure or find the next power of 2 for padding of my numSamples
	int padding = 2;
	for (int i = 1;; i++) {
		if (padding >= numSamples) {
			bits = i;          // i also save the power of 2 the padding is so can know the no of bits i need to rotate
			break;
		}

		padding *= 2;
	}

	// Now i will allocate a temporary complex obect to perform all operations
	Complex* bins = new Complex[padding];

	// Now my array of complex objects is created and my default constructor for complex has already filled it with 0
	// So i copy the data elements to the real part of these objects
	for (int i = 0; i < numSamples; i++)
		bins[i] = Complex(data[i], 0.0f);   // i have assigned bin a complex object with data as real part

	// now according to the algorithm i will shift the bits
	for (int i = 0; i < padding; i++) {
		
		int reversed = 0;

		// to reverse the bits i will use bitwise
		for (int j = 0; j < bits; j++) {
			reversed = reversed | (((i >> j) & 1) << (bits - j - 1));
		}

		if (reversed > i) {  // according to theorem we reverse only if reversed index is greater than original
			Complex temp = bins[i];
			bins[i] = bins[reversed];
			bins[reversed] = temp;
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
				float angle = -2.0f * PI * j / n;

				// Now i will create a twiddle factor using this angle. I will make a complex object twidle in which real part will be cos of 
				// that angle and imaginary part will be sin of that angle
				Complex twidle = Complex(cos(angle), sin(angle));

				// Now i will grab two elements , the top element is
				Complex topElement = bins[i + j];
				// the bottom element is half step ahead
				Complex bottomElement = bins[i + j + n / 2];

				// Now we will find the twiddle factor by multiplying the bottom element with twidle
				Complex factor = bottomElement * twidle;   // i have used the operator overloading function

				// Then the new top and bottom elements will be
				bins[i + j] = topElement + factor;
				bins[i + j + n / 2] = topElement - factor;
			}

		}
	}


	// Now as i have my bin array prepared i will hand all elements to Spectrum constructor and return that

	Spectrum frequency(header, numSamples, padding, bins);

	delete[] bins;

	return frequency;


}

void Whisper::saveToFile(const char* fileName)
{
	ofstream outputFile(fileName, ios::binary);

	if (outputFile.is_open()) {
		// first write the header
		outputFile.write((char*)&header, sizeof(WavHeader));
		// now write the actual data
		outputFile.write((char*)data, numSamples * sizeof(short int));

		outputFile.close();
	}
}

