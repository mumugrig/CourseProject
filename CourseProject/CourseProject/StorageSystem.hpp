/**
 * @file StorageSystem.hpp
 * @brief Defines the StorageSystem class, which acts as a unified interface for managing players and games.
 */
#pragma once
#include "PlayerManager.hpp"
#include "GameManager.hpp"
 /**
  * @class StorageSystem
  * @brief A wrapper class that encapsulates both PlayerManager and GameManager.
  *
  * Provides a centralized interface for accessing and managing players and games in the system.
  */
class StorageSystem {

	/// Manager responsible for player-related operations.
	PlayerManager playerManager;
	/// Manager responsible for game-related operations.
	GameManager gameManager;

public:

	/**
	 * @brief Constructs a StorageSystem with default file names for players and games.
	 *
	 * Initializes PlayerManager with "players.txt" and GameManager with "games.txt".
	 * GameManager depends on PlayerManager for resolving player references.
	 */
	StorageSystem() : playerManager("players.txt"), gameManager("games.txt", playerManager) {}
	
	/**
	 * @brief Accessor for the PlayerManager.
	 * @return Reference to the internal PlayerManager instance.
	 */
	PlayerManager& players() { return playerManager; }

	/**
	 * @brief Accessor for the GameManager.
	 * @return Reference to the internal GameManager instance.
	 */
	GameManager& games() { return gameManager; }

	/**
	 * @brief Default destructor.
	 */
	~StorageSystem() = default;
};