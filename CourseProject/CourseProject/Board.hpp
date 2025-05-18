#pragma once
#include "Serializable.hpp"

class Board : Serializable {
	int board[3][3];
	
	int columnScore(int column[]) const;
	bool notOccupied(int x, int y) const;
public:
	static bool inBounds(int x, int y);
	Board();
	Board(const int** matrix);
	
	bool validPosition(int x, int y) const;
	bool isFull() const;
	int score() const;
	void setValue(int x, int y, int value);
	void clearValue(int x, int y);
	int getValue(int x, int y) const;

	void serialize(std::ostream& out) const override;
	void deserialize(std::istream& in) override;
};