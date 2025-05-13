#pragma once
#include <string>
#include "Serializable.hpp"
class Player : public Serializable<unsigned int> {
	std::string username;
	unsigned int highScore;

	void serialize(std::ostream& out) const override;
	void deserialize(std::istream& in) override;
public:
	Player(unsigned int id, const std::string& username, unsigned int highScore);
	Player(const std::string& username);

	unsigned int getId() const;

	std::string& getUsername();
	const std::string& getUsername() const;

	void setUsername(const std::string& name);

	unsigned int getHighScore() const;
	void setHighScore();

	
};