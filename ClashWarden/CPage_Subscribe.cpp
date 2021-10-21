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
}


BEGIN_MESSAGE_MAP(CPage_Subscribe, CDialogEx)
END_MESSAGE_MAP()


// CPage_Subscribe 消息处理程序
