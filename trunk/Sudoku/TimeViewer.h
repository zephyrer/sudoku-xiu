#pragma once
#include "afxwin.h"

class CTimeViewer :
	public CWnd
{
public:
	CTimeViewer(void);
	~CTimeViewer(void);
private:
	BOOL RegisterWindowClass();
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
private:
	int m_sTime;
	int m_mTime;
	int m_hTime;
public:
	void Pause(void);
	void Resume(void);
	void SetZero(void);
	void Start(void);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
private:
	void SetSecond(void);
	void SetMinute(void);
	void SetHour(void);
};
