// CPage_Option.cpp: 实现文件
//

#include "pch.h"
#include "ClashWarden.h"
#include "CPage_Option.h"
#include "afxdialogex.h"

// CPage_Option 对话框
CClashWardenApp* app2 = (CClashWardenApp*)AfxGetApp();
IMPLEMENT_DYNAMIC(CPage_Option, CDialogEx)

CPage_Option::CPage_Option(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Option, pParent)
{

}


CPage_Option::~CPage_Option()
{
	WritePrivateProfileString(L"General", L"Startup", app2->startup ? L"1" : L"0", app2->iniFile);
}

void CPage_Option::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CStartup, app2->startup);
}


BEGIN_MESSAGE_MAP(CPage_Option, CDialogEx)
	ON_BN_CLICKED(IDC_BTNStartup, &CPage_Option::OnBnClickedBtnstartup)
	ON_BN_CLICKED(IDC_BTNnoStartup, &CPage_Option::OnBnClickedBtnnostartup)
END_MESSAGE_MAP()


// CPage_Option 消息处理程序

BOOL CPage_Option::OnInitDialog()
{
	CDialogEx::OnInitDialog();
//	UpdateData(FALSE);
	return TRUE;
}

void CPage_Option::OnBnClickedBtnstartup()
{
	CRegKey SetReg;
	LPCTSTR ps = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
	LONG lResult = SetReg.Open(HKEY_LOCAL_MACHINE, ps, KEY_ALL_ACCESS);
	if (ERROR_SUCCESS == lResult)
	{
		if(app2->tunmode)
			lResult = SetReg.SetStringValue(L"Clash", app2->path + L"\\bin\\startclashtun.vbs");
		else lResult = SetReg.SetStringValue(L"Clash", app2->path + L"\\bin\\startclash.vbs");
		if (ERROR_SUCCESS != lResult)
		{
			AfxMessageBox(L"注册表写入失败！");
		}
		else
		{
			app2->startup = 1;
			UpdateData(FALSE);
		}
	}
	else AfxMessageBox(L"注册表打开失败！");
	SetReg.Close();
}


void CPage_Option::OnBnClickedBtnnostartup()
{
	CRegKey SetReg;
	LPCTSTR ps = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
	LONG lResult = SetReg.Open(HKEY_LOCAL_MACHINE, ps, KEY_ALL_ACCESS);
	if (ERROR_SUCCESS == lResult)
	{
		wchar_t chVersion[MAX_PATH] = { 0 };
		ULONG nChars = MAX_PATH;
		if (ERROR_SUCCESS == SetReg.QueryStringValue(L"Clash", chVersion, &nChars))
		{
			lResult = SetReg.DeleteValue(L"Clash");
			if (ERROR_SUCCESS != lResult)
			{
				AfxMessageBox(L"注册表改写失败！");
			}
			else
			{
				app2->startup = 0;
				UpdateData(FALSE);
			}
		}
	}
	else AfxMessageBox(L"注册表打开失败！");
	SetReg.Close();
}

