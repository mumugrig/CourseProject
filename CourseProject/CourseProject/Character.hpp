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
	
	Character(const std::string& message, const std::string& description, int cooldownTime, int selections, const colorFunction& color, const hueFunction& selectionColor, char symbol);

	virtual void ability() = 0;
	virtual Position* moveType(const Position* const position) const = 0;
	Selection selectionType() const;
	const std::string& getName() const;
	const std::string& getDescription() const;
	virtual void readAndSetParameters(std::istream& in) = 0;
	virtual void setParameters(const std::vector<int>& params) = 0;
	 int getCooldown() const;
	 bool onCooldown() const;
	void reduceCooldown();;
	void setCooldown();
	char getSymbol() const;
	virtual ~Character();
};