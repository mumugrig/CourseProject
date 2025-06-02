#pragma once
#include <iostream>
#include <fstream>
#include <vector>

/**
 * @brief A generic file manager for storing, loading, and manipulating persistent objects.
 *
 * @tparam T The type of object being stored. Must implement clone(), cloneWithId(IdType), getId(), and have an `id` member.
 * @tparam IdType The type used for unique identifiers (e.g., int, unsigned int).
 *
 * Note: T must be derived from a `Storable<IdType>`-like interface with a getId() method and clone methods.
 */
template <class T, class IdType>
class FileManager {
protected:
	/**
	 * @brief Serializes an element to the given output stream.
	 * @param element The element to serialize.
	 * @param out The output stream to write to.
	 */
	virtual void serialize(const T& element, std::ostream& out) = 0;
	/**
	 * @brief Deserializes an element from the given input stream.
	 * @param in The input stream to read from.
	 * @return A dynamically allocated object of type T.
	 */
	virtual T* deserialize(std::istream& in) = 0;
	/// Stores all loaded objects.
	std::vector<T*> data;
	
	/// The file name associated with this manager.
	std::string fileName;

	/// Tracks the largest used ID for auto-incrementing.
	IdType* largestId = nullptr;
	/// Whether to automatically assign IDs when adding new elements.
	bool auto_inc;
	
	/**
	 * @brief Checks if an element with the same ID already exists.
	 * @param element The element whose ID to check.
	 * @return True if ID is already taken, false otherwise.
	 */
	bool containsId(const T& element) const;
	/**
	 * @brief Finds the index of an element by ID.
	 * @param element The element to locate.
	 * @return The index if found, -1 otherwise.
	 */
	int find(const T& element) const;
	/**
	 * @brief Checks if the input stream is in a valid state for reading.
	 * @param in The stream to validate.
	 * @return True if the stream is valid, false otherwise.
	 */
	bool validFile(std::istream& in);
	/**
	 * @brief Generates the next available ID.
	 * @return The next ID value.
	 */
	virtual IdType auto_increment();
public:
	/**
	* @brief Constructs a FileManager with an optional auto-increment flag.
	* @param fileName The file to associate with.
	* @param auto_inc If true, enables ID auto-increment (default is true).
	*/
	FileManager(const char* fileName , bool auto_inc);
	/**
	 * @brief Constructs a FileManager with auto-increment enabled.
	 * @param fileName The file to associate with.
	 */
	FileManager(const char* fileName);

	FileManager(const FileManager&) = delete;
	FileManager& operator=(const FileManager&) = delete;
	/**
	* @brief Saves all data to file.
	*/
	virtual void save() = 0;
	/**
	* @brief Adds an element to the file manager.
	* @param element The element to add.
	* @throws If auto-increment is disabled and the ID already exists.
	*/
	virtual void add(const T& element);
	/**
	 * @brief Reads an element by ID.
	 * @param id The ID to search for.
	 * @return A reference to the found element.
	 * @throws If ID is not found.
	 */
	T& read(IdType id);
	/**
	 * @brief Reads an element by ID (const version).
	 * @param id The ID to search for.
	 * @return A const reference to the found element.
	 * @throws If ID is not found.
	 */
	const T& read(IdType id) const;
	/**
	 * @brief Returns a read-only reference to the internal data vector.
	 * @return A const reference to all stored objects.
	 */
	const std::vector<T*>& readAll() const;
	/**
	 * @brief Updates an existing element by ID.
	 * @param element The new element data (must match ID).
	 * @throws If no element with matching ID exists.
	 */
	void update(const T& element);
	/**
	 * @brief Removes an element by ID.
	 * @param element The element to remove.
	 * @throws If the element does not exist.
	 */
	void remove(const T& element);
	/**
	 * @brief Destructor. Frees all dynamically allocated objects.
	 */
	~FileManager();
};


template<class T, class IdType>
void FileManager<T, IdType>::remove(const T& element) 
{
	int index = find(element);
	if (index != -1) {
		std::swap(data[index], data[data.size() - 1]);
		delete data[data.size() - 1];
		data[data.size() - 1] = nullptr;
		data.pop_back();
	}
	else {
		throw "element does not exist";
	}

}

template<class T, class IdType>
FileManager<T, IdType>::~FileManager()
{
	delete largestId;
	for (T* el : data) { delete el; }
}

template<class T, class IdType>
bool FileManager<T, IdType>::containsId(const T& element) const
{
	for (T* el : data) {
		if (el->id == element.id) return true;
	}
	return false;
}

template<class T, class IdType>
int FileManager<T, IdType>::find(const T& element) const
{
	for (int i = 0; i < data.size(); i++) {
		if (element.id == data[i]->id) return i;
	}
	return -1;
}

template<class T, class IdType>
inline bool FileManager<T, IdType>::validFile(std::istream& in)
{
	return in.peek() != '0' && in.peek() != -1 && in.peek() != 0 && in.peek() != '\n';
}

template<class T, class IdType>
IdType FileManager<T, IdType>::auto_increment()
{
	if (largestId == nullptr) {
		largestId = new IdType(0);
		for (T* el : data) {
			if (el->getId() > *largestId) *largestId = el->getId();
		}
	}
	++(*largestId);
	return *largestId;
}

template<class T, class IdType>
FileManager<T, IdType>::FileManager(const char* fileName, bool auto_inc) 
	: fileName(fileName), auto_inc(auto_inc)
{
}

template<class T, class IdType>
FileManager<T, IdType>::FileManager(const char* fileName) : fileName(fileName), auto_inc(true)
{
}


template<class T, class IdType>
void FileManager<T, IdType>::add(const T& element)
{
	if (auto_inc) {
		data.push_back(element.cloneWithId(auto_increment()));
	}
	else {
		if (!containsId(element)) {
			data.push_back(element.clone());
		}
		else {
			throw "id alredy exists";
		}
	}
	
}

template<class T, class IdType>
T& FileManager<T, IdType>::read(IdType id)
{
	for (T* el : data) {
		if (el->getId() == id) return *el;
	}
	throw "invalid id";
}

template<class T, class IdType>
const T& FileManager<T, IdType>::read(IdType id) const
{
	for (T* el : data) {
		if (el->getId() == id) return *el;
	}
	throw "invalid id";
}

template<class T, class IdType>
const std::vector<T*>& FileManager<T, IdType>::readAll() const
{
	return data;
}

template<class T, class IdType>
void FileManager<T, IdType>::update(const T& element)
{
	int index = find(element);
	if (index == -1) throw "invalid id";
	delete data[index];
	data[index] = element.clone();
}
