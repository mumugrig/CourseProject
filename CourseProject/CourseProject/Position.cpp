#include "Position.hpp"

Position::Position() : _x(0), _y(0), _board(false) {}

int Position::x() const { return _x; }

int Position::y() const { return _y; }

bool Position::board() const { return _board; }

void Position::setBoard(bool value) { _board = value; }

void Position::moveUp()
{
	_y--;
	if (_y < 0) _y = 2;
}

void Position::moveDown()
{
	_y++;
	if (_y > 2) _y = 0;
}

void Position::moveLeft()
{
	_x--;
	if (_x < 0) _x = 3;
}

void Position::moveRight()
{
	_x++;
	if (_x > 3) _x = 0;
}

inline bool Position::player1SelectCondition(int x, int y) { return !_board && y == _y && x == _x; }

inline bool Position::player2SelectCondition(int x, int y) { return _board && y == _y && x == _x; }
