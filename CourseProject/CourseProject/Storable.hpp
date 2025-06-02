#pragma once
#include <iostream>
#include "FileManager.hpp"


/**
 * @brief An abstract base class for objects that can be stored and managed by FileManager.
 *
 * @tparam IdType The type of the unique identifier.
 */
template <class IdType>
class Storable
{
protected:
	/// Unique identifier for the object.
	IdType id;
	/**
	 * @brief Constructs a Storable object with a specific ID.
	 * @param id The unique identifier to assign.
	 */
	Storable(IdType id) : id(id) {}
	/**
	 * @brief Creates a deep copy of the object.
	 * @return A dynamically allocated clone of the object.
	 */
	virtual Storable* clone() const = 0;
	/**
	 * @brief Creates a deep copy of the object with a new ID.
	 * @param id The new ID to assign to the cloned object.
	 * @return A dynamically allocated clone with the specified ID.
	 */
	virtual Storable* cloneWithId(IdType id) const = 0;
	/**
	* @brief Grant FileManager access to protected members.
	*/
	template<class T, class U>
	friend class FileManager;
	/// Virtual destructor.
	virtual ~Storable() {}
public:
	/**
	 * @brief Returns the ID of the object.
	 * @return A const reference to the ID.
	 */
	const IdType& getId() const { return id; };
};