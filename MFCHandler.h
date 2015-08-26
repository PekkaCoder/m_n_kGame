#pragma once
#include <memory>
#include "Render.h"

using namespace mnkgame;

// does all the drawings and messagehandling for a MFC project
class MFCHandler : public Render
{
	//friend class DrawVariables;
public:
	void setParameters(int sizeSquare, CPoint boardPos);
	// returns board square from (mouse-) coordinate 
	bool getBoardSquareByScreenCoord(CPoint pointScreen, Coordinate& square);
	// handling window messages
	void onMouseMove(UINT nFlags, CPoint point);
	void onLButtonDown(UINT nFlags, CPoint point) noexcept(false);
	void draw(CDC* pDC);

private:
	// overridables
	void drawBoard(DrawVariables* dw, int rows, int cols);
	void drawX(DrawVariables* dw, Coordinate square);
	void drawO(DrawVariables* dw, Coordinate square);
	void drawWinLine(DrawVariables* dw, Coordinate squareStart, Coordinate squareEnd);
	int m_sizeSquare = 35;
	CPoint m_boardPos{ 50,30 };
};

class MFCDrawVariables : public DrawVariables
{
public:
	MFCDrawVariables(CDC* dc) : m_DC(dc) {}
	CDC* getDC() const { return m_DC; }
private:
	CDC* m_DC = nullptr;
};




