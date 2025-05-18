#pragma once
#include "Game.hpp"

enum CharacterEnum {
	ASH,
};

class Character {
protected:
	Board& opponentBoard;
	std::string message;
	std::string description;
	int cooldown;
	bool ready;
public:
	Character(Board& board, const std::string& message, const std::string& description)
		: opponentBoard(board), message(message), description(description), cooldown(0), ready(false)
	{}
	virtual void ability() = 0;
	const std::string& getMessage() const{ return message; }
	const std::string& getDescription() const{ return description; }
	 int getCooldown() const{ return cooldown; }
	 bool onCooldown() const { return cooldown > 0; }
	void reduceCooldown() { --cooldown; };
	virtual ~Character() {}
};