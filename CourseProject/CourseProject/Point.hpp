#pragma once

struct Point {
	int x;
	int y;
	bool board;

	Point() : x(0), y(0), board(0) {}
	Point(int x, int y, bool board) : x(x), y(y), board(board) {} 

	bool operator==(const Point& other) const{
		return x == other.x && y == other.y && board == other.board;
	}
};