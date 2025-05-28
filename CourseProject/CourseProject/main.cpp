#include "VectorUtility.hpp"
#include "GameView.hpp"

#if 1


void printLine() {
	std::cout << ("+---+---+---+") << std::endl;
}

void printRow1(const Game& game, const Board& gameBoard) {
	printLine();
	for (int j = 0; j < 3; j++) {
		std::cout << '|';
		std::cout << ' ';
		char c;
		if (gameBoard.getValue(j, 0) > 0)c = '0' + gameBoard.getValue(j, 0);
		else c = ' ';

		std::cout << c << ' ';
	}
	std::cout << '|' << std::endl;
}

 void printRow2(const Game& game, const Board& gameBoard, const Character& character) {
	std::cout << "+---+---+---+      " << character.color("++---++") << std::endl;
	for (int j = 0; j < 3; j++) {
		std::cout << '|';
		std::cout << ' ';
		char c;
		if (gameBoard.getValue(j, 1) > 0)c = '0' + gameBoard.getValue(j, 1);
		else c = ' ';

		std::cout << c << ' ';
		std::cout << hue::reset;
	}
	std::cout << "|      " << character.color("||");

	std::cout << ' ' << character.color(std::string(1, character.getSymbol())) << ' ';
	std::cout << character.color("||") << std::endl;
	std::cout << "+---+---+---+      " << character.color("++---++") << std::endl;
}

void printRow3(const Game& game, const Board& gameBoard) {
	for (int j = 0; j < 3; j++) {
		std::cout << '|';
		std::cout << ' ';
		char c;
		if (gameBoard.getValue(j, 2) > 0)c = '0' + gameBoard.getValue(j, 2);
		else c = ' ';

		std::cout << c << ' ';
	}
	std::cout << '|' << std::endl;
	printLine();
}

void printPlayer1(const Game& game)
{
	std::cout << game.getPlayer1Username() << std::endl;
	const Board& board1 = game.getPlayer1Board();

	printRow1(game, board1);
	printRow2(game, board1, game.getPlayer1Character());
	printRow3(game, board1);

	std::cout << game.getPlayer1Score() << std::endl;
}
void printPlayer2(const Game& game) {
	std::cout << game.getPlayer2Score() << std::endl;
	const Board board2 = game.getPlayer2Board();
	printRow1(game, board2);
	printRow2(game, board2, game.getPlayer2Character());
	printRow3(game, board2);
	std::cout << game.getPlayer2Username() << std::endl;
}
void printGame(const Game& game, const Player& player, bool withConclusion) {
	if (withConclusion) {
		if (game.getWinnerUsername() == "Draw") std::cout << dye::bright_white_on_grey("Draw") << std::endl;
		else if (game.getWinnerUsername() == player.getUsername()) std::cout << dye::bright_white_on_light_green("Victory") << std::endl;
		else std::cout << dye::bright_white_on_red("Defeat") << std::endl;
	}
	printPlayer1(game);
	std::cout << std::endl << std::endl;
	printPlayer2(game);
	std::cout << std::endl;
}


std::string inputUsername() {
	std::string username;
	std::cin >> username;
	while (username.length() > 50) {
		std::cout << "Username has to be <= 50 characters long" << std::endl;
		std::cin >> username;
	}
	std::cout << std::endl;
	return username;
}

void readPlayer(StorageSystem& files, Player& player, std::string username) {
	try {
		player = *(VectorUtility::first<Player*>([&username](Player* const& p) {return p->getUsername() == username; },
			files.players().readAll()));
	}
	catch (const std::invalid_argument& ex) {
		files.players().add(Player(username));
		files.players().save();
		player = *(VectorUtility::first<Player*>([&username](Player* const& p) {return p->getUsername() == username; },
			files.players().readAll()));
	}
}

void choosePlayers(StorageSystem& files, Player& player1, Player& player2) {
	std::cout << "Enter username for Player1: ";
	std::string username = inputUsername();
	readPlayer(files, player1, username);

	std::cout << "Enter username for Player2: ";
	username = inputUsername();
	readPlayer(files, player2, username);
}

void startGame(StorageSystem& files, Game& game) {
	GameView view(game, files);
	std::cout << "While in game use the arrow keys to move across the boards and shift to select.\n "
		<< "Press backspace to save the game and continue it later." << std::endl;
	system("pause");
	view.startGame();
	files.games().save();
	system("pause");
}

void gameLoop(StorageSystem& files, const Player& player1, const CharacterEnum& characterId1, const Player& player2, const CharacterEnum& characterId2) {

	files.games().add(Game(player1, characterId1, player2, characterId2));

	Game& game = *(VectorUtility::last<Game*>([&player1, &player2](Game* const& g){return g->getPlayer1Username() == player1.getUsername() && g->getPlayer2Username() == player2.getUsername(); },
		files.games().readAll()));

	startGame(files, game);
}


