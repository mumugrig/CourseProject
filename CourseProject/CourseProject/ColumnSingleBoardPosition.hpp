#pragma once
#include "Position.hpp"

class ColumnSingleBoardPosition : public Position {
public:
	ColumnSingleBoardPosition();
	ColumnSingleBoardPosition(const Position& other);

	bool player1SelectCondition(int x, int y) override;

	bool player2SelectCondition(int x, int y) override;

};