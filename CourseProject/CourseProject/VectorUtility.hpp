#pragma once
#include <vector>
#include <functional>
#include <stdexcept>
/**
 * @brief Utility class providing common operations on std::vector using functional predicates.
 */
class VectorUtility {
public:
	/**
	 * @brief Returns a filtered copy of the original vector based on the provided predicate.
	 *
	 * @tparam T The type of elements stored in the vector.
	 * @param f A function or lambda returning true for elements to keep.
	 * @param vector The vector to filter.
	 * @return std::vector<T> A new vector containing elements for which f(element) is true.
	 */
	template <class T>
	static std::vector<T> filter(const std::function<bool(const T&)>& f, const std::vector<T>& vector) {
		std::vector<T> result;
		for (const T& el : vector) {
			if (f(el)) result.push_back(el);
		}
		return result;
	}

	/**
	 * @brief Returns the first element that satisfies the predicate.
	 *
	 * @tparam T The type of elements stored in the vector.
	 * @param f A function or lambda returning true for the desired element.
	 * @param vector The vector to search.
	 * @return const T The first element for which f(element) is true.
	 * @throws std::invalid_argument if no element satisfies the predicate.
	 */
	template <class T>
	static const T first(const std::function<bool(const T&)>& f, const std::vector<T>& vector) {
		for (const T& el : vector) {
			if (f(el)) return el;
		}
		throw std::invalid_argument("does not exist");
	}
	/**
	 * @brief Returns the last element that satisfies the predicate.
	 *
	 * @tparam T The type of elements stored in the vector.
	 * @param f A function or lambda returning true for the desired element.
	 * @param vector The vector to search.
	 * @return const T The last element for which f(element) is true.
	 * @throws std::invalid_argument if no element satisfies the predicate.
	 */
	template<class T>
	static const T last(const std::function<bool(const T&)>& f, const std::vector<T>& vector) {
		for (auto i = vector.rbegin(); i != vector.rend(); i++) {
			if (f(*i)) return *i;
		}
		throw std::invalid_argument("does not exist");
	}

	/**
	 * @brief Checks if any element in the vector satisfies the predicate.
	 *
	 * @tparam T The type of elements stored in the vector.
	 * @param f A function or lambda returning true for the desired element.
	 * @param vector The vector to check.
	 * @return true if at least one element satisfies the predicate.
	 * @return false if no element satisfies the predicate.
	 */
	template <class T>
	static bool any(const std::function<bool(const T&)>& f, const std::vector<T>& vector) {
		for (const T& el : vector) {
			if (f(el)) return true;
		}
		return false;
	}
	/**
 * @brief Transforms each element in the input vector to another type using a function and returns a new vector.
 *
 * @tparam T The type of elements stored in the input vector.
 * @tparam U The type of elements stored in the output vector.
 * @param f A function or lambda to transform elements of type T to type U.
 * @param vector The input vector to transform.
 * @return std::vector<U> A new vector containing the transformed elements.
 */
	template<class T, class U>
	static std::vector<U> map(const std::function<U(const T&)>& f,
							const std::vector<T>& vector) 
	{
		std::vector<U> result;
		for (const T& el : vector) {
			result.push_back(f(el));
		}
		return result;
	}

	/**
	 * @brief Sorts the given vector in place using a custom comparison function.
	 *
	 * Uses a bubble sort algorithm to reorder elements so that the comparator f(a, b) returns true when a should come before b.
	 *
	 * @tparam T The type of elements stored in the vector.
	 * @param f A comparator function or lambda that returns true if the first argument should precede the second.
	 * @param vector The vector to be sorted.
	 * @return std::vector<T>& A reference to the sorted vector.
	 */
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
};