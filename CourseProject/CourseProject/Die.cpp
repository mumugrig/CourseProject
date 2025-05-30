#include "Die.hpp"

void Die::seedRandom()
{
	pcg32_srandom_r(&rng, time(0), (size_t)&rng);
}

Die::Die() : value(0) {
	seedRandom();
}

Die::Die(const Die& other) : value(other.value) {
	seedRandom();
}

void Die::rollDie()
{
	value = pcg32_boundedrand_r(&rng, 6) + 1;
}


void Die::rollInBounds(int min, int max)
{
	value = pcg32_boundedrand_r(&rng, max-min+1) + min;
}

int Die::getValue() const {
	return value;
}
