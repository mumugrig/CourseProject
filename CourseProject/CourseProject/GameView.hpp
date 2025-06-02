#pragma once
#include "StorageSystem.hpp"
#include "Libraries/color.hpp"
#include "BothBoardsPosition.hpp"
#include <Windows.h>

/**
 * @class GameView
 * @brief Manages the display and user interaction for a Game instance in the console.
 */

class GameView {
	/// Stores the currently selected board cell (on either board).
	Position* position;
	/// Reference to the game being played.
	Game& game;
	/// Reference to the storage system used for saving the game.
	StorageSystem& storage;
	/// Flag for whether player 1 is currently using their character ability.
	bool usingAbility1;
	/// Flag for whether player 2 is currently using their character ability.
	bool usingAbility2;

	/**
	 * @brief Returns the ability usage flag of the current player.
	 * @return Reference to the correct `usingAbility` flag.
	 */
	bool& usingAbility() { return (game.getTurn() ? usingAbility2 : usingAbility1); }
	/**
	 * @brief Checks if a specific key is currently pressed.
	 * @param key Virtual-key code (e.g., VK_LEFT).
	 * @return True if the key is pressed, false otherwise.
	 */
	bool keyPressed(char key);
	/// Prints a horizontal line between board rows.
	void printLine();
	/**
	 * @brief Prints the top row of a board.
	 * @param game Reference to the game.
	 * @param gameBoard The board to print.
	 * @param selectCondition Function that checks if a cell is selected.
	 */
	void printRow1( const Board& gameBoard, const std::function<bool(int, int)>& selectCondition);
	/**
	 * @brief Prints the middle row and character representation beside it.
	 * @param game Reference to the game.
	 * @param gameBoard The board to print.
	 * @param selectCondition Function that checks if a cell is selected.
	 * @param character The character whose symbol and color are shown.
	 * @param usingAbility Whether the ability is currently being prepared.
	 */
	void printRow2(const Board& gameBoard, const std::function<bool(int, int)>& selectCondition, const Character& character, bool usingAbility);
	/**
	 * @brief Prints the bottom row of a board.
	 * @param game Reference to the game.
	 * @param gameBoard The board to print.
	 * @param selectCondition Function that checks if a cell is selected.
	 */
	void printRow3(const Board& gameBoard, const std::function<bool(int, int)>& selectCondition);
	/**
	 * @brief Prints the board, character, and score of player 1.
	 * @param game Reference to the game.
	 */
	void printPlayer1();
	/**
	 * @brief Prints the board, character, and score of player 2.
	 * @param game Reference to the game.
	 */
	void printPlayer2();

public:
	/**
	 * @brief Constructs the view for a game.
	 * @param game The game instance to visualize.
	 * @param storage Reference to the storage system for saving.
	 */
	GameView(Game& game, StorageSystem& storage);
	/// Deleted copy constructor.
	GameView(const GameView& other) = delete;
	/// Deleted assignment operator.
	GameView& operator=(const GameView& other) = delete;
	/// Destructor, cleans up dynamically allocated position.
	~GameView();

	/**
	 * @brief Returns a constant reference to the current game.
	 * @return Const reference to the game.
	 */
	const Game& getGame();
	/**
	 * @brief Tries to place the die value at the currently selected cell and updates turn.
	 */
	void selectPlace();
	/**
	 * @brief Clears the screen and prints the full game state: both players, boards, and die roll.
	 * @param game Reference to the game to print.
	 */
	void printGame();
	/**
	 * @brief Starts the interactive game loop. Handles movement, selection, ability usage, and saving.
	 */
	void startGame();
};