#pragma once
#include "FileManager.hpp"
#include "Player.hpp"

class PlayerManager : public FileManager<Player, unsigned int> {
	void serialize(const Player& element, std::ostream& out) override;
	Player* deserialize(std::istream& in) override;
public:
	void save() override;
	void add(const Player& player) override;
	PlayerManager(const char* filename);
	PlayerManager(const char* filename, bool auto_inc);
};