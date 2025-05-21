#pragma once
#include "StorageSystem.hpp"
#include "Libraries/color.hpp"
#include <Windows.h>

class GameView {
	int x;
	int y;
	bool board;

	Game& game;
	StorageSystem& storage;
	bool keyPressed(char key);
	void moveConditionXOneBoard();
	void moveConditionXBothBoards();
	void moveConditionYOneBoard();
	void moveConditionYBothBoards();
	void moveConditionX();
	void moveConditionY();

	bool selectSinglePlayer1Board(int j, int i);
	bool selectSinglePlayer2Board(int j, int i);
public:
	GameView(Game& game, StorageSystem& storage);
	const Game& getGame();
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void selectPlace();

	void printLine();

	void printRow1(const Board& gameBoard, const std::function<bool(int, int)>& selectCondition);
	void printRow2(const Board& gameBoard, const std::function<bool(int, int)>& selectCondition, const Character& character);
	void printRow3(const Board& gameBoard, const std::function<bool(int, int)>& selectCondition);

	void printPlayer1(const Game& game);
	void printPlayer2(const Game& game);
	void printGame(const Game& game);

	void startGame();
};