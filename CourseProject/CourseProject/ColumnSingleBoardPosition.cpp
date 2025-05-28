#include "ColumnSingleBoardPosition.hpp"

ColumnSingleBoardPosition::ColumnSingleBoardPosition() : Position() {}

ColumnSingleBoardPosition::ColumnSingleBoardPosition(const Position& other) : Position(other) {}

bool ColumnSingleBoardPosition::player1SelectCondition(int x, int y) {
	return !_board && x == _x;
}

bool ColumnSingleBoardPosition::player2SelectCondition(int x, int y) {
	return _board && x == _x;
}
