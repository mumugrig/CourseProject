#pragma once
#include "Character.hpp"

class Ash : public Character {
	int x;
	int y;
	bool board;
	Board& playerBoard;
public:
	Ash(Board& playerBoard, Board& opponentBoard) : Character(opponentBoard, 
		"Please enter coordinates and a board(1 for enemy 0 for current): ",
		"Destroy one die from any board.", 4, dye::red_on_black<std::string>), x(0), y(0), board(0), playerBoard(playerBoard) {}

	void readAndSetParameters(std::istream& in) {
		int x;
		int y;
		bool board;
		in >> x >> y >> board;
		setParameters({ x, y, board });
	}

	void setParameters(const std::vector<int>& params) override{
		if (Board::inBounds(params[0], params[1])) {
			this->x = params[0];
			this->y = params[1];
			this->board = params[2];
			ready = true;
		}
		else {
			throw "invalid position";
		}
	}

	void ability() override {
		if (ready && !onCooldown()) {
			if (x != 3) {
				board ? opponentBoard.clearValue(x, y) : playerBoard.clearValue(x, y);
				ready = false;
				setCooldown();
			}
			else if(Board::inBounds(0,y)){

			}
			
		}
		else {
			throw "not ready";
		}
	}
};