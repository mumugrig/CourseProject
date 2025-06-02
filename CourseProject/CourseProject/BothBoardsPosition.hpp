/**
 * @file BothBoardsPosition.hpp
 * @brief Defines BothBoardsPosition class representing a position that wraps around two boards.
 */
#pragma once
#include "Position.hpp"
 /**
  * @class BothBoardsPosition
  * @brief Extends Position to allow movement that wraps across two boards.
  */
class BothBoardsPosition : public Position{
public:
	/**
	 * @brief Default constructor.
	 */
	BothBoardsPosition() : Position() {}
	/**
	 * @brief Copy constructor from Position.
	 * @param other Position to copy from.
	 */
	BothBoardsPosition(const Position& other) : Position(other) {}
	/**
	* @brief Moves position up, wrapping to the other board if moving above top row.
	*/
	virtual void moveUp() override;
	/**
	* @brief Moves position down, wrapping to the other board if moving below bottom row.
	*/
	virtual void moveDown() override;
	/**
	* @brief Moves position left, wrapping horizontally within the board.
	*/
	virtual void moveLeft() override;
	/**
	* @brief Moves position right, wrapping horizontally within the board.
	*/
	virtual void moveRight() override;
};