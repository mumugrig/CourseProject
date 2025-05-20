#include "Player.hpp"


Player::Player(unsigned int id, const std::string& username, unsigned int highScore) :
    Storable(id), highScore(highScore)
{
    setUsername(username);
}

Player::Player(const std::string& username) : Storable(0), username(username), highScore(0)
{
}

const std::string& Player::getUsername() const
{
    return username;
}

void Player::setUsername(const std::string& name)
{
    if (name.size() <= 50) username = name;
    else throw "name has to be <= 50 characters";
}

Player* Player::clone() const {
    return new Player(*this);
}

Player* Player::cloneWithId(unsigned int id) const
{
    return new Player(id, this->username, this->highScore);
}

unsigned int Player::getHighScore() const
{
    return highScore;
}

void Player::setHighScore(unsigned int highScore)
{
    this->highScore = highScore;
}

