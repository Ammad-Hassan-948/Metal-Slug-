#include "ProfileFactory.h"
#include"NoiseProfiles.h"
#include "GameConstants.h"

INoiseProfile* ProfileFactory::create(int profileKind, unsigned int seed)
{
	if (profileKind == ProfileKind::AMPLIFIED) {
		return new AmplifiedProfile(seed);
	}

	if (profileKind == ProfileKind::FLAT) {
		return new FlatProfile(seed);
	}

		return new NormalProfile(seed);
	
}

