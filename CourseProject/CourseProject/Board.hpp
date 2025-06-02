/**
 * @file Board.hpp
 * @brief Defines the Board class used in the game, managing a 3x3 grid.
 */

#pragma once
#include <iostream>
 /**
  * @class Board
  * @brief Represents a 3x3 board for a game where players can place values (typically dice rolls).
  */
class Board {
	int board[3][3]; ///< Internal 3x3 grid representing board values.
	
	/**
	 * @brief Calculates a score for a given column based on value matches.
	 * @param column An array of 3 integers representing one column of the board.
	 * @return Computed score for the column.
	 */
	int columnScore(int column[]) const;
	
public:

	/**
	 * @brief Checks if a specific cell is unoccupied (contains 0).
	 * @param x X-coordinate (column).
	 * @param y Y-coordinate (row).
	 * @return True if the cell is unoccupied, false otherwise.
	 */
	bool notOccupied(int x, int y) const;
	/**
	 * @brief Checks if the given position is within the 3x3 bounds.
	 * @param x X-coordinate.
	 * @param y Y-coordinate.
	 * @return True if within bounds, false otherwise.
	 */
	static bool inBounds(int x, int y);
	/**
	 * @brief Default constructor. Initializes all board cells to 0.
	 */
	Board();
	/**
	 * @brief Constructs a Board from a given 3x3 matrix.
	 * @param matrix Pointer to a 3x3 matrix of integers.
	 */
	Board(const int** matrix);
	/**
	 * @brief Checks if a position is valid and unoccupied.
	 * @param x X-coordinate.
	 * @param y Y-coordinate.
	 * @return True if position is in bounds and not occupied.
	 */
	bool validPosition(int x, int y) const;
	/**
	 * @brief Checks if all positions on the board are occupied.
	 * @return True if the board is full, false otherwise.
	 */
	bool isFull() const;
	/**
	 * @brief Computes the total score of the board.
	 * @return Calculated score based on columns.
	 */
	int score() const;
	/**
	 * @brief Sets a value at a given position if it's valid.
	 * @param x X-coordinate.
	 * @param y Y-coordinate.
	 * @param value The value to place (between 1–6).
	 * @throws std::runtime_error if position is invalid or value out of bounds.
	 */
	void setValue(int x, int y, int value);
	/**
	 * @brief Clears the value at the given position (sets it to 0).
	 * @param x X-coordinate.
	 * @param y Y-coordinate.
	 * @throws std::runtime_error if position is out of bounds.
	 */
	void clearValue(int x, int y);
	/**
	 * @brief Gets the value stored at a specific cell.
	 * @param x X-coordinate.
	 * @param y Y-coordinate.
	 * @return Value at the specified cell.
	 * @throws std::runtime_error if position is out of bounds.
	 */
	int getValue(int x, int y) const;
	/**
	 * @brief Writes the board state to an output stream.
	 * @param out The output stream to write to.
	 */
	void serialize(std::ostream& out) const;
	/**
	 * @brief Reads the board state from an input stream.
	 * @param in The input stream to read from.
	 */
	void deserialize(std::istream& in);
};