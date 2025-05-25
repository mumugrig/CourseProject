#pragma once
#include <vector>

class Selection {
	std::vector<int> params;
	int n;
	
public:
	Selection() : n(0) {}
	Selection(int selections) : n(selections) {}

	bool isReady() const {
		return n == 0;
	}

	void push(int x, int y, bool board) {
		if (n!=0) {
			params.push_back(x);
			params.push_back(y);
			params.push_back(board);
			n--;
		}
	}

	const std::vector<int>& getParameters() const { return params; }

};