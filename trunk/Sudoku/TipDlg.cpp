// TipDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Sudoku.h"
#include "TipDlg.h"


// CTipDlg dialog

IMPLEMENT_DYNAMIC(CTipDlg, CDialog)

CTipDlg::CTipDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTipDlg::IDD, pParent)
{

}

CTipDlg::CTipDlg(CWnd* pParent, int table[9][9])
	: CDialog(CTipDlg::IDD, pParent)
	, m_index(0)
	, m_bStep(false)
{
	for(int i = 0;i < 9;i ++)
	{
		for(int j = 0;j < 9;j ++)
		{
			m_node[i][j].setLoc(i, j);
		}
	}

	for(int i = 0;i < 9;i ++)
	{
		for(int j= 0;j < 9;j ++)
		{
			if(table[i][j] == 0)
			{
				m_nodeList[8].AddNode(&m_node[i][j]);
			}
			else
			{
				m_node[i][j].setNum(table[i][j]);
				m_nodeList[0].AddNode(&m_node[i][j]);
			}
		}
	}


	for(CNode* pt = m_nodeList[0].GetHead();pt != NULL;pt = pt->next)
	{
		delSurround(pt->getData(), pt->getCol(), pt->getRow());
	}

	while (ConfirmNode());
}

bool CTipDlg::delSurround(int num, int col, int row)
{
	for(int i = 0;i < 9;i ++)
	{
		if(m_node[i][row].removeNum(num))
		{
			m_nodeList[m_node[i][row].getLen()].RemoveNode(&m_node[i][row]);
			m_nodeList[m_node[i][row].getLen() - 1].AddNode(&m_node[i][row]);
			if(m_node[i][row].getLen() == 1)
			{
				NodeRC rc;
				rc.col = i;
				rc.row = row;
				rc.way = 0;
				m_vectorNum.push_back(rc);
			}
			if(m_node[i][row].getLen() == 1 && 
				!delSurround(m_node[i][row].getData(), m_node[i][row].getCol(), m_node[i][row].getRow()))
			{
				return false;
			}
		}
		else if(i != col && m_node[i][row].getLen() == 1 && m_node[i][row].getData() == num)
		{
			return false;
		}
	}

	for(int i = 0;i < 9;i ++)
	{
		if(m_node[col][i].removeNum(num))
		{
			m_nodeList[m_node[col][i].getLen()].RemoveNode(&m_node[col][i]);
			m_nodeList[m_node[col][i].getLen() - 1].AddNode(&m_node[col][i]);
			if(m_node[col][i].getLen() == 1)
			{
				NodeRC rc;
				rc.col = col;
				rc.row = i;
				rc.way = 0;
				m_vectorNum.push_back(rc);
			}
			if(m_node[col][i].getLen() == 1 && 
				!delSurround(m_node[col][i].getData(), m_node[col][i].getCol(), m_node[col][i].getRow()))
			{
				return false;
			}
		}
		else if(i != row && m_node[col][i].getLen() == 1 && m_node[col][i].getData() == num)
		{
			return false;
		}
	}

	int baseCol = col / 3 * 3;
	int baseRow = row / 3 * 3;

	//cout << "BaseCol:" << baseCol << "BaseRow:" << baseRow << endl;
	for(int i = 0;i < 3;i ++)
	{
		for(int j = 0;j < 3;j ++)
		{
			if(m_node[baseCol + i][baseRow + j].removeNum(num))
			{
				m_nodeList[m_node[baseCol + i][baseRow + j].getLen()].RemoveNode(&m_node[baseCol + i][baseRow + j]);
				m_nodeList[m_node[baseCol + i][baseRow + j].getLen() - 1].AddNode(&m_node[baseCol + i][baseRow + j]);
				if(m_node[baseCol + i][baseRow + j].getLen() == 1)
				{
					NodeRC rc;
					rc.col = baseCol + i;
					rc.row = baseRow + j;
					rc.way = 0;
					m_vectorNum.push_back(rc);
				}
				if(m_node[baseCol + i][baseRow + j].getLen() == 1 && 
					!delSurround(m_node[baseCol + i][baseRow + j].getData(), m_node[baseCol + i][baseRow + j].getCol(), m_node[baseCol + i][baseRow + j].getRow()))
				{
					return false;
				}
			}
			else if(!((baseCol + i) == col && (baseRow + j) == row) && 
				m_node[baseCol + i][baseRow + j].getLen() == 1 && m_node[baseCol + i][baseRow + j].getData() == num)
			{
				return false;
			}
		}
	}
	return true;
}

