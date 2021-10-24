// CPage_Subscribe.cpp: 实现文件
//

#include "pch.h"
#include "ClashWarden.h"
#include "CPage_Subscribe.h"
#include "afxdialogex.h"


// CPage_Subscribe 对话框

IMPLEMENT_DYNAMIC(CPage_Subscribe, CDialogEx)

CPage_Subscribe::CPage_Subscribe(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Subscribe, pParent)
{

}

CPage_Subscribe::~CPage_Subscribe()
{
}

void CPage_Subscribe::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LSubs, m_Subs);
}


BEGIN_MESSAGE_MAP(CPage_Subscribe, CDialogEx)
END_MESSAGE_MAP()


// CPage_Subscribe 消息处理程序


BOOL CPage_Subscribe::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_Subs.InsertColumn(0, L"名称");
	m_Subs.InsertColumn(1, L"地址");
	m_Subs.SetColumnWidth(0, 100);
	m_Subs.SetColumnWidth(1, 200);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
