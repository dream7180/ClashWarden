
// ClashWardenDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ClashWarden.h"
#include "ClashWardenDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CClashWardenDlg 对话框



CClashWardenDlg::CClashWardenDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CLASHWARDEN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClashWardenDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
}

BEGIN_MESSAGE_MAP(CClashWardenDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CClashWardenDlg::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDCANCEL, &CClashWardenDlg::OnBnClickedCancel)
	ON_MESSAGE(WM_TASKMESSAGE, OnTaskMessage)
	ON_COMMAND(ID_SHOW, OnShow)
	ON_COMMAND(ID_CLOSE, OnClose)
	ON_WM_SYSCOMMAND()
	ON_COMMAND(SC_MINIMIZE, setTray)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CClashWardenDlg 消息处理程序

BOOL CClashWardenDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_Tab.InsertItem(0, L"控制中心  ");
	m_Tab.InsertItem(1, L"服务器订阅  ");
	m_Tab.InsertItem(2, L"设置选项  ");
	m_Tab.InsertItem(3, L"帮助说明  ");

	m_Page1.Create(IDD_DIALOG_Main, GetDlgItem(IDC_TAB1));
	m_Page2.Create(IDD_DIALOG_Subscribe, GetDlgItem(IDC_TAB1));
	m_Page3.Create(IDD_DIALOG_Option, GetDlgItem(IDC_TAB1));
	m_Page4.Create(IDD_DIALOG_About, GetDlgItem(IDC_TAB1));
	CRect rs;
	m_Tab.GetClientRect(&rs);
	//调整子对话框在父窗口中的位置 
	int DpiY = 96;
	HDC hDC = ::GetDC(NULL);
	if (hDC != NULL)
	{
		DpiY = GetDeviceCaps(hDC, LOGPIXELSY);
		::ReleaseDC(NULL, hDC);
	}
	//double  dbScale = (double)(DpiY/DEFAULT_DPI);
	int yadd = (int)((DpiY / 96.0 - 1) * 20);
	rs.top += (23 + yadd);
	rs.bottom -= 2;
	rs.left += 1;
	rs.right -= 3;

	//设置子对话框尺寸并移动到指定位置 
	m_Page1.MoveWindow(&rs);
	m_Page2.MoveWindow(&rs);
	m_Page3.MoveWindow(&rs);
	m_Page4.MoveWindow(&rs);

	//分别设置隐藏和显示 
	m_Page1.ShowWindow(true);
	m_Page2.ShowWindow(false);
	m_Page3.ShowWindow(false);
	m_Page4.ShowWindow(false);

	//设置默认的选项卡 
	m_Tab.SetCurSel(0);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CClashWardenDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CClashWardenDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CClashWardenDlg::OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult)
{
	int CurSel = m_Tab.GetCurSel();
	switch (CurSel)

	{
	case 0:
		m_Page1.ShowWindow(true);
		m_Page2.ShowWindow(false);
		m_Page3.ShowWindow(false);
		m_Page4.ShowWindow(false);
		break;
	case 1:
		m_Page1.ShowWindow(false);
		m_Page2.ShowWindow(true);
		m_Page3.ShowWindow(false);
		m_Page4.ShowWindow(false);
		break;
	case 2:
		m_Page1.ShowWindow(false);
		m_Page2.ShowWindow(false);
		m_Page3.ShowWindow(true);
		m_Page4.ShowWindow(false);
		break;
	case 3:
		m_Page1.ShowWindow(false);
		m_Page2.ShowWindow(false);
		m_Page3.ShowWindow(false);
		m_Page4.ShowWindow(true);
	default:;
	}
	*pResult = 0;
}


void CClashWardenDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}



void CClashWardenDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if (nID == SC_MINIMIZE)
	{
		setTray();//最小化到托盘
	}else CDialogEx::OnSysCommand(nID, lParam);
}


LRESULT CClashWardenDlg::OnTaskMessage(WPARAM wParam, LPARAM lParam)
{
	switch (lParam)
	{
	case WM_LBUTTONUP://如果在图标上发生鼠标左键消息，则显示窗口，删除托盘图标
		ShowWindow(SW_SHOW);
		Shell_NotifyIcon(NIM_DELETE, &nid);
		break;
	case WM_RBUTTONUP:
		CMenu popmenu;
		POINT point;
		::GetCursorPos(&point);//获取当前鼠标的位置
		popmenu.CreatePopupMenu();//创建一个弹出式菜单
		popmenu.AppendMenu(MF_STRING, ID_SHOW, L"显示 Clash Warden");
		popmenu.AppendMenu(MF_STRING, ID_CLOSE, L"关闭");//添加两个菜单项
		SetForegroundWindow(); //这句话的作用是当弹出菜单失去焦点自动消失
		popmenu.TrackPopupMenu(TPM_LEFTBUTTON, point.x, point.y, this);//显示弹出式菜单

		popmenu.Detach();

		break;
	}
	return 0;
}

void CClashWardenDlg::OnShow()
{
	// TODO: 在此添加命令处理程序代码
	ShowWindow(SW_SHOW);
	Shell_NotifyIcon(NIM_DELETE, &nid);
}

void CClashWardenDlg::OnClose()
{
	// TODO: 在此添加命令处理程序代码
	CDialogEx::OnCancel();
}

void CClashWardenDlg::setTray()
{
	nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
	nid.hWnd = this->m_hWnd;
	nid.uID = IDR_MAINFRAME;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = WM_TASKMESSAGE;//自定义的消息名称 
	nid.hIcon = m_hIcon;// LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
	Shell_NotifyIcon(NIM_ADD, &nid); //在托盘区添加图标 
	ShowWindow(SW_HIDE); //隐藏主窗
}


void CClashWardenDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	Shell_NotifyIcon(NIM_DELETE, &nid);
}
