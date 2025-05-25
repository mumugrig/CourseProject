#include "VectorUtility.hpp"
#include "GameView.hpp"

#if 1


void choosePlayers(StorageSystem& files, Player& player1, Player& player2) {
	std::cout << "Enter username for Player1: ";
	std::string username;
	std::cin >> username;
	std::cout << std::endl;
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

void gameplayLoop(StorageSystem& files, const Player& player1, const Player& player2) {
	files.games().add(Game(player1, ASH, player2, FELIX));

	Game& game = files.games().read(1);

	GameView view(game, files);
	view.startGame();
}


int main() {

	StorageSystem files;
	Player player1("null");
	Player player2("null");

	choosePlayers(files, player1, player2);

	gameplayLoop(files, player1, player2);
	files.games().save();
}

#endif