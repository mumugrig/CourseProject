#include "RetainBothBoardsPosition.hpp"

RetainBothBoardsPosition::RetainBothBoardsPosition(Selection& selection) : selection(selection) {}

RetainBothBoardsPosition::RetainBothBoardsPosition(const Position& other, const Selection& selection) : BothBoardsPosition(other), selection(selection) {}

bool RetainBothBoardsPosition::player1SelectCondition(int x, int y) {
	return !point.board && y == point.y && x == point.x || VectorUtility::any<Point>([x, y, this](const Point& p) -> bool { return p == Point(x, y, 0); },
		selection.getParameters());
}

bool RetainBothBoardsPosition::player2SelectCondition(int x, int y) {
	return point.board && y == point.y && x == point.x || VectorUtility::any<Point>([x, y, this](const Point& p) -> bool { return p == Point(x, y, 1); },
		selection.getParameters());
}
