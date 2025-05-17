#pragma once
#include <vector>
#include <functional>

static class VectorUtility {
public:
	//returns a filtered copy of the original vector
	template <class T>
	static std::vector<T> filter(const std::function<bool(const T&)>& f, const std::vector<T>& vector) {
		std::vector<T> result;
		for (const T& el : vector) {
			if (f(el)) result.push_back(el);
		}
		return result;
	}

	//returns first element that fulfills the condition otherwise throws
	template <class T>
	static const T& first(const std::function<bool(const T&)>& f, const std::vector<T> vector) {
		for (const T& el : vector) {
			if (f(el)) return el;
		}
		throw "does not exist";
	}

	//returns true if there is an element that fulfills the condition, otherwise returns false
	template <class T>
	static bool any(const std::function<bool(const T&)>& f, const std::vector<T>& vector) {
		for (const T& el : vector) {
			if (f(el)) return true;
		}
		return false;
	}

	template<class T, class U>
	static std::vector<U> map(const std::function<const U& (const T&)>& f,
							const std::vector<T>& vector) 
	{
		std::vector<U> result;
		for (const T& el : vector) {
			result.push_back(f(el));
		}
		return result;
	}

	//sorts the vector using the given condition instead of <
	//returns a reference to the original vector
	template <class T>
	static std::vector<T>& orderBy(const std::function<bool(const T&, const T&)>& f,
									std::vector<T>& vector) 
	{
		for (size_t i = 0; i < vector.size(); i++) {
			for (size_t j = 0; j < vector.size()-i-1; j++) {
				if (f(vector[j + 1], vector[j])) std::swap(vector[j + 1], vector[j]);
			}
		}
		return vector;
	}

	//sorts the vector using the given condition instead of >
	//returns a reference to the original vector
	template <class T>
	static std::vector<T>& orderByDescending(const std::function<bool(const T&, const T&)>& f,
		std::vector<T>& vector)
	{
		for (size_t i = 0; i < vector.size(); i++) {
			for (size_t j = 0; j < vector.size() - i - 1; j++) {
				if (f(vector[j], vector[j+1])) std::swap(vector[j + 1], vector[j]);
			}
		}
		return vector;
	}
};