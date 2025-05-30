#pragma once
#include <iostream>
#include "FileManager.hpp"
#include "Serializable.hpp"

template <class IdType>
class Storable
{
protected:
	IdType id;
	Storable(IdType id) : id(id) {}
	virtual Storable* clone() const = 0;
	virtual Storable* cloneWithId(IdType id) const = 0;
	template<class T, class U>
	friend class FileManager;
	virtual ~Storable() {}
public:
	
	const IdType& getId() const { return id; };
};