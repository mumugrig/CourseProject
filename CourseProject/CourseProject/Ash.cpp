#include "Ash.hpp"

 Ash::Ash(Board& player1Board, Board& player2Board, Character*& enemyCharacter, bool player) : Character(
	"Ash",
	"Destroy one die from any board.", 4, 1, dye::red_on_black<std::string>, hue::black_on_light_red, 'X'), x(0), y(0), board(0), player1Board(player1Board), player2Board(player2Board), opponentCharacter(enemyCharacter), player(player) {}

 BothBoardsPosition* Ash::moveType(const Position* const position) const {
	return new BothBoardsPosition(*position);
}

 void Ash::readAndSetParameters(std::istream& in) {
	int x;
	int y;
	bool board;
	in >> x >> y >> board;
	setParameters({ x, y, board });
}

 void Ash::setParameters(const std::vector<int>& params) {
	if (Board::inBounds(params[0], params[1]) || (Board::inBounds(0, params[1]) && params[0] == 3 && params[2] != player)) {
		this->x = params[0];
		this->y = params[1];
		this->board = params[2];
		ready = true;
	}
	else {
		throw std::invalid_argument("invalid position");
	}
}

 void Ash::ability() {
	if (ready && !onCooldown()) {
		if (x != 3) {
			board ? player2Board.clearValue(x, y) : player1Board.clearValue(x, y);
		}
		else if (Board::inBounds(0, y)) {
			opponentCharacter->setCooldown();
		}
		ready = false;
		setCooldown();
	}
	else {
		throw "not ready";
	}
}
