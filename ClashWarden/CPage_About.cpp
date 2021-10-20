// CPage_About.cpp: 实现文件
//

#include "pch.h"
#include "ClashWarden.h"
#include "CPage_About.h"
#include "afxdialogex.h"


// CPage_About 对话框

IMPLEMENT_DYNAMIC(CPage_About, CDialogEx)

CPage_About::CPage_About(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_About, pParent)
{

}

CPage_About::~CPage_About()
{
}

void CPage_About::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPage_About, CDialogEx)
END_MESSAGE_MAP()


// CPage_About 消息处理程序
