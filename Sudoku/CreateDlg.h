#pragma once

#include "RecViewer.h"

// CCreateDlg dialog

class CCreateDlg : public CDialog
{
	DECLARE_DYNAMIC(CCreateDlg)

public:
	CCreateDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCreateDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_CREATE };

protected:
	CFont m_font;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	CRecViewer m_recViewer[81];
	DECLARE_MESSAGE_MAP()
private:
	void CheckAddNum(int);
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton6();
	afx_msg LRESULT OnRecViewerClickedMessage(WPARAM, LPARAM);
	afx_msg LRESULT OnRecViewerClearMessage(WPARAM, LPARAM);
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonCheck();
	afx_msg void OnBnClickedButtonBegin();
};
