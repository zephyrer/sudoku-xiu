#include "StdAfx.h"
#include "RecViewer.h"


#define BITMAPVIEWER_CLASSNAME    _T("MFCRecViewerCtrl")  // Window class name


CRecViewer::CRecViewer()
: m_bMouseTrack(true)
, m_colorBkgnd(RGB(255, 255, 255))
, m_colorSel(RGB(255, 0, 0))
, m_bModel(true)
, m_colorFont(RGB(0, 0, 0))
, m_num(0)
, m_selectNum(0)
, m_colorSegment(RGB(0, 0, 0))
{
	for(int i = 0;i < 9;i ++)
	{
		m_bNum[i] = true;
	}
	RegisterWindowClass();
}

BOOL CRecViewer::RegisterWindowClass()
{
	WNDCLASS wndcls;
	HINSTANCE hInst = AfxGetInstanceHandle();

	if (!(::GetClassInfo(hInst, BITMAPVIEWER_CLASSNAME, &wndcls)))
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
		wndcls.lpszClassName    = BITMAPVIEWER_CLASSNAME;

		if (!AfxRegisterClass(&wndcls))
		{
			AfxThrowResourceException();
			return FALSE;
		}
	}

	return TRUE;
}


CRecViewer::~CRecViewer(void)
{
}

BEGIN_MESSAGE_MAP(CRecViewer, CWnd)
	ON_WM_MOUSEMOVE()
	//ON_WM_MOUSELEAVE()
//	ON_WM_PAINT()
	//ON_WM_MOUSEHOVER()
	//ON_WM_MOUSELEAVE()
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSELEAVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()



void CRecViewer::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_bMouseTrack)    //若允许追踪，则。
	{
		TRACKMOUSEEVENT csTME;
		csTME.cbSize = sizeof(csTME);
		csTME.dwFlags = TME_LEAVE|TME_HOVER;
		csTME.hwndTrack = m_hWnd;//指定要追踪的窗口
		csTME.dwHoverTime = 1;  //鼠标在按钮上停留超过10ms，才认为状态为HOVER
		::_TrackMouseEvent(&csTME); //开启Windows的WM_MOUSELEAVE，WM_MOUSEHOVER事件支持
		m_bMouseTrack=FALSE;   //若已经追踪，则停止追踪
	}

	if(!m_bModel && m_num == 0)
	{
		if(m_bNum[0] && point.x >= 3 && point.y <= 14 && point.x <= 12 && point.y >= 3)
		{
			m_bMouseTrack=TRUE;
			DrawSel();
			DrawSegment(0);
			m_selectNum = 1;
			return;
		}
		if(m_bNum[1] && point.x >= 17 && point.y <= 14 && point.x <= 26 && point.y >= 3)
		{
			m_bMouseTrack=TRUE;
			DrawSel();
			DrawSegment(1);
			m_selectNum = 2;
			return;
		}
		if(m_bNum[2] && point.x >= 31 && point.y <= 14 && point.x <= 40 && point.y >= 3)
		{
			m_bMouseTrack=TRUE;
			DrawSel();
			DrawSegment(2);
			m_selectNum = 3;
			return;
		}
		if(m_bNum[3] && point.x >= 3 && point.y <= 28 && point.x <= 12 && point.y >= 17)
		{
			m_bMouseTrack=TRUE;
			DrawSel();
			DrawSegment(3);
			m_selectNum = 4;
			return;
		}
		if(m_bNum[4] && point.x >= 17 && point.y <= 28 && point.x <= 26 && point.y >= 17)
		{
			m_bMouseTrack=TRUE;
			DrawSel();
			DrawSegment(4);
			m_selectNum = 5;
			return;
		}
		if(m_bNum[5] && point.x >= 31 && point.y <= 28 && point.x <= 40 && point.y >= 17)
		{
			m_bMouseTrack=TRUE;
			DrawSel();
			DrawSegment(5);
			m_selectNum = 6;
			return;
		}
		if(m_bNum[6] && point.x >= 3 && point.y <= 42 && point.x <= 12 && point.y >= 31)
		{
			m_bMouseTrack=TRUE;
			DrawSel();
			DrawSegment(6);
			m_selectNum = 7;
			return;
		}
		if(m_bNum[7] && point.x >= 17 && point.y <= 42 && point.x <= 26 && point.y >= 31)
		{
			m_bMouseTrack=TRUE;
			DrawSel();
			DrawSegment(7);
			m_selectNum = 8;
			return;
		}
		if(m_bNum[8] && point.x >= 31 && point.y <= 42 && point.x <= 40 && point.y >= 31)
		{
			m_bMouseTrack=TRUE;
			DrawSel();
			DrawSegment(8);
			m_selectNum = 9;
			return;
		}

		m_selectNum = 0;
		EraseSegment();
		m_bMouseTrack=FALSE;
		DrawSel();
	}

	CWnd::OnMouseMove(nFlags, point);
}


