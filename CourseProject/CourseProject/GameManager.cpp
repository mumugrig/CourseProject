#include "GameManager.hpp"

void GameManager::serialize(const Game& element, std::ostream& out)
{
    out << element.getId() << ' ' << element.player1.getId() << ' ';
     element.board1.serialize(out);
     out << element.player2.getId() << ' ';
     element.board2.serialize(out);
     out << element.turn << std::endl;
}

Game* GameManager::deserialize(std::istream& in)
{
    unsigned int id;
    unsigned int player1Id;
    unsigned int player2Id;
    Board b1;
    Board b2;
    bool turn;
    Player p1("null");
    Player p2("null");

    in >> id;

    in >> player1Id;
    p1 = players.read(player1Id);
    b1.deserialize(in);
    in >> player2Id;
    p2 = players.read(player2Id);
    b2.deserialize(in);
    in >> turn;

    return new Game(id, p1, p2, b1, b2, turn);
}

void GameManager::save()
{
    std::ofstream fout(fileName);
    for (Game* game : data) { serialize(*game, fout); }
    fout.close();
}

GameManager::GameManager(const char* filename, const PlayerManager& playerManager) :
    FileManager(filename), players(playerManager)
{
    std::ifstream fin(filename);
    fin.ignore();
    while (fin.good()) {
        data.push_back(deserialize(fin));
    }
    fin.close();
}

GameManager::GameManager(const char* filename, bool auto_inc,const PlayerManager& playerManager) 
    : FileManager(filename, auto_inc), players(playerManager)
{
    std::ifstream fin(filename);
    fin.ignore();
    while (fin.good()) {
        data.push_back(deserialize(fin));
    }
    fin.close();
}
