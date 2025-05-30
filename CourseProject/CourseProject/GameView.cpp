#include "GameView.hpp"

inline bool GameView::keyPressed(char key) {
	if (GetKeyState(key) & 0x8000)
	{
		return true;
	}
	return false;
}


GameView::GameView(Game& game, StorageSystem& storage) :
	game(game), storage(storage), position(new Position()), usingAbility1(false), usingAbility2(false) 
{
	position->setBoard(game.getTurn());
}

GameView::~GameView()
{
	delete position;
}

inline const Game& GameView::getGame() { return game; }

inline void GameView::selectPlace() {
	game.place(position->x(), position->y());
	position->setBoard(game.getTurn());
}

inline void GameView::printLine() {
	std::cout << ("+---+---+---+") << std::endl;
}

inline void GameView::printRow1(const Game& game, const Board& gameBoard, const std::function<bool(int, int)>& selectCondition) {
	printLine();
	for (int j = 0; j < 3; j++) {
		std::cout << '|';
		if (selectCondition(j, 0)) game.getCurrentCharacter().selectionColor(std::cout);
		std::cout << ' ';
		char c;
		if (gameBoard.getValue(j, 0) > 0)c = '0' + gameBoard.getValue(j, 0);
		else c = ' ';

		std::cout << c << ' ';
		std::cout << hue::reset;
	}
	std::cout << '|' << std::endl;
}

inline void GameView::printRow2(const Game& game, const Board& gameBoard, const std::function<bool(int, int)>& selectCondition, const Character& character, bool usingAbility) {
	std::cout << "+---+---+---+      " << character.color("++---++") << std::endl;
	for (int j = 0; j < 3; j++) {
		std::cout << '|';
		if (selectCondition(j, 1)) game.getCurrentCharacter().selectionColor(std::cout);
		std::cout << ' ';
		char c;
		if (gameBoard.getValue(j, 1) > 0) c = '0' + gameBoard.getValue(j, 1);
		else c = ' ';

		std::cout << c << ' ';
		std::cout << hue::reset;
	}
	std::cout << "|      " << character.color("||");
	if ((selectCondition(3, 0) || selectCondition(3, 1) || selectCondition(3, 2))) {
		game.getCurrentCharacter().selectionColor(std::cout);
		std::cout << ' ' << (usingAbility ? 'O' : character.getSymbol()) << ' ';
	}
	else std::cout << ' ' << character.color(std::string(1, (usingAbility ? 'O' : character.getSymbol()))) << ' ';
	std::cout << hue::reset << character.color("||") << std::endl;
	std::cout << "+---+---+---+      " << character.color("++---++") << std::endl;
}

inline void GameView::printRow3(const Game& game, const Board& gameBoard, const std::function<bool(int, int)>& selectCondition) {
	for (int j = 0; j < 3; j++) {
		std::cout << '|';
		if (selectCondition(j, 2)) game.getCurrentCharacter().selectionColor(std::cout);
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

	printRow1(game, board1, [this](int j, int i) {return position->player1SelectCondition(j, i); });
	printRow2(game, board1, [this](int j, int i) {return position->player1SelectCondition(j, i); }, game.getPlayer1Character(), usingAbility1);
	printRow3(game, board1, [this](int j, int i) {return position->player1SelectCondition(j, i); });

	std::cout << game.getPlayer1Score() << std::endl;
}
void GameView::printPlayer2(const Game& game) {
	std::cout << game.getPlayer2Score() << std::endl;
	const Board board2 = game.getPlayer2Board();
	printRow1(game, board2, [this](int j, int i) {return position->player2SelectCondition(j, i); });
	printRow2(game, board2, [this](int j, int i) {return position->player2SelectCondition(j, i); }, game.getPlayer2Character(), usingAbility2);
	printRow3(game, board2, [this](int j, int i) {return position->player2SelectCondition(j, i); });
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
	std::cout << "Rolled a " << game.getDieValue() << std::endl;
}
void GameView::startGame() {
	printGame(game);
	while (!game.gameEnded()) {
		if (keyPressed(VK_LEFT)) {
			position->moveLeft();
			printGame(game);
		}
		if (keyPressed(VK_UP)) {
			position->moveUp();
			printGame(game);
		}
		if (keyPressed(VK_RIGHT)) {
			position->moveRight();
			printGame(game);
		}
		if (keyPressed(VK_DOWN)) {
			position->moveDown();
			printGame(game);
		}
		if (keyPressed(VK_BACK)) {
			storage.games().save();
			std::cout << "Game has been saved." << std::endl;
			return;
		}
		if (keyPressed(VK_SHIFT)) {
			try {
				if (position->x() == 3 && !game.getCurrentCharacter().onCooldown() && !usingAbility()) {		
					Position* newPosition = game.getCurrentCharacter().moveType(position);
					delete position;
					position = newPosition;
					usingAbility() = true;
				}
				else if (usingAbility() && !game.getCurrentCharacter().selection.isReady()) {
					game.pushCharacterParameters(position->x(), position->y(), position->board());
				}	
				else {
					selectPlace();
				}
				printGame(game);
				Sleep(100);
			}
			catch (const std::runtime_error& ex) {}
		}
		if (usingAbility() && game.getCurrentCharacter().selection.isReady()) {
			try {
				
				game.useAbility();
				Position* newPosition = new Position(*position);
				delete position;
				position = newPosition;
				position->setBoard(game.getTurn());
				usingAbility() = false;
			}
			catch (const std::invalid_argument& ex) {
				//std::cout << ex.what() << std::endl;
				game.resetCharacterParameters();
				
			}
			printGame(game);
		}
		Sleep(50);
	}
	printGame(game);
	std::cout << game.getWinnerUsername() << " won the game!" << std::endl;
}