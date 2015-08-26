#include "stdafx.h"
#include "Engine.h"
#include "MFCHandler.h"

void MFCHandler::onMouseMove(UINT nFlags, CPoint point)
{

}

void MFCHandler::onLButtonDown(UINT nFlags, CPoint point)
{
	Coordinate square;
	if (getBoardSquareByScreenCoord(point, square))
		getEngine()->makeNextMove(square);
}

void MFCHandler::setParameters(int sizeSquare, CPoint boardPos)
{
	m_sizeSquare = sizeSquare;
	m_boardPos = boardPos;
}

bool MFCHandler::getBoardSquareByScreenCoord(CPoint pointScreen, Coordinate& square)
{
	if (pointScreen.x - m_boardPos.x < 0 || pointScreen.y - m_boardPos.y < 0)
		return false;
	square = Coordinate{ (pointScreen.y - m_boardPos.y) / m_sizeSquare , ((pointScreen.x - m_boardPos.x) / m_sizeSquare) };
	return getEngine()->getBoard().isValid(square);
}

void MFCHandler::drawX(DrawVariables* dw, Coordinate square)
{
	MFCDrawVariables* drawVariables = dynamic_cast<MFCDrawVariables*>(dw);
	assert(drawVariables && drawVariables->getDC());
	if (!(drawVariables && drawVariables->getDC()))
		return;
	const int OFFSET = m_sizeSquare / 5; // offset from the square borders to draw X
	CPen thickPen(PS_SOLID, 3, RGB(255, 0, 255));
	CPen* oldPen = static_cast<CPen*>(drawVariables->getDC()->SelectObject(&thickPen));
	// downhill
	drawVariables->getDC()->MoveTo(m_boardPos.x + square.y * m_sizeSquare + OFFSET, m_boardPos.y + square.x * m_sizeSquare + OFFSET);
	drawVariables->getDC()->LineTo(m_boardPos.x + square.y * m_sizeSquare + m_sizeSquare - OFFSET,
		m_boardPos.y + square.x * m_sizeSquare + m_sizeSquare - OFFSET);
	// uphill
	drawVariables->getDC()->MoveTo(m_boardPos.x + square.y * m_sizeSquare + OFFSET, m_boardPos.y + square.x * m_sizeSquare + m_sizeSquare - OFFSET);
	drawVariables->getDC()->LineTo(m_boardPos.x + square.y * m_sizeSquare + m_sizeSquare - OFFSET,
		m_boardPos.y + square.x * m_sizeSquare + OFFSET);

	drawVariables->getDC()->SelectObject(oldPen);
}

void MFCHandler::drawO(DrawVariables* dw, Coordinate square)
{
	MFCDrawVariables* drawVariables = dynamic_cast<MFCDrawVariables*>(dw);
	assert(drawVariables && drawVariables->getDC());
	if (!(drawVariables && drawVariables->getDC()))
		return;
	const int OFFSET = m_sizeSquare / 5; // offset from the square borders to draw O
	CPen thickPen(PS_SOLID, 3, RGB(0, 255, 255));
	CPen* oldPen = static_cast<CPen*>(drawVariables->getDC()->SelectObject(&thickPen));

	drawVariables->getDC()->Ellipse(m_boardPos.x + square.y * m_sizeSquare + OFFSET, m_boardPos.y + square.x * m_sizeSquare + OFFSET,
		m_boardPos.x + square.y * m_sizeSquare + m_sizeSquare - OFFSET, m_boardPos.y + square.x * m_sizeSquare + m_sizeSquare - OFFSET);

	drawVariables->getDC()->SelectObject(oldPen);
}

