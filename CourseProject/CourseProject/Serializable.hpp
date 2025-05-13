#pragma once
#include <iostream>
#include "FileManager.hpp"


template <class IdType>
class Serializable
{
protected:
	IdType id;
	Serializable(IdType id) : id(id) {}
	virtual void serialize(std::ostream& out) const = 0;
	virtual void deserialize(std::istream& in) = 0;
	template<class T, class U>
	friend class FileManager;
public:
	virtual Serializable* clone() const = 0;
	const IdType& getId() const { return id; };
};