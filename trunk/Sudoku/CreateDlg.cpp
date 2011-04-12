// CreateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Sudoku.h"
#include "CreateDlg.h"
#include "NodeTable.h"


// CCreateDlg dialog

IMPLEMENT_DYNAMIC(CCreateDlg, CDialog)

CCreateDlg::CCreateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCreateDlg::IDD, pParent)
{

}

CCreateDlg::~CCreateDlg()
{
}

void CCreateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	for(int i = 0;i < 81;i ++)
	{
		DDX_Control(pDX, IDC_CUSTOM1 + i, m_recViewer[i]);
	}
}


BEGIN_MESSAGE_MAP(CCreateDlg, CDialog)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON6, &CCreateDlg::OnBnClickedButton6)
	ON_MESSAGE(WM_USER + 3, OnRecViewerClickedMessage)
	ON_MESSAGE(WM_USER + 4, OnRecViewerClearMessage)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CCreateDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_CHECK, &CCreateDlg::OnBnClickedButtonCheck)
	ON_BN_CLICKED(IDC_BUTTON_BEGIN, &CCreateDlg::OnBnClickedButtonBegin)
END_MESSAGE_MAP()


// CCreateDlg message handlers

void CCreateDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages

	/*
	CRect rcGlassArea;
	GetClientRect(rcGlassArea);
	dc.FillSolidRect ( rcGlassArea, RGB(0,0,0) );
	*/

	
	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);   
	CBitmap   bmpBackground;   
	bmpBackground.LoadBitmap(IDB_BITMAP_TABLE); 
	//IDB_BITMAP是你自己的图对应的ID   
	BITMAP   bitmap;   
	bmpBackground.GetBitmap(&bitmap);   
	CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground);
	dc.SetBkMode ( TRANSPARENT );

	dc.StretchBlt(7, 7, bitmap.bmWidth, bitmap.bmHeight,&dcMem,0,0,   
		bitmap.bmWidth,bitmap.bmHeight,SRCCOPY); 
	


	/*
	CBitmap bmp;
		BITMAPINFO dib = {0};
	
		dib.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		dib.bmiHeader.biWidth = 466;
		dib.bmiHeader.biHeight = -462;
		dib.bmiHeader.biPlanes = 1;
		dib.bmiHeader.biBitCount = 32;
		dib.bmiHeader.biCompression = BI_RGB;
	
		bmp.CreateDIBSection(dc, &dib, DIB_RGB_COLORS,
			NULL, NULL, 0);*/
	


	//-------------------------
	
	/*
	CRect rect;
	GetClientRect(&rect);
	CBrush brush(RGB(0,0,0));
	GetDC()->FillRect(&rect,&brush);
	*/
	/*
	
	DTTOPTS dto = { sizeof(DTTOPTS) };
	dto.dwFlags = DTT_COMPOSITED | DTT_GLOWSIZE;
	dto.iGlowSize = 20;
	HTHEME htheme = OpenThemeData(m_hWnd,L"globals");
	if(htheme==NULL)
		return;

	OSVERSIONINFO osvi;
	ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&osvi);
	if(osvi.dwMajorVersion < 6)
		return;
	
	
	CWindowDC wdc(this);
		CRect rt;
		GetWindowRect(&rt);
		CFont* pOldFont=wdc.SelectObject(&m_font);  
	
	
		DrawThemeTextEx (htheme,
			wdc.m_hDC,
			TEXT_CONTROLLABEL,
			0, 
			L"MFC is great with Aero",
			-1,
			DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_NOPREFIX,
			CRect(400,400,500,450), 
			&dto );
		wdc.SelectObject(pOldFont);
		
	*/
}

/*
#include <dwmapi.h>
#pragma comment (lib, "dwmapi.lib")
#pragma comment (lib, "UxTheme.lib")
*/

