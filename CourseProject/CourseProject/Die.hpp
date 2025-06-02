/**
 * @file Die.hpp
 * @brief Declares the Die class, a random number generator simulating a die roll.
 */

#pragma once
#include "Libraries/pcg_basic.h"
#include <ctime>


 /**
  * @class Die
  * @brief Simulates a die using a PCG-based pseudo-random number generator.
  */
class Die {
	int value;	 ///< Last rolled value of the die.
	pcg32_random_t rng;		///< PCG random number generator state.

	/**
	 * @brief Seeds the internal random number generator with current time and memory address.
	 */
	void seedRandom();

public:
	/**
	 * @brief Default constructor. Seeds the RNG and initializes value to 0.
	 */
	Die();

	/**
	 * @brief Copy constructor. Copies value and reseeds the RNG.
	 * @param other The Die instance to copy from.
	 */
	Die(const Die& other);

	/// Deleted assignment operator to prevent copying RNG state.
	Die& operator=(const Die&) = delete;

	/**
	 * @brief Rolls a standard 6-sided die and stores the result.
	 */
	void rollDie();
	/**
	 * @brief Rolls the die within a custom [min, max] inclusive range.
	 * @param min The minimum value of the range.
	 * @param max The maximum value of the range.
	 */
	void rollInBounds(int min, int max);
	/**
	 * @brief Retrieves the most recently rolled value.
	 * @return The value rolled by the last call to rollDie or rollInBounds.
	 */
	int getValue() const;

	
};