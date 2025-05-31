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
	OLIVER,
};

class Character {
protected:
	
	const std::string name;
	const std::string description;
	int cooldown;
	int cooldownTime;
	const char symbol;
	virtual void initializeParameters() = 0;
public:

	using colorFunction =  std::function<dye::colorful<std::string>(const std::string&)>;
	using hueFunction = std::function<std::ostream& (std::ostream&)>;
	const colorFunction color;
	const hueFunction selectionColor;
	Selection selection;
	Character(const std::string& message, const std::string& description, int cooldownTime, int selections, const colorFunction& color, const hueFunction& selectionColor, char symbol);

	virtual void ability() = 0;
	virtual Position* moveType(const Position* position) const = 0;
	const std::string& getName() const;
	const std::string& getDescription() const;
	virtual void pushParameters(const Point& point);
	virtual void resetSelection() { selection.reset(); }
	 int getCooldown() const;
	 int getCooldownTime() const;
	 bool onCooldown() const;
	void reduceCooldown();;
	void setCooldown();
	char getSymbol() const;
	virtual ~Character();
};