#pragma once
#include "Character.hpp"
#include "RetainBothBoardsPosition.hpp"
class Oliver : public Character {

	Board& player1Board;
	Board& player2Board;
	Point die1;
	Point die2;
	
	Board& chosenBoard(bool board);
	void initializeParameters() override;

public:
	Oliver(Board& player1Board, Board& player2Board);

	virtual void ability() override;
	virtual Position* moveType(const Position* position) const override;
};