#include "BothBoardsPosition.hpp"

 void BothBoardsPosition::moveUp()
{
	point.y--;
	if (point.y < 0) {
		point.board = !point.board;
		point.y = 2;
	}
}

 void BothBoardsPosition::moveDown()
{
	point.y++;
	if (point.y > 2) {
		point.board = !point.board;
		point.y = 0;
	}
}

 void BothBoardsPosition::moveLeft()
{
	point.x--;
	if (point.x < 0) point.x = 3;
}

 void BothBoardsPosition::moveRight()
{
	point.x++;
	if (point.x > 3) point.x = 0;
}
