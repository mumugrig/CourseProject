#pragma once
#include "Character.hpp"
#include "Board.hpp"
#include "ColumnSingleBoardPosition.hpp"

/**
 * @class Columna
 * @brief Character that lowers all dice values by one in a chosen column on the enemy board.
 */

class Columna : public Character {
	/// Reference to the enemy's Board
	Board& enemyBoard;
	/// Selected column index for ability
	int x;
	/**
	 * @brief Initializes parameters for the ability from the selection.
	 *
	 * @throws std::invalid_argument if the selected column is out of bounds.
	 */
	void initializeParameters() override;
public:
	/**
	* @brief Constructs a Columna character.
	*
	* @param enemyBoard Reference to the enemy's Board
	*/
	Columna(Board& enemyBoard);
	/**
	* @brief Executes Columna's ability to reduce dice values by one in a selected column.
	*
	* @throws std::runtime_error if the ability is on cooldown or the selection is not ready.
	*/
	void ability() override;
	/**
	 * @brief Returns the movement type used by Columna.
	 *
	 * Uses ColumnSingleBoardPosition to allow selecting a column.
	 *
	 * @param position Current position pointer
	 * @return ColumnSingleBoardPosition* New position object for movement
	 */

	ColumnSingleBoardPosition* moveType(const Position* position) const override;

};
