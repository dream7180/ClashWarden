﻿// CPage_Main.cpp: 实现文件
//

#include "pch.h"
#include "ClashWarden.h"
#include "CPage_Main.h"
#include "afxdialogex.h"
#include <thread>
#include <Tlhelp32.h>


// CPage_Main 对话框
COLORREF m_color;
CClashWardenApp* app = (CClashWardenApp*)AfxGetApp();

IMPLEMENT_DYNAMIC(CPage_Main, CDialogEx)

CPage_Main::CPage_Main(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Main, pParent)
{
	
}

CPage_Main::~CPage_Main()
{
	CString inivalue;
	inivalue.Format(L"%d", app->tunmode);
	WritePrivateProfileString(L"General", L"TunMode", inivalue, app->iniFile);
	inivalue.Format(L"%d", app->sysproxy);
	WritePrivateProfileString(L"General", L"SysProxy", inivalue, app->iniFile);
	inivalue.Format(L"%d", app->upwproxy);
	WritePrivateProfileString(L"General", L"yamlWithProxy", inivalue, app->iniFile);
}

void CPage_Main::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CTun, app->tunmode);
	DDX_Check(pDX, IDC_CSysproxy, app->sysproxy);
	DDX_Check(pDX, IDC_CwProxy, app->upwproxy);
}


BEGIN_MESSAGE_MAP(CPage_Main, CDialogEx)
	ON_BN_CLICKED(IDC_BTNStart, &CPage_Main::OnBnClickedBtnstart)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BTNStop, &CPage_Main::OnBnClickedBtnstop)
	ON_BN_CLICKED(IDC_BTNCfg, &CPage_Main::OnBnClickedBtncfg)
	ON_BN_CLICKED(IDC_BTNIP, &CPage_Main::OnBnClickedBtnip)
	ON_BN_CLICKED(IDC_BTNConsole, &CPage_Main::OnBnClickedBtnconsole)
	ON_BN_CLICKED(IDC_CTun, &CPage_Main::OnBnClickedCtun)
	ON_BN_CLICKED(IDC_CSysproxy, &CPage_Main::OnBnClickedCsysproxy)
	ON_STN_DBLCLK(IDC_TStatus, &CPage_Main::OnStnDblclickTstatus)
	ON_BN_CLICKED(IDC_CwProxy, &CPage_Main::OnBnClickedCwproxy)
END_MESSAGE_MAP()


// CPage_Main 消息处理程序

BOOL CPage_Main::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_color = RGB(255, 255, 0);
	ClashStatus();
	ClashDataTime(true);
	ClashDataTime(false);
	//UpdateData(FALSE);
	return TRUE;
}

BOOL CPage_Main::KillProcessFromName(CString strProcessName)
{
	//创建进程快照(TH32CS_SNAPPROCESS表示创建所有进程的快照)
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	//PROCESSENTRY32进程快照的结构体
	PROCESSENTRY32 pe;
	//实例化后使用Process32First获取第一个快照的进程前必做的初始化操作
	pe.dwSize = sizeof(PROCESSENTRY32);
	//下面的IF效果同:
	//if(hProcessSnap == INVALID_HANDLE_VALUE) 无效的句柄
	if (!Process32First(hSnapShot, &pe))
	{
		return FALSE;
	}
	//将字符串转换为小写
	strProcessName.MakeLower();
	//如果句柄有效 则一直获取下一个句柄循环下去
	while (Process32Next(hSnapShot, &pe))
	{
		//pe.szExeFile获取当前进程的可执行文件名称
		CString scTmp = pe.szExeFile;
		//将可执行文件名称所有英文字母修改为小写
		scTmp.MakeLower();
		//比较当前进程的可执行文件名称和传递进来的文件名称是否相同
		//相同的话Compare返回0
		if (!scTmp.Compare(strProcessName))
		{
			//从快照进程中获取该进程的PID(即任务管理器中的PID)
			DWORD dwProcessID = pe.th32ProcessID;
			HANDLE hProcess = ::OpenProcess(PROCESS_TERMINATE, FALSE, dwProcessID);
			::TerminateProcess(hProcess, 0);
			CloseHandle(hProcess);
			return TRUE;
		}
		scTmp.ReleaseBuffer();
	}
	strProcessName.ReleaseBuffer();
	return FALSE;
}


