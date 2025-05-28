#pragma once

class Position {
protected:
	int _x;
	int _y;
	bool _board;
public:

	Position();

	int x() const;
	int y() const;
	bool board() const;
	void setBoard(bool value);

	virtual void moveUp();
	virtual void moveDown();
	virtual void moveLeft();
	virtual void moveRight();
	virtual bool player1SelectCondition(int x, int y);
	virtual bool player2SelectCondition(int x, int y);
};

