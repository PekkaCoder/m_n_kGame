https://github.com/PekkaCoder/mnk-Game
http://www.codeproject.com/Articles/33/Flicker-Free-Drawing-In-MFC

class GameManager
{
public:
private:
	Engine m_engine;
	MFCHandler m_mfcHandler;
};

***********
/*
	m_position.resize(m_rows); 
	m_position.shrink_to_fit();
	for (auto& row : m_position)
	{
		row.resize(m_cols);
		row.shrink_to_fit();
		if (emptyBoard)
			for (auto& col : row)
				col = Player::EMPTY;
	}
*/
***********
// FUNCTION
// 
// 
//
// Parameters:
// 
// 
//
// Return value:
// 
//



bool Engine::checkNSame(int sameLenght, PosInfo& posInfo)
{
	int rows = m_board.getRows();
	int cols = m_board.getCols();
	bool same = true;
	const std::vector<std::vector<Player>>& board = m_board.getPosition();

	auto l_fromSquareCheckNSame = [&board, &posInfo, sameLenght] (int i, int j, WinDir windir)
	{
		bool same = true;
		same = true;
		for (int k = 0; k < sameLenght - 1; ++k)
		{
			if(windir == WinDir::EAST)
				same = (same && (board[i][j + k] == board[i][j + k + 1]));
			else if(windir == WinDir::SOUTH)
				same = (same && (board[i + k][j] == board[i + k + 1][j]));
			if (!same)
				break;
		}
		if (same)
		{
			posInfo.winner = board[i][j]; // the first piece is the winners piece
			posInfo.windir = windir;
			posInfo.winpos = { i, j };
			return true;
		}
		return false;
	};
	// Checks for:
	//     X X X
	for (int i = 0; i < rows; ++i)
	{
		
		for (int j = 0; j < cols; ++j)
		{
			if (board[i][j] == Player::EMPTY)
				continue;
			if(l_fromSquareCheckNSame(i, j, WinDir::EAST))
				return true;
/*			same = true;
			for (int k = 0; k < sameLenght-1; ++k)
			{
				same = (same && (board[i][j+k] == board[i][j + k + 1]));
				if (!same)
					break;
			}
			if (same)
			{
				posInfo.winner = board[i][j]; // the first piece is the winners piece
				posInfo.windir = WinDir::EAST;
				posInfo.winpos = {i, j};
				return true;
			}*/
		}
	}
	// Checks for:
	//     X
	//     X
	//     X
	for (int j = 0; j < cols; ++j)
	{
		for (int i = 0; i < rows; ++i)
		{
			if (board[i][j] == Player::EMPTY)
				continue;
			if (l_fromSquareCheckNSame(i, j, WinDir::SOUTH))
				return true;
/*			same = true;
			for (int k = 0; k < sameLenght - 1; ++k)
			{
				same = (same && (board[i + k][j] == board[i + k + 1][j]));
				if (!same)
					break;
			}
			if (same)
			{
				posInfo.winner = board[i][j]; // the first piece is the winners piece
				posInfo.windir = WinDir::SOUTH;
				posInfo.winpos = { i, j };
				return true;
			}*/
		}
	}
	/*for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{

		}
	}*/
	//pos[1][1] = Player::EMPTY;
	//for (auto a : m_board.getPostion())
	posInfo.winner = Player::EMPTY; // no winner
	return false;
}

================================================================================
    MICROSOFT FOUNDATION CLASS LIBRARY : m_n_kGame Project Overview
===============================================================================

The application wizard has created this m_n_kGame application for
you.  This application not only demonstrates the basics of using the Microsoft
Foundation Classes but is also a starting point for writing your application.

This file contains a summary of what you will find in each of the files that
make up your m_n_kGame application.

m_n_kGame.vcxproj
    This is the main project file for VC++ projects generated using an application wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    application wizard.

m_n_kGame.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the assciation between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

m_n_kGame.h
    This is the main header file for the application.  It includes other
    project specific headers (including Resource.h) and declares the
    Cm_n_kGameApp application class.

m_n_kGame.cpp
    This is the main application source file that contains the application
    class Cm_n_kGameApp.

m_n_kGame.rc
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited in Microsoft
    Visual C++. Your project resources are in 1033.

res\m_n_kGame.ico
    This is an icon file, which is used as the application's icon.  This
    icon is included by the main resource file m_n_kGame.rc.

res\m_n_kGame.rc2
    This file contains resources that are not edited by Microsoft
    Visual C++. You should place all resources not editable by
    the resource editor in this file.

/////////////////////////////////////////////////////////////////////////////

For the main frame window:
    The project includes a standard MFC interface.

MainFrm.h, MainFrm.cpp
    These files contain the frame class CMainFrame, which is derived from
    CFrameWnd and controls all SDI frame features.

/////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////

Help Support:

hlp\m_n_kGame.hhp
    This file is a help project file. It contains the data needed to
    compile the help files into a .chm file.

hlp\m_n_kGame.hhc
    This file lists the contents of the help project.

hlp\m_n_kGame.hhk
    This file contains an index of the help topics.

hlp\afxcore.htm
    This file contains the standard help topics for standard MFC
    commands and screen objects. Add your own help topics to this file.

makehtmlhelp.bat
    This file is used by the build system to compile the help files.

hlp\Images\*.gif
    These are bitmap files required by the standard help file topics for
    Microsoft Foundation Class Library standard commands.


/////////////////////////////////////////////////////////////////////////////

Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named m_n_kGame.pch and a precompiled types file named StdAfx.obj.

Resource.h
    This is the standard header file, which defines new resource IDs.
    Microsoft Visual C++ reads and updates this file.

m_n_kGame.manifest
	Application manifest files are used by Windows XP to describe an applications
	dependency on specific versions of Side-by-Side assemblies. The loader uses this
	information to load the appropriate assembly from the assembly cache or private
	from the application. The Application manifest  maybe included for redistribution
	as an external .manifest file that is installed in the same folder as the application
	executable or it may be included in the executable in the form of a resource.
/////////////////////////////////////////////////////////////////////////////

Other notes:

The application wizard uses "TODO:" to indicate parts of the source code you
should add to or customize.

If your application uses MFC in a shared DLL, you will need
to redistribute the MFC DLLs. If your application is in a language
other than the operating system's locale, you will also have to
redistribute the corresponding localized resources MFC100XXX.DLL.
For more information on both of these topics, please see the section on
redistributing Visual C++ applications in MSDN documentation.

/////////////////////////////////////////////////////////////////////////////
