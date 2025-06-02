/**
 * @file Point.hpp
 * @brief Defines the Point struct used to represent a position on a board.
 */

#pragma once

 /**
  * @class Point
  * @brief Represents a 2D coordinate on a board with an additional flag indicating which board (e.g., player 1 or 2).
  */

struct Point {
	int x;	///< X-coordinate (column).
	int y;	 ///< Y-coordinate (row).
	bool board;	///< Indicates which board this point belongs to (e.g., false = board1, true = board2).

	/**
	 * @brief Default constructor. Initializes to (0, 0) on board1.
	 */
	Point() : x(0), y(0), board(0) {}
	/**
	 * @brief Parameterized constructor.
	 * @param x X-coordinate.
	 * @param y Y-coordinate.
	 * @param board Board indicator.
	 */
	Point(int x, int y, bool board) : x(x), y(y), board(board) {} 
	/**
	 * @brief Equality operator.
	 * @param other Another Point to compare with.
	 * @return True if both points have the same coordinates and board flag.
	 */
	bool operator==(const Point& other) const{
		return x == other.x && y == other.y && board == other.board;
	}
};