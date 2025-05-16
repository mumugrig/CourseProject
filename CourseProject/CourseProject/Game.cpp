#include "Game.hpp"

void Game::passTurn()
{
    turn = !turn;
    rollDie();
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
    unsigned int playerId;
    in >> id >> playerId;
    player1.deserialize(in);
    in >> playerId;
    player2.deserialize(in);
}

void Game::place(bool board, int x, int y)
{
    if (board) {
        board2.setValue(x, y, dieNumber);
    }
    else {
        board1.setValue(x, y, dieNumber);
    }
}

void Game::seedRandom()
{
    pcg32_srandom_r(&rng, time(0), (size_t)this);
}

Game* Game::clone() const 
{
    return new Game(id, player1, player2, board1, board2, turn);
}

Game* Game::cloneWithId(unsigned int id) const
{
    return new Game(id, player1, player2, board1, board2, turn);
}

void Game::updateScore()
{
    score1 = board1.score();
    score2 = board2.score();
}

void Game::removeFromEnemyBoard(int column)
{
    if (turn) {
        for (int i = 0; i < 3; i++) {
            if (board1.getValue(i, column) == dieNumber) {
                board1.clearValue(i, column);
            }
        }
    }
    else {
        for (int i = 0; i < 3; i++) {
            if (board2.getValue(i, column) == dieNumber) {
                board2.clearValue(i, column);
            }
        }
    }
}

Game::Game(Player& p1, Player& p2) : player1(p1), player2(p2), Storable(0), turn(0), dieNumber(0), rng(), score1(0), score2(0)
{
    seedRandom();
    rollDie();
}

Game::Game(unsigned int id, Player& p1,  Player& p2, const Board& board1, const Board& board2, bool turn) :
    player1(p1), player2(p2), board1(board1),board2(board2),turn(turn), Storable(id), dieNumber(0), rng(), score1(board1.score()), score2(board2.score())
{
    seedRandom();
    rollDie();
}

void Game::rollDie()
{  
    dieNumber = pcg32_boundedrand_r(&rng, 6) + 1;
}

int Game::getDie() const
{
    return dieNumber;
}

int Game::getPlayer1Score() const
{
    return score1;
}

int Game::getPlayer2Score() const
{
    return score2;
}


void Game::place(int x, int y)
{
    place(turn, x, y);

    removeFromEnemyBoard(y);

    updateScore();
    passTurn();

}


bool Game::gameEnded() const
{
    return board1.isFull() || board2.isFull();
}
