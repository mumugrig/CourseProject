#pragma once
#include "Player.hpp"
#include "Board.hpp"
#include "Character.hpp"
#include "Ash.hpp"
#include "Libraries/pcg_basic.h"

class Game : public Storable<unsigned int> {

	Player& player1;
	Board board1;
	CharacterEnum character1Id;
	Character* character1;
	int score1;
	Player& player2;
	Board board2;
	CharacterEnum character2Id;
	Character* character2;
	int score2;
	int dieNumber;
	pcg32_random_t rng;
	bool turn;
	void passTurn();
	
	void place(bool board, int x, int y);
	void seedRandom();
	Game* clone() const override;
	Game* cloneWithId(unsigned int id) const override;
	void updateScore();
	void removeFromEnemyBoard(int column);
	void initializeCharacter1(CharacterEnum character);
	void initializeCharacter2(CharacterEnum character);
public:
	Game(Player& p1, CharacterEnum character1, Player& p2, CharacterEnum character2);
	Game(unsigned int id, Player& p1, CharacterEnum character1, Player& p2, CharacterEnum character2,
		const Board& board1, const Board& board2, bool turn);
	Game(const Game& other);
	Game& operator=(const Game& other) = delete;

	void rollDie();
	
	int getDie() const;
	bool getTurn() const;
	const std::string& getPlayer1Username() const;
	const Board& getPlayer1Board() const;
	int getPlayer1Score() const;
	const std::string& getPlayer2Username() const;
	const Board& getPlayer2Board() const;
	int getPlayer2Score() const;

	void place(int x, int y);
	void useAbility();

	bool gameEnded() const;

	~Game();

	template <class T, class K>
	friend class FileManager;
	friend class GameManager;
};