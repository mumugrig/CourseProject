#pragma once
#include "Player.hpp"
#include "Board.hpp"
#include "Character.hpp"
#include "Ash.hpp"
#include "Felix.hpp"
#include "Columna.hpp"
#include "Oliver.hpp"
#include "Libraries/pcg_basic.h"
#include "Die.hpp"

/**
 * @class Game
 * @brief Manages the state and logic of a two-player board game with characters and abilities.
 */

class Game : public Storable<unsigned int> {

	Die die; ///< Shared die used by both players.
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
	
	bool turn; ///< Shared die used by both players.
	///< True if it's player2's turn, false for player1.
	void passTurn();
	/**
	 * @brief Places the die value on the specified board and coordinates.
	 * @param board True for board2, false for board1.
	 * @param x X-coordinate (column).
	 * @param y Y-coordinate (row).
	 */
	void place(bool board, int x, int y);
	/**
	 * @brief Creates a deep copy of the current game instance.
	 * @return A dynamically allocated copy of the game.
	 */
	Game* clone() const override;
	/**
	 * @brief Creates a deep copy of the game with a new ID.
	 * @param id The new ID for the cloned game.
	 * @return A dynamically allocated copy of the game with new ID.
	 */
	Game* cloneWithId(unsigned int id) const override;
	/**
	 * @brief Updates the scores for both players.
	 */
	void updateScore();
	/**
	 * @brief Clears values from the enemy board column that match the current die value.
	 * @param column The column index to check.
	 */
	void updateEnemyBoard(int column);
	/**
	 * @brief Initializes player1's character.
	 * @param character The selected character type.
	 */
	void initializeCharacter1(CharacterEnum character);
	/**
	 * @brief Initializes player2's character.
	 * @param character The selected character type.
	 */
	void initializeCharacter2(CharacterEnum character);
public:
	/**
	 * @brief Constructs a new Game with two players and their selected characters.
	 * @param p1 First player.
	 * @param character1 First player's character.
	 * @param p2 Second player.
	 * @param character2 Second player's character.
	 */
	Game(const Player& p1, CharacterEnum character1, const Player& p2, CharacterEnum character2);
	/**
	 * @brief Constructs a game with a known state (used for loading).
	 * @param id Game ID.
	 * @param p1 First player.
	 * @param character1 First player's character.
	 * @param p2 Second player.
	 * @param character2 Second player's character.
	 * @param board1 Board for player 1.
	 * @param board2 Board for player 2.
	 * @param turn True if it's player2's turn.
	 */
	Game(unsigned int id, const Player& p1, CharacterEnum character1, const Player& p2, CharacterEnum character2,
		const Board& board1, const Board& board2, bool turn);
	/**
	 * @brief Copy constructor (deep copy).
	 * @param other The Game object to copy.
	 */
	Game(const Game& other);
	/// Deleted assignment operator.
	Game& operator=(const Game& other) = delete;
	/**
	 * @brief Gets the value of the current die.
	 * @return An integer representing the die roll.
	 */
	int getDieValue() const;
	/**
	 * @brief Returns true if it is player2's turn.
	 * @return True if it's player2's turn; false otherwise.
	 */
	bool getTurn() const;
	/// @return Username of player 1.
	const std::string& getPlayer1Username() const;
	/// @return Player 1's character.
	const Character& getPlayer1Character() const;
	/// @return Player 1's board.
	const Board& getPlayer1Board() const;
	/// @return Player 1's current score.
	int getPlayer1Score() const;
	/// @return Username of player 2.
	const std::string& getPlayer2Username() const;
	/// @return Player 2's character.
	const Character& getPlayer2Character() const;
	/// @return Player 2's board.
	const Board& getPlayer2Board() const;
	/// @return Player 2's current score.
	int getPlayer2Score() const;
	/**
	 * @brief Determines the winner based on scores.
	 * @return The winner's username or "Draw" if tied.
	 */
	const std::string& getWinnerUsername() const;
	/**
	 * @brief Places a die value on the current player's board and updates the game state.
	 * @param x X-coordinate (column).
	 * @param y Y-coordinate (row).
	 */
	void place(int x, int y);
	/**
	 * @brief Pushes a point as a parameter to the current player's character ability.
	 * @param point The point to push.
	 */
	void pushCharacterParameters(const Point& point);
	/**
	 * @brief Resets selection or parameters of the current player's character.
	 */
	void resetCharacterParameters();
	/**
	 * @brief Gets the character of the player whose turn it is.
	 * @return Reference to the active character.
	 */
	const Character& getCurrentCharacter() const;
	/**
	 * @brief Gets the board of the player whose turn it is.
	 * @return Reference to the active player's board.
	 */
	const Board& getCurrentBoard() const;
	/**
	 * @brief Triggers the ability of the current player's character and updates scores.
	 */
	void useAbility();
	/**
	 * @brief Checks if the game has ended (either board is full).
	 * @return True if the game has ended.
	 */
	bool gameEnded() const;
	/**
	 * @brief Destructor that deallocates character objects.
	 */
	~Game();

	template <class T, class K>
	friend class FileManager;
	friend class GameManager;
};