#include "Character.hpp"

Character::Character(const std::string& message, const std::string& description, int cooldownTime, int selections, const colorFunction& color, const hueFunction& selectionColor, char symbol)
	: name(message), description(description), cooldownTime(cooldownTime), selections(selections), color(color), selectionColor(selectionColor), cooldown(0), ready(false), symbol(symbol)
{

}

Selection Character::selectionType() const { return Selection(selections); }

const std::string& Character::getName() const { return name; }

const std::string& Character::getDescription() const { return description; }

int Character::getCooldown() const { return cooldown; }

bool Character::onCooldown() const { return cooldown > 0; }

void Character::reduceCooldown() { if (cooldown>0) --cooldown; }

void Character::setCooldown() { cooldown = cooldownTime; }

char Character::getSymbol() const {
	if (!onCooldown()) return symbol;
	else return '0' + cooldown;
}

Character::~Character() {}
