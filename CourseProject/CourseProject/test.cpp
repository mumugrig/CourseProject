#include <iostream>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "FileManager.hpp"
#include "Player.hpp"
#include "Board.hpp"
class TestClass : public Storable<int> {
	
public:
	std::string str;
	void serialize(std::ostream& out) const override {
		if (out.good()) {
			out << id << '\n';
			out << str << '\n';
		}	
	}
	void deserialize(std::istream& in) override {

		in >> id >> str;
	}

	TestClass(int id, const std::string& str) : Storable(id), str(str) {}
	TestClass(std::ifstream& in) : Storable(0) { deserialize(in); }
	TestClass* clone() const override {
		return new TestClass(*this);
	}

	TestClass* cloneWithId(int id) const override {
		return new TestClass(id, this->str);
	}
};


TEST_CASE("TestClass serialize and deserialize") {
	TestClass a = { 1, "abcabc" };
	std::ofstream out("file.txt");
	a.serialize(out);
	out.close();
	TestClass b = { 0, "aaaaa"};
	std::ifstream in("file.txt");
	b.deserialize(in);
	CHECK(a.getId() == b.getId());
	CHECK(a.str == b.str);
}
TEST_CASE("TestManager") {
	std::ofstream out("test.txt");
	out.close();
	FileManager<TestClass, int> manager("test.txt");
	CHECK(manager.readAll().empty());
	manager.add(TestClass(1, "a"));
	CHECK_EQ(manager.readAll().size() , 1);
	CHECK_EQ(manager.read(1).getId(), 1);
	CHECK_EQ(manager.read(1).str, "a");
	manager.save();
	std::ifstream in("test.txt");
	TestClass a(in);
	CHECK_EQ(a.getId(), 1);
	CHECK_EQ(a.str, "a");
	a.str = "abc";
	manager.update(a);
	CHECK_EQ(manager.read(a.getId()).str, "abc");
	manager.add(TestClass(2, "aaa"));
	CHECK_EQ(manager.read(2).str, "aaa");
	in.close();
	manager.save();
	in.open("test.txt");
	a.deserialize(in);
	a.deserialize(in);
	CHECK_EQ(a.str, "aaa");
	CHECK_THROWS(manager.add(a));
	CHECK_THROWS(manager.read(-1));
	manager.remove(a);
	CHECK_THROWS(manager.read(a.getId()));
	in.close();

}
TEST_CASE("FileManager auto_increment for int") {
	std::ofstream out("player.txt");
	out.close();

	FileManager<Player, unsigned int> playerManager("player.txt", 1);
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
}

