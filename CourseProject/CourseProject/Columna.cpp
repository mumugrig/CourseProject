#include "Columna.hpp"

void Columna::initializeParameters()
{
	x = selection.getParameters()[0];
	if (!Board::inBounds(x,0)) throw std::invalid_argument("invalid position");
}

Columna::Columna(Board& enemyBoard) : Character("Columna", "Lowers all dice values by one in the chosen column", 4, 1, dye::yellow<std::string>, hue::bright_white_on_yellow, '|'),
enemyBoard(enemyBoard), x(0)
{}

void Columna::ability() {
	if (!onCooldown() && selection.isReady()) {
		initializeParameters();
		for (int i = 0; i < 3; i++) {
			int value = enemyBoard.getValue(x, i);
			enemyBoard.clearValue(x, i);
			if (value > 1) enemyBoard.setValue(x, i, value - 1);
		}
		selection.reset();
		setCooldown();
	}
	else throw std::runtime_error("not ready");
}

ColumnSingleBoardPosition* Columna::moveType(const Position* const position) const {
	ColumnSingleBoardPosition* pos = new ColumnSingleBoardPosition(*position);
	pos->setBoard(!position->board());
	return pos;
}

