#pragma once
#include "GameView.hpp"
#include "VectorUtility.hpp"

class MainMenu {
public:
	static void printLine();

	static void printRow1(const Game& game, const Board& gameBoard);

	static void printRow2(const Game& game, const Board& gameBoard, const Character& character);

	static void printRow3(const Game& game, const Board& gameBoard);

	static void printPlayer1(const Game& game);
	static void printPlayer2(const Game& game);
	static void printGame(const Game& game, const Player& player, bool withConclusion);


	static std::string inputUsername();

	static void readPlayer(StorageSystem& files, Player& player, std::string username);

	static void choosePlayers(StorageSystem& files, Player& player1, Player& player2);

	static void startGame(StorageSystem& files, Game& game);

	static void newGame(StorageSystem& files, const Player& player1, const CharacterEnum& characterId1, const Player& player2, const CharacterEnum& characterId2);


	static void characterSelect(CharacterEnum& characterId);

	static void matchHistory(StorageSystem& files, const Player& player);

	static void playerDetails(StorageSystem& files, const Player& player, CharacterEnum& characterId);

	static void loadGame(StorageSystem& files, const Player& player1, const Player& player2);

	static void printMenu(StorageSystem& files, const Player& player1, CharacterEnum& characterId1, const Player& player2, CharacterEnum& characterId2);


};