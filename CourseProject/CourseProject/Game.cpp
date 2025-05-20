#include "Game.hpp"

void Game::passTurn()
{
    (turn ? character2 : character1)->reduceCooldown();
    turn = !turn;
    rollDie();
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
    return new Game(id, player1, character1Id, player2, character2Id, board1, board2, turn);
}

Game* Game::cloneWithId(unsigned int id) const
{
    return new Game(id, player1, character1Id, player2, character2Id, board1, board2, turn);
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
            if (board1.getValue(column, i) == dieNumber) {
                board1.clearValue(column, i);
            }
        }
    }
    else {
        for (int i = 0; i < 3; i++) {
            if (board2.getValue(column, i) == dieNumber) {
                board2.clearValue(column, i);
            }
        }
    }
}

void Game::initializeCharacter1(CharacterEnum character)
{
    switch (character) {
        case ASH: character1 = new Ash(board1, board2);

    }
}

void Game::initializeCharacter2(CharacterEnum character)
{
    switch (character) {
        case ASH: character2 = new Ash(board2, board1);

    }
}

Game::Game(Player& p1, CharacterEnum character1, Player& p2, CharacterEnum character2) : 
    Storable(0),player1(p1), player2(p2), turn(0), dieNumber(0), rng(), score1(0), score2(0),
    character1Id(character1), character2Id(character2)
{
    initializeCharacter1(character1Id);
    initializeCharacter2(character1Id);

    seedRandom();
    rollDie();
}

Game::Game(unsigned int id, Player& p1, CharacterEnum character1,  Player& p2, CharacterEnum character2,
    const Board& board1, const Board& board2, bool turn) :
    player1(p1), player2(p2), board1(board1),board2(board2),turn(turn),
    Storable(id), dieNumber(0), rng(), score1(board1.score()), score2(board2.score()),
    character1Id(character1), character2Id(character2)
{
    initializeCharacter1(character1);
    initializeCharacter2(character1);

    seedRandom();
    rollDie();
}

Game::Game(const Game& other) : Storable(other.id), player1(other.player1), player2(other.player2),
board1(other.board1), board2(other.board2), turn(other.turn), dieNumber(other.dieNumber), rng(), score1(other.score1),
score2(other.score2), character1Id(other.character1Id), character2Id(other.character2Id)
{
    initializeCharacter1(character1Id);
    initializeCharacter2(character1Id);

    seedRandom();
}

void Game::rollDie()
{  
    dieNumber = pcg32_boundedrand_r(&rng, 6) + 1;
}

int Game::getDie() const
{
    return dieNumber;
}

bool Game::getTurn() const
{
    return turn;
}

const std::string& Game::getPlayer1Username() const
{
    return player1.getUsername();
}

const Character& Game::getPlayer1Character() const
{
    return *character1;
}

const Board& Game::getPlayer1Board() const
{
    return board1;
}

int Game::getPlayer1Score() const
{
    return score1;
}

const std::string& Game::getPlayer2Username() const
{
    return player2.getUsername();
}

const Character& Game::getPlayer2Character() const
{
    return *character2;
}

const Board& Game::getPlayer2Board() const
{
    return board2;
}

int Game::getPlayer2Score() const
{
    return score2;
}


void Game::place(int x, int y)
{
    place(turn, x, y);

    removeFromEnemyBoard(x);

    updateScore();
    passTurn();

}

void Game::readAndSetCharacterParameters(std::istream& in)
{
    turn ? character2->readAndSetParameters(in) : character1->readAndSetParameters(in);
}

const Character& Game::getCurrentCharacter() const
{
    return (turn ? getPlayer2Character() : getPlayer1Character());
}

const Board& Game::getCurrentBoard() const
{
    return (turn ? getPlayer2Board() : getPlayer1Board());
}

void Game::useAbility()
{
    turn ? character2->ability() : character1->ability();
}


bool Game::gameEnded() const
{
    return board1.isFull() || board2.isFull();
}

Game::~Game()
{
    delete character1;
    delete character2;
}
