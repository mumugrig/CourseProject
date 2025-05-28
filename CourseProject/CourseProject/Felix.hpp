#pragma once
#include "Character.hpp"
#include "Die.hpp"
#include "Position.hpp"

class Felix : public Character {

	Die& die;

public:

	Felix(Die& die);

	void ability() override;
	Position* moveType(const Position* const position) const override;

	void readAndSetParameters(std::istream& in) override;
	void setParameters(const std::vector<int>& params) override;
};