#pragma once
#include <string>
#include "Storable.hpp"


class Player : public Storable<unsigned int> {
	std::string username;

	
	void setUsername(const std::string& name);
	Player* clone() const override;
	Player* cloneWithId(unsigned int id) const override;
public:
	Player(unsigned int id, const std::string& username);
	Player(const std::string& username);

	const std::string& getUsername() const;

	template<class T, class K>
	friend class FileManager;
};