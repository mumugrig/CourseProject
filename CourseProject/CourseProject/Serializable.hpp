#pragma once
#include <iostream>

class Serializable {
	virtual void serialize(std::ostream& out) const = 0;
	virtual void deserialize(std::istream& in) = 0;
};