BOOL CCreateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	/*
	OSVERSIONINFO osvi;
	ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&osvi);
	
	if(osvi.dwMajorVersion >= 6)
	{
		MARGINS m = {-1};
		DwmExtendFrameIntoClientArea(m_hWnd, &m);
	}
	
	LOGFONT lf={0};
	GetFont()->GetLogFont(&lf);
	lf.lfHeight*=4;
	m_font.CreateFontIndirect(&lf);
	*/


	m_recViewer[0].MoveWindow(CRect(37, 32, 82, 77), true);
	m_recViewer[1].MoveWindow(CRect(83, 32, 128, 77), true);
	m_recViewer[2].MoveWindow(CRect(129, 32, 174, 77), true);
	m_recViewer[3].MoveWindow(CRect(177, 32, 222, 77), true);
	m_recViewer[4].MoveWindow(CRect(223, 32, 268, 77), true);
	m_recViewer[5].MoveWindow(CRect(269, 32, 314, 77), true);
	m_recViewer[6].MoveWindow(CRect(317, 32, 362, 77), true);
	m_recViewer[7].MoveWindow(CRect(363, 32, 408, 77), true);
	m_recViewer[8].MoveWindow(CRect(409, 32, 454, 77), true);
	m_recViewer[9].MoveWindow(CRect(37, 78, 82, 123), true);
	m_recViewer[10].MoveWindow(CRect(83, 78, 128, 123), true);
	m_recViewer[11].MoveWindow(CRect(129, 78, 174, 123), true);
	m_recViewer[12].MoveWindow(CRect(177, 78, 222, 123), true);
	m_recViewer[13].MoveWindow(CRect(223, 78, 268, 123), true);
	m_recViewer[14].MoveWindow(CRect(269, 78, 314, 123), true);
	m_recViewer[15].MoveWindow(CRect(317, 78, 362, 123), true);
	m_recViewer[16].MoveWindow(CRect(363, 78, 408, 123), true);
	m_recViewer[17].MoveWindow(CRect(409, 78, 454, 123), true);
	m_recViewer[18].MoveWindow(CRect(37, 124, 82, 169), true);
	m_recViewer[19].MoveWindow(CRect(83, 124, 128, 169), true);
	m_recViewer[20].MoveWindow(CRect(129, 124, 174, 169), true);
	m_recViewer[21].MoveWindow(CRect(177, 124, 222, 169), true);
	m_recViewer[22].MoveWindow(CRect(223, 124, 268, 169), true);
	m_recViewer[23].MoveWindow(CRect(269, 124, 314, 169), true);
	m_recViewer[24].MoveWindow(CRect(317, 124, 362, 169), true);
	m_recViewer[25].MoveWindow(CRect(363, 124, 408, 169), true);
	m_recViewer[26].MoveWindow(CRect(409, 124, 454, 169), true);

	m_recViewer[27].MoveWindow(CRect(37, 172, 82, 217), true);
	m_recViewer[28].MoveWindow(CRect(83, 172, 128, 217), true);
	m_recViewer[29].MoveWindow(CRect(129, 172, 174, 217), true);
	m_recViewer[30].MoveWindow(CRect(177, 172, 222, 217), true);
	m_recViewer[31].MoveWindow(CRect(223, 172, 268, 217), true);
	m_recViewer[32].MoveWindow(CRect(269, 172, 314, 217), true);
	m_recViewer[33].MoveWindow(CRect(317, 172, 362, 217), true);
	m_recViewer[34].MoveWindow(CRect(363, 172, 408, 217), true);
	m_recViewer[35].MoveWindow(CRect(409, 172, 454, 217), true);
	m_recViewer[36].MoveWindow(CRect(37, 218, 82, 263), true);
	m_recViewer[37].MoveWindow(CRect(83, 218, 128, 263), true);
	m_recViewer[38].MoveWindow(CRect(129, 218, 174, 263), true);
	m_recViewer[39].MoveWindow(CRect(177, 218, 222, 263), true);
	m_recViewer[40].MoveWindow(CRect(223, 218, 268, 263), true);
	m_recViewer[41].MoveWindow(CRect(269, 218, 314, 263), true);
	m_recViewer[42].MoveWindow(CRect(317, 218, 362, 263), true);
	m_recViewer[43].MoveWindow(CRect(363, 218, 408, 263), true);
	m_recViewer[44].MoveWindow(CRect(409, 218, 454, 263), true);
	m_recViewer[45].MoveWindow(CRect(37, 264, 82, 309), true);
	m_recViewer[46].MoveWindow(CRect(83, 264, 128, 309), true);
	m_recViewer[47].MoveWindow(CRect(129, 264, 174, 309), true);
	m_recViewer[48].MoveWindow(CRect(177, 264, 222, 309), true);
	m_recViewer[49].MoveWindow(CRect(223, 264, 268, 309), true);
	m_recViewer[50].MoveWindow(CRect(269, 264, 314, 309), true);
	m_recViewer[51].MoveWindow(CRect(317, 264, 362, 309), true);
	m_recViewer[52].MoveWindow(CRect(363, 264, 408, 309), true);
	m_recViewer[53].MoveWindow(CRect(409, 264, 454, 309), true);

	m_recViewer[54].MoveWindow(CRect(37, 312, 82, 357), true);
	m_recViewer[55].MoveWindow(CRect(83, 312, 128, 357), true);
	m_recViewer[56].MoveWindow(CRect(129, 312, 174, 357), true);
	m_recViewer[57].MoveWindow(CRect(177, 312, 222, 357), true);
	m_recViewer[58].MoveWindow(CRect(223, 312, 268, 357), true);
	m_recViewer[59].MoveWindow(CRect(269, 312, 314, 357), true);
	m_recViewer[60].MoveWindow(CRect(317, 312, 362, 357), true);
	m_recViewer[61].MoveWindow(CRect(363, 312, 408, 357), true);
	m_recViewer[62].MoveWindow(CRect(409, 312, 454, 357), true);
	m_recViewer[63].MoveWindow(CRect(37, 358, 82, 403), true);
	m_recViewer[64].MoveWindow(CRect(83, 358, 128, 403), true);
	m_recViewer[65].MoveWindow(CRect(129, 358, 174, 403), true);
	m_recViewer[66].MoveWindow(CRect(177, 358, 222, 403), true);
	m_recViewer[67].MoveWindow(CRect(223, 358, 268, 403), true);
	m_recViewer[68].MoveWindow(CRect(269, 358, 314, 403), true);
	m_recViewer[69].MoveWindow(CRect(317, 358, 362, 403), true);
	m_recViewer[70].MoveWindow(CRect(363, 358, 408, 403), true);
	m_recViewer[71].MoveWindow(CRect(409, 358, 454, 403), true);
	m_recViewer[72].MoveWindow(CRect(37, 404, 82, 449), true);
	m_recViewer[73].MoveWindow(CRect(83, 404, 128, 449), true);
	m_recViewer[74].MoveWindow(CRect(129, 404, 174, 449), true);
	m_recViewer[75].MoveWindow(CRect(177, 404, 222, 449), true);
	m_recViewer[76].MoveWindow(CRect(223, 404, 268, 449), true);
	m_recViewer[77].MoveWindow(CRect(269, 404, 314, 449), true);
	m_recViewer[78].MoveWindow(CRect(317, 404, 362, 449), true);
	m_recViewer[79].MoveWindow(CRect(363, 404, 408, 449), true);
	m_recViewer[80].MoveWindow(CRect(409, 404, 454, 449), true);

	for(int i = 0;i < 81;i ++)
	{
		m_recViewer[i].SetModel(false);
		m_recViewer[i].SetSegmentColor(RGB(50, 180, 1));
	}

	for(int i = 0;i < 3;i ++)
	{
		for(int j = 0;j < 3;j ++)
		{
			m_recViewer[i * 9 + j + 3].SetBckColor(RGB(187, 187, 255));
			m_recViewer[i * 9 + j + 27].SetBckColor(RGB(187, 187, 255));
			m_recViewer[i * 9 + j + 33].SetBckColor(RGB(187, 187, 255));
			m_recViewer[i * 9 + j + 57].SetBckColor(RGB(187, 187, 255));
		}
	}

	

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CCreateDlg::OnBnClickedButton6()
{
	// TODO: Add your control notification handler code here
	OnOK();
}

