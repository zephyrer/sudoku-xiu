// SudokuDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Sudoku.h"
#include "SudokuDlg.h"
#include "NodeTable.h"
#include "NumTable.h"
#include "KeyDlg.h"
#include "TipDlg.h"
#include "CreateDlg.h"
#include "KeysDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMClickSyslink1(NMHDR *pNMHDR, LRESULT *pResult);
public:
//	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	ON_NOTIFY(NM_CLICK, IDC_SYSLINK1, &CAboutDlg::OnNMClickSyslink1)
END_MESSAGE_MAP()


// CSudokuDlg dialog




CSudokuDlg::CSudokuDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSudokuDlg::IDD, pParent)
	, m_ctrlBottomToolBar(m_wndBottomToolbar.GetToolBarCtrl())
	, m_selectNum(1)
	, m_bHasWrong(false)
	, m_bModal(true)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//m_bAutoMenuEnable = true;

	for(int i = 0;i < 9;i ++)
	{
		for(int j = 0;j < 9;j ++)
		{
			m_table[i][j] = 0;
		}
	}
}

void CSudokuDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	for(int i = 0;i < 81;i ++)
	{
		DDX_Control(pDX, IDC_CUSTOM1 + i, m_recViewer[i]);
	}
	for(int i = 0;i < 9;i ++)
	{
		DDX_Control(pDX, IDC_CUSTOM82 + i, m_numStatus[i]);
	}

	DDX_Control(pDX, IDC_CUSTOM91, m_timeViewer);
}

BEGIN_MESSAGE_MAP(CSudokuDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_HELP_ABOUT, &CSudokuDlg::OnHelpAbout)
	//ON_BN_CLICKED(IDOK, &CSudokuDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_CUSTOM82, &CSudokuDlg::OnNumStatusClicked1)
	ON_BN_CLICKED(IDC_CUSTOM83, &CSudokuDlg::OnNumStatusClicked2)
	ON_BN_CLICKED(IDC_CUSTOM84, &CSudokuDlg::OnNumStatusClicked3)
	ON_BN_CLICKED(IDC_CUSTOM85, &CSudokuDlg::OnNumStatusClicked4)
	ON_BN_CLICKED(IDC_CUSTOM86, &CSudokuDlg::OnNumStatusClicked5)
	ON_BN_CLICKED(IDC_CUSTOM87, &CSudokuDlg::OnNumStatusClicked6)
	ON_BN_CLICKED(IDC_CUSTOM88, &CSudokuDlg::OnNumStatusClicked7)
	ON_BN_CLICKED(IDC_CUSTOM89, &CSudokuDlg::OnNumStatusClicked8)
	ON_BN_CLICKED(IDC_CUSTOM90, &CSudokuDlg::OnNumStatusClicked9)
	ON_MESSAGE(WM_USER + 1, OnTipInMessage)
	ON_MESSAGE(WM_USER + 2, OnRecViewerClickedMessageNor)
	ON_MESSAGE(WM_USER + 3, OnRecViewerClickedMessageMod)
	ON_MESSAGE(WM_USER + 4, OnRecViewerClearMessage)
	ON_MESSAGE(WM_USER + 5, OnCreateMessage)
	ON_MESSAGE(WM_USER + 6, OnSetColorMessage)
	ON_MESSAGE(WM_USER + 7, OnSetNumMessage)
	ON_MESSAGE(WM_USER + 8, OnTipCancelMessage)
	ON_MESSAGE(WM_USER + 10, OnChooseMessage)
	ON_BN_CLICKED(IDC_RADIO1, &CSudokuDlg::OnBnClickedRadio1)
//	ON_WM_SETCURSOR()
ON_BN_CLICKED(IDC_BUTTON1, &CSudokuDlg::OnBnClickedButton1)
ON_BN_CLICKED(IDC_RADIO2, &CSudokuDlg::OnBnClickedRadio2)
ON_BN_CLICKED(IDC_RADIO3, &CSudokuDlg::OnBnClickedRadio3)
ON_BN_CLICKED(IDC_RADIO4, &CSudokuDlg::OnBnClickedRadio4)
ON_BN_CLICKED(IDC_RADIO5, &CSudokuDlg::OnBnClickedRadio5)
ON_BN_CLICKED(IDC_RADIO6, &CSudokuDlg::OnBnClickedRadio6)
ON_BN_CLICKED(IDC_RADIO7, &CSudokuDlg::OnBnClickedRadio7)
ON_BN_CLICKED(IDC_RADIO8, &CSudokuDlg::OnBnClickedRadio8)
ON_BN_CLICKED(IDC_RADIO9, &CSudokuDlg::OnBnClickedRadio9)
ON_BN_CLICKED(IDC_RADIO11, &CSudokuDlg::OnBnClickedRadio11)
ON_BN_CLICKED(IDC_RADIO12, &CSudokuDlg::OnBnClickedRadio12)
ON_COMMAND(ID_NEWGAME_ADVANCED, &CSudokuDlg::OnNewgameAdvanced)
ON_COMMAND(ID_EDIT_SEEANSWER, &CSudokuDlg::OnEditSeeanswer)
ON_COMMAND(ID_EDIT_TIPS, &CSudokuDlg::OnEditTips)
ON_COMMAND(ID_GAME_CREATEGAME, &CSudokuDlg::OnGameCreategame)
ON_COMMAND(ID_GAME_SAVEASPICTRUES, &CSudokuDlg::OnGameSaveaspictrues)
ON_COMMAND(ID_EDIT_CHECK, &CSudokuDlg::OnEditCheck)
ON_COMMAND(ID_EDIT_UNDOALL, &CSudokuDlg::OnEditUndoall)
ON_COMMAND(ID_NEWGAME_STARTER, &CSudokuDlg::OnNewgameStarter)
ON_COMMAND(ID_NEWGAME_BEGINNER, &CSudokuDlg::OnNewgameBeginner)
ON_COMMAND(ID_NEWGAME_INTERMEDIATE, &CSudokuDlg::OnNewgameIntermediate)
ON_COMMAND(ID_GAME_EXIT, &CSudokuDlg::OnGameExit)
ON_COMMAND(ID_NEWGAME_SUPERHARD, &CSudokuDlg::OnNewgameSuperhard)
END_MESSAGE_MAP()


// CSudokuDlg message handlers

