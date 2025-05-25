#pragma once
#include "Position.hpp"

class BothBoardsPosition : public Position{
public:
	BothBoardsPosition() : Position() {}
	BothBoardsPosition(const Position& other) : Position(other) {}
	virtual void moveUp() override;
	virtual void moveDown() override;
	virtual void moveLeft() override;
	virtual void moveRight() override;
};