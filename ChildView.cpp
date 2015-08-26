
// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "m_n_kGame.h"
#include "ChildView.h"
#include "Definitions.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{

}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	FlickerFree::CMemDC pDC(&dc);

	try
	{
		m_mfcHandler.draw(pDC);
		m_mfcHandler2.draw(pDC);
	}
	catch (...)
	{
		CString errorText(EXCEPTION_MSG);
		AfxMessageBox(errorText);
		this->GetParentFrame()->PostMessage(WM_CLOSE);
	}
	//dc.FillRect(CRect(10, 10, 555, 555), (CBrush*) GetStockObject(BLACK_BRUSH));

	//pDC->LineTo(pt);
/*	CRect rtlp;
	CBrush cbrush;

	rtlp.left = 0;
	rtlp.top = 0;
	rtlp.right = 555;
	rtlp.bottom = 555;

	cbrush.CreateSolidBrush(RGB(255,0,0));
	dc.FillRect(rtlp, &(cbrush));*/
	
	// Do not call CWnd::OnPaint() for painting messages
}



BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return FALSE;
	//return CWnd::OnEraseBkgnd(pDC);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	//Invalidate();
	//UpdateWindow();
	// TODO: Add your message handler code here and/or call default
	CWnd::OnMouseMove(nFlags, point);
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	try
	{
		m_mfcHandler.onLButtonDown(nFlags, point);
		m_mfcHandler2.onLButtonDown(nFlags, point);
		Invalidate();
		UpdateWindow();
	}
	catch (...)
	{
		CString errorText(EXCEPTION_MSG);
		AfxMessageBox(errorText);
		this->GetParentFrame()->PostMessage(WM_CLOSE);
	}
	CWnd::OnLButtonDown(nFlags, point);
}

void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	try
	{
		Coordinate coord;
		if (m_mfcHandler.getBoardSquareByScreenCoord(point, coord))
		{
			m_engine.setParameters(&m_mfcHandler, 6, 5, 3);
			m_engine.newGame();
			m_engine2.newGame();
			Invalidate();
			UpdateWindow();
		}
	}
	catch (...)
	{
		CString errorText(EXCEPTION_MSG);
		AfxMessageBox(errorText);
		this->GetParentFrame()->PostMessage(WM_CLOSE);
	}

	CWnd::OnRButtonDown(nFlags, point);
}

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	try
	{
		m_mfcHandler.setParameters(40, CPoint(60, 20));
		m_engine.setParameters(&m_mfcHandler, 3, 3, 3);
		m_engine.newGame();

		m_mfcHandler2.setParameters(60, CPoint(500, 20));
		m_engine2.setParameters(&m_mfcHandler2, 5, 4, 3);
		m_engine.newGame();
	}
	catch (...)
	{
		CString errorText(EXCEPTION_MSG);
		AfxMessageBox(errorText);
		this->GetParentFrame()->PostMessage(WM_CLOSE);
		return -1;
	}

	return 0;
}
