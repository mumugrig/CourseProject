#pragma once
#include "Character.hpp"
#include "Board.hpp"
#include "ColumnSingleBoardPosition.hpp"

class Columna : public Character {

	Board& enemyBoard;
	int x;
public:

	Columna(Board& enemyBoard);

	void ability() override;

	ColumnSingleBoardPosition* moveType(const Position* const position) const override;

	 void readAndSetParameters(std::istream& in) override;

	 void setParameters(const std::vector<int>& params) override;

};
