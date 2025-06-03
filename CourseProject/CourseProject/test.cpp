#include <iostream>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "Libraries/doctest.h"
#include "Player.hpp"
#include "Board.hpp"
#include "Point.hpp"
#include "Game.hpp"
#include "FileManager.hpp"
#include "PlayerManager.hpp"
#include "GameManager.hpp"



class TestObject {
public:
    int id;
    std::string name;

    TestObject(int id, const std::string& name) : id(id), name(name) {}

    int getId() const { return id; }

    TestObject* clone() const {
        return new TestObject(id, name);
    }

    TestObject* cloneWithId(int newId) const {
        return new TestObject(newId, name);
    }

    bool operator==(const TestObject& other) const {
        return id == other.id && name == other.name;
    }
};

class TestFileManager : public FileManager<TestObject, int> {
public:
    using FileManager::FileManager;

    void serialize(const TestObject& element, std::ostream& out) override {
        out << element.id << " " << element.name << "\n";
    }

    TestObject* deserialize(std::istream& in) override {
        int id;
        std::string name;
        in >> id >> name;
        return new TestObject(id, name);
    }

    void save() override {
        std::ofstream out(fileName);
        for (auto el : data) {
            serialize(*el,out);
        }
    }
};

TEST_CASE("FileManager - Auto Increment Add and Read") {
    TestFileManager fm("dummy.txt");

    TestObject obj1(0, "Alpha");
    TestObject obj2(0, "Beta");

    fm.add(obj1);
    fm.add(obj2);

    CHECK(fm.read(1).name == "Alpha");
    CHECK(fm.read(2).name == "Beta");
}

TEST_CASE("FileManager - Manual Add and Duplicate ID Check") {
    TestFileManager fm("dummy.txt", false);

    TestObject obj1(10, "Gamma");
    fm.add(obj1);

    CHECK_THROWS(fm.add(obj1));
}

TEST_CASE("FileManager - Update Element") {
    TestFileManager fm("dummy.txt");

    TestObject original(0, "Initial");
    fm.add(original);

    TestObject updated(1, "Updated");
    fm.update(updated);

    CHECK(fm.read(1).name == "Updated");
}

TEST_CASE("FileManager - Remove Element") {
    TestFileManager fm("dummy.txt");

    TestObject obj(0, "ToRemove");
    fm.add(obj);

    TestObject ref(1, "");
    fm.remove(ref);

    CHECK_THROWS(fm.read(1));
}

TEST_CASE("FileManager - ReadAll") {
    TestFileManager fm("dummy.txt");

    fm.add(TestObject(0, "One"));
    fm.add(TestObject(0, "Two"));

    const auto& all = fm.readAll();
    CHECK(all.size() == 2);
    CHECK(all[0]->name == "One");
    CHECK(all[1]->name == "Two");
}

TEST_CASE("Player basic construction and access") {
    SUBCASE("Construct with ID and username") {
        Player p(42, "JohnDoe");
        CHECK(p.getId() == 42);
        CHECK(p.getUsername() == "JohnDoe");
    }

    SUBCASE("Construct with username only (default ID)") {
        Player p("player1");
        CHECK(p.getId() == 0);
        CHECK(p.getUsername() == "player1");
    }

    SUBCASE("Username too long throws") {
        std::string longName(51, 'a');
        CHECK_THROWS_AS(Player(1, longName), const char*);
    }
}

TEST_CASE("Board construction and default state") {
    Board b;

    SUBCASE("All cells initialized to 0") {
        for (int y = 0; y < 3; ++y)
            for (int x = 0; x < 3; ++x)
                CHECK(b.getValue(x, y) == 0);
    }

    SUBCASE("Board is initially not full") {
        CHECK(b.isFull() == false);
    }
}

