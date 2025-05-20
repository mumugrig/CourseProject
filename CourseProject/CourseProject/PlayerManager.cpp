#include "PlayerManager.hpp"
#include "VectorUtility.hpp"
#include <stdexcept>
void PlayerManager::serialize(const Player& element, std::ostream& out)
{
	out << element.getId() << ' '
		<< element.getUsername() << ' '
		<< element.getHighScore() << std::endl;
}

Player* PlayerManager::deserialize(std::istream& in)
{
	unsigned int id;
	std::string name;
	unsigned int highScore;
	in >> id >> name >> highScore;
	return new Player(id, name, highScore);
}

void PlayerManager::save()
{
	std::ofstream fout(fileName);
	for (Player* p : data) { serialize(*p, fout); }
	fout.close();
}

void PlayerManager::add(const Player& player)
{
	if (!VectorUtility::any<Player*>(
		[&x = player.getUsername()](Player* const& p){return p->getUsername() == x; }, data)
		){
		FileManager::add(player);
	}
	else {
		throw std::runtime_error("username already exists");
	}	
}

PlayerManager::PlayerManager(const char* filename) : FileManager(filename)
{
	std::ifstream fin(filename);
	while (fin.good() && validFile(fin)) {
		data.push_back(deserialize(fin));
		fin.ignore();
	}
	fin.close();
}

PlayerManager::PlayerManager(const char* filename, bool auto_inc) : FileManager(filename, auto_inc)
{
	std::ifstream fin(filename);
	while (fin.good() && validFile(fin)) {
		data.push_back(deserialize(fin));
		fin.ignore();
	}
	fin.close();
}
