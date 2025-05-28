#pragma once
#include <vector>

class Selection {
	std::vector<int> params;
	int n;
	
public:
	Selection();
	Selection(int selections);

	bool isReady() const;

	void push(int x, int y, bool board);

	const std::vector<int>& getParameters() const;
};