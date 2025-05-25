#pragma once
#include "StorageSystem.hpp"
#include "Libraries/color.hpp"
#include "SingleBoardPosition.hpp"
#include "BothBoardsPosition.hpp"
#include <Windows.h>


class GameView {

	Position* position;
	
	Game& game;
	StorageSystem& storage;

	bool usingAbility;
	Selection abilitySelection;

	bool keyPressed(char key);

	bool selectSinglePlayer1Board(int j, int i);
	bool selectSinglePlayer2Board(int j, int i);


	void printLine();

	void printRow1(const Board& gameBoard, const std::function<bool(int, int)>& selectCondition);
	void printRow2(const Board& gameBoard, const std::function<bool(int, int)>& selectCondition, const Character& character);
	void printRow3(const Board& gameBoard, const std::function<bool(int, int)>& selectCondition);

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