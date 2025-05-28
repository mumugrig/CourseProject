#include "Felix.hpp"

Felix::Felix(Die& die) : Character("Felix", "Rerolls your die", 2, 0, dye::green<std::string>, hue::bright_white_on_green, '?'), die(die) {}

void Felix::ability() {
	if (!onCooldown()) {
		die.rollDie();
		setCooldown();
	}
	else {
		throw std::runtime_error("not ready");
	}
}

Position* Felix::moveType(const Position* const position) const { return new Position(*position); }

void Felix::readAndSetParameters(std::istream& in) {}

void Felix::setParameters(const std::vector<int>& params) {}
