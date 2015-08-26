#pragma once
#include <vector>
#include <cassert>
#include "definitions.h"

namespace mnkgame
{
// the board and the pieces on it
class Board
{
public:
	// sets the new size for the board and empties the squares if empty==true
	void setBoardSize(int rows, int cols, bool emptyBoard = true) noexcept(false);
	void empty(); // empties the board
	int getRows() const { return m_rows; }
	int getCols() const { return m_cols; }
	// returns the piece (value) on a certain square
	const Player& getSquareValue(const Coordinate& square) const
	{
		assert(isValid(square));
		return m_position[square.x][square.y];
	}
	// is square inside the board (a valid square coordinate)
	bool isValid(const Coordinate& square) const;
	// sets a piece (or empty) on a square 
	void setSquareValue(const Coordinate& square, Player player);
	const std::vector<std::vector<Player>>& getPosition() const { return m_position; }

private:
	int m_rows = 0;
	int m_cols = 0;
	std::vector<std::vector<Player>> m_position; // the position of pieces on this board
};

}
