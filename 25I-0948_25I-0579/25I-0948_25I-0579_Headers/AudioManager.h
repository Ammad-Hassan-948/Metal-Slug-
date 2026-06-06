#pragma once
#include <SFML/Audio.hpp>
#include <iostream>

using namespace sf;

class AudioManager
{
private:
    Music cleanMusic;
    Music muffledMusic;
    bool isUnderwater;

    // Helper to process the FFT
    void applyUnderwaterFilter(const char* inputAudio, const char* outputAudio);

public:
    AudioManager();
    ~AudioManager();

    // to setup and play the sound if under water
    void loadAndPlayMusic(const char* origPath, const char* muffledPath);

    // every frame to check if we need to swap
    void updateWaterState(bool inWater);
};
	


