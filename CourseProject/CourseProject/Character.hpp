#pragma once
#include "Board.hpp"
#include <functional>
#include "Libraries/color.hpp"
#include "Position.hpp"
#include "Selection.hpp"

/**
 * @enum CharacterEnum
 * @brief Enumeration for different character types.
 */
enum CharacterEnum {
	ASH,
	FELIX,
	COLUMNA,
	OLIVER,
};
/**
 * @class Character
 * @brief Abstract base class representing a game character with abilities, selection logic, and cooldowns.
 */
class Character {
protected:
	/// Character's name
	const std::string name;
	/// Character's description
	const std::string description;
	/// Current cooldown counter for abilities
	int cooldown;
	/// Maximum cooldown time after ability use
	int cooldownTime;
	/// Character symbol displayed on board or UI
	const char symbol;
	/**
	 * @brief Initializes character-specific parameters (to be implemented by derived classes).
	 */
	virtual void initializeParameters() = 0;
public:
	/// Function type for coloring output strings (using dye::colorful)
	using colorFunction =  std::function<dye::colorful<std::string>(const std::string&)>;
	/// Function type for streaming color hues (e.g., for selection highlights)
	using hueFunction = std::function<std::ostream& (std::ostream&)>;
	/// Function for coloring text associated with this character
	const colorFunction color;
	/// Function for coloring selection highlights
	const hueFunction selectionColor;
	/// Current selection state holding selected points
	Selection selection;

	/**
	 * @brief Constructs a new Character instance.
	 * @param name Character name
	 * @param description Character description
	 * @param cooldownTime Maximum cooldown time for the character's ability
	 * @param selections Number of selection points allowed
	 * @param color Function to color text related to the character
	 * @param selectionColor Function to color selection highlights
	 * @param symbol Character's display symbol
	 */
	Character(const std::string& message, const std::string& description, int cooldownTime, int selections, const colorFunction& color, const hueFunction& selectionColor, char symbol);
	/**
	 * @brief Executes the character's special ability (must be implemented by derived classes).
	 */
	virtual void ability() = 0;
	/**
	 * @brief Returns a position that matches the character's needed movement type.
	 * @param position Current position pointer
	 * @return Position pointer representing the new movement type
	 */
	virtual Position* moveType(const Position* position) const = 0;
	/**
	 * @brief Gets the character's name.
	 * @return const std::string& Name of the character
	 */
	const std::string& getName() const;
	/**
	 * @brief Gets the character's description.
	 * @return const std::string& Description string
	 */
	const std::string& getDescription() const;

	/**
	 * @brief Adds a selection point to the character's current selection.
	 * @param point The point to add
	 */
	virtual void pushParameters(const Point& point);
	/**
	 * @brief Resets the character's selection to empty.
	 */
	virtual void resetSelection();
	/**
	 * @brief Gets the current cooldown value.
	 * @return int Current cooldown ticks left
	 */
	 int getCooldown() const;
	 /**
	 * @brief Gets the maximum cooldown time for the character.
	 * @return int Maximum cooldown time
	 */
	 int getCooldownTime() const;
	 /**
	 * @brief Checks if the character's ability is currently on cooldown.
	 * @return true If cooldown is active
	 * @return false If cooldown is not active
	 */
	 bool onCooldown() const;
	 /**
	 * @brief Reduces the cooldown timer by one tick if it is greater than zero.
	 */
	void reduceCooldown();
	/**
	 * @brief Resets cooldown to the maximum cooldown time (ability used).
	 */
	void setCooldown();

	/**
	 * @brief Returns the character's symbol or a digit representing the cooldown.
	 * @return char Character symbol if not on cooldown, else cooldown digit.
	 */
	char getSymbol() const;
	/**
	 * @brief Virtual destructor.
	 */
	virtual ~Character();
};