#pragma once
#include "Player.hpp"

class Game : public Serializable<unsigned int> {
	Player& Player1;
	Player& Player2;
	bool turn;
	//matrix board;

	void passTurn();
	void serialize(std::ostream& out) const override;

public:
	Game(const Player& p1, const Player& p2);
	Game(const Player& p1, const Player& p2, bool turn);

	void save() const;
	void load();

	bool gameEnded();

};