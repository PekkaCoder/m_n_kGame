#include "Engine.h"
#include "Render.h"

namespace mnkgame
{

// checkUnbrokenRow
// Checks if there is an unbroken row of rowLenght pieces to the east, south-east, south or south-west 
// direction. If there is, posInfo (which is passed) will be filled with
// the information about the found row.
//
// Parameters:
// rowLenght - the number or pieces in a row
// posInfo - if an unbroken row is found, the information about it
//
// Return value:
// true if the row is found, otherwise false
//
static bool checkUnbrokenRow(const Board& board, int rowLenght, PosInfo& posInfo)
{
	int rows = board.getRows();
	int cols = board.getCols();
	bool same = true; // true as long as same pieces are found in a row
	const std::vector<std::vector<Player>>& boardPos = board.getPosition();
	// lambda to check if there are same pieces in a row from a certain square
	auto l_fromSquareCheckNSame = [&boardPos, &posInfo, rowLenght, cols, rows](int i, int j, WinDir windir)
	{
		// special case: the first square is empty
		if (boardPos[i][j] == Player::EMPTY)
			return false;
		bool same = true; // the first square is not empty so "same" can be set to true
		for (int k = 0; k < rowLenght - 1; ++k)
		{
			if (windir == WinDir::EAST)
			{
				if (j > cols - rowLenght)
					same = false; // j is too much on right so the winner is not possible
				else
					same = (same && (boardPos[i][j + k] == boardPos[i][j + k + 1]));
			}
			else if (windir == WinDir::SOUTH)
			{
				if (i > rows - rowLenght)
					same = false; // i is too much on down so the winner is not possible
				else
					same = (same && (boardPos[i + k][j] == boardPos[i + k + 1][j]));
			}
			else if (windir == WinDir::SOUTH_EAST)
			{
				if (j > cols - rowLenght || i > rows - rowLenght)
					same = false; // i or j is too much on right or down so the winner is not possible
				else
					same = (same && (boardPos[i + k][j + k] == boardPos[i + k + 1][j + k + 1]));
			}
			else if (windir == WinDir::SOUTH_WEST)
			{
				if (j < rowLenght - 1 || i > rows - rowLenght)
					same = false; // i or j is too much on left or down so the winner is not possible
				else
					same = (same && (boardPos[i + k][j - k] == boardPos[i + k + 1][j - k - 1]));
			}
			if (!same)
				break;
		}
		if (same)
		{
			posInfo.winner = boardPos[i][j]; // the first piece is the winners piece
			posInfo.windir = windir;
			posInfo.winpos = { i, j };
			return true;
		}
		return false;
	};

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			if (l_fromSquareCheckNSame(i, j, WinDir::EAST))
				return true;
			if (l_fromSquareCheckNSame(i, j, WinDir::SOUTH))
				return true;
			if (l_fromSquareCheckNSame(i, j, WinDir::SOUTH_EAST))
				return true;
			if (l_fromSquareCheckNSame(i, j, WinDir::SOUTH_WEST))
				return true;
		}
	}

	posInfo.winner = Player::EMPTY; // if we came here -> no winner
	return false;
}

void Engine::setParameters(Render* renderer, int rows, int cols, int winRowLenght)
{
	m_winRowLenght = winRowLenght;
	renderer->m_engine = this;
	m_board.setBoardSize(rows, cols);
}

void Engine::newGame()
{
	m_gameState = GameState::READY_TO_START;
	m_gameOverInfo.winner = Player::EMPTY; // no-one is winner; draw currently
	m_board.empty();
	m_moveHistory.clear();
	m_nextTurn = Player::X;
}

// Engine::makeNextMove
// Makes the next move. Knows which side is to move. Only makes a move if the square is
// empty. Adds move to a history list/array. If game is over calls renderer virtual function
// gameOver and sets the engine state to GAME_OVER (thus the game cannot be continued).
//
// Parameters:
// square - the square where the player wants to do the next move.
//
// Return value:
// true if the move was made, otherwise false.
//
bool Engine::makeNextMove(const Coordinate& square)
{
	if (m_gameState == GameState::GAME_OVER)
		return false;
	assert(m_board.isValid(square));
	if (!m_board.isValid(square))
		return false;
	if (m_board.getSquareValue(square) != Player::EMPTY)
		return false;
	// move to square is valid so let's do it
	m_board.setSquareValue(square, m_nextTurn);
	m_moveHistory.push_back(square);
	bool noMoreMovesLeft = (m_moveHistory.size() == m_board.getRows() * m_board.getCols());
	if (isWin() || noMoreMovesLeft)
		m_gameState = GameState::GAME_OVER;
	else
		m_nextTurn = (m_nextTurn == Player::X) ? Player::O : Player::X; // toggle turn

	return true;
}

bool Engine::isWin()
{
	return checkUnbrokenRow(m_board, m_winRowLenght, m_gameOverInfo);
}

}
