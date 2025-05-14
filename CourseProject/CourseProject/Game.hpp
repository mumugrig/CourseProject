#pragma once
#include "Player.hpp"
#include "Board.hpp"

class Game : public Storable<unsigned int> {

	Player& player1;
	Board board1;
	Player& player2;
	Board board2;
	bool turn;
	int dieNumber;

	void passTurn();
	void serialize(std::ostream& out) const override;
	void deserialize(std::istream& in) override;
	void place(bool board, int x, int y);
public:
	Game( Player& p1,  Player& p2);
	Game(unsigned int id, Player& p1,  Player& p2,
		const Board& board1, const Board& board2, bool turn);

	int rollDie();
	
	void placeInPlayerBoard(int x, int y);

	void save() const;
	void save(const char* filename) const;
	void load(const char* filename);

	bool gameEnded();

};