#pragma once
#include "Libraries/pcg_basic.h"
#include <time.h>

class Die {
	int value;
	pcg32_random_t rng;

	void seedRandom()
	{
		pcg32_srandom_r(&rng, time(0), (size_t)this);
	}

public:
	Die() : value(0) {
		seedRandom();
	}

	Die(const Die& other) : value(other.value) {
		seedRandom();
	}

	Die& operator=(const Die&) = delete;

	void rollDie()
	{
		value = pcg32_boundedrand_r(&rng, 6) + 1;
	}

	int getValue() const {
		return value;
	}

	
};