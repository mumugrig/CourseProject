#pragma once
#include "Character.hpp"
#include "Board.hpp"
#include "ColumnSingleBoardPosition.hpp"

class Columna : public Character {

	Board& enemyBoard;
	int x;
	void initializeParameters() override;
public:

	Columna(Board& enemyBoard);

	void ability() override;

	ColumnSingleBoardPosition* moveType(const Position* position) const override;

};
