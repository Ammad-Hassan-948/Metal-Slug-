#include "AudioManager.h"
#include"Whisper.h"
#include"Filter.h"
#include"Spectrum.h"

void AudioManager::applyUnderwaterFilter(const char* inputAudio, const char* outputAudio)
{
    // first load this clean audio file using my whisper class
    Whisper cleanAudio(inputAudio);

    // apply fft on it
    Spectrum spectrum = cleanAudio.performFFT();

    // create a filter object based on size and sample rate
    Filter lowPassFilter(spectrum.getPaddedSamples(), spectrum.getSampleRate());

    // This is what i am using as a cut off threshhold for low pass
    lowPassFilter.lowPass(1200.0f);

    // also apply the filter
    spectrum.applyFilter(lowPassFilter);

    // now apply inverse fft to get this audio back into time domain
    Whisper muffledAudio = spectrum.inverseFFT();

    // Also save this file at output audio path
    muffledAudio.saveToFile(outputAudio);

}


AudioManager::AudioManager()
{
	isUnderwater = false;
}

AudioManager::~AudioManager()
{
	cleanMusic.stop();
    muffledMusic.stop();
}

void AudioManager::loadAndPlayMusic(const char* origPath, const char* muffledPath)
{
    applyUnderwaterFilter(origPath, muffledPath);

    // First i will play the normal music which is cleaned and original
    cleanMusic.openFromFile(origPath);
    muffledMusic.openFromFile(muffledPath);

    cleanMusic.setLoop(true);
    muffledMusic.setLoop(true);

    cleanMusic.setVolume(100.0f);
    muffledMusic.setVolume(0.0f);

    cleanMusic.play();
    muffledMusic.play();
}

void AudioManager::updateWaterState(bool inWater)
{
    // if our bool in water is true and was originally not under water
    if (inWater && !isUnderwater) {

        // make this bool true and stop current music
        isUnderwater = true;


        cleanMusic.setVolume(0.0f);
        muffledMusic.setVolume(100.0f);
    }
    // if bool was originally true and the input bool is now false go back to original audio
    else if (!inWater && isUnderwater) {

        isUnderwater = false;


        cleanMusic.setVolume(100.0f);
        muffledMusic.setVolume(0.0f);
    }
}
