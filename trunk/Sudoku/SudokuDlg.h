// SudokuDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "RecViewer.h"
#include "NumStatus.h"
#include "TimeViewer.h"
#include "numtable.h"
#include <vector>

using namespace std;
// CSudokuDlg dialog
class CSudokuDlg : public CDialog
{
// Construction
public:
	CSudokuDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SUDOKU_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
protected:
	CToolBar m_wndToolbar;
	CToolBar m_wndBottomToolbar;
	CStatusBar m_wndStatus;
	
public:
	afx_msg void OnHelpAbout();
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
protected:
	CRecViewer m_recViewer[81];
	CNumStatus m_numStatus[9];
	CTimeViewer m_timeViewer;
	CToolBarCtrl& m_ctrlBottomToolBar;
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
private:
	CToolTipCtrl m_tooltip;
	int m_selectNum;
	bool m_bHasWrong;
	bool m_bModal;
	int m_table[9][9];
	int m_resultTable[9][9];
	vector<int> m_wrongNum;
public:
	//afx_msg void OnBnClickedOk();
	afx_msg void OnNumStatusClicked1();
	afx_msg void OnNumStatusClicked2();
	afx_msg void OnNumStatusClicked3();
	afx_msg void OnNumStatusClicked4();
	afx_msg void OnNumStatusClicked5();
	afx_msg void OnNumStatusClicked6();
	afx_msg void OnNumStatusClicked7();
	afx_msg void OnNumStatusClicked8();
	afx_msg void OnNumStatusClicked9();
	afx_msg void OnBnClickedRadio1();
//	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg LRESULT OnTipInMessage(WPARAM, LPARAM);
	afx_msg LRESULT OnRecViewerClickedMessageNor(WPARAM, LPARAM);
	afx_msg LRESULT OnRecViewerClickedMessageMod(WPARAM, LPARAM);
	afx_msg LRESULT OnRecViewerClearMessage(WPARAM, LPARAM);
	afx_msg LRESULT OnCreateMessage(WPARAM, LPARAM);
	afx_msg LRESULT OnChooseMessage(WPARAM, LPARAM);
	afx_msg LRESULT OnSetNumMessage(WPARAM, LPARAM);
	afx_msg LRESULT OnTipCancelMessage(WPARAM, LPARAM);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio4();
	afx_msg void OnBnClickedRadio5();
	afx_msg void OnBnClickedRadio6();
	afx_msg void OnBnClickedRadio7();
	afx_msg void OnBnClickedRadio8();
	afx_msg void OnBnClickedRadio9();
	bool CheckWrongRec(int id);
	afx_msg void OnBnClickedRadio11();
	afx_msg void OnBnClickedRadio12();
	afx_msg void OnNewgameAdvanced();
	afx_msg LRESULT OnSetColorMessage(WPARAM, LPARAM);
private:
	CNumTable m_numTable;
	void CheckAddNum(int id);
public:
	afx_msg void OnEditSeeanswer();
	afx_msg void OnEditTips();
	afx_msg void OnGameCreategame();
	afx_msg void OnGameSaveaspictrues();
private:
	int GetImageCLSID(const WCHAR* format, CLSID* pCLSID);
protected:
	TCHAR m_szFile[MAX_PATH];
public:
	afx_msg void OnEditCheck();
	afx_msg void OnEditUndoall();
	afx_msg void OnNewgameStarter();
	afx_msg void OnNewgameBeginner();
	afx_msg void OnNewgameIntermediate();
	afx_msg void OnGameExit();
private:
	void Finished(void);
public:
	afx_msg void OnNewgameSuperhard();
};
