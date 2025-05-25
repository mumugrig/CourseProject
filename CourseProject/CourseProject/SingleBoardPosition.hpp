#pragma once
#include "Position.hpp"

class SingleBoardPosition : public Position {
public:

	SingleBoardPosition() : Position() {}
	SingleBoardPosition(const Position& other) : Position(other) {}

	virtual void moveUp() override;
	virtual void moveDown() override;
	virtual void moveLeft() override;
	virtual void moveRight() override;
};