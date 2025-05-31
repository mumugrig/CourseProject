#pragma once
#include "Character.hpp"
#include "Die.hpp"
#include "Position.hpp"

class Felix : public Character {

	Die& die;
	int count;
	void initializeParameters() override {}
public:
	Felix(Die& die);
	void ability() override;
	Position* moveType(const Position* position) const override;
};