void CRecViewer::DrawSel(void)
{
	CPen pen;
	if(!m_bMouseTrack)
	{
		pen.CreatePen(PS_SOLID, 1, m_colorSel);
	}
	else
	{
		pen.CreatePen(PS_SOLID, 1, m_colorBkgnd);
	}

	CClientDC dc(this);
	CRect rc;
	GetWindowRect(&rc);
	CPen *pOldPen = dc.SelectObject(&pen);

	dc.MoveTo(CPoint(1, 1));
	dc.LineTo(CPoint(rc.Width() - 2, 1));
	dc.LineTo(CPoint(rc.Width() - 2, rc.Height() - 2));

	dc.LineTo(CPoint(1, rc.Height() - 2));
	dc.LineTo(CPoint(1, 1));
	dc.SelectObject(pOldPen);

}


void CRecViewer::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	if(!m_bMouseTrack)
	{
		GetParent()->SendMessage(WM_USER + 1, GetDlgCtrlID(), (LPARAM) m_hWnd);
		//GetParent()->SendMessage(WM_COMMAND, MAKEWPARAM(GetDlgCtrlID(), BN_CLICKED), (LPARAM) m_hWnd);
		DrawSel();
	}
	CWnd::OnMouseHover(nFlags, point);
}

void CRecViewer::OnMouseLeave()
{
	// TODO: Add your message handler code here and/or call default
	m_bMouseTrack=TRUE;
	DrawSel();
	if(!m_bModel && m_num == 0)
		EraseSegment();	//Fear that the segment doesn't erase
	CWnd::OnMouseLeave();
}

COLORREF CRecViewer::GetBckColor(void) const
{
	return m_colorBkgnd;
}

void CRecViewer::SetBckColor(const COLORREF color)
{
	m_colorBkgnd = color;
	CClientDC dc(this);
	CRect rc;
	GetWindowRect(&rc);
	CBrush brush(m_colorBkgnd);
	CRect rect(1, 1, rc.Width(), rc.Height());
	dc.FillRect(&rect,&brush);

	if(!m_bMouseTrack)
	{
		DrawSel();
	}

	if(m_num != 0)
	{
		CFont font;
		font.CreatePointFont(300, _T("Aharoni"), NULL);
		dc.SelectObject(&font);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(m_colorFont);
		CString str;
		str.Format(_T("%d"), m_num);
		dc.TextOut(14, 3, str);
	}
	else if(!m_bModel)
	{
		DrawSegmentNum();
	}
}


void CRecViewer::SetNum(const int num)
{
	m_colorFont = RGB(0, 0, 0);
	m_num = num;
	CClientDC dc(this);
	CRect rc;
	GetWindowRect(&rc);
	CBrush brush(m_colorBkgnd);
	CRect rect(1, 1, rc.Width(), rc.Height());
	dc.FillRect(&rect, &brush);

	if(m_num != 0)
	{
		CFont font;
		font.CreatePointFont(300, _T("Aharoni"), NULL);
		dc.SelectObject(&font);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(RGB(0, 0, 0));
		CString str;
		str.Format(_T("%d"), num);
		dc.TextOut(14, 3, str);
	}
	else
	{
		for(int i = 0;i < 9;i ++)
		{
			m_bNum[i] = true;
		}
		if(!m_bModel)
			DrawSegmentNum();
	}

	if(!m_bMouseTrack)
	{
		DrawSel();
	}
}

