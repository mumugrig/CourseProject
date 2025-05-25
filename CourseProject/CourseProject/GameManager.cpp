#include "GameManager.hpp"

void GameManager::serialize(const Game& element, std::ostream& out)
{
    out << element.getId() << ' ' << element.player1.getId() << ' ' << element.character1Id << ' ';
     element.board1.serialize(out);
     out << element.player2.getId() << ' ' << element.character2Id << ' ';
     element.board2.serialize(out);
     out << element.turn << std::endl;
}

Game* GameManager::deserialize(std::istream& in)
{
    unsigned int id;
    unsigned int player1Id;
    unsigned int player2Id;
    int character1;
    int character2;
    Board b1;
    Board b2;
    bool turn;
 

    in >> id;

    in >> player1Id;
    const Player& p1 = players.read(player1Id);
    in >> character1;
    b1.deserialize(in);
    in >> player2Id;
    const Player& p2 = players.read(player2Id);
    in >> character2;
    b2.deserialize(in);
    in >> turn;

    return new Game(id, p1, (CharacterEnum)character1, p2, (CharacterEnum)character2, b1, b2, turn);
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
    while (fin.good() && validFile(fin)) {
        data.push_back(deserialize(fin));
        fin.ignore();
    }
    fin.close();
}

GameManager::GameManager(const char* filename, bool auto_inc,const PlayerManager& playerManager) 
    : FileManager(filename, auto_inc), players(playerManager)
{
    std::ifstream fin(filename);
    while (fin.good() && validFile(fin)) {
        data.push_back(deserialize(fin));
        fin.ignore();
    }
    fin.close();
}
