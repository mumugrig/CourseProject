#pragma once
#include "Character.hpp"
#include "Die.hpp"
#include "Position.hpp"

/**
 * @class Felix
 * @brief A character that can reroll the player's die. Every third use forces a high roll (5 or 6).
 */
class Felix : public Character {
	/// Reference to the player's die.
	Die& die;
	/// Tracks how many times the ability has been used.
	int count;
	/**
	 * @brief No parameter initialization is required for Felix.
	 */
	void initializeParameters() override {}
public:
	/**
	 * @brief Constructs a Felix character.
	 * @param die Reference to a Die object Felix can reroll.
	 */
	Felix(Die& die);
	/**
	 * @brief Rerolls the die. Every third use forces a roll between 5 and 6.
	 * @throws std::runtime_error if the ability is on cooldown.
	 */
	void ability() override;
	/**
	 * @brief Returns a basic movement type with standard position behavior.
	 * @param position Pointer to the current position.
	 * @return The same position it was given
	 */
	Position* moveType(const Position* position) const override;
};