void CRecViewer::SetNum(const int num, const COLORREF color)
{
	m_colorFont = color;
	m_num = num;
	CClientDC dc(this);
	CRect rc;
	GetWindowRect(&rc);
	CBrush brush(m_colorBkgnd);
	CRect rect(1, 1, rc.Width(), rc.Height());
	dc.FillRect(&rect, &brush);

	if(m_num != 0)
	{
		CFont font;
		font.CreatePointFont(300, _T("Aharoni"), NULL);
		dc.SelectObject(&font);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(color);
		CString str;
		str.Format(_T("%d"), num);
		dc.TextOut(14, 3, str);
	}
	else
	{
		for(int i = 0;i < 9;i ++)
		{
			m_bNum[i] = true;
		}
	}

	if(!m_bMouseTrack)
	{
		DrawSel();
	}
}
void CRecViewer::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if(m_num == 0)
	{
		if(m_bModel)
		{
			GetParent()->SendMessage(WM_USER + 2, GetDlgCtrlID(), 0);
		}
		else if(m_selectNum != 0)
		{
			GetParent()->SendMessage(WM_USER + 3, GetDlgCtrlID(), m_selectNum);
		}
	}
	else if(m_bModel)
	{
		GetParent()->SendMessage(WM_USER + 2, GetDlgCtrlID(), 0);
	}
	CWnd::OnLButtonDown(nFlags, point);
}


