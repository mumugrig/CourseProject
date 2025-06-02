#pragma once
#include "Character.hpp"
#include "BothBoardsPosition.hpp"
/**
 * @class Ash
 * @brief Concrete character "Ash" that can destroy a die on either board.
 *
 * This character can target and clear a die from any board position,
 * or trigger a cooldown effect on the opponent's character.
 */

class Ash : public Character {
	/// Target point selected for ability
	Point target;
	/// Indicates if this character belongs to player 1 (true) or player 2 (false)
	const bool player;
	/// Reference to player 1's board
	Board& player1Board;
	/// Reference to player 2's board
	Board& player2Board;
	/// Reference to opponent's character pointer (for cooldown effect)
	Character*& opponentCharacter;
	/**
	 * @brief Initializes ability parameters from the current selection.
	 */
	void initializeParameters() override;
public:
	/**
	 * @brief Constructs an Ash character.
	 *
	 * @param player1Board Reference to player 1's Board
	 * @param player2Board Reference to player 2's Board
	 * @param enemyCharacter Reference to pointer to opponent's Character
	 * @param player True if this character belongs to player 1, false otherwise
	 */
	Ash(Board& player1Board, Board& player2Board, Character*& enemyCharacter, bool player);

	/**
	 * @brief Returns the type of movement allowed by Ash.
	 *
	 * @param position Current position pointer
	 * @return BothBoardsPosition* New position object representing movement on both boards
	 */
	BothBoardsPosition* moveType(const Position* position) const override;

	/**
	* @brief Executes Ash's special ability.
	*
	* Ability destroys a die at the target location or applies cooldown effect on opponent.
	* @throws exceptions if selection isn't ready or if position is invalid.
	*/
	void ability() override;
};