LRESULT CCreateDlg::OnRecViewerClickedMessage(WPARAM wParam, LPARAM lParam)
{
	m_recViewer[wParam - IDC_CUSTOM1].SetNum(lParam, RGB(0, 0, 255));
	int baseRow = (wParam - IDC_CUSTOM1) / 9;
	int baseCol = (wParam - IDC_CUSTOM1) % 9;
	baseRow = baseRow / 3 * 3;
	baseCol = baseCol / 3 * 3;
	for(int i = 0;i < 3;i ++)
	{
		for(int j = 0;j < 3;j ++)
		{
			if (m_recViewer[(baseRow + i) * 9 + baseCol + j].GetNum() == 0)
			{
				m_recViewer[(baseRow + i) * 9 + baseCol + j].RemoveNum(lParam);
			}
		}
	}
	int baseIndex = (wParam - IDC_CUSTOM1) / 9 * 9;
	for(int i = 0;i < 9;i ++)
	{
		if(m_recViewer[baseIndex + i].GetNum() == 0)
		{
			m_recViewer[baseIndex + i].RemoveNum(lParam);
		}
	}

	baseIndex = (wParam - IDC_CUSTOM1) % 9;
	for(int i = 0;i < 81;i += 9)
	{
		if(m_recViewer[baseIndex + i].GetNum() == 0)
		{
			m_recViewer[baseIndex + i].RemoveNum(lParam);
		}
	}

	return 0;
}

