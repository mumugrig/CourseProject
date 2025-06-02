/**
 * @file RetainBothBoardsPosition.hpp
 * @brief Position that retains selection on both boards based on given Selection.
 */
#pragma once
#include "BothBoardsPosition.hpp"
#include "Selection.hpp"
#include "VectorUtility.hpp"
 /**
  * @class RetainBothBoardsPosition
  * @brief Extends BothBoardsPosition and restricts selection based on a Selection object.
  */
class RetainBothBoardsPosition : public BothBoardsPosition {
	/// Reference to a Selection object controlling valid positions
	const Selection& selection;

public:
	/**
	 * @brief Constructs with a Selection reference.
	 * @param selection Reference to a Selection controlling allowed points.
	 */
	RetainBothBoardsPosition(Selection& selection);
	/**
	 * @brief Constructs from another Position and a Selection reference.
	 * @param other Base Position to copy.
	 * @param selection Reference to a Selection controlling allowed points.
	 */
	RetainBothBoardsPosition(const Position& other, const Selection& selection);
	/**
	 * @brief Checks if player 1 has selected the position.
	 * True if point matches current position on board2 or in the Selection parameters.
	 * @param x X-coordinate to check.
	 * @param y Y-coordinate to check.
	 * @return True if player 1 selection condition met.
	 */
	bool player1SelectCondition(int x, int y) override;
	/**
	* @brief Checks if player 2 has selected the position.
	* True if point matches current position on board1 or in the Selection parameters.
	* @param x X-coordinate to check.
	* @param y Y-coordinate to check.
	* @return True if player 2 selection condition met.
	*/
	bool player2SelectCondition(int x, int y) override;
};