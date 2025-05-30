#include "Character.hpp"

Character::Character(const std::string& name, const std::string& description, int cooldownTime, int selections, const colorFunction& color, const hueFunction& selectionColor, char symbol)
	: name(name), description(description), cooldownTime(cooldownTime), selection(selections), color(color), selectionColor(selectionColor), cooldown(0), symbol(symbol)
{

}


const std::string& Character::getName() const { return name; }

const std::string& Character::getDescription() const { return description; }

void Character::pushParameters(int x, int y, bool board) { selection.push(x, y, board); }

int Character::getCooldown() const { return cooldown; }

int Character::getCooldownTime() const { return cooldownTime; }

bool Character::onCooldown() const { return cooldown > 0; }

void Character::reduceCooldown() { if (cooldown>0) --cooldown; }

void Character::setCooldown() { cooldown = cooldownTime; }

char Character::getSymbol() const {
	if (!onCooldown()) return symbol;
	else return '0' + cooldown;
}

Character::~Character() {}