LRESULT CCreateDlg::OnRecViewerClearMessage(WPARAM wParam, LPARAM lParam)
{
	if(m_recViewer[wParam - IDC_CUSTOM1].GetNum() == 0)
	{
		return 0;
	}

	m_recViewer[wParam - IDC_CUSTOM1].SetNum(0);

	int baseRow = (wParam - IDC_CUSTOM1) / 9;
	int baseCol = (wParam - IDC_CUSTOM1) % 9;
	baseRow = baseRow / 3 * 3;
	baseCol = baseCol / 3 * 3;
	for(int i = 0;i < 3;i ++)
	{
		for(int j = 0;j < 3;j ++)
		{
			if (m_recViewer[(baseRow + i) * 9 + baseCol + j].GetNum() == 0)
			{
				CheckAddNum((baseRow + i) * 9 + baseCol + j);
			}
			else
			{
				m_recViewer[wParam - IDC_CUSTOM1].RemoveNum(m_recViewer[(baseRow + i) * 9 + baseCol + j].GetNum());
			}
		}
	}
	int baseIndex = (wParam - IDC_CUSTOM1) / 9 * 9;
	for(int i = 0;i < 9;i ++)
	{
		if(m_recViewer[baseIndex + i].GetNum() == 0)
		{
			CheckAddNum(baseIndex + i);
		}
		else
		{
			m_recViewer[wParam - IDC_CUSTOM1].RemoveNum(m_recViewer[baseIndex + i].GetNum());
		}
	}

	baseIndex = (wParam - IDC_CUSTOM1) % 9;
	for(int i = 0;i < 81;i += 9)
	{
		if(m_recViewer[baseIndex + i].GetNum() == 0)
		{
			CheckAddNum(baseIndex + i);
		}
		else
		{
			m_recViewer[wParam - IDC_CUSTOM1].RemoveNum(m_recViewer[baseIndex + i].GetNum());
		}
	}
	return 0;
}