void MFCHandler::drawBoard(DrawVariables* dw, int rows, int cols)
{
	MFCDrawVariables* drawVariables = dynamic_cast<MFCDrawVariables*>(dw);
	assert(drawVariables && drawVariables->getDC());
	if (!(drawVariables && drawVariables->getDC()))
		return;
	CPen thickPen(PS_SOLID, 3, RGB(0, 0, 255));
	CPen* oldPen = static_cast<CPen*>(drawVariables->getDC()->SelectObject(&thickPen));
	// rows
	for (int i = 0; i <= rows; ++i)
	{
		drawVariables->getDC()->MoveTo(m_boardPos.x, m_boardPos.y + i * m_sizeSquare);
		drawVariables->getDC()->LineTo(m_boardPos.x + cols * m_sizeSquare, m_boardPos.y + i * m_sizeSquare);
	}
	// columns
	for (int j = 0; j <= cols; ++j)
	{
		drawVariables->getDC()->MoveTo(m_boardPos.x + j * m_sizeSquare, m_boardPos.y);
		drawVariables->getDC()->LineTo(m_boardPos.x + j * m_sizeSquare, m_boardPos.y + rows * m_sizeSquare);
	}
	CString str;
	// coordinates - note: coordinates on screen are (right, up). So (1,1) is at the bottom left.
	// Because the code uses (right, down)- system (see Definitions.h) we do a conversion here.
	for (int j = 0; j < cols; ++j)
	{
		str.Format(_T("%i"), j + 1);
		drawVariables->getDC()->TextOut(m_boardPos.x + m_sizeSquare * j + static_cast<int>(0.35*m_sizeSquare), m_boardPos.y + m_sizeSquare * rows + 5, str);
	}
	for (int j = 0; j < rows; ++j)
	{
		str.Format(_T("%i"), j + 1);
		drawVariables->getDC()->TextOut(m_boardPos.x - 25, m_boardPos.y + m_sizeSquare * rows - j * m_sizeSquare - static_cast<int>(0.7*m_sizeSquare), str);
	}
	// move history
	int x, y;
	int count = 0;
	for (const auto& move : getEngine()->getMoveHistory())
	{
		x = move.y + 1;
		y = getEngine()->getBoard().getRows() - move.x;
		str.Format(_T("%i. %i, %i"), count + 1, x, y);
		drawVariables->getDC()->TextOut(m_boardPos.x + cols * m_sizeSquare + 20, m_boardPos.y + 15 * count, str);
		++count;
	}
	// if game if over print the game over text/info
	if (getEngine()->getGameState() == GameState::GAME_OVER)
	{
		PosInfo winInfo = getEngine()->getGameOverInfo();
		if (winInfo.winner == Player::O)
			str.Format(_T("Game Over! O won"), x, y);
		else if (winInfo.winner == Player::X)
			str.Format(_T("Game Over! X won"), x, y);
		else
			str.Format(_T("Game Over! Draw"), x, y);
		drawVariables->getDC()->TextOut(m_boardPos.x + cols * m_sizeSquare + 20, m_boardPos.y + 15 * count++, str);
	}

	drawVariables->getDC()->SelectObject(oldPen);
}

void MFCHandler::drawWinLine(DrawVariables* dw, Coordinate squareStart, Coordinate squareEnd)
{
	MFCDrawVariables* drawVariables = dynamic_cast<MFCDrawVariables*>(dw);
	assert(drawVariables && drawVariables->getDC());
	if (!(drawVariables && drawVariables->getDC()))
		return;
	CPen winPen(PS_SOLID, 8, RGB(88, 120, 188));
	CPen* oldPen = static_cast<CPen*>(drawVariables->getDC()->SelectObject(&winPen));

	drawVariables->getDC()->MoveTo(m_boardPos.x + squareStart.y * m_sizeSquare + static_cast<int>(0.5 * m_sizeSquare),
		m_boardPos.y + squareStart.x * m_sizeSquare + static_cast<int>(0.5 * m_sizeSquare));
	drawVariables->getDC()->LineTo(m_boardPos.x + squareEnd.y * m_sizeSquare + static_cast<int>(0.5 * m_sizeSquare),
		m_boardPos.y + squareEnd.x * m_sizeSquare + static_cast<int>(0.5 * m_sizeSquare));

	drawVariables->getDC()->SelectObject(oldPen);
}

void MFCHandler::draw(CDC* pDC)
{
	Render::draw(&MFCDrawVariables{ pDC });
}

