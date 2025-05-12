#pragma once
#include <iostream>

template <class IdType>
class Serializable
{
protected:
	IdType id;
	virtual void serialize(std::ostream& out) const = 0;
};