void CCreateDlg::CheckAddNum(int id)
{
	for(int num = 1;num < 10;num ++)
	{
		int baseRow = id / 9;
		int baseCol = id % 9;
		baseRow = baseRow / 3 * 3;
		baseCol = baseCol / 3 * 3;
		for(int i = 0;i < 3;i ++)
		{
			for(int j = 0;j < 3;j ++)
			{
				if (m_recViewer[(baseRow + i) * 9 + baseCol + j].GetNum() == num)
				{
					goto Label;
				}
			}
		}
		int baseIndex = id / 9 * 9;
		for(int i = 0;i < 9;i ++)
		{
			if(m_recViewer[baseIndex + i].GetNum() == num)
			{
				goto Label;
			}
		}

		baseIndex = id % 9;
		for(int i = 0;i < 81;i += 9)
		{
			if(m_recViewer[baseIndex + i].GetNum() == num)
			{
				goto Label;
			}
		}
		m_recViewer[id].AddNum(num);
Label:;
	}
}
void CCreateDlg::OnBnClickedButtonClear()
{
	if(IDOK == MessageBox(_T("Are you sure to clear all?"), _T("Confirm"), MB_OKCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2))
	{
		for(int i = 0;i < 81;i ++)
		{
			m_recViewer[i].SetNum(0);
		}
	}
}

void CCreateDlg::OnBnClickedButtonCheck()
{
	int table[9][9];
	for(int i = 0;i < 9;i ++)
	{
		for(int j = 0;j < 9;j ++)
		{
			table[i][j] = m_recViewer[i * 9 + j].GetNum();
		}
	}

	CNodeTable nodeTable1;
	nodeTable1.initTable(table);
	int awrNum = nodeTable1.AwrNum();
	if(awrNum == 0)
	{
		MessageBox(_T("It has no answers"), _T("Wrong"), MB_OK | MB_ICONERROR);
	}
	else if(awrNum == 1)
	{
		if(IDOK == MessageBox(_T("It has only one answer\nStart game now?"), _T("Right"), MB_OKCANCEL | MB_ICONQUESTION))
		{
			int *num = new int[81];
			for(int i = 0;i < 9;i ++)
			{
				for(int j = 0;j < 9;j ++)
				{
					num[i * 9 + j] = table[i][j];
				}
			}
			GetParent()->PostMessage(WM_USER + 5, 0, (LPARAM) num);
			OnOK();
		}
	}
	else
	{
		MessageBox(_T("It has multiple answers"), _T("Wrong"), MB_OK | MB_ICONERROR);
	}
}

void CCreateDlg::OnBnClickedButtonBegin()
{
	int table[9][9];
	for(int i = 0;i < 9;i ++)
	{
		for(int j = 0;j < 9;j ++)
		{
			table[i][j] = m_recViewer[i * 9 + j].GetNum();
		}
	}

	CNodeTable nodeTable;
	nodeTable.initTable(table);
	int awrNum = nodeTable.AwrNum();
	if(awrNum == 0)
	{
		MessageBox(_T("It has no answers"), _T("Wrong"), MB_OK | MB_ICONERROR);
	}
	else if(awrNum == 1)
	{
		int *num = new int[81];
		for(int i = 0;i < 9;i ++)
		{
			for(int j = 0;j < 9;j ++)
			{
				num[i * 9 + j] = table[i][j];
			}
		}
		GetParent()->PostMessage(WM_USER + 5, 0, (LPARAM) num);
		OnOK();
	}
	else
	{
		if(IDOK == MessageBox(_T("It has multiple answers\nDo you want to continue?"), _T("Wrong"), MB_OKCANCEL | MB_ICONERROR | MB_DEFBUTTON2))
		{
			int *num = new int[81];
			for(int i = 0;i < 9;i ++)
			{
				for(int j = 0;j < 9;j ++)
				{
					num[i * 9 + j] = table[i][j];
				}
			}
			GetParent()->PostMessage(WM_USER + 5, 0, (LPARAM) num);
			OnOK();
		}
	}
}