BOOL CPage_Main::IsProcessExist(CString strFindFile)
{
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	BOOL bMore = Process32First(hProcessSnap, &pe32);
	while (bMore)
	{
		bMore = Process32Next(hProcessSnap, &pe32);
		CString strExeFile;
		strExeFile.Format(L"%s", pe32.szExeFile);
		if (strExeFile.CompareNoCase(strFindFile) == 0)
		{
			CloseHandle(hProcessSnap);
			return TRUE;
		}
	}

	CloseHandle(hProcessSnap);
	return FALSE;
}


void CPage_Main::ClashStatus()
{
	bool clashruning = IsProcessExist(L"clash.exe");
	if (clashruning) {
		m_color = RGB(0, 255, 0);//此处改变字体的颜色
		GetDlgItem(IDC_TStatus)->InvalidateRect(NULL);
		GetDlgItem(IDC_TStatus)->SetWindowTextW(L" 正在运行 ");
		GetDlgItem(IDC_BTNStart)->SetWindowTextW(L" 重新启动 ");
	}
	else {
		m_color = RGB(255, 255, 0);//此处改变字体的颜色
		GetDlgItem(IDC_TStatus)->InvalidateRect(NULL);
		GetDlgItem(IDC_TStatus)->SetWindowTextW(L" 已经停止 ");
		GetDlgItem(IDC_BTNStart)->SetWindowTextW(L" 启动 Clash ");
	}
}


void CPage_Main::ClashDataTime(bool isIP)
{
	CFileStatus status;
	CTime tm;
	tm = CTime::GetCurrentTime();
	CString systemdate = tm.Format("%Y-%m-%d");
	CString modtime = L"0000-00-00-00, 00:00:00";
	if (isIP) {
		CFile::GetStatus(app->path + L"\\profile\\Country.mmdb", status);
		CString moddate = status.m_mtime.Format("%Y-%m-%d");
		if (systemdate == moddate)
		{
			modtime = L"今天, " + status.m_mtime.Format("%H:%M:%S");
		}
		else {
			modtime = status.m_mtime.Format("%Y-%m-%d, %H:%M:%S");
		}
		GetDlgItem(IDC_TIPTime)->SetWindowTextW(modtime);
	}
	else
	{
		CFile::GetStatus(app->path + L"\\profile\\config.yaml", status);
		CString moddate = status.m_mtime.Format("%Y-%m-%d");
		if (systemdate == moddate)
		{
			modtime = L"今天, " + status.m_mtime.Format("%H:%M:%S");
		}
		else {
			modtime = status.m_mtime.Format("%Y-%m-%d, %H:%M:%S");
		}
		GetDlgItem(IDC_TCfgTime)->SetWindowTextW(modtime);
	}
}

void CPage_Main::OnBnClickedBtnstart()
{
	KillProcessFromName(L"clash.exe");
	CString runpath = app->path;
	if (app->tunmode)
	{
		runpath += _T("\\bin\\startclashtun.vbs");
	}
	else
	{
		runpath += _T("\\bin\\startclash.vbs");
	}
	ShellExecute(NULL, _T("open"), runpath, NULL, 0, 0);
	Sleep(500);
	ClashStatus();
}

