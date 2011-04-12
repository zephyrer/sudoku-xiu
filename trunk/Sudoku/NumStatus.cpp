#include "StdAfx.h"
#include "NumStatus.h"

#define NUMSTATUS_CLASSNAME    _T("MFCNumStatusCtrl")  // Window class name


CNumStatus::CNumStatus(): m_num(0)
{
	//SetBitmap(IDB_BITMAP1);
	RegisterWindowClass();
}

BOOL CNumStatus::RegisterWindowClass()
{
	WNDCLASS wndcls;
	HINSTANCE hInst = AfxGetInstanceHandle();

	if (!(::GetClassInfo(hInst, NUMSTATUS_CLASSNAME, &wndcls)))
	{
		// otherwise we need to register a new class

		wndcls.style            = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
		wndcls.lpfnWndProc      = ::DefWindowProc;
		wndcls.cbClsExtra       = wndcls.cbWndExtra = 0;
		wndcls.hInstance        = hInst;
		wndcls.hIcon            = NULL;
		wndcls.hCursor          = AfxGetApp()->LoadStandardCursor(IDC_HAND);
		wndcls.hbrBackground    = (HBRUSH) (COLOR_3DFACE + 1);
		wndcls.lpszMenuName     = NULL;
		wndcls.lpszClassName    = NUMSTATUS_CLASSNAME;

		if (!AfxRegisterClass(&wndcls))
		{
			AfxThrowResourceException();
			return FALSE;
		}
	}

	return TRUE;
}

CNumStatus::~CNumStatus(void)
{
}
BEGIN_MESSAGE_MAP(CNumStatus, CWnd)
	ON_WM_PAINT()
//	ON_WM_LBUTTONDOWN()
ON_WM_LBUTTONDOWN()
//ON_WM_SETCURSOR()
END_MESSAGE_MAP()

void CNumStatus::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CWnd::OnPaint() for painting messages
	CPen pen(PS_SOLID, 1, RGB(160, 160, 160));
	CPen *pOldPen = dc.SelectObject(&pen);
	CRect rc;
	GetWindowRect(&rc);
	dc.MoveTo(CPoint(rc.Width() - 1, 0));
	dc.LineTo(CPoint(0, 0));
	dc.LineTo(CPoint(0, rc.Height() - 1));

	CPen pen2(PS_SOLID, 1, RGB(255, 255, 255));
	dc.SelectObject(&pen2);
	dc.LineTo(CPoint(rc.Width() - 1, rc.Height() - 1));
	dc.LineTo(CPoint(rc.Width() - 1, 0));
	dc.SelectObject(pOldPen);
	

	if(m_num < 9)
	{
		CClientDC dc(this);
		CRect rc;
		GetWindowRect(&rc);
		double ht = (rc.Height() * 1.0 - 3) / 9;
		CBrush brush(RGB(0, 0, 255));
		for(int i = 1;i < m_num + 1;i ++)
		{
			CRect rect(2, (int) (ht * (9 - i) + 3), rc.Width() - 2,(int) (ht * (10 - i) + 1));
			dc.FillRect(&rect,&brush);
		}
	}
	else if(m_num == 9)
	{
		CClientDC dc(this);
		CRect rc;
		GetWindowRect(&rc);
		double ht = (rc.Height() * 1.0 - 3) / 9;
		CBrush brush(RGB(255, 0, 0));
		for(int i = 1;i < 10;i ++)
		{
			CRect rect(2, (int) (ht * (9 - i) + 3), rc.Width() - 2,(int) (ht * (10 - i) + 1));
			dc.FillRect(&rect,&brush);
		}
	}
	
}

CNumStatus& CNumStatus::operator ++(int)
{
	m_num ++;
	if(m_num < 9)
	{
		CClientDC dc(this);
		CRect rc;
		GetWindowRect(&rc);
		double ht = (rc.Height() * 1.0 - 3) / 9;
		CBrush brush(RGB(0, 0, 255));
		CRect rect(2, (int) (ht * (9 - m_num) + 3), rc.Width() - 2,(int) (ht * (10 - m_num) + 1));
		dc.FillRect(&rect,&brush);
	}
	else if(m_num == 9)
	{
		CClientDC dc(this);
		CRect rc;
		GetWindowRect(&rc);
		double ht = (rc.Height() * 1.0 - 3) / 9;
		CBrush brush(RGB(255, 0, 0));
		for(int i = 1;i < 10;i ++)
		{
			CRect rect(2, (int) (ht * (9 - i) + 3), rc.Width() - 2,(int) (ht * (10 - i) + 1));
			dc.FillRect(&rect,&brush);
		}
	}
	return *this;
}

CNumStatus& CNumStatus::operator --(int)
{
	if(m_num != 0)
	{
		m_num --;
		if(m_num < 8)
		{
			CClientDC dc(this);
			CRect rc;
			GetWindowRect(&rc);
			double ht = (rc.Height() * 1.0 - 3) / 9;
			CBrush brush(RGB(240, 240, 240));
			CRect rect(2, (int) (ht * (8 - m_num) + 3), rc.Width() - 2,(int) (ht * (9 - m_num) + 1));
			dc.FillRect(&rect,&brush);
		}
		else if(m_num == 8)
		{
			CClientDC dc(this);
			CRect rc;
			GetWindowRect(&rc);
			double ht = (rc.Height() * 1.0 - 3) / 9;
			CBrush brush(RGB(0, 0, 255));
			for(int i = 1;i < 9;i ++)
			{
				CRect rect(2, (int) (ht * (9 - i) + 3), rc.Width() - 2,(int) (ht * (10 - i) + 1));
				dc.FillRect(&rect,&brush);
			}

			CBrush brush2(RGB(240, 240, 240));
			CRect rect2(2, 3, rc.Width() - 2,(int) (ht + 1));
			dc.FillRect(&rect2,&brush2);
		}
	}
	return *this;
}

//void CNumStatus::OnLButtonDown(UINT nFlags, CPoint point)
//{
//	// TODO: Add your message handler code here and/or call default
//
//	::PostMessage(this->GetParent()->m_hWnd, WM_LBUTTONDOWN, 0, 0);
//	CWnd::OnLButtonDown(nFlags, point);
//}

void CNumStatus::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), BN_CLICKED), (LPARAM) m_hWnd);
	CWnd::OnLButtonDown(nFlags, point);
}

//BOOL CNumStatus::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
//{
//	// TODO: Add your message handler code here and/or call default
//	SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEALL));
//	return true;
//	//return CWnd::OnSetCursor(pWnd, nHitTest, message);
//}

void CNumStatus::SetZero(void)
{
	while(m_num > 0)
		(* this) --;
}
