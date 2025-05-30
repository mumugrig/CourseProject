#pragma once
#include "StorageSystem.hpp"
#include "Libraries/color.hpp"
#include "BothBoardsPosition.hpp"
#include <Windows.h>


class GameView {

	Position* position;
	
	Game& game;
	StorageSystem& storage;

	bool usingAbility1;
	bool usingAbility2;

	bool& usingAbility() { return (game.getTurn() ? usingAbility2 : usingAbility1); }

	bool keyPressed(char key);

	void printLine();
	void printRow1(const Game& game, const Board& gameBoard, const std::function<bool(int, int)>& selectCondition);
	void printRow2(const Game& game, const Board& gameBoard, const std::function<bool(int, int)>& selectCondition, const Character& character, bool usingAbility);
	void printRow3(const Game& game, const Board& gameBoard, const std::function<bool(int, int)>& selectCondition);

	void printPlayer1(const Game& game);
	void printPlayer2(const Game& game);

public:
	GameView(Game& game, StorageSystem& storage);
	GameView(const GameView& other) = delete;
	GameView& operator=(const GameView& other) = delete;
	~GameView();

	const Game& getGame();

	void selectPlace();

	void printGame(const Game& game);

	void startGame();
};