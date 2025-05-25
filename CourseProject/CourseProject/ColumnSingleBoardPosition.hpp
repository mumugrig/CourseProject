#pragma once
#include "SingleBoardPosition.hpp"

class ColumnSingleBoardPosition : public SingleBoardPosition{
public:
	ColumnSingleBoardPosition() : SingleBoardPosition() {}
	ColumnSingleBoardPosition(const Position& other) : SingleBoardPosition(other) {}

	bool player1SelectCondition(int x, int y) override {
		return !_board && x == _x;
	}

	bool player2SelectCondition(int x, int y) override {
		return _board && x == _x;
	}

};