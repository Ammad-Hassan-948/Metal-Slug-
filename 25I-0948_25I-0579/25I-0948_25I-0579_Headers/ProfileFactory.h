#pragma once
#include"INoiseProfile.h"


class ProfileFactory {

public:

	static INoiseProfile* create(int profileKind, unsigned int seed);

private:

	ProfileFactory(){}
};