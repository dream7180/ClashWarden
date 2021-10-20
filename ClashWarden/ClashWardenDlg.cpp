
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
END_MESSAGE_MAP()


// CClashWardenDlg 消息处理程序

BOOL CClashWardenDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	m_Tab.InsertItem(0, L"控制中心");
	m_Tab.InsertItem(1, L"启动设置");
	m_Tab.InsertItem(2, L"关于");

	m_Page1.Create(IDD_DIALOG_Main, GetDlgItem(IDC_TAB1));
	m_Page2.Create(IDD_DIALOG_Option, GetDlgItem(IDC_TAB1));
	m_Page3.Create(IDD_DIALOG_About, GetDlgItem(IDC_TAB1));
	CRect rs;
	m_Tab.GetClientRect(&rs);
	//调整子对话框在父窗口中的位置 
	rs.top += 28;
	rs.bottom -= 2;
	rs.left += 1;
	rs.right -= 3;

	//设置子对话框尺寸并移动到指定位置 
	m_Page1.MoveWindow(&rs);
	m_Page2.MoveWindow(&rs);
	m_Page3.MoveWindow(&rs);

	//分别设置隐藏和显示 
	m_Page1.ShowWindow(true);
	m_Page2.ShowWindow(false);
	m_Page3.ShowWindow(false);

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
		break;
	case 1:
		m_Page1.ShowWindow(false);
		m_Page2.ShowWindow(true);
		m_Page3.ShowWindow(false);
		break;
	case 2:
		m_Page1.ShowWindow(false);
		m_Page2.ShowWindow(false);
		m_Page3.ShowWindow(true);
		break;
	default:;
	}
	*pResult = 0;
}
