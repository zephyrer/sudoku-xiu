// MyTipEdit.cpp : implementation file
//

#include "stdafx.h"
#include "Sudoku.h"
#include "MyTipEdit.h"

// CMyTipEdit

IMPLEMENT_DYNAMIC(CMyTipEdit, CEdit)

CMyTipEdit::CMyTipEdit()
{
	m_crText = RGB(0, 0, 0);
}

CMyTipEdit::~CMyTipEdit()
{
	if (m_brBackGnd.GetSafeHandle())
		m_brBackGnd.DeleteObject();
}


BEGIN_MESSAGE_MAP(CMyTipEdit, CEdit)
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()



// CMyTipEdit message handlers



HBRUSH CMyTipEdit::CtlColor(CDC* pDC, UINT nCtlColor)
{
	// TODO: Return a non-NULL brush if the parent's handler should not be called

	//set text color
	pDC->SetTextColor(m_crText);
	//set the text's background color
	pDC->SetBkColor(m_crBackGnd);

	//return the brush used for background this sets control background
	return m_brBackGnd;
}

void CMyTipEdit::SetBackColor(COLORREF rgb)
{
	//set background color ref (used for text's background)
	m_crBackGnd = rgb;

	//free brush
	if (m_brBackGnd.GetSafeHandle())
		m_brBackGnd.DeleteObject();
	//set brush to new color
	m_brBackGnd.CreateSolidBrush(rgb);

	//redraw
	Invalidate(TRUE);
}


void CMyTipEdit::SetTextColor(COLORREF rgb)
{
	//set text color ref
	m_crText = rgb;

	//redraw
	Invalidate(TRUE);
}