#include "Felix.hpp"

Felix::Felix(Die& die) : Character("Felix", "Rerolls your die", 2, 0, dye::green<std::string>, hue::bright_white_on_green, '?'), die(die), count(0) {}

void Felix::ability() {
	if (!onCooldown()) {
		++count;
		if (count == 3) {
			die.rollInBounds(5, 6);
			count = 0;
		}
		else {
			die.rollDie();
		}
		setCooldown();	
	}
	else {
		throw std::runtime_error("not ready");
	}
}

Position* Felix::moveType(const Position* const position) const { return new Position(*position); }