void CRecViewer::DrawSegment(const int num)
{
	switch(num)
	{
	case 0:
		{
			CClientDC dc(this);
			CPen pen(PS_SOLID, 1, m_colorSel);
			CPen *pOldPen = dc.SelectObject(&pen);

			dc.MoveTo(CPoint(3, 3));
			dc.LineTo(CPoint(3, 14));
			dc.LineTo(CPoint(12, 14));

			dc.LineTo(CPoint(12, 3));
			dc.LineTo(CPoint(3, 3));
			dc.SelectObject(pOldPen);
			break;
		}
	case 1:
		{
			CClientDC dc(this);
			CPen pen(PS_SOLID, 1, m_colorSel);
			CPen *pOldPen = dc.SelectObject(&pen);

			dc.MoveTo(CPoint(17, 3));
			dc.LineTo(CPoint(17, 14));
			dc.LineTo(CPoint(26, 14));

			dc.LineTo(CPoint(26, 3));
			dc.LineTo(CPoint(17, 3));
			dc.SelectObject(pOldPen);
			break;
		}
	case 2:
		{
			CClientDC dc(this);
			CPen pen(PS_SOLID, 1, m_colorSel);
			CPen *pOldPen = dc.SelectObject(&pen);

			dc.MoveTo(CPoint(31, 3));
			dc.LineTo(CPoint(31, 14));
			dc.LineTo(CPoint(40, 14));

			dc.LineTo(CPoint(40, 3));
			dc.LineTo(CPoint(31, 3));
			dc.SelectObject(pOldPen);
			break;
		}
	case 3:
		{
			CClientDC dc(this);
			CPen pen(PS_SOLID, 1, m_colorSel);
			CPen *pOldPen = dc.SelectObject(&pen);

			dc.MoveTo(CPoint(3, 17));
			dc.LineTo(CPoint(3, 28));
			dc.LineTo(CPoint(12, 28));

			dc.LineTo(CPoint(12, 17));
			dc.LineTo(CPoint(3, 17));
			dc.SelectObject(pOldPen);
			break;
		}
	case 4:
		{
			CClientDC dc(this);
			CPen pen(PS_SOLID, 1, m_colorSel);
			CPen *pOldPen = dc.SelectObject(&pen);

			dc.MoveTo(CPoint(17, 17));
			dc.LineTo(CPoint(17, 28));
			dc.LineTo(CPoint(26, 28));

			dc.LineTo(CPoint(26, 17));
			dc.LineTo(CPoint(17, 17));
			dc.SelectObject(pOldPen);
			break;
		}
	case 5:
		{
			CClientDC dc(this);
			CPen pen(PS_SOLID, 1, m_colorSel);
			CPen *pOldPen = dc.SelectObject(&pen);

			dc.MoveTo(CPoint(31, 17));
			dc.LineTo(CPoint(31, 28));
			dc.LineTo(CPoint(40, 28));

			dc.LineTo(CPoint(40, 17));
			dc.LineTo(CPoint(31, 17));
			dc.SelectObject(pOldPen);
			break;
		}
	case 6:
		{
			CClientDC dc(this);
			CPen pen(PS_SOLID, 1, m_colorSel);
			CPen *pOldPen = dc.SelectObject(&pen);

			dc.MoveTo(CPoint(3, 31));
			dc.LineTo(CPoint(3, 42));
			dc.LineTo(CPoint(12, 42));

			dc.LineTo(CPoint(12, 31));
			dc.LineTo(CPoint(3, 31));
			dc.SelectObject(pOldPen);
			break;
		}
	case 7:
		{
			CClientDC dc(this);
			CPen pen(PS_SOLID, 1, m_colorSel);
			CPen *pOldPen = dc.SelectObject(&pen);

			dc.MoveTo(CPoint(17, 31));
			dc.LineTo(CPoint(17, 42));
			dc.LineTo(CPoint(26, 42));

			dc.LineTo(CPoint(26, 31));
			dc.LineTo(CPoint(17, 31));
			dc.SelectObject(pOldPen);
			break;
		}
	case 8:
		{
			CClientDC dc(this);
			CPen pen(PS_SOLID, 1, m_colorSel);

			CPen *pOldPen = dc.SelectObject(&pen);

			dc.MoveTo(CPoint(31, 31));
			dc.LineTo(CPoint(31, 42));
			dc.LineTo(CPoint(40, 42));

			dc.LineTo(CPoint(40, 31));
			dc.LineTo(CPoint(31, 31));
			dc.SelectObject(pOldPen);
			break;
		}
	}
}
void CRecViewer::SetModel(bool model)
{
	m_bModel = model;
	if(true == model)
	{
		if(m_num == 0)
		{
			CClientDC dc(this);
			CRect rc;
			GetWindowRect(&rc);
			CBrush brush(m_colorBkgnd);
			CRect rect(1, 1, rc.Width(), rc.Height());
			dc.FillRect(&rect, &brush);
		}
	}
	else
	{
		if(m_num == 0)
		{
			DrawSegmentNum();
		}
	}
}

void CRecViewer::DrawSegmentNum()
{
	if(m_bNum[0])
	{
		CClientDC dc(this);
		CFont font;
		font.CreatePointFont(90, _T(""), NULL);
		dc.SelectObject(&font);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(m_colorSegment);
		dc.TextOut(5, 3, _T("1"));
	}
	if(m_bNum[1])
	{
		CClientDC dc(this);
		CFont font;
		font.CreatePointFont(90, _T(""), NULL);
		dc.SelectObject(&font);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(m_colorSegment);
		dc.TextOut(19, 3, _T("2"));
	}
	if(m_bNum[2])
	{
		CClientDC dc(this);
		CFont font;
		font.CreatePointFont(90, _T(""), NULL);
		dc.SelectObject(&font);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(m_colorSegment);
		dc.TextOut(33, 3, _T("3"));
	}
	if(m_bNum[3])
	{
		CClientDC dc(this);
		CFont font;
		font.CreatePointFont(90, _T(""), NULL);
		dc.SelectObject(&font);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(m_colorSegment);
		dc.TextOut(5, 17, _T("4"));
	}
	if(m_bNum[4])
	{
		CClientDC dc(this);
		CFont font;
		font.CreatePointFont(90, _T(""), NULL);
		dc.SelectObject(&font);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(m_colorSegment);
		dc.TextOut(19, 17, _T("5"));
	}
	if(m_bNum[5])
	{
		CClientDC dc(this);
		CFont font;
		font.CreatePointFont(90, _T(""), NULL);
		dc.SelectObject(&font);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(m_colorSegment);
		dc.TextOut(33, 17, _T("6"));
	}
	if(m_bNum[6])
	{
		CClientDC dc(this);
		CFont font;
		font.CreatePointFont(90, _T(""), NULL);
		dc.SelectObject(&font);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(m_colorSegment);
		dc.TextOut(5, 31, _T("7"));
	}
	if(m_bNum[7])
	{
		CClientDC dc(this);
		CFont font;
		font.CreatePointFont(90, _T(""), NULL);
		dc.SelectObject(&font);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(m_colorSegment);
		dc.TextOut(19, 31, _T("8"));
	}
	if(m_bNum[8])
	{
		CClientDC dc(this);
		CFont font;
		font.CreatePointFont(90, _T(""), NULL);
		dc.SelectObject(&font);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(m_colorSegment);
		dc.TextOut(33, 31, _T("9"));
	}
}

