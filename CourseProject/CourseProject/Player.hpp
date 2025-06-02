
/**
 * @file Player.hpp
 * @brief Defines the Player class, representing a user in the system.
 */

#pragma once
#include <string>
#include "Storable.hpp"

 /**
  * @class Player
  * @brief Represents a player with a unique ID and username.
  *
  * Inherits from Storable to enable file-based storage and cloning.
  */

class Player : public Storable<unsigned int> {
	std::string username;

	/**
	 * @brief Validates and sets the username.
	 * @param name The username to assign. Must be 50 characters or fewer.
	 * @throws const char* if the name exceeds 50 characters.
	 */
	void setUsername(const std::string& name);
	/**
	 * @brief Creates a deep copy of the player.
	 * @return A pointer to a new Player object cloned from this one.
	 */
	Player* clone() const override;
	/**
	 * @brief Clones the player with a new ID.
	 * @param id The new ID to assign.
	 * @return A pointer to a new Player with the specified ID.
	 */
	Player* cloneWithId(unsigned int id) const override;
public:
	/**
	 * @brief Constructs a Player with a given ID and username.
	 * @param id The player's unique ID.
	 * @param username The player's username.
	 */
	Player(unsigned int id, const std::string& username);
	/**
	 * @brief Constructs a Player with a username. ID defaults to 0.
	 * @param username The player's username.
	 */
	Player(const std::string& username);
	/**
	 * @brief Gets the player's username.
	 * @return A constant reference to the username string.
	 */
	const std::string& getUsername() const;

	/// Grant access to the FileManager for serialization and object management.
	template<class T, class K>
	friend class FileManager;
};