#pragma once

namespace mnkgame
{

// note: assert on/off flag: #define NDEBUG
enum class Player : char { EMPTY = 0, X, O };
enum class WinDir : char { EAST = 1, SOUTH_EAST, SOUTH, SOUTH_WEST };
enum class GameState : char { READY_TO_START = 1, GAME_OVER };

/*
Board consists of squares. The size of the board is m_rows x m_cols (class Board).
Coordinate system for the game:

			columns
		_____________________
		|(0,0)|(0,1)|(0,2) ...
rows	|(1,0)|(1,1)|(1,2) ...
		|(2,0)|(2,1)|(2,2) ...
		|...
		|
In code x refers to rows and y to columns. x and y are zero based, so
x=0 is the first row.
*/
struct Coordinate
{
	int x; // row
	int y; // column
};

// information about a position (can be any information)
struct PosInfo
{
	Player winner; // EMPTY means "no winner"/draw
	WinDir windir;
	Coordinate winpos;
};

/////////////////////////////////////////////////////////////////////////////////////
// Constants

const char EXCEPTION_MSG[] =
"An unmanageable error occured. Maybe failure to allocate\n"
"memory - please free some memory/close application.\n"
"MNK Game program terminates now.";

const Player PLAYER_TO_START = Player::X;
static_assert(PLAYER_TO_START == Player::O || PLAYER_TO_START == Player::X, "PLAYER_TO_START needs to be X or O");

}

