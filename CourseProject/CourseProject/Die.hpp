#pragma once
#include "Libraries/pcg_basic.h"
#include <ctime>

class Die {
	int value;
	pcg32_random_t rng;

	void seedRandom();

public:
	Die();

	Die(const Die& other);

	Die& operator=(const Die&) = delete;

	void rollDie();
	void rollInBounds(int min, int max);
	int getValue() const;

	
};