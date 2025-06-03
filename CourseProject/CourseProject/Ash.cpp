#include "Ash.hpp"

void Ash::initializeParameters()
{
	target = selection.getParameters()[0];
}

Ash::Ash(Board& player1Board, Board& player2Board, Character*& enemyCharacter, bool player) : Character(
	"Ash",
	"Destroy one die from either board.", 4, 1, dye::red_on_black<std::string>, hue::black_on_light_red, 'X'), target({0,0,0}), player1Board(player1Board), player2Board(player2Board), opponentCharacter(enemyCharacter), player(player) {}

 BothBoardsPosition* Ash::moveType(const Position* position) const {
	return new BothBoardsPosition(*position);
}



 void Ash::ability() {
	if (selection.isReady() && !onCooldown()) {
		initializeParameters();
		if (target.x != 3) {
			target.board ? player2Board.clearValue(target.x, target.y) : player1Board.clearValue(target.x, target.y);
		}
		else if (Board::inBounds(0, target.y) && target.board!=player) {
			opponentCharacter->setCooldown();
			cooldownTime = min(max(opponentCharacter->getCooldownTime() + 1, cooldownTime),9);
		}
		else throw std::invalid_argument("invalid position");
		selection.reset();
		setCooldown();
	}
	else {
		throw "not ready";
	}
}
