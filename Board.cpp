#include "Board.h"

namespace mnkgame
{

void Board::setBoardSize(int rows, int cols, bool emptyBoard)
{
	if (rows == m_rows && cols == m_cols)
	{
		// size is already correct so no need to resize
		if (emptyBoard)
			empty();
		return;
	}
	m_rows = rows;
	m_cols = cols;
	// resize m_position to size m_rows x m_cols
	if(emptyBoard)
		m_position = std::vector<std::vector<Player>>(m_rows, std::vector<Player>(cols, Player::EMPTY));
	else
		m_position = std::vector<std::vector<Player>>(m_rows, std::vector<Player>(cols));
}

void Board::empty()
{
	for (auto& row : m_position)
	{
		for (auto& rowElement : row)
			rowElement = Player::EMPTY;
	}
}

bool Board::isValid(const Coordinate& square) const
{
	return square.x >= 0 && square.y >= 0 && square.x < m_rows && square.y < m_cols;
}

void Board::setSquareValue(const Coordinate& square, Player player)
{
	assert(isValid(square));
	if (isValid(square))
		m_position[square.x][square.y] = player;
}

}


