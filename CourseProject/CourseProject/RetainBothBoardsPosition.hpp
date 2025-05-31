#pragma once
#include "BothBoardsPosition.hpp"
#include "Selection.hpp"
#include "VectorUtility.hpp"

class RetainBothBoardsPosition : public BothBoardsPosition {
	
	const Selection& selection;

public:

	RetainBothBoardsPosition(Selection& selection);

	RetainBothBoardsPosition(const Position& other, const Selection& selection);

	bool player1SelectCondition(int x, int y) override;

	bool player2SelectCondition(int x, int y) override;
};