bool CTipDlg::ConfirmNode(void)
{
	int lev = 1;
	for(int lev = 1;lev < 9;lev ++)
	{
		for(CNode *pt = m_nodeList[lev].GetHead();pt != NULL;pt = pt->next)
		{
			for(int num = 1;num < 10;num ++)
			{
				if(pt->hasNum(num))
				{
					bool otherHas = false;
					for(int i = 0;i < 9;i ++)
					{
						if(m_node[i][pt->getRow()].hasNum(num) && i != pt->getCol())
						{
							otherHas = true;
							break;
						}
					}

					if(otherHas)
					{
						otherHas = false;
						for(int i = 0;i < 9;i ++)
						{
							if(m_node[pt->getCol()][i].hasNum(num) && i != pt->getRow())
							{
								otherHas = true;
								break;
							}
						}
					}
					else
					{
						
						NodeRC rc;
						rc.col = pt->getCol();
						rc.row = pt->getRow();
						rc.way = 1;
						m_vectorNum.push_back(rc);


						goto labelEnd2;
					}

					if(otherHas)
					{
						otherHas = false;
						int baseRow = pt->getRow() / 3 * 3;
						int baseCol = pt->getCol() / 3 * 3;
						for(int i = baseRow;i < baseRow + 3;i ++)
						{
							for(int j = baseCol;j < baseCol + 3;j ++)
							{
								if(m_node[j][i].hasNum(num) && !(i == pt->getRow() && j == pt->getCol()))
								{
									otherHas = true;
									goto labelEnd2;
								}
							}
						}
					}
					else
					{
						
						NodeRC rc;
						rc.col = pt->getCol();
						rc.row = pt->getRow();
						rc.way = 2;
						m_vectorNum.push_back(rc);

						goto labelEnd2;
					}
					if(!otherHas)
					{
						NodeRC rc;
						rc.col = pt->getCol();
						rc.row = pt->getRow();
						rc.way = 3;
						m_vectorNum.push_back(rc);
					}
labelEnd2:
					if(!otherHas)
					{
						m_nodeList[pt->getLen() - 1].RemoveNode(pt);
						pt->setNum(num);

						m_nodeList[0].AddNode(pt);
						delSurround(num, pt->getCol(), pt->getRow());
						return true;
					}



				}
			}
		}
	}
	return false;
}


CTipDlg::~CTipDlg()
{
}

void CTipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_EDIT1, m_wndTipEdit);
	DDX_Control(pDX, IDC_EDIT1, m_wndTipEdit);
}


