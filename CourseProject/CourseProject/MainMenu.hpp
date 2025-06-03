#pragma once
#include "GameView.hpp"
#include "VectorUtility.hpp"


/**
 * @class MainMenu
 * @brief Provides a user interface to control the game: manage players, start/load games, and view history.
 */
class MainMenu {
	/**
	 * @brief Prints a horizontal line for board formatting.
	 */
	static void printLine();
	/**
	 * @brief Prints the first row of a player's board.
	 * @param game The current game instance.
	 * @param gameBoard The board to print.
	 */
	static void printRow1(const Game& game, const Board& gameBoard);
	/**
	 * @brief Prints the second row of a player's board, including the character symbol.
	 * @param game The current game instance.
	 * @param gameBoard The board to print.
	 * @param character The character used by the player.
	 */
	static void printRow2(const Game& game, const Board& gameBoard, const Character& character);
	/**
	* @brief Prints the third row of a player's board.
	* @param game The current game instance.
	* @param gameBoard The board to print.
	*/
	static void printRow3(const Game& game, const Board& gameBoard);
	/**
	* @brief Prints the first player's board, username, and score.
	* @param game The current game instance.
	*/
	static void printPlayer1(const Game& game);
	/**
	* @brief Prints the second player's board, username, and score.
	* @param game The current game instance.
	*/
	static void printPlayer2(const Game& game);
	/**
	 * @brief Prints the full game state for both players, with optional conclusion display.
	 * @param game The game to print.
	 * @param player The current player viewing the game.
	 * @param withConclusion Whether to display "Victory", "Defeat", or "Draw".
	 */
	static void printGame(const Game& game, const Player& player, bool withConclusion);
	/**
	 * @brief Prompts the user to input a username and validates its length.
	 * @return The entered username.
	 */
	static std::string inputUsername();
	/**
	 * @brief Loads a player from storage or creates a new one if not found.
	 * @param files The storage system containing player data.
	 * @param player Reference to the player to load.
	 * @param username The username to look for or create.
	 */
	static void readPlayer(StorageSystem& files, Player& player, std::string username);
	/**
	 * @brief Starts the game using a GameView and handles game saving.
	 * @param files The storage system for saving games.
	 * @param game The game to be played.
	 */
	static void startGame(StorageSystem& files, Game& game);
	/**
	 * @brief Creates a new game and starts it.
	 * @param files The storage system to save the new game.
	 * @param player1 First player.
	 * @param characterId1 First player's character.
	 * @param player2 Second player.
	 * @param characterId2 Second player's character.
	 */
	static void newGame(StorageSystem& files, const Player& player1, const CharacterEnum& characterId1, const Player& player2, const CharacterEnum& characterId2);
	/**
	* @brief Displays a character selection menu.
	* @param characterId The selected character ID.
	*/
	static void characterSelect(CharacterEnum& characterId);
	/**
	* @brief Displays the match history for a player.
	* @param files The storage system containing games.
	* @param player The player whose history will be shown.
	*/
	static void matchHistory(StorageSystem& files, const Player& player);
	/**
	 * @brief Shows the menu for selecting character and viewing match history.
	 * @param files The storage system.
	 * @param player The player to look up.
	 * @param characterId Reference to the player's current character.
	 */
	static void playerDetails(StorageSystem& files, const Player& player, CharacterEnum& characterId);
	/**
	 * @brief Displays a list of saved games and allows the user to resume one.
	 * @param files The storage system containing saved games.
	 * @param player1 First player.
	 * @param player2 Second player.
	 */
	static void loadGame(StorageSystem& files, const Player& player1, const Player& player2);
	/**
	* @brief Displays the rules of the game.
	*/
	static void printRules();
public:
	/**
	 * @brief Prompts the user to choose two players by username.
	 * @param files The storage system.
	 * @param player1 Reference to the first player object to populate.
	 * @param player2 Reference to the second player object to populate.
	 */
	static void choosePlayers(StorageSystem& files, Player& player1, Player& player2);
	/**
	 * @brief Displays the main menu for starting, loading games, and managing players.
	 * @param files The storage system.
	 * @param player1 First player.
	 * @param characterId1 First player's character.
	 * @param player2 Second player.
	 * @param characterId2 Second player's character.
	 */
	static void printMenu(StorageSystem& files, const Player& player1, CharacterEnum& characterId1, const Player& player2, CharacterEnum& characterId2);


};