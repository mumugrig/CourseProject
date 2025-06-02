/**
 * @file Position.hpp
 * @brief Defines the Position class representing a position on a board with movement capabilities.
 */
#pragma once
#include "Point.hpp"

 /**
  * @class Position
  * @brief Represents a position on a board encapsulating a Point with movement and selection logic.
  */
class Position {
protected:
	Point point; ///< The point representing the position coordinates and board indicator.
public:
	/**
	* @brief Default constructor initializes position to (0,0) on board 0.
	*/
	Position(); 
	/**
	* @brief Gets the X-coordinate of the position.
	* @return The X-coordinate.
	*/
	int x() const;
	/**
	 * @brief Gets the Y-coordinate of the position.
	 * @return The Y-coordinate.
	 */
	int y() const;
	/**
	 * @brief Gets the board indicator of the position.
	 * @return True if the position is on board 1, false otherwise.
	 */
	bool board() const;
	/**
   * @brief Sets the board indicator for the position.
   * @param value The new board indicator.
   */
	void setBoard(bool value);
	/**
	* @brief Provides read-only access to the internal Point.
	* @return A const reference to the Point.
	*/
	const Point& getPoint();
	/**
	* @brief Moves the position up (decreasing Y).
	* Can be overridden to provide custom behavior.
	*/
	virtual void moveUp();
	/**
	 * @brief Moves the position down (increasing Y).
	 * Can be overridden to provide custom behavior.
	 */
	virtual void moveDown();
	/**
	 * @brief Moves the position left (decreasing X).
	 * Can be overridden to provide custom behavior.
	 */
	virtual void moveLeft();
	/**
	* @brief Moves the position right (increasing X).
	* Can be overridden to provide custom behavior.
	*/
	virtual void moveRight();
	/**
	 * @brief Checks if player 1 has selected the position.
	 * Can be overridden to provide custom selection rules.
	 * @param x X-coordinate.
	 * @param y Y-coordinate.
	 * @return True if selection is allowed for player 1.
	 */
	virtual bool player1SelectCondition(int x, int y);
	/**
	* @brief Checks if player 2 has selected the position.
	* Can be overridden to provide custom selection rules.
	* @param x X-coordinate.
	* @param y Y-coordinate.
	* @return True if selection is allowed for player 2.
	*/
	virtual bool player2SelectCondition(int x, int y);
	/**
	 * @brief Virtual destructor.
	 */
	virtual ~Position() {}
};

