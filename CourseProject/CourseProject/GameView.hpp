#pragma once
#include "StorageSystem.hpp"
#include "Libraries/color.hpp"
#include <Windows.h>



class GameView {
	int x;
	int y;

	Game& game;
	StorageSystem& storage;
	bool keyPressed(char key) {
		if(GetKeyState(key) & 0x8000)
		{
			return true;
		}
		return false;
	}
	bool moveConditionXCurrentBoard();
	bool moveConditionXOpponentBoard();
	bool moveConditionXBothBoards();
	bool moveConditionYCurrentBoard();
	bool moveConditionYOpponentBoard();
	bool moveConditionYBothBoards();

	bool moveConditionX(int x){

	}

	bool moveConditionY(int y) {

	}
public:
	GameView(Game& game, StorageSystem& storage) : game(game), storage(storage), x(0), y(0) {}
	const Game& getGame() { return game; }
	void moveUp() {
		y--;
		if (y < 0)y = 2;
	}
	void moveDown() {
		y++;
		if (y > 2)y = 0;
	}
	void moveLeft() {
		x--;
		if (x < 0)x = 3;
	}
	void moveRight() {
		x++;
		if (x > 3) x = 0;
	}
	void selectPlace() {
		game.place(x, y);
	}

	void printLine() {
		std::cout << /*dye::aqua*/("-------------") << std::endl;
	}

	void printPlayer1(const Game& game) {
		std::cout << game.getPlayer1Username() << std::endl;
		printLine();
		const Board board1 = game.getPlayer1Board();
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				std::cout << '|';
				if (!game.getTurn() && i == y && j == x) std::cout << hue::black_on_light_red;
				std::cout	<< ' ';
				char c;
				if (board1.getValue(j, i) > 0)c = '0' + board1.getValue(j, i);
				else c= ' ';
				
				std::cout << c << ' ';
				std::cout << hue::reset;
			}
			std::cout << '|' << std::endl;
			printLine();
		}
		std::cout << game.getPlayer1Score() << std::endl;
		
	}

	void printPlayer2(const Game& game) {
		std::cout << game.getPlayer2Score() << std::endl;
		printLine();
		const Board board2 = game.getPlayer2Board();
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				std::cout << '|';
				if (game.getTurn() && i == y && j == x) std::cout << hue::black_on_light_red;
				std::cout << ' ';
				char c;
				if (board2.getValue(j, i) > 0)c = '0' + board2.getValue(j, i);
				else c = ' ';

				std::cout << c << ' ';
				std::cout << hue::reset;
			}
			std::cout << '|' << std::endl;
			printLine();
		}
		std::cout << game.getPlayer2Username() << std::endl;
	}
	void printGame(const Game& game) {
		system("cls");
		printPlayer1(game);
		std::cout << std::endl << std::endl;
		printPlayer2(game);
		std::cout << std::endl;
		std::cout << (game.getTurn() ? game.getPlayer2Username() : game.getPlayer1Username())
			<< "\'s turn." << std::endl;
		std::cout << "Rolled a " << game.getDie() << std::endl;
	}

	void startGame() {
		printGame(game);
		while (!game.gameEnded()) {	
			if (keyPressed(VK_LEFT)) {
				moveLeft();
				printGame(game);
			}
			if (keyPressed(VK_UP)) {
				moveUp();
				printGame(game);
			}
			if (keyPressed(VK_RIGHT)) {
				moveRight();
				printGame(game);
			}
			if (keyPressed(VK_DOWN)) {
				moveDown();
				printGame(game);
			}
			if (keyPressed(VK_RETURN)) {
				try {
					selectPlace();
					printGame(game);
				}
				catch (const std::runtime_error& ex) {}
			}
			Sleep(50);
		}
		printGame(game);
	}
};