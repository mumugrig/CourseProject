#pragma once
#include <vector>
#include "Point.hpp"

class Selection {
	std::vector<Point> params;
	int n;
	
public:
	Selection();
	Selection(int selections);

	bool isReady() const;

	void push(const Point& point);

	void reset();

	const std::vector<Point>& getParameters() const;
};