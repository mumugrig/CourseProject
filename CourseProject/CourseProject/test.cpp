#include <iostream>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "Libraries/doctest.h"
#include "Player.hpp"
#include "Board.hpp"
#include "Game.hpp"
#include "FileManager.hpp"
#include "PlayerManager.hpp"
#include "GameManager.hpp"



TEST_CASE("TestManager") {
	std::ofstream out("test.txt");
	out.close();
	PlayerManager manager("test.txt", 1);
	CHECK(manager.readAll().empty());
	manager.add(Player("a"));
	CHECK_EQ(manager.readAll().size() , 1);
	CHECK_EQ(manager.read(1).getId(), 1);
	CHECK_EQ(manager.read(1).getUsername(), "a");
	manager.save();
	std::ifstream in("test.txt");
	Player a = manager.read(1);
	CHECK_EQ(a.getId(), 1);
	CHECK_EQ(a.getUsername(), "a");
	manager.add(Player("aaa"));
	CHECK_EQ(manager.read(2).getUsername(), "aaa");
	in.close();
	manager.save();
	in.open("test.txt");

	CHECK_THROWS(manager.add(a));
	CHECK_THROWS(manager.read(-1));
	manager.remove(a);
	CHECK_THROWS(manager.read(a.getId()));
	in.close();

}
TEST_CASE("FileManager auto_increment for int") {
	std::ofstream out("player.txt");
	out.close();

	PlayerManager playerManager("player.txt", 1);
	playerManager.add(Player("player1"));
	CHECK_EQ(playerManager.readAll()[0]->getId(), 1);
	playerManager.add(Player("player2"));
	CHECK_EQ(playerManager.readAll()[1]->getId(), 2);
	CHECK_EQ(playerManager.read(2).getUsername(), "player2");
}
TEST_CASE("Board") {
	Board b = Board();
	b.setValue(0, 0, 6);
	CHECK_EQ(b.score(), 6);
	b.setValue(0, 1, 6);
	CHECK_EQ(b.score(), 24);
	b.setValue(0, 2, 6);
	CHECK_EQ(b.score(), 54);
	std::ofstream out("board.txt");
	b.serialize(out);
	out.close();
	std::ifstream in("board.txt");
	Board c = Board();
	SUBCASE("Deserialization") {
		c.deserialize(in);
		in.close();
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				CHECK_EQ(b.getValue(i, j), c.getValue(i, j));
			}
		}
	}
	CHECK_THROWS(b.setValue(0, 1, 1));
	CHECK_THROWS(b.setValue(0, -1, 1));
	CHECK_THROWS(b.setValue(0, 1, 0));

}
TEST_CASE("Game") {
	std::ofstream out("games.txt");
	out.close();

	Player p1("player1");
	Player p2("player2");
	Game game(p1, p2);

	CHECK(game.getDie() <= 6 );
	CHECK(game.getDie() >= 1);

	game.place(0,0);
	
	CHECK(game.getPlayer1Score() >= 1);
	CHECK(game.getPlayer1Score() <= 6);

	game.place(1, 0);
	CHECK(game.getPlayer2Score() >= 1);
	CHECK(game.getPlayer2Score() <= 6);

	CHECK_THROWS(game.place(0, 0));

	PlayerManager playerManager("players.txt", 1);
	{
		GameManager gameManager("games.txt", 1, playerManager);
		playerManager.add(p1);
		playerManager.add(p2);
		playerManager.save();
		gameManager.add(game);
		gameManager.save();
	}
	GameManager gameManager("games.txt", 1, playerManager);
	Game game2 = gameManager.read(1);
	CHECK_EQ(game.getPlayer1Score(), game2.getPlayer1Score());
}
