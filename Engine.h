#pragma once
#include "Board.h"

namespace mnkgame
{

class Render;

// mnk game engine
class Engine
{
public:
	// winRowLenght: how many (one sides) pieces in a row is a win
	void setParameters(Render* renderer, int rows, int cols, 
		int winRowLenght) noexcept(false);
	void newGame();
	const Board& getBoard() const;
	bool makeNextMove(const Coordinate& square) noexcept(false);
	// checks if there is a win; if there is then saves the info about 
	// it to m_gameOverInfo
	bool isWin();
	PosInfo getGameOverInfo() const;
	GameState getGameState() const;
	const std::vector<Coordinate>& getMoveHistory() const;
	int getWinRowLenght() const;

private:
	GameState m_gameState = GameState::READY_TO_START;
	// after the game is over this contains information about the end
	PosInfo m_gameOverInfo{ Player::EMPTY };
	Board m_board;
	// who's turn is next (PLAYER_TO_START starts the game)
	Player m_nextTurn = PLAYER_TO_START; 
	int m_winRowLenght = 3;	// how many needed in a row to win
	std::vector<Coordinate> m_moveHistory;
};

inline const Board& Engine::getBoard() const 
{ 
	return m_board; 
}

inline GameState Engine::getGameState() const
{ 
	return m_gameState; 
}

inline PosInfo Engine::getGameOverInfo() const
{ 
	return m_gameOverInfo; 
}

inline const std::vector<Coordinate>& Engine::getMoveHistory() const
{
	return m_moveHistory;
}

inline int Engine::getWinRowLenght() const
{ 
	return m_winRowLenght; 
}

}

