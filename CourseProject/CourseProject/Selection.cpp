#include "Selection.hpp"

Selection::Selection() : n(0) {}

Selection::Selection(int selections) : n(selections) {}

bool Selection::isReady() const {
	return n == 0;
}

void Selection::push(int x, int y, bool board) {
	if (n != 0) {
		params.push_back(x);
		params.push_back(y);
		params.push_back(board);
		n--;
	}
}

void Selection::reset()
{
	n = params.size() / 3;
	params.clear();
}

const std::vector<int>& Selection::getParameters() const { return params; }