void CRecViewer::EraseSegmentNum(const int num)
{
	switch(num)
	{
	case 1:
		{
			CClientDC dc(this);
			CBrush brush(m_colorBkgnd);
			CRect rect(3, 3, 12, 14);
			dc.FillRect(&rect, &brush);
			break;
		}
	case 2:
		{
			CClientDC dc(this);
			CBrush brush(m_colorBkgnd);
			CRect rect(17, 3, 26, 14);
			dc.FillRect(&rect, &brush);
			break;
		}
	case 3:
		{
			CClientDC dc(this);
			CBrush brush(m_colorBkgnd);
			CRect rect(31, 3, 40, 14);
			dc.FillRect(&rect, &brush);

			break;
		}
	case 4:
		{
			CClientDC dc(this);
			CBrush brush(m_colorBkgnd);
			CRect rect(3, 17, 12, 28);
			dc.FillRect(&rect, &brush);

			break;
		}
	case 5:
		{
			CClientDC dc(this);
			CBrush brush(m_colorBkgnd);
			CRect rect(17, 17, 26, 28);
			dc.FillRect(&rect, &brush);
			break;
		}
	case 6:
		{
			CClientDC dc(this);
			CBrush brush(m_colorBkgnd);
			CRect rect(31, 17, 40, 28);
			dc.FillRect(&rect, &brush);

			break;
		}
	case 7:
		{
			CClientDC dc(this);
			CBrush brush(m_colorBkgnd);
			CRect rect(3, 31, 12, 42);
			dc.FillRect(&rect, &brush);

			break;
		}
	case 8:
		{
			CClientDC dc(this);
			CBrush brush(m_colorBkgnd);
			CRect rect(17, 31, 26, 42);
			dc.FillRect(&rect, &brush);

			break;
		}
	case 9:
		{
			CClientDC dc(this);
			CBrush brush(m_colorBkgnd);
			CRect rect(31, 31, 40, 42);
			dc.FillRect(&rect, &brush);

			break;
		}
	}
}

BOOL CRecViewer::OnEraseBkgnd(CDC* pDC)
{	
	CDC dcCompatible;
	dcCompatible.CreateCompatibleDC(pDC);
	CPen pen(PS_SOLID, 1, RGB(255, 255, 255));
	CPen *pOldPen = dcCompatible.SelectObject(&pen);
	CRect rc;
	GetWindowRect(&rc);
	dcCompatible.MoveTo(CPoint(rc.Width(), 0));
	dcCompatible.LineTo(CPoint(0, 0));
	dcCompatible.LineTo(CPoint(0, rc.Height()));
	dcCompatible.SelectObject(pOldPen);
	CBrush brush(m_colorBkgnd);
	CRect rect(1, 1, rc.Width(), rc.Height());
	dcCompatible.FillRect(&rect,&brush);
	pDC->BitBlt(0, 0, rc.Width(), rc.Height(), &dcCompatible, 0, 0, SRCCOPY);
	return true;
	//return CWnd::OnEraseBkgnd(pDC);
}