TEST_CASE("Setting and clearing values") {
    Board b;

    SUBCASE("Set and get value at valid position") {
        b.setValue(1, 1, 4);
        CHECK(b.getValue(1, 1) == 4);
    }

    SUBCASE("Clearing a value sets it back to 0") {
        b.setValue(2, 2, 6);
        b.clearValue(2, 2);
        CHECK(b.getValue(2, 2) == 0);
    }

    SUBCASE("Set value throws for invalid position") {
        CHECK_THROWS_AS(b.setValue(3, 0, 3), std::runtime_error);
        CHECK_THROWS_AS(b.setValue(0, 3, 3), std::runtime_error);
    }

    SUBCASE("Set value throws for already occupied cell") {
        b.setValue(0, 0, 2);
        CHECK_THROWS_AS(b.setValue(0, 0, 4), std::runtime_error);
    }

    SUBCASE("Set value throws for invalid value") {
        CHECK_THROWS_AS(b.setValue(1, 1, 0), std::runtime_error);
        CHECK_THROWS_AS(b.setValue(1, 1, 7), std::runtime_error);
    }

    SUBCASE("Clear value throws if out of bounds") {
        CHECK_THROWS_AS(b.clearValue(-1, 0), std::runtime_error);
        CHECK_THROWS_AS(b.clearValue(0, 3), std::runtime_error);
    }
}

TEST_CASE("Position checks") {
    Board b;
    b.setValue(0, 0, 2);

    CHECK(Board::inBounds(2, 2));
    CHECK_FALSE(Board::inBounds(3, 0));

    CHECK(b.notOccupied(1, 1));
    CHECK_FALSE(b.notOccupied(0, 0));

    CHECK(b.validPosition(1, 1));
    CHECK_FALSE(b.validPosition(0, 0));
}

TEST_CASE("Full board check") {
    Board b;
    for (int y = 0; y < 3; ++y)
        for (int x = 0; x < 3; ++x)
            b.setValue(x, y, 1);

    CHECK(b.isFull());
}

TEST_CASE("Board scoring") {
    Board b;

    b.setValue(0, 0, 2);
    b.setValue(0, 1, 2);
    b.setValue(0, 2, 2);

    b.setValue(1, 0, 1);
    b.setValue(1, 1, 2);
    b.setValue(1, 2, 3);

    b.setValue(2, 0, 5);
    b.setValue(2, 1, 1);
    b.setValue(2, 2, 5);

    CHECK(b.score() == 18 + 6 + 21);
}

TEST_CASE("Board Serialization and Deserialization") {
    Board b;
    b.setValue(0, 0, 1);
    b.setValue(1, 1, 2);
    b.setValue(2, 2, 3);

    std::stringstream ss;
    b.serialize(ss);

    Board loaded;
    loaded.deserialize(ss);

    CHECK(loaded.getValue(0, 0) == 1);
    CHECK(loaded.getValue(1, 1) == 2);
    CHECK(loaded.getValue(2, 2) == 3);
    CHECK(loaded.getValue(0, 1) == 0);
}

TEST_CASE("Die default constructor") {
    Die d;
    CHECK(d.getValue() == 0);
}

TEST_CASE("Die rolling produces values between 1 and 6") {
    Die d;
    for (int i = 0; i < 100; ++i) {
        d.rollDie();
        int val = d.getValue();
        CHECK(val >= 1);
        CHECK(val <= 6);
    }
}

TEST_CASE("Die rollInBounds produces values in correct range") {
    Die d;

    SUBCASE("Roll between 2 and 5") {
        for (int i = 0; i < 100; ++i) {
            d.rollInBounds(2, 5);
            int val = d.getValue();
            CHECK(val >= 2);
            CHECK(val <= 5);
        }
    }

    SUBCASE("Roll single value range (e.g., 3 to 3)") {
        d.rollInBounds(3, 3);
        CHECK(d.getValue() == 3);
    }
}

TEST_CASE("Default constructor") {
    Selection s;
    CHECK(s.isReady());               
    CHECK(s.getParameters().empty());
}

TEST_CASE("Constructor with n selections") {
    Selection s(2);
    CHECK_FALSE(s.isReady());          
    CHECK(s.getParameters().empty());   
}

TEST_CASE("push() only accepts up to n points") {
    Selection s(2);
    Point p1{ 0, 0 ,0}, p2{ 1, 1,0 }, p3{ 2, 2,0 };

    s.push(p1);
    CHECK(s.getParameters().size() == 1);
    CHECK_FALSE(s.isReady());

    s.push(p2);
    CHECK(s.getParameters().size() == 2);
    CHECK(s.isReady());

    s.push(p3);
    CHECK(s.getParameters().size() == 2);
}

