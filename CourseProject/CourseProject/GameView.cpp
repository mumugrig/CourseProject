#include "GameView.hpp"

inline bool GameView::keyPressed(char key) {
	if (GetKeyState(key) & 0x8000)
	{
		return true;
	}
	return false;
}

inline void GameView::moveConditionXOneBoard() {
	if (x < 0)x = 3;
	if (x > 3) x = 0;
}

inline void GameView::moveConditionXBothBoards() {
	if (x < 0)x = 3;
	if (x > 3) x = 0;
}

inline void GameView::moveConditionYOneBoard() {
	if (y < 0) y = 2;
	if (y > 2) y = 0;
}

inline void GameView::moveConditionYBothBoards() {
	if (y < 0) {
		y = 2;
		board = !board;
	}
	if (y > 2) {
		y = 0;
		board = !board;
	}
}

inline void GameView::moveConditionX() {
	moveConditionXOneBoard();
}

inline void GameView::moveConditionY() {
	moveConditionYOneBoard();
}

inline bool GameView::selectSinglePlayer1Board(int j, int i) {
	return !board && i == y && j == x;
}

inline bool GameView::selectSinglePlayer2Board(int j, int i) {
	return board && i == y && j == x;
}

GameView::GameView(Game& game, StorageSystem& storage) :
	game(game), storage(storage), x(0), y(0), board(false) {}

inline const Game& GameView::getGame() { return game; }

inline void GameView::moveUp() {
	y--;
	moveConditionY();
}

inline void GameView::moveDown() {
	y++;
	moveConditionY();
}

inline void GameView::moveLeft() {
	x--;
	moveConditionX();
}

inline void GameView::moveRight() {
	x++;
	moveConditionX();
}

inline void GameView::selectPlace() {
	game.place(x, y);
	board = game.getTurn();
}

inline void GameView::printLine() {
	std::cout << ("+---+---+---+") << std::endl;
}

inline void GameView::printRow1(const Board& gameBoard, const std::function<bool(int, int)>& selectCondition) {
	printLine();
	for (int j = 0; j < 3; j++) {
		std::cout << '|';
		if (selectCondition(j, 0)) std::cout << hue::black_on_light_red;
		std::cout << ' ';
		char c;
		if (gameBoard.getValue(j, 0) > 0)c = '0' + gameBoard.getValue(j, 0);
		else c = ' ';

		std::cout << c << ' ';
		std::cout << hue::reset;
	}
	std::cout << '|' << std::endl;
}

inline void GameView::printRow2(const Board& gameBoard, const std::function<bool(int, int)>& selectCondition, const Character& character) {
	std::cout << "+---+---+---+      " << game.getPlayer1Character().color("++---++") << std::endl;
	for (int j = 0; j < 3; j++) {
		std::cout << '|';
		if (selectCondition(j, 1)) std::cout << hue::black_on_light_red;
		std::cout << ' ';
		char c;
		if (gameBoard.getValue(j, 1) > 0)c = '0' + gameBoard.getValue(j, 1);
		else c = ' ';

		std::cout << c << ' ';
		std::cout << hue::reset;
	}
	if (selectCondition(3,0) || selectCondition(3,1) || selectCondition(3,2)) std::cout << "|      " << character.color("|| ") << character.color("O") << character.color(" ||") << std::endl;
	else std::cout << "|      " << character.color("|| ") << character.color("X") << character.color(" ||") << std::endl;
	std::cout << "+---+---+---+      " << character.color("++---++") << std::endl;
}

inline void GameView::printRow3(const Board& gameBoard, const std::function<bool(int, int)>& selectCondition) {
	for (int j = 0; j < 3; j++) {
		std::cout << '|';
		if (selectCondition(j, 2)) std::cout << hue::black_on_light_red;
		std::cout << ' ';
		char c;
		if (gameBoard.getValue(j, 2) > 0)c = '0' + gameBoard.getValue(j, 2);
		else c = ' ';

		std::cout << c << ' ';
		std::cout << hue::reset;
	}
	std::cout << '|' << std::endl;
	printLine();
}

void GameView::printPlayer1(const Game& game)
{
	std::cout << game.getPlayer1Username() << std::endl;
	const Board& board1 = game.getPlayer1Board();

	printRow1(board1, [this](int j, int i) {return selectSinglePlayer1Board(j, i); });
	printRow2(board1, [this](int j, int i) {return selectSinglePlayer1Board(j, i); }, game.getPlayer1Character());
	printRow3(board1, [this](int j, int i) {return selectSinglePlayer1Board(j, i); });

	std::cout << game.getPlayer1Score() << std::endl;

}
void GameView::printPlayer2(const Game& game) {
	std::cout << game.getPlayer2Score() << std::endl;
	const Board board2 = game.getPlayer2Board();
	printRow1(board2, [this](int j, int i) {return selectSinglePlayer2Board(j, i); });
	printRow2(board2, [this](int j, int i) {return selectSinglePlayer2Board(j, i); }, game.getPlayer2Character());
	printRow3(board2, [this](int j, int i) {return selectSinglePlayer2Board(j, i); });
	std::cout << game.getPlayer2Username() << std::endl;
}
void GameView::printGame(const Game& game) {
	system("cls");
	printPlayer1(game);
	std::cout << std::endl << std::endl;
	printPlayer2(game);
	std::cout << std::endl;
	std::cout << (game.getTurn() ? game.getPlayer2Username() : game.getPlayer1Username())
		<< "\'s turn." << std::endl;
	std::cout << "Rolled a " << game.getDie() << std::endl;
}
void GameView::startGame() {
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
				if (x == 3) {

				}
				else {
					selectPlace();
				}
				printGame(game);
			}
			catch (const std::runtime_error& ex) {}
		}
		Sleep(50);
	}
	printGame(game);
}