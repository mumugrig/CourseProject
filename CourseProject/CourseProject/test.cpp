#include <iostream>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "FileManager.hpp"


class TestClass : public Serializable<int> {
	
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

	TestClass(int id, const std::string& str) : Serializable(id), str(str) {}
	TestClass(std::ifstream& in) : Serializable(0) { deserialize(in); }
	TestClass* clone() const override {
		return new TestClass(*this);
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
	std::ofstream out("test.txt");
	out.close();
}


