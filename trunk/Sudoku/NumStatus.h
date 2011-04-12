#pragma once
#include "afxwin.h"

class CNumStatus :
	public CWnd
{
public:
	CNumStatus(void);
	~CNumStatus(void);
private:
	BOOL RegisterWindowClass();
	int m_num;
	void DrawRect(void);
public:
	CNumStatus& operator++ (int);
	CNumStatus& operator-- (int);
	void SetZero(void);
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
//	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	
};
