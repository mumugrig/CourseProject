/**
 * @file Selection.hpp
 * @brief Represents a selection of points with a fixed capacity.
 */
#pragma once
#include <vector>
#include "Point.hpp"
/**
 * @class Selection
 * @brief Manages a collection of selected points with a limited number of selections allowed.
 */
class Selection {
	/// Container for selected points
	std::vector<Point> params;
	/// Number of selections remaining to be made
	int n;
	
public:
	/**
	 * @brief Default constructor initializes with zero selections allowed.
	 */
	Selection();
	/**
	* @brief Constructs a Selection allowing a specified number of selections.
	* @param selections Number of points allowed to be selected.
	*/
	Selection(int selections);
	/**
	* @brief Checks if the selection is complete (no remaining selections).
	* @return True if selection is complete, false otherwise.
	*/
	bool isReady() const;
	/**
	* @brief Adds a point to the selection if capacity allows.
	* Decrements remaining selection count.
	* @param point The point to add.
	*/
	void push(const Point& point);
	/**
   * @brief Clears the selection and resets the number of allowed selections to previous count.
   */
	void reset();
	/**
	* @brief Returns a const reference to the current selected points.
	* @return Const reference to vector of points.
	*/
	const std::vector<Point>& getParameters() const;
};