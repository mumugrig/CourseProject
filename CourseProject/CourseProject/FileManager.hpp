#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include "Serializable.hpp"

template <class IdType>
class FileManager {
	using Serializable = Serializable<IdType>;
	std::vector<Serializable*> set;
	std::ofstream fout;
	std::ifstream fin;
	std::string fileName;
protected:
	bool containsId(const Serializable& element) const;
	int find(const Serializable& element) const;
public:
	FileManager(const char* fileName);

	FileManager(const FileManager&) = delete;
	FileManager& operator=(const FileManager&) = delete;

	virtual void save();
	virtual void add(const Serializable& element);
	virtual Serializable* read(IdType id) = 0;
	virtual const Serializable* read(IdType id) const = 0;
	virtual const std::vector<Serializable*>& readAll() = 0;
	virtual void update(const Serializable& element) = 0;
	virtual void remove(const Serializable& element);

	virtual ~FileManager();
};


template<class IdType>
void FileManager<IdType>::remove(const Serializable& element)
{
	int index = find(element);
	if (index != -1) {
		std::swap(set[index], set[set.size - 1]);
		delete set[set.size - 1];
		set[set.size - 1] = nullptr;
		set.pop_back();
	}
	else {
		throw "element does not exist";
	}

}

template<class IdType>
FileManager<IdType>::~FileManager()
{
	for (Serializable* el : set) { delete el; }
}

template<class IdType>
bool FileManager<IdType>::containsId(const Serializable& element) const
{
	for (Serializable* el : set) {
		if (el->id == element.id) return true;
	}
	return false;
}

template<class IdType>
int FileManager<IdType>::find(const Serializable& element) const
{
	for (int i = 0; i < set.size; i++) {
		if (element.id == set[i].id) return i;
	}
	return -1;
}

template<class IdType>
FileManager<IdType>::FileManager(const char* fileName) : fileName(fileName)
{
}

template<class IdType>
void FileManager<IdType>::save()
{
	fout.open(fileName, std::ios::trunc | std::ios::out);
	for (Serializable* el : set) { el->serialize(fout); }
}

template<class IdType>
void FileManager<IdType>::add(const Serializable& element)
{
	if (!contains(element)) {
		set.push_back(element);
	}
	else {
		throw "id already exists";
	}
}
