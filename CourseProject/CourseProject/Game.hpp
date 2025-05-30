#pragma once
#include "Player.hpp"
#include "Board.hpp"
#include "Character.hpp"
#include "Ash.hpp"
#include "Felix.hpp"
#include "Columna.hpp"
#include "Libraries/pcg_basic.h"
#include "Die.hpp"

class Game : public Storable<unsigned int> {

	Die die;
	const Player& player1;
	Board board1;
	CharacterEnum character1Id;
	Character* character1;
	int score1;
	const Player& player2;
	Board board2;
	CharacterEnum character2Id;
	Character* character2;
	int score2;
	
	bool turn;

	void passTurn();
	
	void place(bool board, int x, int y);
	Game* clone() const override;
	Game* cloneWithId(unsigned int id) const override;
	void updateScore();
	void updateEnemyBoard(int column);
	void initializeCharacter1(CharacterEnum character);
	void initializeCharacter2(CharacterEnum character);
public:
	Game(const Player& p1, CharacterEnum character1, const Player& p2, CharacterEnum character2);
	Game(unsigned int id, const Player& p1, CharacterEnum character1, const Player& p2, CharacterEnum character2,
		const Board& board1, const Board& board2, bool turn);
	Game(const Game& other);
	Game& operator=(const Game& other) = delete;
	
	int getDieValue() const;
	bool getTurn() const;
	const std::string& getPlayer1Username() const;
	const Character& getPlayer1Character() const;
	const Board& getPlayer1Board() const;
	int getPlayer1Score() const;
	const std::string& getPlayer2Username() const;
	const Character& getPlayer2Character() const;
	const Board& getPlayer2Board() const;
	int getPlayer2Score() const;
	const std::string& getWinnerUsername() const;

	void place(int x, int y);
	void pushCharacterParameters(int x, int y, bool board);
	void resetCharacterParameters();
	const Character& getCurrentCharacter() const;
	const Board& getCurrentBoard() const;
	void useAbility();

	bool gameEnded() const;

	~Game();

	template <class T, class K>
	friend class FileManager;
	friend class GameManager;
};