#pragma once
#include "Character.hpp"
#include "BothBoardsPosition.hpp"


class Ash : public Character {
	int x;
	int y;
	bool board;
	const bool player;
	Board& player1Board;
	Board& player2Board;
	Character*& opponentCharacter;
public:
	Ash(Board& player1Board, Board& player2Board, Character*& enemyCharacter, bool player) : Character( 
		"Please enter coordinates and a board(1 for enemy 0 for current): ",
		"Destroy one die from any board.", 4, 1, dye::red_on_black<std::string>, hue::black_on_light_red ,'X'), x(0), y(0), board(0), player1Board(player1Board), player2Board(player2Board), opponentCharacter(enemyCharacter), player(player) {}

	BothBoardsPosition* moveType(const Position* const position) const override {
		return new BothBoardsPosition(*position);
	}



	void readAndSetParameters(std::istream& in) {
		int x;
		int y;
		bool board;
		in >> x >> y >> board;
		setParameters({ x, y, board });
	}

	void setParameters(const std::vector<int>& params) override{
		if (Board::inBounds(params[0], params[1]) || (Board::inBounds(0, params[1]) && params[0]==3 && params[2]!=player)) {
			this->x = params[0];
			this->y = params[1];
			this->board = params[2];
			ready = true;
		}
		else {
			throw std::invalid_argument("invalid position");
		}
	}

	void ability() override {
		if (ready && !onCooldown()) {
			if (x != 3) {
				board ? player2Board.clearValue(x, y) : player1Board.clearValue(x, y);
			}
			else if(Board::inBounds(0,y)){
				opponentCharacter->setCooldown();
			}
			ready = false;
			setCooldown();
		}
		else {
			throw "not ready";
		}
	}
};