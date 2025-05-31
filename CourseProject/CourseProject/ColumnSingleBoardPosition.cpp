#include "ColumnSingleBoardPosition.hpp"

ColumnSingleBoardPosition::ColumnSingleBoardPosition() : Position() {}

ColumnSingleBoardPosition::ColumnSingleBoardPosition(const Position& other) : Position(other) {}

bool ColumnSingleBoardPosition::player1SelectCondition(int x, int y) {
	return !point.board && x == point.x;
}

bool ColumnSingleBoardPosition::player2SelectCondition(int x, int y) {
	return point.board && x == point.x;
}
