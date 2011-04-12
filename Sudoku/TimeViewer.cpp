#include "StdAfx.h"
#include "TimeViewer.h"

#define TIMEVIEWER_CLASSNAME    _T("MFCTimeViererCtrl")  // Window class name


CTimeViewer::CTimeViewer()
: m_sTime(0)
, m_mTime(0)
, m_hTime(0)
{
	//SetBitmap(IDB_BITMAP1);
	RegisterWindowClass();
}

BOOL CTimeViewer::RegisterWindowClass()
{
	WNDCLASS wndcls;
	HINSTANCE hInst = AfxGetInstanceHandle();

	if (!(::GetClassInfo(hInst, TIMEVIEWER_CLASSNAME, &wndcls)))
	{
		// otherwise we need to register a new class

		wndcls.style            = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
		wndcls.lpfnWndProc      = ::DefWindowProc;
		wndcls.cbClsExtra       = wndcls.cbWndExtra = 0;
		wndcls.hInstance        = hInst;
		wndcls.hIcon            = NULL;
		wndcls.hCursor          = AfxGetApp()->LoadStandardCursor(IDC_ARROW);
		wndcls.hbrBackground    = (HBRUSH) (COLOR_3DFACE + 1);
		wndcls.lpszMenuName     = NULL;
		wndcls.lpszClassName    = TIMEVIEWER_CLASSNAME;

		if (!AfxRegisterClass(&wndcls))
		{
			AfxThrowResourceException();
			return FALSE;
		}
	}

	return TRUE;
}

CTimeViewer::~CTimeViewer(void)
{
}
BEGIN_MESSAGE_MAP(CTimeViewer, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
END_MESSAGE_MAP()

void CTimeViewer::OnPaint()
{
	CPaintDC dc(this);
	CRect rc;
	GetWindowRect(&rc);
	CBrush brush(RGB(0, 0, 0));
	CRect rect(0, 0, rc.Width(), rc.Height());
	dc.FillRect(&rect,&brush);
	COLORREF clr = dc.SetTextColor(RGB(0, 255, 0));
	dc.SetBkMode(TRANSPARENT);

	dc.TextOut(25, 3, _T(":"));

	dc.TextOut(48, 3, _T(":"));


	CString str;
	if(m_hTime < 10)
	{
		str.Format(_T("0%d"), m_hTime);
	}
	else
	{
		str.Format(_T("%d"), m_hTime);
	}
	
	dc.TextOut(8, 3, str);
	if(m_mTime < 10)
	{
		str.Format(_T("0%d"), m_mTime);
	}
	else
	{
		str.Format(_T("%d"), m_mTime);
	}
	
	dc.TextOut(31, 3, str);
	if(m_sTime < 10)
	{
		str.Format(_T("0%d"), m_sTime);
	}
	else
	{
		str.Format(_T("%d"), m_sTime);
	}
	
	dc.TextOut(54, 3, str);
	dc.SetTextColor(clr);
}

BOOL CTimeViewer::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	CPaintDC dc(this);
	CRect rc;
	GetWindowRect(&rc);
	CBrush brush(RGB(0, 0, 0));
	CRect rect(0, 0, rc.Width() - 1, rc.Height() - 1);
	dc.FillRect(&rect,&brush);
	return true;
	//return CWnd::OnEraseBkgnd(pDC);
}

void CTimeViewer::Pause(void)
{
	KillTimer(1);
}

void CTimeViewer::Resume(void)
{
	SetTimer(1, 1000, NULL);
}

void CTimeViewer::SetZero(void)
{
	KillTimer(1);
	m_sTime = 0;
	m_mTime = 0;
	m_hTime = 0;

	CClientDC dc(this);
	CRect rc;
	GetWindowRect(&rc);
	CBrush brush(RGB(0, 0, 0));
	CRect rect(0, 0, rc.Width(), rc.Height());
	dc.FillRect(&rect,&brush);
	COLORREF clr = dc.SetTextColor(RGB(0, 255, 0));
	dc.SetBkMode(TRANSPARENT);

	dc.TextOut(25, 3, _T(":"));

	dc.TextOut(48, 3, _T(":"));


	CString str;
	str.Format(_T("0%d"), m_hTime);
	

	dc.TextOut(8, 3, str);
	str.Format(_T("0%d"), m_mTime);

	dc.TextOut(31, 3, str);
	str.Format(_T("0%d"), m_sTime);

	dc.TextOut(54, 3, str);
	dc.SetTextColor(clr);
}

void CTimeViewer::Start(void)
{
	SetTimer(1, 1000, NULL);
}

void CTimeViewer::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	m_sTime ++;
	if(m_sTime == 60)
	{
		m_sTime = 0;
		m_mTime ++;
		if(m_mTime == 60)
		{
			m_hTime ++;
			SetSecond();
			SetHour();
			SetMinute();
		}
		else
		{
			SetMinute();
			SetSecond();
		}
	}
	else
	{
		SetSecond();
	}
	CWnd::OnTimer(nIDEvent);
}

void CTimeViewer::SetSecond(void)
{
	CClientDC dc(this);
	CBrush brush(RGB(0, 0, 0));
	//dc.TextOut(54, 3, _T("00"));
	CRect rc(54, 0, 70, 20);
	dc.FillRect(&rc, &brush);
	CString str;
	if(m_sTime < 10)
	{
		str.Format(_T("0%d"), m_sTime);
	}
	else
	{
		str.Format(_T("%d"), m_sTime);
	}
	COLORREF clr = dc.SetTextColor(RGB(0, 255, 0));
	dc.SetBkMode(TRANSPARENT);
	dc.TextOut(54, 3, str);
	dc.SetTextColor(clr);
}

void CTimeViewer::SetMinute(void)
{
	CClientDC dc(this);
	CBrush brush(RGB(0, 0, 0));
	//dc.TextOut(54, 3, _T("00"));
	CRect rc(31, 0, 47, 20);
	dc.FillRect(&rc, &brush);
	CString str;
	if(m_mTime < 10)
	{
		str.Format(_T("0%d"), m_mTime);
	}
	else
	{
		str.Format(_T("%d"), m_mTime);
	}
	COLORREF clr = dc.SetTextColor(RGB(0, 255, 0));
	dc.SetBkMode(TRANSPARENT);
	dc.TextOut(31, 3, str);
	dc.SetTextColor(clr);
}

void CTimeViewer::SetHour(void)
{
	CClientDC dc(this);
	CBrush brush(RGB(0, 0, 0));
	//dc.TextOut(54, 3, _T("00"));
	CRect rc(8, 0, 24, 20);
	dc.FillRect(&rc, &brush);
	CString str;
	if(m_hTime < 10)
	{
		str.Format(_T("0%d"), m_hTime);
	}
	else
	{
		str.Format(_T("%d"), m_hTime);
	}
	COLORREF clr = dc.SetTextColor(RGB(0, 255, 0));
	dc.SetBkMode(TRANSPARENT);
	dc.TextOut(8, 3, str);
	dc.SetTextColor(clr);
}
