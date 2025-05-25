#pragma once

class Position {
protected:
	int _x;
	int _y;
	bool _board;
public:
	Position() : _x(0), _y(0), _board(false) {}

	int x() const { return _x; }
	int y() const{ return _y; }
	bool board() const { return _board; }
	void setBoard(bool value) { _board = value; }

	virtual void moveUp() = 0;
	virtual void moveDown() = 0;
	virtual void moveLeft() = 0;
	virtual void moveRight() = 0;
	virtual bool player1SelectCondition(int x, int y) { return !_board && y == _y && x == _x; }
	virtual bool player2SelectCondition(int x, int y) { return _board && y == _y && x == _x; }
};