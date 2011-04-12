// KeysDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Sudoku.h"
#include "KeysDlg.h"


// CKeysDlg dialog

IMPLEMENT_DYNAMIC(CKeysDlg, CDialog)

CKeysDlg::CKeysDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKeysDlg::IDD, pParent)
{

}

CKeysDlg::CKeysDlg(CWnd* pParent, int num1[9][9], int num2[9][9])
: CDialog(CKeysDlg::IDD, pParent)
{
	for(int i = 0;i < 9;i ++)
	{
		for(int j = 0;j < 9;j ++)
		{
			m_num1[i][j] = num1[i][j];
			m_num2[i][j] = num2[i][j];
		}
	}
}

CKeysDlg::~CKeysDlg()
{
}

void CKeysDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_KEY, m_wndKeyEdit);
}


BEGIN_MESSAGE_MAP(CKeysDlg, CDialog)
END_MESSAGE_MAP()


// CKeysDlg message handlers

BOOL CKeysDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_wndKeyEdit.SetBackColor(RGB(255, 255, 255));
	CFont font;
	font.CreatePointFont(150, _T(""), NULL);
	m_wndKeyEdit.SetFont(&font);
	CString str = _T("It has at least two different answers.\r\n\r\n");
	for(int i = 0;i < 9;i ++)
	{
		CString tempStr;
		for(int j = 0;j < 9;j ++)
		{
			tempStr.Format(_T("%d   "), m_num1[i][j]);
			str += tempStr;
		}

		str += _T("                ");
		for(int j = 0;j < 9;j ++)
		{
			tempStr.Format(_T("%d   "), m_num2[i][j]);
			str += tempStr;
		}
		str += _T("\r\n");
	}
	m_wndKeyEdit.SetWindowText(str);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
