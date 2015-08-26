
// m_n_kGame.h : main header file for the m_n_kGame application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// Cm_n_kGameApp:
// See m_n_kGame.cpp for the implementation of this class
//

class Cm_n_kGameApp : public CWinApp
{
public:
	Cm_n_kGameApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
	virtual LRESULT ProcessWndProcException(CException* e, const MSG* pMsg);
};

extern Cm_n_kGameApp theApp;
