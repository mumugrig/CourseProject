#pragma once
#include "Board.hpp"
#include <functional>
#include "Libraries/color.hpp"
enum CharacterEnum {
	ASH,
};

class Character {
protected:
	
	Board& opponentBoard;
	std::string message;
	std::string description;
	int cooldown;
	int cooldownTime;
	bool ready;
public:
	using colorFunction =  std::function<dye::colorful<std::string>(const std::string&)>;
	const colorFunction color;
	Character(Board& board, const std::string& message, const std::string& description,int cooldownTime, const colorFunction& color)
		: opponentBoard(board), message(message), description(description),cooldownTime(cooldownTime), color(color), cooldown(0), ready(false)
	{
		
	}
	virtual void ability() = 0;
	const std::string& getMessage() const { return message; }
	const std::string& getDescription() const{ return description; }
	virtual void readAndSetParameters(std::istream& in) = 0;
	virtual void setParameters(const std::vector<int>& params) = 0;
	 int getCooldown() const{ return cooldown; }
	 bool onCooldown() const { return cooldown > 0; }
	void reduceCooldown() { if(cooldown>0) --cooldown; };
	void setCooldown() { cooldown += cooldownTime; }
	virtual ~Character() {}
};