#pragma once
#include "PlayerManager.hpp"
#include "GameManager.hpp"
class StorageSystem {
	PlayerManager playerManager;
	GameManager gameManager;

public:
	StorageSystem() : playerManager("players.txt"), gameManager("games.txt", playerManager) {}
	
	PlayerManager& players() { return playerManager; }
	GameManager& games() { return gameManager; }
};