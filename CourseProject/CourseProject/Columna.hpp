#pragma once
#include "Character.hpp"
#include "Board.hpp"
#include "ColumnSingleBoardPosition.hpp"
class Columna : public Character {

	Board& enemyBoard;
	int x;
public:

	Columna(Board& enemyBoard) : Character("Columna", "Lowers all dice values by one in the chosen column", 4, 1, dye::yellow<std::string>, hue::bright_white_on_yellow, '|'),
	enemyBoard(enemyBoard), x(0)
	{}

	void ability() override {
		if (!onCooldown() && ready) {
			for (int i = 0; i < 3; i++) {
				int value = enemyBoard.getValue(x, i);
				enemyBoard.clearValue(x, i);
				if (value > 1) enemyBoard.setValue(x, i, value - 1);
			}
			ready = false;
			setCooldown();
		}
		else throw std::runtime_error("not ready");
	}

	ColumnSingleBoardPosition* moveType(const Position* const position) const override {
		ColumnSingleBoardPosition* pos = new ColumnSingleBoardPosition(*position);
		pos->setBoard(!position->board());
		return pos;
	 }

	 void readAndSetParameters(std::istream& in) override {}

	 void setParameters(const std::vector<int>& params) override {
		 if (Board::inBounds(params[0], params[1])) {
			 x = params[0];
			 ready = true;
		 }
		 else throw std::invalid_argument("invalid position");
	 }

};
