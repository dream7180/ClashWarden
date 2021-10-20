// CPage_Option.cpp: 实现文件
//

#include "pch.h"
#include "ClashWarden.h"
#include "CPage_Option.h"
#include "afxdialogex.h"


// CPage_Option 对话框

IMPLEMENT_DYNAMIC(CPage_Option, CDialogEx)

CPage_Option::CPage_Option(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Option, pParent)
{

}

CPage_Option::~CPage_Option()
{
}

void CPage_Option::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPage_Option, CDialogEx)
END_MESSAGE_MAP()


// CPage_Option 消息处理程序
