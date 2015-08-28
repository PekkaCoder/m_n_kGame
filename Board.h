#pragma once
#include <vector>
#include <cassert>
#include "definitions.h"

namespace mnkgame
{
// the board and the pieces on it (the position)
class Board
{
public:
	// always use these to get the size of the board, even inside this class
	int getRows() const;
	int getCols() const;
	// to be able to use [2][1] kind of syntax to get elements values 
	const std::vector<std::vector<Player>>& getPosition() const;
	// sets the new size for the board and empties the squares if empty==true
	void setBoardSize(int rows, int cols, 
		bool emptyBoard = true) noexcept(false);
	void empty(); // empties the board
	// returns the piece (value) on a certain square
	Player getSquareValue(const Coordinate& square) const;
	// sets a piece (or empty) on a square 
	void setSquareValue(const Coordinate& square, Player player);
	// is square inside the board (a valid square coordinate)
	bool isValid(const Coordinate& square) const;

private:
	// the position of pieces on this board (including empty)
	std::vector<std::vector<Player>> m_position;
};

inline int Board::getRows() const
{
	return static_cast<int>(m_position.size());
}

inline int Board::getCols() const
{
	return getRows() == 0 ? 0 : static_cast<int>(m_position[0].size());
}

inline const std::vector<std::vector<Player>>& Board::getPosition() const
{
	return m_position;
}

inline Player Board::getSquareValue(const Coordinate& square) const
{
	assert(isValid(square));
	return m_position.at(square.x).at(square.y);
}

}
