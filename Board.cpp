#include "Board.h"

namespace mnkgame
{

void Board::setBoardSize(int rows, int cols, bool emptyBoard)
{
	if (rows == getRows() && cols == getCols())
	{
		// size is already correct so no need to resize
		if (emptyBoard)
			empty();
		return;
	}
	// resize m_position to size rows x cols
	if(emptyBoard)
		m_position = std::vector<std::vector<Player>>(rows, 
			std::vector<Player>(cols, Player::EMPTY));
	else
		m_position = std::vector<std::vector<Player>>(rows, 
			std::vector<Player>(cols));
}

void Board::empty()
{
	for (auto& row : m_position)
	{
		for (auto& col : row)
			// setting the square with row "row" and column "col" 
			col = Player::EMPTY;
	}
}

bool Board::isValid(const Coordinate& square) const
{
	return square.x >= 0 && square.y >= 0 && 
		square.x < getRows() && square.y < getCols();
}

void Board::setSquareValue(const Coordinate& square, Player player)
{
	assert(isValid(square));
	if (isValid(square))
		m_position[square.x][square.y] = player;
}

}