BOOL CSudokuDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	
	m_wndToolbar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS | CBRS_SIZE_DYNAMIC);
	m_wndToolbar.LoadToolBar(IDR_TOOLBAR);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

	CImageList imgs;
	CBitmap bmp;
	bmp.LoadBitmap(IDR_TOOLBAR);
	imgs.Create(32, 32, ILC_MASK | ILC_COLOR24, 14, 1);
	imgs.Add(&bmp, RGB(0, 128, 128));

	m_wndToolbar.SendMessage(TB_SETIMAGELIST, 0, (LPARAM) imgs.m_hImageList);
	imgs.Detach();
	bmp.Detach();
	
	
	//Bottom toolbar
	m_wndBottomToolbar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_TOOLTIPS | CBRS_SIZE_DYNAMIC);
	m_wndBottomToolbar.LoadToolBar(IDR_TOOLBAR2);
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);

	CImageList imgs2;
	CBitmap bmp2;
	bmp2.LoadBitmap(IDR_TOOLBAR2);
	imgs2.Create(16, 16, ILC_MASK | ILC_COLOR24, 6, 1);
	imgs2.Add(&bmp2, RGB(240, 240, 240));

	m_wndBottomToolbar.SendMessage(TB_SETIMAGELIST, 0, (LPARAM) imgs2.m_hImageList);
	imgs2.Detach();
	bmp2.Detach();

	m_wndBottomToolbar.MoveWindow(CRect(97, 513, 250, 538), true);
	
	m_wndStatus.Create(this);
	UINT nID[] = {ID_SEPARATOR, 100};
	m_wndStatus.SetIndicators(nID, 2);

	RECT rect = {0};
	GetClientRect(&rect);
	m_wndStatus.MoveWindow(0, rect.bottom - 20, rect.right, 20, TRUE);

	m_wndStatus.SetPaneInfo(0, 0, 0, rect.right - 10 - 80);
	m_wndStatus.SetPaneInfo(1, 100, 0, 80);

	/*
	if (!m_wndBottomToolbar.Create(this,IDD_DIALOGBAR, WS_VISIBLE|WS_CHILD
			|CBRS_SIZE_DYNAMIC|CBRS_BOTTOM, IDD_DIALOGBAR))
	
		{
			TRACE0("Failed to create CMyDialogBar bar!");
		}*/


	m_recViewer[0].MoveWindow(CRect(37, 70, 82, 115), true);
	m_recViewer[1].MoveWindow(CRect(83, 70, 128, 115), true);
	m_recViewer[2].MoveWindow(CRect(129, 70, 174, 115), true);
	m_recViewer[3].MoveWindow(CRect(177, 70, 222, 115), true);
	m_recViewer[4].MoveWindow(CRect(223, 70, 268, 115), true);
	m_recViewer[5].MoveWindow(CRect(269, 70, 314, 115), true);
	m_recViewer[6].MoveWindow(CRect(317, 70, 362, 115), true);
	m_recViewer[7].MoveWindow(CRect(363, 70, 408, 115), true);
	m_recViewer[8].MoveWindow(CRect(409, 70, 454, 115), true);
	m_recViewer[9].MoveWindow(CRect(37, 116, 82, 161), true);
	m_recViewer[10].MoveWindow(CRect(83, 116, 128, 161), true);
	m_recViewer[11].MoveWindow(CRect(129, 116, 174, 161), true);
	m_recViewer[12].MoveWindow(CRect(177, 116, 222, 161), true);
	m_recViewer[13].MoveWindow(CRect(223, 116, 268, 161), true);
	m_recViewer[14].MoveWindow(CRect(269, 116, 314, 161), true);
	m_recViewer[15].MoveWindow(CRect(317, 116, 362, 161), true);
	m_recViewer[16].MoveWindow(CRect(363, 116, 408, 161), true);
	m_recViewer[17].MoveWindow(CRect(409, 116, 454, 161), true);
	m_recViewer[18].MoveWindow(CRect(37, 162, 82, 207), true);
	m_recViewer[19].MoveWindow(CRect(83, 162, 128, 207), true);
	m_recViewer[20].MoveWindow(CRect(129, 162, 174, 207), true);
	m_recViewer[21].MoveWindow(CRect(177, 162, 222, 207), true);
	m_recViewer[22].MoveWindow(CRect(223, 162, 268, 207), true);
	m_recViewer[23].MoveWindow(CRect(269, 162, 314, 207), true);
	m_recViewer[24].MoveWindow(CRect(317, 162, 362, 207), true);
	m_recViewer[25].MoveWindow(CRect(363, 162, 408, 207), true);
	m_recViewer[26].MoveWindow(CRect(409, 162, 454, 207), true);

	m_recViewer[27].MoveWindow(CRect(37, 210, 82, 255), true);
	m_recViewer[28].MoveWindow(CRect(83, 210, 128, 255), true);
	m_recViewer[29].MoveWindow(CRect(129, 210, 174, 255), true);
	m_recViewer[30].MoveWindow(CRect(177, 210, 222, 255), true);
	m_recViewer[31].MoveWindow(CRect(223, 210, 268, 255), true);
	m_recViewer[32].MoveWindow(CRect(269, 210, 314, 255), true);
	m_recViewer[33].MoveWindow(CRect(317, 210, 362, 255), true);
	m_recViewer[34].MoveWindow(CRect(363, 210, 408, 255), true);
	m_recViewer[35].MoveWindow(CRect(409, 210, 454, 255), true);
	m_recViewer[36].MoveWindow(CRect(37, 256, 82, 301), true);
	m_recViewer[37].MoveWindow(CRect(83, 256, 128, 301), true);
	m_recViewer[38].MoveWindow(CRect(129, 256, 174, 301), true);
	m_recViewer[39].MoveWindow(CRect(177, 256, 222, 301), true);
	m_recViewer[40].MoveWindow(CRect(223, 256, 268, 301), true);
	m_recViewer[41].MoveWindow(CRect(269, 256, 314, 301), true);
	m_recViewer[42].MoveWindow(CRect(317, 256, 362, 301), true);
	m_recViewer[43].MoveWindow(CRect(363, 256, 408, 301), true);
	m_recViewer[44].MoveWindow(CRect(409, 256, 454, 301), true);
	m_recViewer[45].MoveWindow(CRect(37, 302, 82, 347), true);
	m_recViewer[46].MoveWindow(CRect(83, 302, 128, 347), true);
	m_recViewer[47].MoveWindow(CRect(129, 302, 174, 347), true);
	m_recViewer[48].MoveWindow(CRect(177, 302, 222, 347), true);
	m_recViewer[49].MoveWindow(CRect(223, 302, 268, 347), true);
	m_recViewer[50].MoveWindow(CRect(269, 302, 314, 347), true);
	m_recViewer[51].MoveWindow(CRect(317, 302, 362, 347), true);
	m_recViewer[52].MoveWindow(CRect(363, 302, 408, 347), true);
	m_recViewer[53].MoveWindow(CRect(409, 302, 454, 347), true);

	m_recViewer[54].MoveWindow(CRect(37, 350, 82, 395), true);
	m_recViewer[55].MoveWindow(CRect(83, 350, 128, 395), true);
	m_recViewer[56].MoveWindow(CRect(129, 350, 174, 395), true);
	m_recViewer[57].MoveWindow(CRect(177, 350, 222, 395), true);
	m_recViewer[58].MoveWindow(CRect(223, 350, 268, 395), true);
	m_recViewer[59].MoveWindow(CRect(269, 350, 314, 395), true);
	m_recViewer[60].MoveWindow(CRect(317, 350, 362, 395), true);
	m_recViewer[61].MoveWindow(CRect(363, 350, 408, 395), true);
	m_recViewer[62].MoveWindow(CRect(409, 350, 454, 395), true);
	m_recViewer[63].MoveWindow(CRect(37, 396, 82, 441), true);
	m_recViewer[64].MoveWindow(CRect(83, 396, 128, 441), true);
	m_recViewer[65].MoveWindow(CRect(129, 396, 174, 441), true);
	m_recViewer[66].MoveWindow(CRect(177, 396, 222, 441), true);
	m_recViewer[67].MoveWindow(CRect(223, 396, 268, 441), true);
	m_recViewer[68].MoveWindow(CRect(269, 396, 314, 441), true);
	m_recViewer[69].MoveWindow(CRect(317, 396, 362, 441), true);
	m_recViewer[70].MoveWindow(CRect(363, 396, 408, 441), true);
	m_recViewer[71].MoveWindow(CRect(409, 396, 454, 441), true);
	m_recViewer[72].MoveWindow(CRect(37, 442, 82, 487), true);
	m_recViewer[73].MoveWindow(CRect(83, 442, 128, 487), true);
	m_recViewer[74].MoveWindow(CRect(129, 442, 174, 487), true);
	m_recViewer[75].MoveWindow(CRect(177, 442, 222, 487), true);
	m_recViewer[76].MoveWindow(CRect(223, 442, 268, 487), true);
	m_recViewer[77].MoveWindow(CRect(269, 442, 314, 487), true);
	m_recViewer[78].MoveWindow(CRect(317, 442, 362, 487), true);
	m_recViewer[79].MoveWindow(CRect(363, 442, 408, 487), true);
	m_recViewer[80].MoveWindow(CRect(409, 442, 454, 487), true);

	((CButton *) GetDlgItem(IDC_RADIO1))->SetCheck(TRUE);
	((CButton *) GetDlgItem(IDC_RADIO11))->SetCheck(TRUE);

	for(int i = 0;i < 3;i ++)
	{
		for(int j = 0;j < 3;j ++)
		{
			m_recViewer[i * 9 + j + 3].SetBckColor(RGB(247, 247, 217));
			m_recViewer[i * 9 + j + 27].SetBckColor(RGB(247, 247, 217));
			m_recViewer[i * 9 + j + 33].SetBckColor(RGB(247, 247, 217));
			m_recViewer[i * 9 + j + 57].SetBckColor(RGB(247, 247, 217));
		}
	}
		//SetWindowPos
	//m_wndToolbar.EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndToolbar);

	//tooltip
	if(m_tooltip.Create(this)) {
		
		CRect toolButtonRect;
		CToolBarCtrl& toolBar = m_wndToolbar.GetToolBarCtrl();
		int buttonCount = toolBar.GetButtonCount();
		for (int i = 0; i < buttonCount; i ++) {
			TBBUTTON btn;
			if (toolBar.GetButton(i, &btn) && btn.fsStyle == TBSTYLE_BUTTON) {
				m_wndToolbar.GetItemRect(i, &toolButtonRect);
				m_tooltip.AddTool(&m_wndToolbar, btn.idCommand, toolButtonRect, btn.idCommand);
			} 
		}
		m_wndToolbar.GetToolBarCtrl().SetToolTips(&m_tooltip);
		

		CRect toolBottomButtonRect;
		//m_ctrlBottomToolBar = m_wndBottomToolbar.GetToolBarCtrl();
		int buttonCount2 = m_ctrlBottomToolBar.GetButtonCount();
		for (int i = 0; i < buttonCount2; i ++) {
			TBBUTTON btn;
			if (m_ctrlBottomToolBar.GetButton(i, &btn) && btn.fsStyle == TBSTYLE_BUTTON) {
				m_wndBottomToolbar.GetItemRect(i, &toolBottomButtonRect);
				m_tooltip.AddTool(&m_wndBottomToolbar, btn.idCommand, toolBottomButtonRect, btn.idCommand);
			} 
		}
		m_wndBottomToolbar.GetToolBarCtrl().SetToolTips(&m_tooltip);
		m_ctrlBottomToolBar.EnableButton(ID_EDIT_UNDO, FALSE);
	}
	
	
	/*
	if(!m_tooltip.Create(this))
		{
			MessageBox(_T("Fail to create CToolTip"));
		}
		else
		{
			CRect rect;
			m_wndToolbar.GetWindowRect(rect);
			m_tooltip.AddTool(&m_wndToolbar, _T("sdfji"));
			//m_tooltip.AddTool(GetDlgItem(ID_HELP_ABOUT), 
				//_T("You can also use the keyboard or the num pad!"));
			for(int i = 0;i < 9;i ++)
			{
				m_tooltip.AddTool(GetDlgItem(IDC_RADIO1 + i), 
					_T("You can also use the keyboard or the num pad!"));
			}
			/ *
			m_tooltip.AddTool(GetDlgItem(ID_EDIT_INT), 
			_T("You can also use the keyboard or the num pad!"));* /
	
			m_tooltip.SetDelayTime(100);
			m_tooltip.Activate(TRUE);
		}*/

	PostMessage(WM_USER + 10, 0, 0);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSudokuDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSudokuDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		CDC dcMem;
		dcMem.CreateCompatibleDC(&dc);   
		CBitmap   bmpBackground;   
		bmpBackground.LoadBitmap(IDB_BITMAP_TABLE); 
		//IDB_BITMAP是你自己的图对应的ID   
		BITMAP   bitmap;   
		bmpBackground.GetBitmap(&bitmap);   
		CBitmap   *pbmpOld=dcMem.SelectObject(&bmpBackground);  
		dc.StretchBlt(7, 45, bitmap.bmWidth, bitmap.bmHeight,&dcMem,0,0,   
			bitmap.bmWidth,bitmap.bmHeight,SRCCOPY);  
		//CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSudokuDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSudokuDlg::OnHelpAbout()
{
	// TODO: Add your command handler code here
	CAboutDlg dlg;
	dlg.DoModal();
}


