#pragma once
#include "FileManager.hpp"
#include "Game.hpp"
#include "PlayerManager.hpp"
class GameManager : public FileManager<Game, unsigned int> {
	
	const PlayerManager& players;

	void serialize(const Game& element, std::ostream& out) override;
	Game* deserialize(std::istream& in) override;
	

public:
	void save() override;
	GameManager(const char* filename, const PlayerManager& playerManager);
	GameManager(const char* filename, bool auto_inc, const PlayerManager& playerManager);
};