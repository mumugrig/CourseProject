#pragma once
#include "Character.hpp"
#include "Die.hpp"
#include "SingleBoardPosition.hpp"

class Felix : public Character {

	Die& die;

public:

	Felix(Die& die) : Character("Rerolls your die", "Rerolls your die", 2, 0, dye::green<std::string>, hue::bright_white_on_green, '?'), die(die) {}

	void ability() override {
		if (!onCooldown()) {
			die.rollDie();
			setCooldown();
		}
		else {
			throw std::runtime_error("not ready");
		}
	}
	Position* moveType(const Position* const position) const override { return new SingleBoardPosition(*position); }

	void readAndSetParameters(std::istream& in) override {}
	void setParameters(const std::vector<int>& params) override {}
};