#pragma once
#include "Character.hpp"

class Ash : public Character {
	int x;
	int y;
	bool board;
	Board& playerBoard;
public:
	Ash(Board& playerBoard, Board& opponentBoard) :Character(opponentBoard, 
		"Please enter coordinates and a board(1 for enemy 0 for current): ",
		"Destroy one die from any board."), x(0), y(0), board(0), playerBoard(playerBoard) {}

	void readAndSetParameters(std::istream& in) {
		int x;
		int y;
		bool board;
		in >> x >> y >> board;
		setParameters(x, y, board);
	}

	void setParameters(int x, int y, bool board) {
		if (Board::inBounds(x, y)) {
			this->x = x;
			this->y = y;
			this->board = board;
			ready = true;
		}
		else {
			throw "invalid position";
		}
	}

	void ability() override {
		if (ready && !onCooldown()) {
			board ? opponentBoard.clearValue(x, y) : playerBoard.clearValue(x, y);
			ready = false;
			cooldown += 4;
		}
		else {
			throw "not ready";
		}
	}
};