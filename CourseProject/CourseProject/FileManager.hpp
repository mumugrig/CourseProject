#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include "Serializable.hpp"


//T has to be derived from Storable<IdType>
template <class T, class IdType>
class FileManager {
	std::vector<T*> data;
	std::string fileName;
	bool auto_inc;
	IdType* largestId = nullptr;
	bool containsId(const T& element) const;
	int find(const T& element) const;
	virtual IdType auto_increment();
public:
	FileManager(const char* fileName , bool auto_inc);
	FileManager(const char* fileName);

	FileManager(const FileManager&) = delete;
	FileManager& operator=(const FileManager&) = delete;

	void save();
	void add(const T& element);
	T& read(IdType id);
	const T& read(IdType id) const;
	const std::vector<T*>& readAll() const;
	void update(const T& element);
	void remove(const T& element);

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
	save();
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
	std::ifstream fin(fileName);
	fin.ignore();
	while (fin.good()) {
		data.push_back(new T(fin));
	}
	fin.close();
}

template<class T, class IdType>
FileManager<T, IdType>::FileManager(const char* fileName) : fileName(fileName), auto_inc(false)
{
	std::ifstream fin(fileName);
	fin.ignore();
	while (fin.good()) {
		data.push_back(new T(fin));
	}
	fin.close();
}


template<class T, class IdType>
void FileManager<T, IdType>::save()
{
	std::ofstream fout(fileName, std::ios::trunc | std::ios::out);
	for (T* el : data) { el->serialize(fout); }
	fout.close();
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
			throw "id already exists";
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
