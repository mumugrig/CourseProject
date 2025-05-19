#include <iostream>
#include "StorageSystem.hpp"
#include "VectorUtility.hpp"
#include <stdlib.h>
#if 1

void printLine() {
	std::cout << "-------------" << std::endl;
}

void printPlayer1(const Game& game) {
	std::cout << game.getPlayer1Username() << std::endl;
	printLine();
	const Board board1 = game.getPlayer1Board();
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			std::cout << "| " << board1.getValue(j, i) << ' ';
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
			std::cout << "| " << board2.getValue(j, i) << ' ';
		}
		std::cout << '|' << std::endl;
		printLine();
	}
	std::cout << game.getPlayer2Username() << std::endl;
}
void printGame(const Game& game) {
	printPlayer1(game);
	std::cout << std::endl << std::endl << std::endl;
	printPlayer2(game);
	std::cout << std::endl;
}

int main() {
	StorageSystem files;
	//std::cout << "Enter username for Player1: ";
	//std::string username;
	//std::cin >> username;
	//std::cout << std::endl;
	//while (VectorUtility::any<Player*>(
	//	[&username](Player* const& p) {return p->getUsername() == username; }, files.players().readAll())
	//	) {
	//	std::cout << "username already exists" << std::endl;
	//	std::cin >> username;
	//}
	
	std::ofstream out("players.txt");
	out.close();
	out.open("games.txt");
	out.close();

	files.players().add(Player("player1"));
	files.players().add(Player("player2"));
	Player p1 = files.players().read(1);
	Player p2 = files.players().read(2);

	files.games().add(Game(p1, ASH, p2, ASH));

	Game game = files.games().read(1);
	int x = -1, y = -1;
	char input = 0;
	while (!game.gameEnded()) {
		system("cls");
		printGame(game);
		std::cout << (game.getTurn() ? game.getPlayer2Username() : game.getPlayer1Username())
			<< "\'s turn." << std::endl;
		std::cout << "Rolled a " << game.getDie() << std::endl;
		if (game.getCurrentCharacter().getCooldown() == 0) {
			std::cout << "Do you want to use your ability(1) or place your die(2): ";
			std::cin >> input;
			std::cout << std::endl;
		}
		else { input = '2'; }
		while (input != '1' && input != '2') {
			std::cout << "Invalid input: expected 1 or 2" << std::endl;
			std::cin >> input;
			std::cout << std::endl;
		}
		if (input == '1') {
			std::cout << game.getCurrentCharacter().getMessage() << std::endl;
			game.readAndSetCharacterParameters(std::cin);
			game.useAbility();
		}
		else if (input == '2') {
			std::cout << "Enter position: ";
			std::cin >> x >> y;
			while (!(game.getCurrentBoard().validPosition(x, y))) {
				std::cout << "invalid position" << std::endl;
				std::cout << "Enter position: ";
				std::cin >> x >> y;
			}
			game.place(x, y);
		}
		
	}
}

#endif