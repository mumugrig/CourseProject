#pragma once
#include "Player.hpp"
#include "Board.hpp"
#include "Libraries/pcg_basic.h"

class Game : public Storable<unsigned int> {

	Player& player1;
	Board board1;
	int score1;
	Player& player2;
	Board board2;
	int score2;
	bool turn;
	int dieNumber;
	pcg32_random_t rng;
	void passTurn();
	void serialize(std::ostream& out) const override;
	void deserialize(std::istream& in) override;
	void place(bool board, int x, int y);
	void seedRandom();
	Game* clone() const override;
	Game* cloneWithId(unsigned int id) const override;
	void updateScore();
	void removeFromEnemyBoard(int column);
public:
	Game( Player& p1,  Player& p2);
	Game(unsigned int id, Player& p1,  Player& p2,
		const Board& board1, const Board& board2, bool turn);

	void rollDie();
	
	int getDie() const;
	int getPlayer1Score() const;
	int getPlayer2Score() const;

	void place(int x, int y);

	bool gameEnded() const;

};