void CRecViewer::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	CRect rc;
	GetWindowRect(&rc);
	CBrush brush(m_colorBkgnd);
	CRect rect(1, 1, rc.Width(), rc.Height());
	dc.FillRect(&rect,&brush);
	if(m_num != 0)
	{
		CFont font;
		font.CreatePointFont(300, _T("Aharoni"), NULL);
		dc.SelectObject(&font);
		dc.SetBkMode(TRANSPARENT);
		dc.SetTextColor(m_colorFont);
		CString str;
		str.Format(_T("%d"), m_num);
		dc.TextOut(14, 3, str);
	}
	else if(!m_bModel)
	{
		DrawSegmentNum();
	}
}

void CRecViewer::EraseSegment(void)
{
	CClientDC dc(this);
	CPen pen(PS_SOLID, 1, m_colorBkgnd);
	CPen *pOldPen = dc.SelectObject(&pen);

	dc.MoveTo(CPoint(3, 3));
	dc.LineTo(CPoint(3, 14));
	dc.LineTo(CPoint(12, 14));

	dc.LineTo(CPoint(12, 3));
	dc.LineTo(CPoint(3, 3));

	dc.MoveTo(CPoint(17, 3));
	dc.LineTo(CPoint(17, 14));
	dc.LineTo(CPoint(26, 14));

	dc.LineTo(CPoint(26, 3));
	dc.LineTo(CPoint(17, 3));

	dc.MoveTo(CPoint(31, 3));
	dc.LineTo(CPoint(31, 14));
	dc.LineTo(CPoint(40, 14));

	dc.LineTo(CPoint(40, 3));
	dc.LineTo(CPoint(31, 3));

	dc.MoveTo(CPoint(3, 17));
	dc.LineTo(CPoint(3, 28));
	dc.LineTo(CPoint(12, 28));

	dc.LineTo(CPoint(12, 17));
	dc.LineTo(CPoint(3, 17));

	dc.MoveTo(CPoint(17, 17));
	dc.LineTo(CPoint(17, 28));
	dc.LineTo(CPoint(26, 28));

	dc.LineTo(CPoint(26, 17));
	dc.LineTo(CPoint(17, 17));

	dc.MoveTo(CPoint(31, 17));
	dc.LineTo(CPoint(31, 28));
	dc.LineTo(CPoint(40, 28));

	dc.LineTo(CPoint(40, 17));
	dc.LineTo(CPoint(31, 17));

	dc.MoveTo(CPoint(3, 31));
	dc.LineTo(CPoint(3, 42));
	dc.LineTo(CPoint(12, 42));

	dc.LineTo(CPoint(12, 31));
	dc.LineTo(CPoint(3, 31));

	dc.MoveTo(CPoint(17, 31));
	dc.LineTo(CPoint(17, 42));
	dc.LineTo(CPoint(26, 42));

	dc.LineTo(CPoint(26, 31));
	dc.LineTo(CPoint(17, 31));

	dc.MoveTo(CPoint(31, 31));
	dc.LineTo(CPoint(31, 42));
	dc.LineTo(CPoint(40, 42));

	dc.LineTo(CPoint(40, 31));
	dc.LineTo(CPoint(31, 31));
	dc.SelectObject(pOldPen);
}

int CRecViewer::GetNum(void) const
{
	return m_num;
}
void CRecViewer::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	GetParent()->SendMessage(WM_USER + 4, GetDlgCtrlID(), 0);
	CWnd::OnRButtonDown(nFlags, point);
}

bool CRecViewer::AddNum(const int num)
{
	if(m_bNum[num - 1])
	{
		return false;
	}

	m_bNum[num - 1] = true;
	DrawSegmentNum();
	return true;
}

bool CRecViewer::RemoveNum(const int num)
{
	if(!m_bNum[num - 1])
	{
		return false;
	}

	m_bNum[num - 1] = false;
	EraseSegmentNum(num);
	return true;
}

void CRecViewer::SetSegmentColor(const COLORREF color)
{
	m_colorSegment = color;
}