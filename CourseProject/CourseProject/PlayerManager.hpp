#pragma once
#include "FileManager.hpp"
#include "Player.hpp"
/**
 * @class PlayerManager
 * @brief Manages Player objects using a file-based storage mechanism.
 *
 * Inherits from FileManager.
 */

class PlayerManager : public FileManager<Player, unsigned int> {
	/**
	* @brief Serializes a Player object to an output stream.
	*
	* Format: `<id> <username>\n`
	*
	* @param element The Player to serialize.
	* @param out The output stream to write to.
	*/
	void serialize(const Player& element, std::ostream& out) override;
	/**
	* @brief Deserializes a Player object from an input stream.
	*
	* Expects the same format as produced by `serialize`.
	*
	* @param in The input stream to read from.
	* @return A dynamically allocated Player object.
	*/
	Player* deserialize(std::istream& in) override;
public:
	/**
	* @brief Saves all loaded Player objects to the associated file.
	*
	* Uses the `serialize` method to write each player.
	*/
	void save() override;
	/**
	* @brief Adds a Player to the manager if the username is unique.
	*
	* Prevents duplicate usernames by scanning the loaded data. Throws if a match is found.
	*
	* @param player The Player to add.
	* @throws std::runtime_error if the username already exists.
	*/
	void add(const Player& player) override;
	/**
	* @brief Constructs a PlayerManager with auto-increment enabled by default.
	*
	* Loads all players from the specified file.
	*
	* @param filename The path to the file.
	*/
	PlayerManager(const char* filename);
	/**
	* @brief Constructs a PlayerManager with optional auto-increment behavior.
	*
	* Loads all players from the specified file.
	*
	* @param filename The path to the file.
	* @param auto_inc Whether to auto-increment player IDs.
	*/
	PlayerManager(const char* filename, bool auto_inc);
};