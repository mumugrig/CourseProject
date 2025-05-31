#include "Position.hpp"

Position::Position() : point({ 0,0,0 }) {}

int Position::x() const { return point.x; }

int Position::y() const { return point.y; }

bool Position::board() const { return point.board; }

void Position::setBoard(bool value) { point.board = value; }

const Point& Position::getPoint()
{
	return point;
}

void Position::moveUp()
{
	point.y--;
	if (point.y < 0) point.y = 2;
}

void Position::moveDown()
{
	point.y++;
	if (point.y > 2) point.y = 0;
}

void Position::moveLeft()
{
	point.x--;
	if (point.x < 0) point.x = 3;
}

void Position::moveRight()
{
	point.x++;
	if (point.x > 3) point.x = 0;
}

inline bool Position::player1SelectCondition(int x, int y) { return !point.board && y == point.y && x == point.x; }

inline bool Position::player2SelectCondition(int x, int y) { return point.board && y == point.y && x == point.x; }
