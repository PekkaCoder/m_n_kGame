#include <map>
#include "Render.h"

namespace mnkgame
{

void Render::draw(DrawVariables* dw)
{
	if (m_engine == nullptr)
		return;
	drawBoard(dw, m_engine->getBoard().getRows(), m_engine->getBoard().getCols());
	drawPosition(dw);
	if (m_engine->getGameState() == GameState::GAME_OVER)
	{
		// draw the win line over the winners pieces
		static const std::map<WinDir, Coordinate> s_winDir{ { WinDir::EAST, {0,1} }, { WinDir::SOUTH, {1,0} },
			{ WinDir::SOUTH_EAST, {1,1} }, { WinDir::SOUTH_WEST, {1,-1} } };
		PosInfo winInfo = m_engine->getGameOverInfo();
		Coordinate coordStart, coordEnd;
		coordStart = winInfo.winpos;
		coordEnd = { coordStart.x + s_winDir.at(winInfo.windir).x * (m_engine->getWinRowLenght() - 1),
					 coordStart.y + s_winDir.at(winInfo.windir).y * (m_engine->getWinRowLenght() - 1) };
		drawWinLine(dw, coordStart, coordEnd);
	}
}

void Render::drawPosition(DrawVariables* dw)
{
	if (m_engine == nullptr)
		return;
	int rows, cols;
	rows = m_engine->getBoard().getRows();
	cols = m_engine->getBoard().getCols();

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			if (m_engine->getBoard().getSquareValue({ i, j }) == Player::X)
				drawX(dw, { i, j });
			else if (m_engine->getBoard().getSquareValue({ i, j }) == Player::O)
				drawO(dw, { i, j });
		}
	}
}

}
