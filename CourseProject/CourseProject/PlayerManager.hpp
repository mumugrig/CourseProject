#pragma once
#include "Player.hpp"
#include "FileManager.hpp"
#include <vector>

class PlayerManager : FileManager<unsigned int> {
	std::vector<Player*> players;
public:

};