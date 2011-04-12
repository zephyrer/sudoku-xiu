#pragma once


// CKeyDlg dialog

class CKeyDlg : public CDialog
{
	DECLARE_DYNAMIC(CKeyDlg)

public:
	CKeyDlg(CWnd* pParent = NULL);   // standard constructor
	CKeyDlg(CWnd* pParent, int num[9][9], bool isAnswer[81]);
	virtual ~CKeyDlg();
private:
	int m_num[9][9];
	bool m_bIsAnswer[81];

// Dialog Data
	enum { IDD = IDD_DIALOG_KEY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
};
