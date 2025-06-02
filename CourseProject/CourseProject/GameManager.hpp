#pragma once
#include "FileManager.hpp"
#include "Game.hpp"
#include "PlayerManager.hpp"

/**
 * @class GameManager
 * @brief Manages Game objects using a file-based storage mechanism.
 *
 * Inherits from FileManager and uses PlayerManager to resolve Player references during deserialization.
 */

class GameManager : public FileManager<Game, unsigned int> {
	
	/// Reference to the PlayerManager used to resolve player data
	const PlayerManager& players;

	/**
	 * @brief Serializes a Game object to an output stream.
	 * @param element The Game object to serialize.
	 * @param out The output stream to write to.
	 */
	void serialize(const Game& element, std::ostream& out) override;
	/**
	 * @brief Deserializes a Game object from an input stream.
	 * @param in The input stream to read from.
	 * @return A dynamically allocated Game object.
	 */
	Game* deserialize(std::istream& in) override;
	

public:
	/**
	 * @brief Saves all Game objects to file.
	 */
	void save() override;
	/**
	 * @brief Constructs a GameManager with auto-increment enabled.
	 * @param filename Path to the file storing Game data.
	 * @param playerManager Reference to a PlayerManager for resolving players.
	 */
	GameManager(const char* filename, const PlayerManager& playerManager);

	/**
	 * @brief Constructs a GameManager with configurable auto-increment behavior.
	 * @param filename Path to the file storing Game data.
	 * @param auto_inc Whether to enable ID auto-incrementation.
	 * @param playerManager Reference to a PlayerManager for resolving players.
	 */

	GameManager(const char* filename, bool auto_inc, const PlayerManager& playerManager);
};