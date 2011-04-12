#pragma once

#include "MyTipEdit.h"
#include "Node.h"
#include "NodeList.h"
#include <vector>


using namespace std;
// CTipDlg dialog
struct NodeRC
{
	int col;
	int row;
	int way;
};

class CTipDlg : public CDialog
{
	DECLARE_DYNAMIC(CTipDlg)

public:
	CTipDlg(CWnd* pParent = NULL);   // standard constructor
	CTipDlg(CWnd* pParent, int table[9][9]);
	virtual ~CTipDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_TIPS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//CMyTipEdit m_wndTipEdit;
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
private:
	CMyTipEdit m_wndTipEdit;
	unsigned int m_index;
	CNode m_node[9][9];
	CNodeList m_nodeList[9];
	bool delSurround(int num, int col, int row);
	bool ConfirmNode(void);
	bool m_bStep;
	vector<NodeRC> m_vectorNum;
protected:
//	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnCancel();
};
