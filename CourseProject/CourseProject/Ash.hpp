#pragma once
#include "Character.hpp"
#include "BothBoardsPosition.hpp"


class Ash : public Character {
	Point target;
	const bool player;
	Board& player1Board;
	Board& player2Board;
	Character*& opponentCharacter;
	void initializeParameters() override;
public:
	Ash(Board& player1Board, Board& player2Board, Character*& enemyCharacter, bool player);

	BothBoardsPosition* moveType(const Position* position) const override;

	void ability() override;
};