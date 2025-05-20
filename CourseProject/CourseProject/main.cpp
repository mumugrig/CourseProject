#include <iostream>
#include "StorageSystem.hpp"
#include "VectorUtility.hpp"
#include "Renderer.hpp"
#include "GameView.hpp"

#if 1


void choosePlayers(StorageSystem& files) {
	std::cout << "Enter username for Player1: ";
	std::string username;
	std::cin >> username;
	std::cout << std::endl;
	Player player1("null");
	try {
		player1 = *(VectorUtility::first<Player*>([&username](Player* const& p) {return p->getUsername() == username; },
			files.players().readAll()));
	}
	catch (const std::invalid_argument& ex) {
		files.players().add(Player(username));
		files.players().save();
		player1 = *(VectorUtility::first<Player*>([&username](Player* const& p) {return p->getUsername() == username; },
			files.players().readAll()));
	}

	std::cout << "Enter username for Player2: ";
	std::cin >> username;
	std::cout << std::endl;
	Player player2("null");
	try {
		player2 = *(VectorUtility::first<Player*>([&username](Player* const& p) {return p->getUsername() == username; },
			files.players().readAll()));
	}
	catch (const std::invalid_argument& ex) {
		files.players().add(Player(username));
		files.players().save();
		player2 = *(VectorUtility::first<Player*>([&username](Player* const& p) {return p->getUsername() == username; },
			files.players().readAll()));
	}
}
void gameplayLoop(StorageSystem& files) {
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
		//printGame(game);
		std::cout << (game.getTurn() ? game.getPlayer2Username() : game.getPlayer1Username())
			<< "\'s turn." << std::endl;
		std::cout << "Rolled a " << game.getDie() << std::endl;
		if (game.getCurrentCharacter().getCooldown() == 0) {
			std::cout << "Do you want to use your ability(1) or place your die(2): ";
			std::cin >> input;
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
	//printGame(game);
}//doesnt work
void gameplayLoop2(StorageSystem& files) {
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

	GameView view(game, files);
	view.startGame();
}


int main() {
	//std::cout.sync_with_stdio(false);
	//std::cin.tie(nullptr);
	StorageSystem files;
	
	gameplayLoop2(files);

	

	//std::cout << hue::black_on_light_yellow;
	//gameplayLoop(files);
	
	
}

#endif