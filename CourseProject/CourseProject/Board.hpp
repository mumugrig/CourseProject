#pragma once
#include "Serializable.hpp"

class Board : Serializable {
	int board[3][3];
	bool inBounds(int x, int y);
	int columnScore(int column[]);
	bool notOccupied(int x, int y);
public:
	Board();
	Board(const int** matrix);
	
	bool isFull();
	int score();
	void setValue(int x, int y, int value);
	int getValue(int x, int y) const;

	void serialize(std::ostream& out) const override;
	void deserialize(std::istream& in) override;
};