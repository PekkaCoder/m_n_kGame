#pragma once
#include "definitions.h"
#include "Engine.h"
#include <iostream>
namespace mnkgame
{

// DrawVariables objects passed to draw functions as an argument
class DrawVariables
{
public:
	virtual ~DrawVariables() = 0;
};

inline DrawVariables::~DrawVariables()
{
	std::cout << "DrawVariables::~DrawVariables";
}

class Render
{
public:
	Engine* getEngine() const { return m_engine; }
	// call Render::draw from defived classes to do all drawing 
	void draw(DrawVariables* dw);

protected:
	virtual void drawBoard(DrawVariables* dw, int rows, int cols) = 0;
	virtual void drawX(DrawVariables* dw, Coordinate square) = 0;
	virtual void drawO(DrawVariables* dw, Coordinate square) = 0;
	virtual void drawWinLine(DrawVariables* dw, Coordinate squareStart, Coordinate squareEnd) = 0;
	// prohibits deletion of a derived class object through the pointer of this class;
	// only derived class objects can be deleted not with pointers to base/this class.
	~Render() = default;

private:
	void drawPosition(DrawVariables* dw);
	friend void Engine::setParameters(Render* renderer, int rows, int cols, int winRowLenght);
	Engine* m_engine = nullptr;
};

}

