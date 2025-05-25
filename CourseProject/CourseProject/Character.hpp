#pragma once
#include "Board.hpp"
#include <functional>
#include "Libraries/color.hpp"
#include "Position.hpp"
#include "Selection.hpp"
enum CharacterEnum {
	ASH,
	FELIX,
	COLUMNA,
};

class Character {
protected:
	
	const std::string name;
	const std::string description;
	int cooldown;
	const int cooldownTime;
	const int selections;
	bool ready;
	const char symbol;

public:

	using colorFunction =  std::function<dye::colorful<std::string>(const std::string&)>;
	using hueFunction = std::function<std::ostream& (std::ostream&)>;
	const colorFunction color;
	const hueFunction selectionColor;
	
	Character(const std::string& message, const std::string& description, int cooldownTime, int selections, const colorFunction& color, const hueFunction& selectionColor, char symbol)
	: name(message), description(description),cooldownTime(cooldownTime), selections(selections), color(color), selectionColor(selectionColor), cooldown(0), ready(false), symbol(symbol)
	{
		
	}

	virtual void ability() = 0;
	virtual Position* moveType(const Position* const position) const = 0;
	Selection selectionType() const { return Selection(selections); }
	const std::string& getName() const { return name; }
	const std::string& getDescription() const{ return description; }
	virtual void readAndSetParameters(std::istream& in) = 0;
	virtual void setParameters(const std::vector<int>& params) = 0;
	 int getCooldown() const{ return cooldown; }
	 bool onCooldown() const { return cooldown > 0; }
	void reduceCooldown() { if(cooldown>0) --cooldown; };
	void setCooldown() { cooldown = cooldownTime; }
	char getSymbol() const {
		if (!onCooldown()) return symbol;
		else return '0' + cooldown;
	}
	virtual ~Character() {}
};