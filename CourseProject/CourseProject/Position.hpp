#pragma once
#include "Point.hpp"



class Position {
protected:
	Point point;
public:

	Position();

	int x() const;
	int y() const;
	bool board() const;
	void setBoard(bool value);
	const Point& getPoint();
	virtual void moveUp();
	virtual void moveDown();
	virtual void moveLeft();
	virtual void moveRight();
	virtual bool player1SelectCondition(int x, int y);
	virtual bool player2SelectCondition(int x, int y);

	virtual ~Position() {}
};

