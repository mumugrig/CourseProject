#include "Ash.hpp"

void Ash::initializeParameters()
{
	x = selection.getParameters()[0];
	y = selection.getParameters()[1];
	board = selection.getParameters()[2];
}

Ash::Ash(Board& player1Board, Board& player2Board, Character*& enemyCharacter, bool player) : Character(
	"Ash",
	"Destroy one die from any board.", 4, 1, dye::red_on_black<std::string>, hue::black_on_light_red, 'X'), x(0), y(0), board(0), player1Board(player1Board), player2Board(player2Board), opponentCharacter(enemyCharacter), player(player) {}

 BothBoardsPosition* Ash::moveType(const Position* const position) const {
	return new BothBoardsPosition(*position);
}



 void Ash::ability() {
	if (selection.isReady() && !onCooldown()) {
		initializeParameters();
		if (x != 3) {
			board ? player2Board.clearValue(x, y) : player1Board.clearValue(x, y);
		}
		else if (Board::inBounds(0, y) && board!=player) {
			opponentCharacter->setCooldown();
			cooldownTime = max(opponentCharacter->getCooldownTime() + 1, cooldownTime);
		}
		else throw std::invalid_argument("invalid position");
		selection.reset();
		setCooldown();
	}
	else {
		throw "not ready";
	}
}
