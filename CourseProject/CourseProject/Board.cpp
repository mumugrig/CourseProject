#include "Board.hpp"

bool Board::inBounds(int x, int y)
{
	return x >= 0 && x < 3 && y >= 0 && y < 3;
}

int Board::columnScore(int column[]) const
{
	int count = 1;
	int number = 0;
	if (column[0] == column[1] || column[0] == column[2]) {
		count++;
		number = column[0];
	}
	if (column[1] == column[2]) {
		count++;
		number = column[1];
	}
	int result = 0;
	for (int i = 0; i < 3; i++) {
		if (column[i] == number) {
			result += number * count;
		}
		else {
			result += column[i];
		}
	}
	return result;
}

bool Board::notOccupied(int x, int y) const
{
	return board[y][x] == 0;
}

Board::Board()
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			board[i][j] = 0;
		}
	}
}

Board::Board(const int** matrix)
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			board[i][j] = matrix[i][j];
		}
	}
}

bool Board::validPosition(int x, int y) const
{
	return inBounds(x, y) && notOccupied(x, y);
}

bool Board::isFull() const
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == 0) return false;
		}
	}
	return true;
}

int Board::score() const
{
	int result = 0;
	for (int i = 0; i < 3; i++) {
		int column[3] = { 0 };
		for (int j = 0; j < 3; j++) {
			column[j] = board[j][i];	
		}
		result += columnScore(column);
	}
	return result;
}

void Board::setValue(int x, int y, int value)
{
	if (value >= 1 && value <= 6 && validPosition(x, y)) {
		board[y][x] = value;
	}
	else {
		throw std::runtime_error("invalid position");
	}
}

void Board::clearValue(int x, int y)
{
	if (inBounds(x, y)) {
		board[y][x] = 0;
	}
	else throw std::runtime_error("invalid position");
}

int Board::getValue(int x, int y) const
{
	return board[y][x];
}

void Board::serialize(std::ostream& out) const
{
	for (int i = 0; i < 9; i++) {
		out << board[i / 3][i % 3] << ' ';
	}
	out << std::endl;
}

void Board::deserialize(std::istream& in)
{
	for (int i = 0; i < 9; i++) {
		in >> board[i / 3][i % 3];
	}
}
