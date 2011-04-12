// KeyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Sudoku.h"
#include "KeyDlg.h"


// CKeyDlg dialog

IMPLEMENT_DYNAMIC(CKeyDlg, CDialog)

CKeyDlg::CKeyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKeyDlg::IDD, pParent)
{

}

CKeyDlg::CKeyDlg(CWnd* pParent, int num[9][9], bool isAnswer[81])
	: CDialog(CKeyDlg::IDD, pParent)
{
	
	for(int i = 0;i < 9;i ++)
	{
		for(int j = 0;j < 9;j ++)
		{
			m_num[i][j] = num[i][j];
		}
	}

	for(int i = 0;i < 81;i ++)
	{
		m_bIsAnswer[i] = isAnswer[i];
	}
	
}

CKeyDlg::~CKeyDlg()
{
}

void CKeyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CKeyDlg, CDialog)
//	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
END_MESSAGE_MAP()


void CKeyDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting

	CDC   dcMem;   
	dcMem.CreateCompatibleDC(&dc);   
	CBitmap   bmpTable;   
	bmpTable.LoadBitmap(IDB_BITMAP_KEY);   
	BITMAP   bitmap;
	bmpTable.GetBitmap(&bitmap);   
	CBitmap   *pbmpOld=dcMem.SelectObject(&bmpTable);   
	dc.StretchBlt(7,7,428,428,&dcMem,0,0,   
		bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);
	
	CFont font;
	font.CreatePointFont(300, _T("Aharoni"), NULL);
	dc.SelectObject(&font);
	dc.SetBkMode(TRANSPARENT);

	for(int i = 0;i < 9;i ++)
	{
		for(int j = 0;j < 9;j ++)
		{
			if(m_bIsAnswer[i * 9 + j])
			{
				dc.SetTextColor(RGB(0, 0, 255));
			}
			else
			{
				dc.SetTextColor(RGB(0, 0, 0));
			}
			
			int offsetX = 0;
			int offsetY = 0;
			if(i > 5)
			{
				offsetX += 4;
			}
			else if(i > 2)
			{
				offsetX += 2;
			}

			if(j > 5)
			{
				offsetY += 4;
			}
			else if(j > 2)
			{
				offsetY += 2;
			}
			CString str;
			str.Format(_T("%d"), m_num[i][j]);
			dc.TextOut(22 + j * 47 + offsetY, 12 + i * 47 + offsetX, str);
		}
	}
	
	/*
	dc.SetTextColor(RGB(0, 0, 255));
	dc.TextOut(0, 0, _T("sj"));
	*/
	
}
