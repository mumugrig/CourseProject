#include "Oliver.hpp"

Board& Oliver::chosenBoard(bool board) {
	return board ? player2Board : player1Board;
}

void Oliver::initializeParameters() {
	die1 = selection.getParameters()[0];
	die2 = selection.getParameters()[1];
	if (chosenBoard(die1.board).notOccupied(die1.x, die1.y) || chosenBoard(die2.board).notOccupied(die2.x, die2.y)) {
		throw std::invalid_argument("invalid position");
	}
}

Oliver::Oliver(Board& player1Board, Board& player2Board) : Character("Oliver", "Swap two dice. Has to target squares with a placed die on them", 4, 2, dye::light_purple<std::string>, hue::bright_white_on_light_purple, ':'),
player1Board(player1Board), player2Board(player2Board) {}

void Oliver::ability() {

	if (selection.isReady() && !onCooldown()) {
		initializeParameters();
		int value1 = chosenBoard(die1.board).getValue(die1.x, die1.y);
		int value2 = chosenBoard(die2.board).getValue(die2.x, die2.y);

		chosenBoard(die1.board).clearValue(die1.x, die1.y);
		chosenBoard(die1.board).setValue(die1.x, die1.y, value2);

		chosenBoard(die2.board).clearValue(die2.x, die2.y);
		chosenBoard(die2.board).setValue(die2.x, die2.y, value1);

		setCooldown();
		selection.reset();
	}
	else throw std::runtime_error("not ready");
}

Position* Oliver::moveType(const Position* position) const {
	return new RetainBothBoardsPosition(*position, selection);
}
