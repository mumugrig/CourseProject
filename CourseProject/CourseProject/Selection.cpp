#include "Selection.hpp"

Selection::Selection() : n(0) {}

Selection::Selection(int selections) : n(selections) {}

bool Selection::isReady() const {
	return n == 0;
}

void Selection::push(const Point& point) {
	if (n != 0) {
		params.push_back(point);
		n--;
	}
}

void Selection::reset()
{
	n = params.size();
	params.clear();
}

const std::vector<Point>& Selection::getParameters() const { return params; }