BOOL CSudokuDlg::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// TODO: Add your specialized code here and/or call the base class
	return CDialog::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


BOOL CSudokuDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: Add your specialized code here and/or call the base class
	//m_tooltip.RelayEvent(pMsg);
	if(pMsg->message == WM_KEYDOWN)  
	{
		switch(pMsg->wParam)  
		{  
		case   '1':
			GetDlgItem(IDC_RADIO1)->SendMessage(BM_CLICK,   0,   0);  
			return TRUE;
		case   '2':
			GetDlgItem(IDC_RADIO2)->SendMessage(BM_CLICK,   0,   0);  
			return TRUE;
		case   '3':
			GetDlgItem(IDC_RADIO3)->SendMessage(BM_CLICK,   0,   0);  
			return TRUE;
		case   '4':
			GetDlgItem(IDC_RADIO4)->SendMessage(BM_CLICK,   0,   0);  
			return TRUE;
		case   '5':
			GetDlgItem(IDC_RADIO5)->SendMessage(BM_CLICK,   0,   0);  
			return TRUE;
		case   '6':
			GetDlgItem(IDC_RADIO6)->SendMessage(BM_CLICK,   0,   0);  
			return TRUE;
		case   '7':
			GetDlgItem(IDC_RADIO7)->SendMessage(BM_CLICK,   0,   0);  
			return TRUE;
		case   '8':
			GetDlgItem(IDC_RADIO8)->SendMessage(BM_CLICK,   0,   0);  
			return TRUE;
		case   '9':
			GetDlgItem(IDC_RADIO9)->SendMessage(BM_CLICK,   0,   0);  
			return TRUE;
		case   VK_NUMPAD1:
			GetDlgItem(IDC_RADIO1)->SendMessage(BM_CLICK,   0,   0);  
			return TRUE;
		case   VK_NUMPAD2:
			GetDlgItem(IDC_RADIO2)->SendMessage(BM_CLICK,   0,   0);  
			return TRUE;
		case   VK_NUMPAD3:
			GetDlgItem(IDC_RADIO3)->SendMessage(BM_CLICK,   0,   0);  
			return TRUE;
		case   VK_NUMPAD4:
			GetDlgItem(IDC_RADIO4)->SendMessage(BM_CLICK,   0,   0);  
			return TRUE;
		case   VK_NUMPAD5:
			GetDlgItem(IDC_RADIO5)->SendMessage(BM_CLICK,   0,   0);  
			return TRUE;
		case   VK_NUMPAD6:
			GetDlgItem(IDC_RADIO6)->SendMessage(BM_CLICK,   0,   0);  
			return TRUE;
		case   VK_NUMPAD7:
			GetDlgItem(IDC_RADIO7)->SendMessage(BM_CLICK,   0,   0);  
			return TRUE;
		case   VK_NUMPAD8:
			GetDlgItem(IDC_RADIO8)->SendMessage(BM_CLICK,   0,   0);  
			return TRUE;
		case   VK_NUMPAD9:
			GetDlgItem(IDC_RADIO9)->SendMessage(BM_CLICK,   0,   0);  
			return TRUE;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

/*
void CSudokuDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	m_numStatus[0] ++;
	m_timeViewer.Start();
	//OnOK();
}*/


void CSudokuDlg::OnNumStatusClicked1()
{
	GetDlgItem(IDC_RADIO1)->SendMessage(BM_CLICK, 0, 0);
}

void CSudokuDlg::OnNumStatusClicked9()
{
	GetDlgItem(IDC_RADIO9)->SendMessage(BM_CLICK, 0, 0);
}

void CSudokuDlg::OnNumStatusClicked2()
{
	GetDlgItem(IDC_RADIO2)->SendMessage(BM_CLICK, 0, 0);
}

void CSudokuDlg::OnNumStatusClicked3()
{
	GetDlgItem(IDC_RADIO3)->SendMessage(BM_CLICK, 0, 0);
}

void CSudokuDlg::OnNumStatusClicked4()
{
	GetDlgItem(IDC_RADIO4)->SendMessage(BM_CLICK, 0, 0);
}

void CSudokuDlg::OnNumStatusClicked5()
{
	GetDlgItem(IDC_RADIO5)->SendMessage(BM_CLICK, 0, 0);
}

void CSudokuDlg::OnNumStatusClicked6()
{
	GetDlgItem(IDC_RADIO6)->SendMessage(BM_CLICK, 0, 0);
}

void CSudokuDlg::OnNumStatusClicked8()
{
	GetDlgItem(IDC_RADIO8)->SendMessage(BM_CLICK, 0, 0);
}

void CSudokuDlg::OnNumStatusClicked7()
{
	GetDlgItem(IDC_RADIO7)->SendMessage(BM_CLICK, 0, 0);
}

void CSudokuDlg::OnBnClickedRadio1()
{
	for(int i = 0;i < 81;i ++)
	{
		if(m_recViewer[i].GetNum() == m_selectNum)
		{
			int result = (i / 9) / 3 - (i % 9) / 3;
			if(1 == result || (-1) == result)
			{
				m_recViewer[i].SetBckColor(RGB(247, 247, 217));
			}
			else
			{
				m_recViewer[i].SetBckColor(RGB(255, 255, 255));
			}
		}
	}

	m_selectNum = 1;

	for(int i = 0;i < 81;i ++)
	{
		if(m_recViewer[i].GetNum() == m_selectNum)
		{
			m_recViewer[i].SetBckColor(RGB(255, 255, 0));
		}
	}
}



LRESULT CSudokuDlg::OnTipInMessage(WPARAM wParam, LPARAM lParam)
{
	int col = (wParam - 1013) % 9;
	char row = (wParam - 1013) / 9 + 'A';
	CString str;
	str.Format(_T("Position: %c %d"), row, col + 1);
	m_wndStatus.SetPaneText(1, str);
	return 0;
}

LRESULT CSudokuDlg::OnRecViewerClickedMessageNor(WPARAM wParam, LPARAM lParam)
{
	for(unsigned int i = 0;i < m_wrongNum.size();i ++)
	{
		if(m_recViewer[m_wrongNum.at(i)].GetNum() == m_selectNum)
		{
			m_recViewer[m_wrongNum.at(i)].SetBckColor(RGB(255, 255, 0));
		}
		else
		{
			int result = (m_wrongNum.at(i) / 9) / 3 - (m_wrongNum.at(i) % 9) / 3;
			if(1 == result || (-1) == result)
			{
				m_recViewer[m_wrongNum.at(i)].SetBckColor(RGB(247, 247, 217));
			}
			else
			{
				m_recViewer[m_wrongNum.at(i)].SetBckColor(RGB(255, 255, 255));
			}
		}
	}
	m_wrongNum.clear();
	if(m_table[(wParam - IDC_CUSTOM1) / 9][(wParam - IDC_CUSTOM1) % 9] != 0)
	{
		return 0;
	}

	if(m_recViewer[wParam - IDC_CUSTOM1].GetNum() != 0)
	{
		m_numStatus[m_recViewer[wParam - IDC_CUSTOM1].GetNum() - 1] --;
	}
	m_numStatus[m_selectNum - 1] ++;

	m_recViewer[wParam - IDC_CUSTOM1].SetNum(m_selectNum, RGB(0, 0, 255));
	m_recViewer[wParam - IDC_CUSTOM1].SetBckColor(RGB(255, 255, 0));

	int wrong1;
	int wrong2;
	bool once = false;
	for(int i = 0;i < 81;i ++)
	{
		if(m_recViewer[i].GetBckColor() == RGB(255, 0, 0))
		{
			
			if(m_recViewer[i].GetNum() == m_selectNum)
			{
				m_recViewer[i].SetBckColor(RGB(255, 255, 0));
			}
			else
			{
				int result = (i / 9) / 3 - (i % 9) / 3;
				if(1 == result || (-1) == result)
				{
					m_recViewer[i].SetBckColor(RGB(247, 247, 217));
				}
				else
				{
					m_recViewer[i].SetBckColor(RGB(255, 255, 255));
				}
			}

			if(!once)
			{
				wrong1 = i;
				once = true;
			}
			else
			{
				wrong2 = i;
				break;
			}
		}
	}
	if(!CheckWrongRec(wParam - IDC_CUSTOM1) && once)
	{
		m_recViewer[wrong1].SetBckColor(RGB(255, 0, 0));
		m_recViewer[wrong2].SetBckColor(RGB(255, 0, 0));
	}

	bool bRight = true;
	for(int i = 0;i < 81;i ++)
	{
		if(m_recViewer[i].GetNum() != m_resultTable[i / 9][i % 9])
		{
			bRight = false;
			break;
		}
	}
	if(bRight)
	{
		Finished();
	}
	return 0;
}

LRESULT CSudokuDlg::OnRecViewerClickedMessageMod(WPARAM wParam, LPARAM lParam)
{
	for(unsigned int i = 0;i < m_wrongNum.size();i ++)
	{
		if(m_recViewer[m_wrongNum.at(i)].GetNum() == m_selectNum)
		{
			m_recViewer[m_wrongNum.at(i)].SetBckColor(RGB(255, 255, 0));
		}
		else
		{
			int result = (m_wrongNum.at(i) / 9) / 3 - (m_wrongNum.at(i) % 9) / 3;
			if(1 == result || (-1) == result)
			{
				m_recViewer[m_wrongNum.at(i)].SetBckColor(RGB(247, 247, 217));
			}
			else
			{
				m_recViewer[m_wrongNum.at(i)].SetBckColor(RGB(255, 255, 255));
			}
		}
	}
	m_wrongNum.clear();

	if(m_table[(wParam - IDC_CUSTOM1) / 9][(wParam - IDC_CUSTOM1) % 9] != 0)
	{
		return 0;
	}

	if(m_recViewer[wParam - IDC_CUSTOM1].GetNum() != 0)
	{
		m_numStatus[m_recViewer[wParam - IDC_CUSTOM1].GetNum() - 1] --;
	}
	m_numStatus[lParam - 1] ++;

	m_recViewer[wParam - IDC_CUSTOM1].SetNum(lParam, RGB(0, 0, 255));
	if(lParam == m_selectNum)
	{
		m_recViewer[wParam - IDC_CUSTOM1].SetBckColor(RGB(255, 255, 0));
	}
	int wrong1;
	int wrong2;
	bool once = false;
	for(int i = 0;i < 81;i ++)
	{
		if(m_recViewer[i].GetBckColor() == RGB(255, 0, 0))
		{

			if(m_recViewer[i].GetNum() == m_selectNum)
			{
				m_recViewer[i].SetBckColor(RGB(255, 255, 0));
			}
			else
			{
				int result = (i / 9) / 3 - (i % 9) / 3;
				if(1 == result || (-1) == result)
				{
					m_recViewer[i].SetBckColor(RGB(247, 247, 217));
				}
				else
				{
					m_recViewer[i].SetBckColor(RGB(255, 255, 255));
				}
			}

			if(!once)
			{
				wrong1 = i;
				once = true;
			}
			else
			{
				wrong2 = i;
				break;
			}
		}
	}
	if(!CheckWrongRec(wParam - IDC_CUSTOM1) && once)
	{
		m_recViewer[wrong1].SetBckColor(RGB(255, 0, 0));
		m_recViewer[wrong2].SetBckColor(RGB(255, 0, 0));
	}

	int baseRow = (wParam - IDC_CUSTOM1) / 9;
	int baseCol = (wParam - IDC_CUSTOM1) % 9;
	baseRow = baseRow / 3 * 3;
	baseCol = baseCol / 3 * 3;
	for(int i = 0;i < 3;i ++)
	{
		for(int j = 0;j < 3;j ++)
		{
			if (m_recViewer[(baseRow + i) * 9 + baseCol + j].GetNum() == 0)
			{
				m_recViewer[(baseRow + i) * 9 + baseCol + j].RemoveNum(lParam);
			}
		}
	}
	int baseIndex = (wParam - IDC_CUSTOM1) / 9 * 9;
	for(int i = 0;i < 9;i ++)
	{
		if(m_recViewer[baseIndex + i].GetNum() == 0)
		{
			m_recViewer[baseIndex + i].RemoveNum(lParam);
		}
	}

	baseIndex = (wParam - IDC_CUSTOM1) % 9;
	for(int i = 0;i < 81;i += 9)
	{
		if(m_recViewer[baseIndex + i].GetNum() == 0)
		{
			m_recViewer[baseIndex + i].RemoveNum(lParam);
		}
	}

	bool bRight = true;
	for(int i = 0;i < 81;i ++)
	{
		if(m_recViewer[i].GetNum() != m_resultTable[i / 9][i % 9])
		{
			bRight = false;
			break;
		}
	}
	if(bRight)
	{
		Finished();
	}
	return 0;
}

LRESULT CSudokuDlg::OnRecViewerClearMessage(WPARAM wParam, LPARAM lParam)
{
	for(unsigned int i = 0;i < m_wrongNum.size();i ++)
	{
		if(m_recViewer[m_wrongNum.at(i)].GetNum() == m_selectNum)
		{
			m_recViewer[m_wrongNum.at(i)].SetBckColor(RGB(255, 255, 0));
		}
		else
		{
			int result = (m_wrongNum.at(i) / 9) / 3 - (m_wrongNum.at(i) % 9) / 3;
			if(1 == result || (-1) == result)
			{
				m_recViewer[m_wrongNum.at(i)].SetBckColor(RGB(247, 247, 217));
			}
			else
			{
				m_recViewer[m_wrongNum.at(i)].SetBckColor(RGB(255, 255, 255));
			}
		}
	}
	m_wrongNum.clear();

	if(m_table[(wParam - IDC_CUSTOM1) / 9][(wParam - IDC_CUSTOM1) % 9] != 0)
	{
		return 0;
	}

	if(m_recViewer[wParam - IDC_CUSTOM1].GetNum() == 0)
	{
		return 0;
	}

	m_numStatus[m_recViewer[wParam - IDC_CUSTOM1].GetNum() - 1] --;

	m_recViewer[wParam - IDC_CUSTOM1].SetNum(0);

	if(m_recViewer[wParam - IDC_CUSTOM1].GetBckColor() == RGB(255, 0, 0))
	{
		//Clear this rec.
		int i = wParam - IDC_CUSTOM1;
		int result = (i / 9) / 3 - (i % 9) / 3;
		if(1 == result || (-1) == result)
		{
			m_recViewer[i].SetBckColor(RGB(247, 247, 217));
		}
		else
		{
			m_recViewer[i].SetBckColor(RGB(255, 255, 255));
		}

		//Clear another rect.
		for(int j = 0;j < 81;j ++)
		{
			if(m_recViewer[j].GetBckColor() == RGB(255, 0, 0))
			{
				//MessageBox(_T("sdfji"));
				if(m_selectNum == m_recViewer[j].GetNum())
				{
					m_recViewer[j].SetBckColor(RGB(255, 255, 0));
				}
				else
				{
					int result = (j / 9) / 3 - (j % 9) / 3;
					if(1 == result || (-1) == result)
					{
						m_recViewer[j].SetBckColor(RGB(247, 247, 217));
					}
					else
					{
						m_recViewer[j].SetBckColor(RGB(255, 255, 255));
					}
				}
				break;
			}
			
		}

		if(m_bHasWrong)
		{
			for(int j = 0;j < 81;j ++)
			{
				if(m_recViewer[j].GetNum() != 0)
				{
					if(CheckWrongRec(j))
					{
						return 0;
					}
				}
			}
			m_bHasWrong = false;
		}
	}

	int i = wParam - IDC_CUSTOM1;
	int result = (i / 9) / 3 - (i % 9) / 3;
	if(1 == result || (-1) == result)
	{
		m_recViewer[i].SetBckColor(RGB(247, 247, 217));
	}
	else
	{
		m_recViewer[i].SetBckColor(RGB(255, 255, 255));
	}
	
	if(!m_bModal)
	{
		
		int baseRow = (wParam - IDC_CUSTOM1) / 9;
		int baseCol = (wParam - IDC_CUSTOM1) % 9;
		baseRow = baseRow / 3 * 3;
		baseCol = baseCol / 3 * 3;
		for(int i = 0;i < 3;i ++)
		{
			for(int j = 0;j < 3;j ++)
			{
				if (m_recViewer[(baseRow + i) * 9 + baseCol + j].GetNum() == 0)
				{
					CheckAddNum((baseRow + i) * 9 + baseCol + j);
				}
				else
				{
					m_recViewer[wParam - IDC_CUSTOM1].RemoveNum(m_recViewer[(baseRow + i) * 9 + baseCol + j].GetNum());
				}
			}
		}
		int baseIndex = (wParam - IDC_CUSTOM1) / 9 * 9;
		for(int i = 0;i < 9;i ++)
		{
			if(m_recViewer[baseIndex + i].GetNum() == 0)
			{
				CheckAddNum(baseIndex + i);
			}
			else
			{
				m_recViewer[wParam - IDC_CUSTOM1].RemoveNum(m_recViewer[baseIndex + i].GetNum());
			}
		}

		baseIndex = (wParam - IDC_CUSTOM1) % 9;
		for(int i = 0;i < 81;i += 9)
		{
			if(m_recViewer[baseIndex + i].GetNum() == 0)
			{
				CheckAddNum(baseIndex + i);
			}
			else
			{
				m_recViewer[wParam - IDC_CUSTOM1].RemoveNum(m_recViewer[baseIndex + i].GetNum());
			}
		}
	}
	return 0;
}

void CSudokuDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	
	//m_recViewer[4].SetNum(8, RGB(255, 0, 0));
}

void CSudokuDlg::OnBnClickedRadio2()
{
	for(int i = 0;i < 81;i ++)
	{
		if(m_recViewer[i].GetNum() == m_selectNum && m_recViewer[i].GetBckColor() != RGB(255, 0, 0))
		{
			int result = (i / 9) / 3 - (i % 9) / 3;
			if(1 == result || (-1) == result)
			{
				m_recViewer[i].SetBckColor(RGB(247, 247, 217));
			}
			else
			{
				m_recViewer[i].SetBckColor(RGB(255, 255, 255));
			}
		}
	}

	m_selectNum = 2;

	for(int i = 0;i < 81;i ++)
	{
		if(m_recViewer[i].GetNum() == m_selectNum)
		{
			m_recViewer[i].SetBckColor(RGB(255, 255, 0));
		}
	}
}

void CSudokuDlg::OnBnClickedRadio3()
{
	for(int i = 0;i < 81;i ++)
	{
		if(m_recViewer[i].GetNum() == m_selectNum)
		{
			int result = (i / 9) / 3 - (i % 9) / 3;
			if(1 == result || (-1) == result)
			{
				m_recViewer[i].SetBckColor(RGB(247, 247, 217));
			}
			else
			{
				m_recViewer[i].SetBckColor(RGB(255, 255, 255));
			}
		}
	}

	m_selectNum = 3;

	for(int i = 0;i < 81;i ++)
	{
		if(m_recViewer[i].GetNum() == m_selectNum)
		{
			m_recViewer[i].SetBckColor(RGB(255, 255, 0));
		}
	}
}

void CSudokuDlg::OnBnClickedRadio4()
{
	for(int i = 0;i < 81;i ++)
	{
		if(m_recViewer[i].GetNum() == m_selectNum)
		{
			int result = (i / 9) / 3 - (i % 9) / 3;
			if(1 == result || (-1) == result)
			{
				m_recViewer[i].SetBckColor(RGB(247, 247, 217));
			}
			else
			{
				m_recViewer[i].SetBckColor(RGB(255, 255, 255));
			}
		}
	}

	m_selectNum = 4;

	for(int i = 0;i < 81;i ++)
	{
		if(m_recViewer[i].GetNum() == m_selectNum)
		{
			m_recViewer[i].SetBckColor(RGB(255, 255, 0));
		}
	}
}

void CSudokuDlg::OnBnClickedRadio5()
{
	for(int i = 0;i < 81;i ++)
	{
		if(m_recViewer[i].GetNum() == m_selectNum)
		{
			int result = (i / 9) / 3 - (i % 9) / 3;
			if(1 == result || (-1) == result)
			{
				m_recViewer[i].SetBckColor(RGB(247, 247, 217));
			}
			else
			{
				m_recViewer[i].SetBckColor(RGB(255, 255, 255));
			}
		}
	}

	m_selectNum = 5;

	for(int i = 0;i < 81;i ++)
	{
		if(m_recViewer[i].GetNum() == m_selectNum)
		{
			m_recViewer[i].SetBckColor(RGB(255, 255, 0));
		}
	}
}

void CSudokuDlg::OnBnClickedRadio6()
{
	for(int i = 0;i < 81;i ++)
	{
		if(m_recViewer[i].GetNum() == m_selectNum)
		{
			int result = (i / 9) / 3 - (i % 9) / 3;
			if(1 == result || (-1) == result)
			{
				m_recViewer[i].SetBckColor(RGB(247, 247, 217));
			}
			else
			{
				m_recViewer[i].SetBckColor(RGB(255, 255, 255));
			}
		}
	}

	m_selectNum = 6;

	for(int i = 0;i < 81;i ++)
	{
		if(m_recViewer[i].GetNum() == m_selectNum)
		{
			m_recViewer[i].SetBckColor(RGB(255, 255, 0));
		}
	}
}

void CSudokuDlg::OnBnClickedRadio7()
{
	for(int i = 0;i < 81;i ++)
	{
		if(m_recViewer[i].GetNum() == m_selectNum)
		{
			int result = (i / 9) / 3 - (i % 9) / 3;
			if(1 == result || (-1) == result)
			{
				m_recViewer[i].SetBckColor(RGB(247, 247, 217));
			}
			else
			{
				m_recViewer[i].SetBckColor(RGB(255, 255, 255));
			}
		}
	}

	m_selectNum = 7;

	for(int i = 0;i < 81;i ++)
	{
		if(m_recViewer[i].GetNum() == m_selectNum)
		{
			m_recViewer[i].SetBckColor(RGB(255, 255, 0));
		}
	}
}

void CSudokuDlg::OnBnClickedRadio8()
{
	for(int i = 0;i < 81;i ++)
	{
		if(m_recViewer[i].GetNum() == m_selectNum)
		{
			int result = (i / 9) / 3 - (i % 9) / 3;
			if(1 == result || (-1) == result)
			{
				m_recViewer[i].SetBckColor(RGB(247, 247, 217));
			}
			else
			{
				m_recViewer[i].SetBckColor(RGB(255, 255, 255));
			}
		}
	}

	m_selectNum = 8;

	for(int i = 0;i < 81;i ++)
	{
		if(m_recViewer[i].GetNum() == m_selectNum)
		{
			m_recViewer[i].SetBckColor(RGB(255, 255, 0));
		}
	}
}

void CSudokuDlg::OnBnClickedRadio9()
{
	for(int i = 0;i < 81;i ++)
	{
		if(m_recViewer[i].GetNum() == m_selectNum)
		{
			int result = (i / 9) / 3 - (i % 9) / 3;
			if(1 == result || (-1) == result)
			{
				m_recViewer[i].SetBckColor(RGB(247, 247, 217));
			}
			else
			{
				m_recViewer[i].SetBckColor(RGB(255, 255, 255));
			}
		}
	}

	m_selectNum = 9;

	for(int i = 0;i < 81;i ++)
	{
		if(m_recViewer[i].GetNum() == m_selectNum)
		{
			m_recViewer[i].SetBckColor(RGB(255, 255, 0));
		}
	}
}

bool CSudokuDlg::CheckWrongRec(int id)
{
	int baseRow = id / 9;
	int baseCol = id % 9;
	baseRow = baseRow / 3 * 3;
	baseCol = baseCol / 3 * 3;
	for(int i = 0;i < 3;i ++)
	{
		for(int j = 0;j < 3;j ++)
		{
			if (m_recViewer[(baseRow + i) * 9 + baseCol + j].GetNum() != 0 && ((baseRow + i) * 9 + baseCol + j != id) &&
				m_recViewer[(baseRow + i) * 9 + baseCol + j].GetNum() == m_recViewer[id].GetNum())
			{
				m_recViewer[(baseRow + i) * 9 + baseCol + j].SetBckColor(RGB(255, 0, 0));
				m_recViewer[id].SetBckColor(RGB(255, 0, 0));
				m_bHasWrong = true;
				return true;
			}
		}
	}
	int baseIndex = id / 9 * 9;
	for(int i = 0;i < 9;i ++)
	{
		if(m_recViewer[baseIndex + i].GetNum() != 0 && ((baseIndex + i) != id) &&
			m_recViewer[baseIndex + i].GetNum() == m_recViewer[id].GetNum())
		{
			m_recViewer[baseIndex + i].SetBckColor(RGB(255, 0, 0));
			m_recViewer[id].SetBckColor(RGB(255, 0, 0));
			m_bHasWrong = true;
			return true;
		}
	}

	baseIndex = id % 9;
	for(int i = 0;i < 81;i += 9)
	{
		if(m_recViewer[baseIndex + i].GetNum() != 0 && ((baseIndex + i) != id) &&
			m_recViewer[baseIndex + i].GetNum() == m_recViewer[id].GetNum())
		{
			m_recViewer[baseIndex + i].SetBckColor(RGB(255, 0, 0));
			m_recViewer[id].SetBckColor(RGB(255, 0, 0));
			m_bHasWrong = true;
			return true;
		}
	}

	return false;
}

void CSudokuDlg::OnBnClickedRadio11()
{
	// TODO: Add your control notification handler code here
	for(int i = 0;i < 81;i ++)
		m_recViewer[i].SetModel(true);
	m_bModal = true;
}

void CSudokuDlg::OnBnClickedRadio12()
{
	// TODO: Add your control notification handler code here
	
	m_bModal = false;
	for(int id = 0;id < 81;id ++)
	{
		if(m_recViewer[id].GetNum() != 0)
		{
			int baseRow = id / 9;
			int baseCol = id % 9;
			baseRow = baseRow / 3 * 3;
			baseCol = baseCol / 3 * 3;
			for(int i = 0;i < 3;i ++)
			{
				for(int j = 0;j < 3;j ++)
				{
					if (m_recViewer[(baseRow + i) * 9 + baseCol + j].GetNum() == 0)
					{
						m_recViewer[(baseRow + i) * 9 + baseCol + j].RemoveNum(m_recViewer[id].GetNum());
					}
				}
			}
			int baseIndex = id / 9 * 9;
			for(int i = 0;i < 9;i ++)
			{
				if(m_recViewer[baseIndex + i].GetNum() == 0)
				{
					m_recViewer[baseIndex + i].RemoveNum(m_recViewer[id].GetNum());
				}
			}

			baseIndex = id % 9;
			for(int i = 0;i < 81;i += 9)
			{
				if(m_recViewer[baseIndex + i].GetNum() == 0)
				{
					m_recViewer[baseIndex + i].RemoveNum(m_recViewer[id].GetNum());
				}
			}
		}
	}
	for(int i = 0;i < 81;i ++)
		m_recViewer[i].SetModel(false);
}

void CSudokuDlg::OnNewgameAdvanced()
{
	// TODO: Add your command handler code here
	/*
	for(int i = 0;i < 81;i ++)
			m_recViewer[i].SetModel(true);*/
	
	for(int i = 0;i < 9;i ++)
	{
		m_numStatus[i].SetZero();
	}
	int table[9][9] = {0};
	m_numTable.CreateNumTbe(table);

	for(int i = 0;i < 9;i ++)
	{
		for(int j = 0;j < 9;j ++)
		{
			m_resultTable[i][j] = table[i][j];
		}
	}

	for(int i = 0;i < 3;i ++)
	{
		for(int j = 0;j < 3;j ++)
		{
			switch(rand() % 6)
			{
			case 0:
				{
					table[i * 3][j * 3] = 0;
					table[i * 3 + 1][j * 3 + 1] = 0;
					table[i * 3 + 2][j * 3 + 2] = 0;
					break;
				}
			case 1:
				{
					table[i * 3][j * 3] = 0;
					table[i * 3 + 1][j * 3 + 2] = 0;
					table[i * 3 + 2][j * 3 + 1] = 0;
					break;
				}
			case 2:
				{
					table[i * 3][j * 3 + 1] = 0;
					table[i * 3 + 1][j * 3] = 0;
					table[i * 3 + 2][j * 3 + 2] = 0;
					break;
				}
			case 3:
				{
					table[i * 3][j * 3 + 1] = 0;
					table[i * 3 + 1][j * 3 + 2] = 0;
					table[i * 3 + 2][j * 3] = 0;
					break;
				}
			case 4:
				{
					table[i * 3][j * 3 + 2] = 0;
					table[i * 3 + 1][j * 3] = 0;
					table[i * 3 + 2][j * 3 + 1] = 0;
					break;
				}
			case 5:
				{
					table[i * 3][j * 3 + 2] = 0;
					table[i * 3 + 1][j * 3 + 1] = 0;
					table[i * 3 + 2][j * 3] = 0;
					break;
				}
			}
		}
	}

	int zero = 81;


	for(int i = 0;i < 9;i ++)
	{
		for(int j = 0;j < 9;j ++)
		{
			int temp = table[i][j];
			if(temp != 0)
			{

				table[i][j] = 0;
				CNodeTable nodeTable;
				nodeTable.initTable(table);
				if(nodeTable.AwrNum() > 1)
				{
					table[i][j] = temp;
					zero --;
				}
			}
		}
	}

	for(int i = 0;i < 9;i ++)
	{
		for(int j = 0;j < 9;j ++)
		{
			if(table[i][j] != 0)
			{
				m_recViewer[i * 9 + j].SetNum(table[i][j]);
				m_numStatus[table[i][j] - 1] ++;
			}
			else
			{
				m_recViewer[i * 9 + j].SetNum(0);
			}

			m_table[i][j] = table[i][j];
		}
	}
	for(int i = 0;i < 81;i ++)
	{
		int result = (i / 9) / 3 - (i % 9) / 3;
		if(1 == result || (-1) == result)
		{
			m_recViewer[i].SetBckColor(RGB(247, 247, 217));
		}
		else
		{
			m_recViewer[i].SetBckColor(RGB(255, 255, 255));
		}
	}
	GetDlgItem(IDC_RADIO1 + m_selectNum - 1)->SendMessage(BM_CLICK, 0, 0);

	if(!m_bModal)
		GetDlgItem(IDC_RADIO12)->SendMessage(BM_CLICK, 0, 0);
	m_timeViewer.SetZero();
	m_timeViewer.Start();
}

void CSudokuDlg::CheckAddNum(int id)
{
	for(int num = 1;num < 10;num ++)
	{
		int baseRow = id / 9;
		int baseCol = id % 9;
		baseRow = baseRow / 3 * 3;
		baseCol = baseCol / 3 * 3;
		for(int i = 0;i < 3;i ++)
		{
			for(int j = 0;j < 3;j ++)
			{
				if (m_recViewer[(baseRow + i) * 9 + baseCol + j].GetNum() == num)
				{
					goto Label;
				}
			}
		}
		int baseIndex = id / 9 * 9;
		for(int i = 0;i < 9;i ++)
		{
			if(m_recViewer[baseIndex + i].GetNum() == num)
			{
				goto Label;
			}
		}

		baseIndex = id % 9;
		for(int i = 0;i < 81;i += 9)
		{
			if(m_recViewer[baseIndex + i].GetNum() == num)
			{
				goto Label;
			}
		}
		m_recViewer[id].AddNum(num);
Label:;
	}
}

void CSudokuDlg::OnEditSeeanswer()
{
	// TODO: Add your command handler code here
	if(IDOK == MessageBox(_T("Are you sure to see the answer?"), _T("Confirm"), MB_OKCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2))
	{
		/*
		bool a[81];
		//a[10] = false;
		for(int i = 0;i < 9;i ++)
		{
			for(int j = 0;j < 9;j ++)
			{
				if(m_table[i][j] != 0)
				{
					a[i * 9 + j] = false;
				}
			}
		}
		CKeyDlg dlg(this, m_resultTable, a);
		dlg.DoModal();
		*/

		CNodeTable nodeTable;
		nodeTable.initTable(m_table);
		int awrNum = nodeTable.AwrNum();
		if(awrNum == 0)
		{
			MessageBox(_T("It has no answers"), _T("Wrong"), MB_OK | MB_ICONERROR);
		}
		else if(awrNum == 1)
		{
			bool a[81];
			//a[10] = false;
			for(int i = 0;i < 9;i ++)
			{
				for(int j = 0;j < 9;j ++)
				{
					if(m_table[i][j] != 0)
					{
						a[i * 9 + j] = false;
					}
				}
			}

			int table[9][9];
			for(int i = 0;i < 9;i ++)
			{
				for(int j = 0;j < 9;j ++)
				{
					table[i][j] = nodeTable.GetFirstNode(i, j)->getData();
				}
			}
			CKeyDlg dlg(this, table, a);
			dlg.DoModal();
		}
		else
		{
			int table1[9][9];
			for(int i = 0;i < 9;i ++)
			{
				for(int j = 0;j < 9;j ++)
				{
					table1[i][j] = nodeTable.GetFirstNode(i, j)->getData();
				}
			}

			int table2[9][9];
			for(int i = 0;i < 9;i ++)
			{
				for(int j = 0;j < 9;j ++)
				{
					table2[i][j] = nodeTable.GetNode(i, j)->getData();
				}
			}
			CKeysDlg dlg(this, table1, table2);
			dlg.DoModal();
		}
	}
}

void CSudokuDlg::OnEditTips()
{
	int table[9][9];
	for(int i = 0;i < 9;i ++)
	{
		for(int j = 0;j < 9;j ++)
		{
			table[i][j] = m_recViewer[i * 9 + j].GetNum();
		}
	}

	for(int i = 0;i < 81;i ++)
	{
		if(m_recViewer[i].GetBckColor() != RGB(255, 255, 255))
		{
			m_recViewer[i].SetBckColor(RGB(255, 255, 255));
		}
	}
	CTipDlg dlg(this, table);
	// /dlg.SetWindowPos(this, 0, 0, 100, 100, 0);
	
	dlg.DoModal();
	
}

void CSudokuDlg::OnGameCreategame()
{
	// TODO: Add your command handler code here
	CCreateDlg dlg;
	dlg.DoModal();
	
}

void CSudokuDlg::OnGameSaveaspictrues()
{
	// TODO: Add your command handler code here
	if(*m_szFile == _T('\0'))
		return;
	
	LPCTSTR lpFilter = _T("JPEG Image File (*.jpg) |*.jpg| Bitmap (*.bmp) |*.bmp| GIF (*.gif) |*.gif||");
	CFileDialog dlg(FALSE, _T("*.jpg"), _T("Untitled"), OFN_READONLY | OFN_OVERWRITEPROMPT, lpFilter, this);
	if(dlg.DoModal() == IDOK)
	{

		CDC* pDC = GetDC();
		Bitmap bmp(466, 462);

		Graphics g(&bmp);
		HDC hDC = g.GetHDC();
		BitBlt(hDC, 0, 0, 466, 462, *pDC, 7, 45, SRCCOPY);
		g.ReleaseHDC(hDC);

		ReleaseDC(pDC);

		WCHAR szSave[MAX_PATH] = {0};
#ifdef UNICODE
		_tcscpy_s(szSave, dlg.GetPathName());
#else
		MultiByteToWideChar(CP_ACP, 0, dlg.GetPathName(), -1, szSave, sizeof(szSave)/sizeof(szSave[0]));
#endif
		CLSID fmt = {0};
		int nFilter = dlg.m_ofn.nFilterIndex;
		switch(nFilter)
		{
		case 3:
			//wcscat_s(szSave, _T(".gif"));
			GetImageCLSID(L"image/gif", &fmt);
			break;
		case 1:
			//wcscat_s(szSave, _T(".jpg"));
			GetImageCLSID(L"image/jpeg", &fmt);
			break;
		default:
			//wcscat_s(szSave, _T(".bmp"));
			GetImageCLSID(L"image/bmp", &fmt);
			break;
		}

		bmp.Save(szSave, &fmt);
	}
}

int CSudokuDlg::GetImageCLSID(const WCHAR* format, CLSID* pCLSID)
{
	UINT nNum = 0;
	UINT nSize = 0;
	ImageCodecInfo* pImageCodecInfo = NULL;

	//Get the system's support pictrue's format.
	GetImageEncodersSize(&nNum, &nSize);
	if(nSize == 0)
		return FALSE;

	pImageCodecInfo = (ImageCodecInfo *) (malloc(nSize));
	if(pImageCodecInfo == NULL)
		return FALSE;

	GetImageEncoders(nNum, nSize, pImageCodecInfo);

	for(UINT i = 0;i < nNum;i ++)
	{
		if(wcscmp(pImageCodecInfo[i].MimeType, format) == 0)
		{
			*pCLSID = pImageCodecInfo[i].Clsid;
			free(pImageCodecInfo);
			return TRUE;
		}
	}
	free(pImageCodecInfo);
	return FALSE;
}

void CSudokuDlg::OnEditCheck()
{
	// TODO: Add your command handler code here
	CNodeTable nodeTable;
	nodeTable.initTable(m_table);
	if(nodeTable.AwrNum() != 1)
	{
		MessageBox(_T("No mistakes"), _T("Result"), MB_ICONINFORMATION | MB_OK);
		return;
	}

	for(int i = 0;i < 9;i ++)
	{
		for(int j = 0;j < 9;j ++)
		{
			if(m_recViewer[i * 9 + j].GetBckColor() != RGB(255, 0, 0) && m_recViewer[i * 9 + j].GetNum() != 0 && m_resultTable[i][j] != m_recViewer[i * 9 + j].GetNum())
			{
				m_recViewer[i * 9 + j].SetBckColor(RGB(255, 0, 0));
				m_wrongNum.push_back(i * 9 + j);
			}
		}
	}

	bool hasWrong = false;
	for(int i = 0;i < 81;i ++)
	{
		if(m_recViewer[i].GetBckColor() == RGB(255, 0, 0))
		{
			hasWrong = true;
		}
	}

	if(!hasWrong)
	{
		MessageBox(_T("No mistakes"), _T("Result"), MB_ICONINFORMATION | MB_OK);
	}
}

void CSudokuDlg::OnEditUndoall()
{
	if(IDOK == MessageBox(_T("Are you sure to undo all?"), _T("Confirm"), MB_OKCANCEL | MB_ICONQUESTION | MB_DEFBUTTON2))
	{
		for(int i = 0;i < 9;i ++)
		{
			for(int j = 0;j < 9;j ++)
			{
				if(0 == m_table[i][j])
				{
					m_recViewer[i * 9 + j].SetNum(0);
				}
			}
		}

		for(int i = 0;i < 81;i ++)
		{
			int result = (i / 9) / 3 - (i % 9) / 3;
			if(1 == result || (-1) == result)
			{
				m_recViewer[i].SetBckColor(RGB(247, 247, 217));
			}
			else
			{
				m_recViewer[i].SetBckColor(RGB(255, 255, 255));
			}
		}
		GetDlgItem(IDC_RADIO1 + m_selectNum - 1)->SendMessage(BM_CLICK, 0, 0);

		if(!m_bModal)
			GetDlgItem(IDC_RADIO12)->SendMessage(BM_CLICK, 0, 0);
		m_timeViewer.SetZero();
		m_timeViewer.Start();
	}
}

LRESULT CSudokuDlg::OnCreateMessage(WPARAM wParam, LPARAM lParam)
{
	int* table = (int*) lParam;
	for(int i = 0;i < 9;i ++)
	{
		for(int j = 0;j < 9;j ++)
		{
			if(table[i * 9 + j] != 0)
			{
				m_recViewer[i * 9 + j].SetNum(table[i * 9 + j]);
				m_numStatus[table[i * 9 + j] - 1] ++;
			}
			else
			{
				m_recViewer[i * 9 + j].SetNum(0);
			}

			m_table[i][j] = table[i * 9 + j];
		}
	}
	for(int i = 0;i < 81;i ++)
	{
		int result = (i / 9) / 3 - (i % 9) / 3;
		if(1 == result || (-1) == result)
		{
			m_recViewer[i].SetBckColor(RGB(247, 247, 217));
		}
		else
		{
			m_recViewer[i].SetBckColor(RGB(255, 255, 255));
		}
	}
	GetDlgItem(IDC_RADIO1 + m_selectNum - 1)->SendMessage(BM_CLICK, 0, 0);

	if(!m_bModal)
		GetDlgItem(IDC_RADIO12)->SendMessage(BM_CLICK, 0, 0);
	m_timeViewer.SetZero();
	m_timeViewer.Start();
	delete[] table;

	//Initial the result.
	CNodeTable nodeTable;
	nodeTable.initTable(m_table);
	if(nodeTable.AwrNum() == 1)
	{
		for(int i = 0;i < 9;i ++)
		{
			for(int j = 0;j < 9;j ++)
			{
				m_resultTable[i][j] = nodeTable.GetFirstNode(i, j)->getData();
			}
		}
	}
	return 0;
}
void CAboutDlg::OnNMClickSyslink1(NMHDR *pNMHDR, LRESULT *pResult)
{
	 ShellExecuteW(NULL, L"open", _T("http://software.nju.edu.cn"), NULL, NULL, SW_SHOWNORMAL); 
}

//BOOL CAboutDlg::OnInitDialog()
//{
//	CDialog::OnInitDialog();
//
//	m_link.SetWindowText(_T("欢迎光临<a href="\" mce_href="\""http://blog.csdn.net/akof1314\">无幻博客</a>")); 
//
//	return TRUE;  // return TRUE unless you set the focus to a control
//	// EXCEPTION: OCX Property Pages should return FALSE
//}

void CSudokuDlg::OnNewgameStarter()
{
	for(int i = 0;i < 9;i ++)
	{
		m_numStatus[i].SetZero();
	}
	int table[9][9] = {0};
	m_numTable.CreateNumTbe(table);

	for(int i = 0;i < 9;i ++)
	{
		for(int j = 0;j < 9;j ++)
		{
			m_resultTable[i][j] = table[i][j];
		}
	}


	for(int i = 0;i < 9;i ++)
	{
		for(int j = 0;j < 9;j ++)
		{
			if((rand() % 9) > 3)
			{
				int temp = table[i][j];
				table[i][j] = 0;
				CNodeTable nodeTable;
				nodeTable.initTable(table);
				if(nodeTable.AwrNum() > 1)
				{
					table[i][j] = temp;
				}
			}
		}
	}

	for(int i = 0;i < 9;i ++)
	{
		for(int j = 0;j < 9;j ++)
		{
			if(table[i][j] != 0)
			{
				m_recViewer[i * 9 + j].SetNum(table[i][j]);
				m_numStatus[table[i][j] - 1] ++;
			}
			else
			{
				m_recViewer[i * 9 + j].SetNum(0);
			}

			m_table[i][j] = table[i][j];
		}
	}
	for(int i = 0;i < 81;i ++)
	{
		int result = (i / 9) / 3 - (i % 9) / 3;
		if(1 == result || (-1) == result)
		{
			m_recViewer[i].SetBckColor(RGB(247, 247, 217));
		}
		else
		{
			m_recViewer[i].SetBckColor(RGB(255, 255, 255));
		}
	}
	GetDlgItem(IDC_RADIO1 + m_selectNum - 1)->SendMessage(BM_CLICK, 0, 0);

	if(!m_bModal)
		GetDlgItem(IDC_RADIO12)->SendMessage(BM_CLICK, 0, 0);
	m_timeViewer.SetZero();
	m_timeViewer.Start();
}

void CSudokuDlg::OnNewgameBeginner()
{
	for(int i = 0;i < 9;i ++)
	{
		m_numStatus[i].SetZero();
	}
	int table[9][9] = {0};
	m_numTable.CreateNumTbe(table);

	for(int i = 0;i < 9;i ++)
	{
		for(int j = 0;j < 9;j ++)
		{
			m_resultTable[i][j] = table[i][j];
		}
	}


	for(int i = 0;i < 9;i ++)
	{
		for(int j = 0;j < 9;j ++)
		{
			if((rand() % 9) > 2)
			{
				int temp = table[i][j];
				table[i][j] = 0;
				CNodeTable nodeTable;
				nodeTable.initTable(table);
				if(nodeTable.AwrNum() > 1)
				{
					table[i][j] = temp;
				}
			}
		}
	}

	for(int i = 0;i < 9;i ++)
	{
		for(int j = 0;j < 9;j ++)
		{
			if(table[i][j] != 0)
			{
				m_recViewer[i * 9 + j].SetNum(table[i][j]);
				m_numStatus[table[i][j] - 1] ++;
			}
			else
			{
				m_recViewer[i * 9 + j].SetNum(0);
			}

			m_table[i][j] = table[i][j];
		}
	}
	for(int i = 0;i < 81;i ++)
	{
		int result = (i / 9) / 3 - (i % 9) / 3;
		if(1 == result || (-1) == result)
		{
			m_recViewer[i].SetBckColor(RGB(247, 247, 217));
		}
		else
		{
			m_recViewer[i].SetBckColor(RGB(255, 255, 255));
		}
	}
	GetDlgItem(IDC_RADIO1 + m_selectNum - 1)->SendMessage(BM_CLICK, 0, 0);

	if(!m_bModal)
		GetDlgItem(IDC_RADIO12)->SendMessage(BM_CLICK, 0, 0);
	m_timeViewer.SetZero();
	m_timeViewer.Start();
}

void CSudokuDlg::OnNewgameIntermediate()
{

	for(int i = 0;i < 9;i ++)
	{
		m_numStatus[i].SetZero();
	}
	int table[9][9] = {0};
	m_numTable.CreateNumTbe(table);

	for(int i = 0;i < 9;i ++)
	{
		for(int j = 0;j < 9;j ++)
		{
			m_resultTable[i][j] = table[i][j];
		}
	}


	for(int i = 0;i < 9;i ++)
	{
		for(int j = 0;j < 9;j ++)
		{
			if((rand() % 9) > 2)
			{
				int temp = table[i][j];
				table[i][j] = 0;
				CNodeTable nodeTable;
				nodeTable.initTable(table);
				if(nodeTable.AwrNum() > 1)
				{
					table[i][j] = temp;
				}
			}
		}
	}

	for(int i = 0;i < 9;i ++)
	{
		for(int j = 0;j < 9;j ++)
		{
			if(table[i][j] != 0)
			{
				int temp = table[i][j];
				table[i][j] = 0;
				CNodeTable nodeTable;
				nodeTable.initTable(table);
				if(nodeTable.AwrNum() > 1)
				{
					table[i][j] = temp;
				}
			}
		}
	}

	for(int i = 0;i < 9;i ++)
	{
		for(int j = 0;j < 9;j ++)
		{
			if(table[i][j] != 0)
			{
				m_recViewer[i * 9 + j].SetNum(table[i][j]);
				m_numStatus[table[i][j] - 1] ++;
			}
			else
			{
				m_recViewer[i * 9 + j].SetNum(0);
			}

			m_table[i][j] = table[i][j];
		}
	}
	for(int i = 0;i < 81;i ++)
	{
		int result = (i / 9) / 3 - (i % 9) / 3;
		if(1 == result || (-1) == result)
		{
			m_recViewer[i].SetBckColor(RGB(247, 247, 217));
		}
		else
		{
			m_recViewer[i].SetBckColor(RGB(255, 255, 255));
		}
	}
	GetDlgItem(IDC_RADIO1 + m_selectNum - 1)->SendMessage(BM_CLICK, 0, 0);

	if(!m_bModal)
		GetDlgItem(IDC_RADIO12)->SendMessage(BM_CLICK, 0, 0);
	m_timeViewer.SetZero();
	m_timeViewer.Start();
}

LRESULT CSudokuDlg::OnChooseMessage(WPARAM wParam, LPARAM lParam)
{
	HRESULT hr;
	TASKDIALOGCONFIG tdc = { sizeof(TASKDIALOGCONFIG) };
	int nClickedBtn;
	LPCWSTR szTitle = L"Select Difficulty",
		szHeader = L"What level of difficulty do you want to play?",
		szBodyText = L"There are five levels of difficulty." \
		L"You must choose one to play.";


	LPCWSTR szExtraInfo =
		L"Note: You can create a game by clicking the Create on the edit menu.";

	TASKDIALOG_BUTTON aCustomButtons[] = {
		{ 1000, L"&Starter\n" 
		 L"Less than 40 block will be empty."},
		{ 1001, L"&Beginner\n" 
		 L"Less than 50 block will be empty."},
		{ 1002, L"&Intermediate\n" 
		 L"Less than 55 block will be empty."},
		{ 1003, L"&Advanced\n" 
		 L"Less than 55 block will be empty."},
		{ 1004, L"Super &Hard\n" 
		 L"Extremely hard to play."}
	};

	tdc.hwndParent = m_hWnd;
	tdc.dwFlags = TDF_USE_COMMAND_LINKS | TDF_EXPAND_FOOTER_AREA;
	tdc.pButtons = aCustomButtons;
	tdc.cButtons = _countof(aCustomButtons);
	tdc.pszWindowTitle = szTitle;
	//tdc.pszMainIcon = TD_SHIELD_ICON;
	tdc.pszMainInstruction = szHeader;
	tdc.pszExpandedInformation = szExtraInfo;
	tdc.dwCommonButtons = TDCBF_CANCEL_BUTTON;
	tdc.pszContent = szBodyText;


	hr = TaskDialogIndirect(&tdc, &nClickedBtn, NULL, NULL);

	if(SUCCEEDED(hr) && 1000 == nClickedBtn)
	{
		::PostMessage(this->m_hWnd,WM_COMMAND,ID_NEWGAME_STARTER,0);
	} else if(SUCCEEDED(hr) && 1001 == nClickedBtn)
	{
		::PostMessage(this->m_hWnd,WM_COMMAND,ID_NEWGAME_BEGINNER,0);
	} else if(SUCCEEDED(hr) && 1002 == nClickedBtn)
	{
		::PostMessage(this->m_hWnd,WM_COMMAND, ID_NEWGAME_INTERMEDIATE,0);
	} else if(SUCCEEDED(hr) && 1003 == nClickedBtn)
	{
		::PostMessage(this->m_hWnd,WM_COMMAND,ID_NEWGAME_ADVANCED,0);
	} else if(SUCCEEDED(hr) && 1004 == nClickedBtn)
	{
		::PostMessage(this->m_hWnd,WM_COMMAND, ID_NEWGAME_SUPERHARD,0);
	} else {
		exit(0);
	}

	return 0;
}
void CSudokuDlg::OnGameExit()
{
	exit(0);
}

LRESULT CSudokuDlg::OnSetColorMessage(WPARAM wParam, LPARAM lParam)
{
	if(lParam != 100)
	{
		COLORREF color = wParam;
		m_recViewer[lParam].SetBckColor(color);
	}
	else
	{
		for(int i = 0;i < 81;i ++)
		{
			if(m_recViewer[i].GetNum() == m_selectNum)
			{
				int result = (i / 9) / 3 - (i % 9) / 3;
				if(1 == result || (-1) == result)
				{
					m_recViewer[i].SetBckColor(RGB(247, 247, 217));
				}
				else
				{
					m_recViewer[i].SetBckColor(RGB(255, 255, 255));
				}
			}
		}
	}
	return 0;
}

LRESULT CSudokuDlg::OnSetNumMessage(WPARAM wParam, LPARAM lParam)
{
	m_numStatus[wParam - 1] ++;
	m_recViewer[lParam].SetNum(wParam, RGB(0, 0, 255));
	if(!m_bModal)
	{
		int baseRow = (lParam) / 9;
		int baseCol = (lParam) % 9;
		baseRow = baseRow / 3 * 3;
		baseCol = baseCol / 3 * 3;
		for(int i = 0;i < 3;i ++)
		{
			for(int j = 0;j < 3;j ++)
			{
				if (m_recViewer[(baseRow + i) * 9 + baseCol + j].GetNum() == 0)
				{
					m_recViewer[(baseRow + i) * 9 + baseCol + j].RemoveNum(wParam);
				}
			}
		}
		int baseIndex = (lParam) / 9 * 9;
		for(int i = 0;i < 9;i ++)
		{
			if(m_recViewer[baseIndex + i].GetNum() == 0)
			{
				m_recViewer[baseIndex + i].RemoveNum(wParam);
			}
		}

		baseIndex = (lParam) % 9;
		for(int i = 0;i < 81;i += 9)
		{
			if(m_recViewer[baseIndex + i].GetNum() == 0)
			{
				m_recViewer[baseIndex + i].RemoveNum(wParam);
			}
		}
	}
	return 0;
}

LRESULT CSudokuDlg::OnTipCancelMessage(WPARAM wParam, LPARAM lParam)
{
	for(int i = 0;i < 81;i ++)
	{
		int result = (i / 9) / 3 - (i % 9) / 3;
		if(1 == result || (-1) == result)
		{
			m_recViewer[i].SetBckColor(RGB(247, 247, 217));
		}
		else
		{
			m_recViewer[i].SetBckColor(RGB(255, 255, 255));
		}
	}

	GetDlgItem(IDC_RADIO1 + m_selectNum - 1)->SendMessage(BM_CLICK, 0, 0);
	return 0;
}


void CSudokuDlg::Finished(void)
{
	m_timeViewer.Pause();
	HRESULT hr;
	TASKDIALOGCONFIG tdc = { sizeof(TASKDIALOGCONFIG) };
	int nClickedBtn;
	LPCWSTR szTitle = L"Congratulations",
		szHeader = L"You have finished the task!",
		szBodyText = L"What do you want to do next?";
	TASKDIALOG_BUTTON aCustomButtons[] = {
		{ 1000, L"Play &another game" },
		{ 1001, L"E&xit the game" }
	};

	tdc.hwndParent = m_hWnd;
	tdc.dwCommonButtons = TDCBF_CANCEL_BUTTON;
	tdc.pButtons = aCustomButtons;
	tdc.cButtons = _countof(aCustomButtons);
	tdc.pszWindowTitle = szTitle;
	tdc.pszMainIcon = TD_INFORMATION_ICON;
	tdc.pszMainInstruction = szHeader;
	tdc.pszContent = szBodyText;

	hr = TaskDialogIndirect ( &tdc, &nClickedBtn, NULL, NULL );

	if ( SUCCEEDED(hr) && 1000 == nClickedBtn )
	{
		PostMessage(WM_USER + 10, 0, 0);
	}
	else if ( SUCCEEDED(hr) && 1001 == nClickedBtn )
	{
		exit(0);
	}

}

void CSudokuDlg::OnNewgameSuperhard()
{
	for(int i = 0;i < 9;i ++)
	{
		m_numStatus[i].SetZero();
	}
	int table[9][9] = {0};
	m_numTable.CreateNumTbe(table);

	for(int i = 0;i < 9;i ++)
	{
		for(int j = 0;j < 9;j ++)
		{
			m_resultTable[i][j] = table[i][j];
		}
	}


	for(int i = 0;i < 9;i ++)
	{
		for(int j = 0;j < 9;j ++)
		{
			if((rand() % 9) > 2)
			{
				int temp = table[i][j];
				table[i][j] = 0;
				CNodeTable nodeTable;
				nodeTable.initTable(table);
				if(nodeTable.AwrNum() > 1)
				{
					table[i][j] = temp;
				}
			}
		}
	}

	for(int i = 0;i < 9;i ++)
	{
		for(int j = 0;j < 9;j ++)
		{
			if(table[i][j] != 0)
			{
				int temp = table[i][j];
				table[i][j] = 0;
				CNodeTable nodeTable;
				nodeTable.initTable(table);
				if(nodeTable.AwrNum() > 1)
				{
					table[i][j] = temp;
				}
			}
		}
	}

	for(int i = 0;i < 9;i ++)
	{
		for(int j = 0;j < 9;j ++)
		{
			if(table[i][j] != 0)
			{
				m_recViewer[i * 9 + j].SetNum(table[i][j]);
				m_numStatus[table[i][j] - 1] ++;
			}
			else
			{
				m_recViewer[i * 9 + j].SetNum(0);
			}

			m_table[i][j] = table[i][j];
		}
	}
	for(int i = 0;i < 81;i ++)
	{
		int result = (i / 9) / 3 - (i % 9) / 3;
		if(1 == result || (-1) == result)
		{
			m_recViewer[i].SetBckColor(RGB(247, 247, 217));
		}
		else
		{
			m_recViewer[i].SetBckColor(RGB(255, 255, 255));
		}
	}
	GetDlgItem(IDC_RADIO1 + m_selectNum - 1)->SendMessage(BM_CLICK, 0, 0);

	if(!m_bModal)
		GetDlgItem(IDC_RADIO12)->SendMessage(BM_CLICK, 0, 0);
	m_timeViewer.SetZero();
	m_timeViewer.Start();
}