BEGIN_MESSAGE_MAP(CTipDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CTipDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CTipDlg message handlers

void CTipDlg::OnBnClickedOk()
{
	if(m_index < m_vectorNum.size())
	{
		if(m_vectorNum.at(m_index).way == 0)
		{
			if(!m_bStep)
			{
				CString str;
				str.Format(_T("At colum %d, row %c, it must be %d"), m_vectorNum.at(m_index).row + 1, m_vectorNum.at(m_index).col + 'A', 
					m_node[m_vectorNum.at(m_index).col][m_vectorNum.at(m_index).row].getData());
				m_wndTipEdit.SetWindowText(str);
				GetDlgItem(IDOK)->SetWindowText(_T("OK"));
				GetParent()->SendMessage(WM_USER + 6, (WPARAM) RGB(255, 0, 255), (LPARAM) m_vectorNum.at(m_index).col * 9 + m_vectorNum.at(m_index).row);
				m_bStep = true;
			}
			else
			{
				m_wndTipEdit.SetWindowText(_T(""));
				GetDlgItem(IDOK)->SetWindowText(_T("Next"));
				GetParent()->SendMessage(WM_USER + 7, (WPARAM) m_node[m_vectorNum.at(m_index).col][m_vectorNum.at(m_index).row].getData(),  (LPARAM) m_vectorNum.at(m_index).col * 9 + m_vectorNum.at(m_index).row);
				GetParent()->SendMessage(WM_USER + 6, (WPARAM) RGB(255, 255, 255), (LPARAM) m_vectorNum.at(m_index).col * 9 + m_vectorNum.at(m_index).row);
				m_index ++;
				m_bStep = false;
			}
			
		}
		else if(m_vectorNum.at(m_index).way == 1)
		{
			if(!m_bStep)
			{
				CString str;
				str.Format(_T("At colum %d, row %c, it must be %d"), m_vectorNum.at(m_index).row + 1, m_vectorNum.at(m_index).col + 'A', 
					m_node[m_vectorNum.at(m_index).col][m_vectorNum.at(m_index).row].getData());
				m_wndTipEdit.SetWindowText(str);
				GetDlgItem(IDOK)->SetWindowText(_T("OK"));
				for(int i = m_vectorNum.at(m_index).row;i < m_vectorNum.at(m_index).row + 81;i += 9)
				{
					if(i != (m_vectorNum.at(m_index).col * 9 + m_vectorNum.at(m_index).row))
					{
						GetParent()->SendMessage(WM_USER + 6, (WPARAM) RGB(0, 255, 255), (LPARAM) i);
					}
					else
					{
						GetParent()->SendMessage(WM_USER + 6, (WPARAM) RGB(255, 0, 255), (LPARAM) i);
					}
				}
				m_bStep = true;
			}
			else
			{
				m_wndTipEdit.SetWindowText(_T(""));
				GetDlgItem(IDOK)->SetWindowText(_T("Next"));
				GetParent()->SendMessage(WM_USER + 7, (WPARAM) m_node[m_vectorNum.at(m_index).col][m_vectorNum.at(m_index).row].getData(),  (LPARAM) m_vectorNum.at(m_index).col * 9 + m_vectorNum.at(m_index).row);
				for(int i = m_vectorNum.at(m_index).row;i < m_vectorNum.at(m_index).row + 81;i += 9)
				{
					GetParent()->SendMessage(WM_USER + 6, (WPARAM) RGB(255, 255, 255), (LPARAM) i);
				}
				m_index ++;
				m_bStep = false;
			}
		}
		else if(m_vectorNum.at(m_index).way == 2)
		{
			if(!m_bStep)
			{
				CString str;
				str.Format(_T("At colum %d, row %c, it must be %d"), m_vectorNum.at(m_index).row + 1, m_vectorNum.at(m_index).col + 'A', 
					m_node[m_vectorNum.at(m_index).col][m_vectorNum.at(m_index).row].getData());
				m_wndTipEdit.SetWindowText(str);
				GetDlgItem(IDOK)->SetWindowText(_T("OK"));
				for(int i = m_vectorNum.at(m_index).col * 9;i < m_vectorNum.at(m_index).col * 9 + 9;i ++)
				{
					if(i != (m_vectorNum.at(m_index).col * 9 + m_vectorNum.at(m_index).row))
					{
						GetParent()->SendMessage(WM_USER + 6, (WPARAM) RGB(0, 255, 255), (LPARAM) i);
					}
					else
					{
						GetParent()->SendMessage(WM_USER + 6, (WPARAM) RGB(255, 0, 255), (LPARAM) i);
					}
				}
				m_bStep = true;
			}
			else
			{
				m_wndTipEdit.SetWindowText(_T(""));
				GetDlgItem(IDOK)->SetWindowText(_T("Next"));
				GetParent()->SendMessage(WM_USER + 7, (WPARAM) m_node[m_vectorNum.at(m_index).col][m_vectorNum.at(m_index).row].getData(),  (LPARAM) m_vectorNum.at(m_index).col * 9 + m_vectorNum.at(m_index).row);
				for(int i = m_vectorNum.at(m_index).col * 9;i < m_vectorNum.at(m_index).col * 9 + 9;i ++)
				{
					GetParent()->SendMessage(WM_USER + 6, (WPARAM) RGB(255, 255, 255), (LPARAM) i);
				}
				m_index ++;
				m_bStep = false;
			}
		}
		else if(m_vectorNum.at(m_index).way == 3)
		{
			if(!m_bStep)
			{
				CString str;
				str.Format(_T("At colum %d, row %c, it must be %d"), m_vectorNum.at(m_index).row + 1, m_vectorNum.at(m_index).col + 'A', 
					m_node[m_vectorNum.at(m_index).col][m_vectorNum.at(m_index).row].getData());
				m_wndTipEdit.SetWindowText(str);
				GetDlgItem(IDOK)->SetWindowText(_T("OK"));
	
				int baseRow = m_vectorNum.at(m_index).row / 3 * 3;
				int baseCol = m_vectorNum.at(m_index).col / 3 * 3;
				for(int i = baseRow;i < baseRow + 3;i ++)
				{
					for(int j = baseCol;j < baseCol + 3;j ++)
					{
						if(!(i == m_vectorNum.at(m_index).row && j == m_vectorNum.at(m_index).col))
						{
							GetParent()->SendMessage(WM_USER + 6, (WPARAM) RGB(0, 255, 255), (LPARAM) (i + j * 9));
						}
						else
						{
							GetParent()->SendMessage(WM_USER + 6, (WPARAM) RGB(255, 0, 255), (LPARAM) (i + j * 9));
						}
					}
				}
				m_bStep = true;

			}
			else
			{
				m_wndTipEdit.SetWindowText(_T(""));
				GetDlgItem(IDOK)->SetWindowText(_T("Next"));
				GetParent()->SendMessage(WM_USER + 7, (WPARAM) m_node[m_vectorNum.at(m_index).col][m_vectorNum.at(m_index).row].getData(),  (LPARAM) m_vectorNum.at(m_index).col * 9 + m_vectorNum.at(m_index).row);
				int baseRow = m_vectorNum.at(m_index).row / 3 * 3;
				int baseCol = m_vectorNum.at(m_index).col / 3 * 3;
				for(int i = baseRow;i < baseRow + 3;i ++)
				{
					for(int j = baseCol;j < baseCol + 3;j ++)
					{
						GetParent()->SendMessage(WM_USER + 6, (WPARAM) RGB(255, 255, 255), (LPARAM) (i + j * 9));
					}
				}
				m_index ++;
				m_bStep = false;
			}
		}
		
		
	}
	else
	{
		GetDlgItem(IDOK)->EnableWindow(false);
		m_wndTipEdit.SetWindowText(_T("No tips"));
	}
}

BOOL CTipDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_wndTipEdit.SetBackColor(RGB(255, 255, 255));
	CFont font;
	font.CreatePointFont(150, _T(""), NULL);
	m_wndTipEdit.SetFont(&font);

	//Set this dialog in the bottom of the parent dialog
	CRect rc;
	GetParent()->GetWindowRect(rc);
	CRect rcDlg;
	GetWindowRect(rcDlg);
	SetWindowPos(GetParent(), rc.left, rc.bottom - 60, rcDlg.Size().cx, rcDlg.Size().cy, 0);

	GetDlgItem(IDOK)->PostMessage(BM_CLICK, 0, 0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
//BOOL CTipDlg::PreCreateWindow(CREATESTRUCT& cs)
//{
//	// TODO: Add your specialized code here and/or call the base class
//	cs.x = 0;
//	cs.y = 0;
//	return CDialog::PreCreateWindow(cs);
//}

void CTipDlg::OnCancel()
{
	// TODO: Add your specialized code here and/or call the base class
	GetParent()->SendMessage(WM_USER + 8, 0, 0);
	CDialog::OnCancel();
}