BOOL CPage_Main::ExecuteBat(CString strCmd, bool isIP)
{
	ASSERT(strCmd != NULL);
	int runflag = 0;

	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));


	// Start the child process.
	if (!::CreateProcess(NULL,   // No module name (use command line)
		StringToChar(strCmd),        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		CREATE_NO_WINDOW,//The process is a console application that is being run without a console window
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory
		&si,            // Pointer to STARTUPINFO structure
		&pi)           // Pointer to PROCESS_INFORMATION structure
		)
	{
		//异常处理
		::MessageBox(NULL, TEXT("执行外部命令出错！"), NULL, MB_OK);
		return FALSE;
	}

	if (pi.hThread == NULL)
	{
		return false;
	}

	while (1)
	{
		DWORD result;
		MSG msg;
		result = MsgWaitForMultipleObjects(1, &pi.hThread, FALSE, INFINITE, QS_ALLINPUT);

		if (result == WAIT_OBJECT_0 + 1)
		{
			//响应windows消息
			if (runflag == 0)
			{
				if (isIP) GetDlgItem(IDC_TIPTime)->SetWindowTextW(L"正在更新, 请稍候...");
				else GetDlgItem(IDC_TCfgTime)->SetWindowTextW(L"正在更新, 请稍候...");
				runflag = 1;
			}
			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			//线程运行结束(result==WAIT_OBJECT_0) ||
			//传递了一个无效的句柄(result==WAIT_FAILED) ||
			//线程等待时间已到(result==WAIT_TIMEOUT) ||
			//其他情况(...)
			runflag = 0;
			break;
		}
	}

	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
	ClashDataTime(isIP);
	return TRUE;
}

TCHAR* CPage_Main::StringToChar(CString& str)
{
	int len = str.GetLength();
	TCHAR* tr = str.GetBuffer(len);
	str.ReleaseBuffer();
	return tr;
}

HBRUSH CPage_Main::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd->GetDlgCtrlID() == IDC_TStatus) {
		pDC->SetBkColor(m_color);
	}
	return hbr;
}


void CPage_Main::OnBnClickedBtnstop()
{
	KillProcessFromName(L"clash.exe");
	Sleep(500);
	ClashStatus();
}


void CPage_Main::OnBnClickedBtncfg()
{
	CString runpath = app->path;
	if (app->upwproxy) {
		runpath += _T("\\config\\yamlupdate.bat");
	}
	else {
		runpath += _T("\\config\\yamlupdatep.bat");
	}
	ExecuteBat(runpath, false);
}


void CPage_Main::OnBnClickedBtnip()
{
	CString runpath = app->path;
	runpath += _T("\\config\\geoipupdate.bat");
	ExecuteBat(runpath, true);
}


void CPage_Main::OnBnClickedBtnconsole()
{
	ShellExecuteW(NULL, L"open", L"http://127.0.0.1:9090/ui/#/proxies", NULL, NULL, SW_SHOWNORMAL);
}


void CPage_Main::OnBnClickedCtun()
{
	UpdateData(TRUE);
}


void CPage_Main::OnBnClickedCsysproxy()
{
	UpdateData(TRUE);
	CRegKey SetReg;
	LPCTSTR ps = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Internet Settings";
	LONG lResult = SetReg.Open(HKEY_CURRENT_USER, ps, KEY_ALL_ACCESS);
	if (ERROR_SUCCESS == lResult)
	{
		if (app->sysproxy) {
			lResult = SetReg.SetStringValue(L"ProxyServer", L"127.0.0.1:7890");
			if (ERROR_SUCCESS != lResult)
			{
				AfxMessageBox(L"注册表写入失败！");
			}
			else {
				SetReg.SetDWORDValue(L"ProxyEnable", 1);
			}
		}
		else
		{
			SetReg.SetDWORDValue(L"ProxyEnable", 0);
		}
	}
	else AfxMessageBox(L"注册表打开失败！");
	SetReg.Close();
}


void CPage_Main::OnStnDblclickTstatus()
{
	ClashStatus();
}


void CPage_Main::OnBnClickedCwproxy()
{
	UpdateData(TRUE);
}