void characterSelect(CharacterEnum& characterId) {
	system("cls");
	std::cout << "Pick your character: " << std::endl;
	std::cout << "1. Ash" << std::endl;
	std::cout << "2. Felix" << std::endl;
	std::cout << "3. Columna" << std::endl;
	char input;
	std::cin >> input;
	while (input < '1' || input > '3') {
		std::cout << "invalid input" << std::endl;
		std::cin.ignore(INT_MAX, '\n');
		std::cin >> input;
	}
	characterId = (CharacterEnum)(input - '0' - 1);
}

void matchHistory(StorageSystem& files, const Player& player) {
	system("cls");
	char input = 0;
	std::vector<Game*> playerGames = VectorUtility::filter<Game*>(
		[&player](const Game* const& game)
		{
			return (game->getPlayer1Username() == player.getUsername() ||
			game->getPlayer2Username() == player.getUsername()) &&
			game->gameEnded(); 
		}, files.games().readAll());

	if (playerGames.empty()) {
		std::cout << "You havent played any games yet." << std::endl;
	}
	else {
		VectorUtility::orderBy<Game*>(
			[](const Game* const& game1, const Game* const& game2) 
			{
				return game1->getId() < game2->getId();
			}, playerGames);

		int counter = 0;
		int previousCounter = 1;
		while (input != '0') {
			if (counter != previousCounter) {
				previousCounter = counter;
				system("cls");
				for (int i = 4 * counter; i < 4 * (counter + 1) && i < playerGames.size(); i++) {
					std::cout << playerGames.size() - i << "----------------------------------------------" << std::endl;
					printGame(*playerGames[playerGames.size()-i-1], player, true);

					std::cout << std::endl;
				}
				std::cout << "Input \'n\' for next page, \'p\' for previous and 0 to exit" << std::endl;
			}
			
			std::cin >> input;
			std::cin.ignore(INT_MAX, '\n');
			switch (input) {
			case 'n': {
				if (counter <= playerGames.size() / 4) counter++;
					break;
			}
			case 'p': {
				if (counter > 0)counter--;
				break;
			}
			default: break;
			}
			
		}		
	}
}

void playerDetails(StorageSystem& files, const Player& player, CharacterEnum& characterId) {
	char input = 0;
	while (input != '0') {
		system("cls");
		std::cout << "1. Select Character" << std::endl;
		std::cout << "2. Match History" << std::endl;
		std::cout << "0. Back" << std::endl;

		std::cin >> input;
		while (input < '0' || input > '2') {
			std::cout << "invalid input" << std::endl;
			std::cin.ignore(INT_MAX, '\n');
			std::cin >> input;
		}
		switch (input) {
		case '1':characterSelect(characterId); break;
		case '2': matchHistory(files, player); break;
		default: break;
		}
	}
	
}

void loadGame(StorageSystem& files, const Player& player1, const Player& player2) {
	std::vector<Game*> savedGames = VectorUtility::filter<Game*>([&player1, &player2](const Game* const& game) {return (game->getPlayer1Username() == player1.getUsername() ||
		game->getPlayer2Username() == player2.getUsername()) && !game->gameEnded(); }, files.games().readAll());
	if (savedGames.empty()) {
		std::cout << "You dont have saved games." << std::endl;
	}
	else {
		VectorUtility::orderBy<Game*>([](const Game* const& game1, const Game* const& game2) {return game1->getId() < game2->getId(); }, savedGames);
		for (int i = savedGames.size()-1; i >= 0; i--) {
			std::cout << i + 1 << "----------------------------------------------" << std::endl;
			printGame(*savedGames[i], player1, false);

			std::cout << std::endl;
		}

	}
	int input;
	std::cout << "Choose game to load(0 to exit): " << std::endl;
	std::cin >> input;
	if (input == 0) return;
	else {
		startGame(files, *(savedGames[input - 1]));
	}
}

void mainMenu(StorageSystem& files, const Player& player1, CharacterEnum& characterId1, const Player& player2, CharacterEnum& characterId2) {
	char input = '1';
	while (input != '0') {
		system("cls");
		std::cout << "1. Start Game" << std::endl;
		std::cout << "2. Load Game" << std::endl;
		std::cout << "3. " << player1.getUsername() << " Details" << std::endl;
		std::cout << "4. " << player2.getUsername() << " Details" << std::endl;
		std::cout << "0. Exit" << std::endl;
		
		std::cin.sync();
		std::cin >> input;

		while (input < '0' || input > '4') {
			std::cout << "invalid input" << std::endl;
			std::cin.ignore(INT_MAX, '\n');
			std::cin >> input;
		}
		switch (input) {
		case '1':
			{
				gameLoop(files, player1, characterId1, player2, characterId2);
				break;
			}
		case '2': loadGame(files, player1, player2); break;
		case '3': playerDetails(files, player1, characterId1); break;
		case '4': playerDetails(files, player2, characterId2); break;
		}		
	}
	
}



int main() {
	StorageSystem files;
	Player player1("null");
	Player player2("null");
	CharacterEnum characterId1 = ASH;
	CharacterEnum characterId2 = ASH;

	choosePlayers(files, player1, player2);
	mainMenu(files, player1, characterId1, player2, characterId2);
	
	files.games().save();
}

#endif