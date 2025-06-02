#pragma once
#include "Character.hpp"
#include "RetainBothBoardsPosition.hpp"

/**
 * @class Oliver
 * @brief A character that swaps the values of two dice on either board.
 */
class Oliver : public Character {
	/// Reference to player 1's board.
	Board& player1Board;
	/// Reference to player 2's board.
	Board& player2Board;
	/// Coordinates of the first selected die.
	Point die1;
	/// Coordinates of the second selected die.
	Point die2;

	/**
	 * @brief Returns a reference to the chosen board based on the board flag.
	 * @param board True for player2Board, false for player1Board.
	 * @return Reference to the selected board.
	 */
	Board& chosenBoard(bool board);
	/**
	 * @brief Initializes internal parameters by reading from the selection.
	 * @throws std::invalid_argument if selected dice positions are invalid (not occupied).
	 */
	void initializeParameters() override;

public:
	/**
	 * @brief Constructs an Oliver character.
	 * @param player1Board Reference to player 1's board.
	 * @param player2Board Reference to player 2's board.
	 */
	Oliver(Board& player1Board, Board& player2Board);
	/**
	 * @brief Swaps the values of two selected dice on either board.
	 * @throws std::runtime_error if ability is on cooldown or selection is incomplete.
	 */
	virtual void ability() override;
	/**
	 * @brief Returns a new movement type that retains both boards and uses current selection.
	 * @param position Pointer to the current position.
	 * @return A new RetainBothBoardsPosition instance.
	 */
	virtual Position* moveType(const Position* position) const override;
};