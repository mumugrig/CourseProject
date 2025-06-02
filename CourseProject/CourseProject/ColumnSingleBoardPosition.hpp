/**
 * @file ColumnSingleBoardPosition.hpp
 * @brief Defines ColumnSingleBoardPosition which restricts selection by column and board.
 */
#pragma once
#include "Position.hpp"
 /**
  * @class ColumnSingleBoardPosition
  * @brief Position variant that restricts selection to a single column on a single board.
  */
class ColumnSingleBoardPosition : public Position {
public:
	/**
	* @brief Default constructor.
	*/
	ColumnSingleBoardPosition();
	/**
	 * @brief Constructs from another Position.
	 * @param other Position to copy.
	 */
	ColumnSingleBoardPosition(const Position& other);
	/**
	 * @brief Checks if player 1 has selected the position.
	 * Selects all cells on a column in Player1 board
	 * @param x X-coordinate to check.
	 * @param y Y-coordinate to check.
	 * @return True if selection condition met.
	 */
	bool player1SelectCondition(int x, int y) override;
	/**
	 * @brief Checks if player 2 has selected the position.
	 * Selects all cells on a column in Player2 board
	 * @param x X-coordinate to check.
	 * @param y Y-coordinate to check.
	 * @return True if selection condition met.
	 */
	bool player2SelectCondition(int x, int y) override;

};