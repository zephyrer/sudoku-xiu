#pragma once
#include "mytipedit.h"


// CKeysDlg dialog

class CKeysDlg : public CDialog
{
	DECLARE_DYNAMIC(CKeysDlg)

public:
	CKeysDlg(CWnd* pParent = NULL);   // standard constructor
	CKeysDlg(CWnd* pParent, int num1[9][9], int num2[9][9]);
	virtual ~CKeysDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_MULKEYS };
private:
	int m_num1[9][9];
	int m_num2[9][9];
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	CMyTipEdit m_wndKeyEdit;
public:
	virtual BOOL OnInitDialog();
};
