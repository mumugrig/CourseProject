#include "Game.hpp"

void Game::passTurn()
{
    turn = !turn;
}

void Game::serialize(std::ostream& out) const
{
    out << id << ' ' << player1.getId() << ' ';
    board1.serialize(out);
    out << player2.getId() << ' ';
    board2.serialize(out);
}

void Game::deserialize(std::istream& in)
{
}

void Game::place(bool board, int x, int y)
{
}

Game::Game(Player& p1, Player& p2) : player1(p1), player2(p2), Storable(0), turn(0), dieNumber(0)
{
}

Game::Game(unsigned int id, Player& p1,  Player& p2, const Board& board1, const Board& board2, bool turn) :
    player1(p1), player2(p2), board1(board1),board2(board2),turn(turn), Storable(id), dieNumber(0)
{
}

int Game::rollDie()
{
    return 0;
}

void Game::placeInPlayerBoard(int x, int y)
{
    place(turn, x, y);
}

void Game::save() const
{
}

void Game::save(const char* filename) const
{
}

void Game::load(const char* filename)
{
}

bool Game::gameEnded()
{
    return false;
}