TEST_CASE("reset() restores point count and clears parameters") {
    Selection s(2);
    Point p1{ 0, 0 ,0}, p2{ 1, 1,0 };

    s.push(p1);
    s.push(p2);
    CHECK(s.isReady());
    CHECK(s.getParameters().size() == 2);

    s.reset();
    CHECK_FALSE(s.isReady());
    CHECK(s.getParameters().empty());

    s.push(p1);
    CHECK(s.getParameters().size() == 1);
}

TEST_CASE("Default constructor initializes to (0,0,false)") {
    Position pos;
    CHECK(pos.x() == 0);
    CHECK(pos.y() == 0);
    CHECK(pos.board() == false);
}

TEST_CASE("setBoard and board accessors") {
    Position pos;
    pos.setBoard(true);
    CHECK(pos.board() == true);
    pos.setBoard(false);
    CHECK(pos.board() == false);
}

TEST_CASE("Move up wraps from y=0 to y=2") {
    Position pos;
    pos.moveUp();  
    CHECK(pos.y() == 2);
    pos.moveUp();  
    CHECK(pos.y() == 1);
}

TEST_CASE("Move down wraps from y=2 to y=0") {
    Position pos;
    pos.moveUp();
    pos.moveDown();
    CHECK(pos.y() == 0);
    pos.moveDown(); 
    CHECK(pos.y() == 1);
}

TEST_CASE("Move left wraps from x=0 to x=3") {
    Position pos;
    pos.moveLeft();
    CHECK(pos.x() == 3);
    pos.moveLeft(); 
    CHECK(pos.x() == 2);
}

TEST_CASE("Move right wraps from x=3 to x=0") {
    Position pos;
    pos.moveLeft(); 
    pos.moveRight();
    CHECK(pos.x() == 0);
    pos.moveRight(); 
    CHECK(pos.x() == 1);
}

TEST_CASE("Selection conditions") {
    Position pos;
    pos.setBoard(false);
    pos.moveRight();
    pos.moveDown(); 
    CHECK(pos.player1SelectCondition(1, 1) == true);
    CHECK(pos.player2SelectCondition(1, 1) == false);

    pos.setBoard(true);
    CHECK(pos.player1SelectCondition(1, 1) == false);
    CHECK(pos.player2SelectCondition(1, 1) == true);
}

Game createSimpleGame() {
    Player p1("player1"), p2("player2");
    return Game(p1, CharacterEnum::FELIX, p2, CharacterEnum::FELIX);
}

TEST_CASE("Game initializes properly") {
    Player p1("player1"), p2("player2");
    Game game(p1, CharacterEnum::FELIX, p2, CharacterEnum::FELIX);

    CHECK(game.getPlayer1Username() == "player1");
    CHECK(game.getPlayer2Username() == "player2");
    CHECK(game.getPlayer1Score() == 0);
    CHECK(game.getPlayer2Score() == 0);
    CHECK(game.getTurn() == false);
    CHECK(game.getDieValue() >= 1);
    CHECK(game.getDieValue() <= 6);
}

TEST_CASE("Game places values and updates boards correctly") {
    Game game = createSimpleGame();
    int value = game.getDieValue();

    CHECK(game.getCurrentBoard().notOccupied(0, 0));

    game.place(0, 0);

    CHECK(game.getTurn() == true); 
    CHECK(game.getPlayer1Board().getValue(0, 0) == value);
}

TEST_CASE("Game scores update correctly") {
    Game game = createSimpleGame();
    game.place(0, 0); 
    int score1 = game.getPlayer1Score();
    CHECK(score1 > 0);

    game.place(1, 0); 
    int score2 = game.getPlayer2Score();
    CHECK(score2 > 0);
}

TEST_CASE("Game enemy board is updated after placement") {
    Game game = createSimpleGame();
    int value = game.getDieValue();

    game.place(1, 0); 

    for (int i = 0; i < 3; ++i) {
        CHECK(game.getPlayer2Board().getValue(1, i) != value);
    }
}
