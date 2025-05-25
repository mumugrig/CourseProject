#include "BothBoardsPosition.hpp"

 void BothBoardsPosition::moveUp()
{
	_y--;
	if (_y < 0) {
		_board = !_board;
		_y = 2;
	}
}

 void BothBoardsPosition::moveDown()
{
	_y++;
	if (_y > 2) {
		_board = !_board;
		_y = 0;
	}
}

 void BothBoardsPosition::moveLeft()
{
	_x--;
	if (_x < 0) _x = 3;
}

 void BothBoardsPosition::moveRight()
{
	_x++;
	if (_x > 3) _x = 0;
}
