#pragma once
#include "stdafx.h"
#include "resource.h"

class CRecViewer :
	public CWnd
{
public:
	CRecViewer(void);
	~CRecViewer(void);

public:
	DECLARE_MESSAGE_MAP()
	//	afx_msg void OnPaint();
private:
	BOOL RegisterWindowClass();
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
public:
	//	afx_msg void OnMouseLeave();
//	afx_msg void OnPaint();
private:
	void DrawSel(void);
public:
	//	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	//	afx_msg void OnMouseLeave();
private:
	bool m_bMouseTrack;
	bool m_bModel;	//True represents the common model, it has blank rect, false represents the 9 numbers to choose.
	int m_num;
public:
	afx_msg void OnMouseHover(UINT nFlags, CPoint point);
	afx_msg void OnMouseLeave();
private:
	// The rect's background color
	COLORREF m_colorBkgnd;
	// The selected rect's color
	COLORREF m_colorSel;
	COLORREF m_colorFont;
	COLORREF m_colorSegment;
	int m_selectNum;
	bool m_bNum[9];
private:
	void DrawSegmentNum();
	void EraseSegmentNum(const int);
public:
	void DrawSegment(const int);
	bool RemoveNum(const int);
	bool AddNum(const int);
public:
	COLORREF GetBckColor(void) const;
	void SetBckColor(const COLORREF color);
	void SetNum(const int);
	void SetNum(const int, const COLORREF);
	void SetSegmentColor(const COLORREF);
	int GetNum(void) const;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	void SetModel(bool model);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
private:
	void EraseSegment(void);
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};
