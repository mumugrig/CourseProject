#include "SingleBoardPosition.hpp"

void SingleBoardPosition::moveUp()
{
	_y--;
	if (_y < 0) _y = 2;
}

 void SingleBoardPosition::moveDown()
{
	_y++;
	if (_y > 2) _y = 0;
}

 void SingleBoardPosition::moveLeft()
{
	_x--;
	if (_x < 0) _x = 3;
}

 void SingleBoardPosition::moveRight()
{
	_x++;
	if (_x > 3) _x = 0;
}
