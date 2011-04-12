#pragma once


// CMyTipEdit

class CMyTipEdit : public CEdit
{
	DECLARE_DYNAMIC(CMyTipEdit)

public:
	CMyTipEdit();
	virtual ~CMyTipEdit();
	void SetTextColor(COLORREF rgb);
	void SetBackColor(COLORREF rgb);
protected:
	COLORREF m_crText;
	COLORREF m_crBackGnd;
	//background brush
	CBrush m_brBackGnd;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
};


