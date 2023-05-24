﻿// CPage_Subscribe.cpp: 实现文件
//

#include "pch.h"
#include "ClashWarden.h"
#include "CPage_Subscribe.h"
#include "afxdialogex.h"

#define MAX_SECTION 2600

// CPage_Subscribe 对话框

IMPLEMENT_DYNAMIC(CPage_Subscribe, CDialogEx)

int subscribe = -1;
CStringArray  UrlNames, UrlKey;
CClashWardenApp* app3 = (CClashWardenApp*)AfxGetApp();
CString sub_reserved = app3->path + L"\\config\\subscription_reserved.ini";

CPage_Subscribe::CPage_Subscribe(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Subscribe, pParent)
{

}

CPage_Subscribe::~CPage_Subscribe()
{
	//CString inivalue;
	//inivalue.Format(L"%d", app3->subscribe);
	//WritePrivateProfileString(L"General", L"SubscribeSN", inivalue, app3->iniFile);
	if (resetURL) {
		for (int j = 0; j < UrlNames.GetCount(); j++)
		{
			WritePrivateProfileString(L"Subscription", UrlNames[j], UrlKey[j], app3->iniFile);
		}
	}
}

void CPage_Subscribe::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LSubs, m_Subs);
}


BEGIN_MESSAGE_MAP(CPage_Subscribe, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LSubs, &CPage_Subscribe::OnitemSelChange)
END_MESSAGE_MAP()


// CPage_Subscribe 消息处理程序


BOOL CPage_Subscribe::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_Subs.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES | LVS_EX_LABELTIP);
	resetURL = false;
	CRect rect;
	GetDlgItem(IDC_LSubs)->GetClientRect(&rect);
	m_Subs.InsertColumn(0, L"名称");
	m_Subs.InsertColumn(1, L"地址");
	m_Subs.SetColumnWidth(0, (int)(rect.Width()*0.2));
	m_Subs.SetColumnWidth(1, (int)(rect.Width() * 0.8));

	getSubsSection(L"Subscription");
	//if (app3->subscribe > -1) {
	//	m_Subs.SetCheck(app3->subscribe, true);
	//}


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

VOID CPage_Subscribe::getSubsSection(const CString ini_section)
{
	TCHAR Section[MAX_SECTION] = { 0 };
	//ZeroMemory(Section, MAX_SECTION);
	CString tempStr2, strKey, strValue;
	CFile fileR(app3->path + _T("\\config\\subscription"), CFile::modeRead);
	BYTE head[3];
	fileR.Read(head, 3);
	if (!(head[0] == 0xEF && head[1] == 0xBB && head[2] == 0xBF))
	{
		fileR.SeekToBegin();
	}
	ULONGLONG FileSize = fileR.GetLength();
	char* pContent = (char*)calloc(FileSize + 1, sizeof(char));
	fileR.Read(pContent, (UINT)FileSize);
	fileR.Close();
	int n = MultiByteToWideChar(CP_UTF8, 0, pContent, (int)FileSize + 1, NULL, 0);
	wchar_t* pWideChar = (wchar_t*)calloc(n + 1, sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8, 0, pContent, (int)FileSize + 1, pWideChar, n);
	CString UrlFile = CString(pWideChar);
	free(pContent);
	free(pWideChar);
	GetPrivateProfileSection(ini_section, Section, MAX_SECTION, app3->iniFile);
	if (Section[0] == '\0') {
		memset(Section, 0, sizeof(Section));
		GetPrivateProfileSection(ini_section, Section, MAX_SECTION, sub_reserved);
		for (int j = 0; j < MAX_SECTION - 2; j++)
		{
			if (0 == j && Section[j] != '\0')
			{
				tempStr2 = Section;
				int npos = tempStr2.Find('=');
				strKey = tempStr2.Left(npos);
				strValue = tempStr2.Mid(npos + 1);

				int nItemRow = m_Subs.GetItemCount();
				int nIndex = m_Subs.InsertItem(nItemRow, strKey);
				m_Subs.SetItemText(nIndex, 0, strKey);
				m_Subs.SetItemText(nIndex, 1, strValue);
				UrlNames.Add(strKey);
				UrlKey.Add(strValue);
				if (strValue == UrlFile) {
					subscribe = nIndex;
					m_Subs.SetCheck(subscribe, true);
				}
			}
			else if (Section[j] == '\0')
			{
				if (Section[j + 1] == '\0')
					break;//两个\0表示结束

				tempStr2 = Section + j + 1;
				int npos = tempStr2.Find('=');
				strKey = tempStr2.Left(npos);
				strValue = tempStr2.Mid(npos + 1);

				int nItemRow = m_Subs.GetItemCount();
				int nIndex = m_Subs.InsertItem(nItemRow, strKey);
				m_Subs.SetItemText(nIndex, 0, strKey);
				m_Subs.SetItemText(nIndex, 1, strValue);
				UrlNames.Add(strKey);
				UrlKey.Add(strValue);
				if (strValue == UrlFile) {
					subscribe = nIndex;
					m_Subs.SetCheck(subscribe, true);
				}
			}
		}
		resetURL = true;
	}
	else
	{
		for (int j = 0; j < MAX_SECTION - 2; j++)
		{
			if (0 == j && Section[j] != '\0')
			{
				tempStr2 = Section;
				int npos = tempStr2.Find('=');
				strKey = tempStr2.Left(npos);
				strValue = tempStr2.Mid(npos + 1);

				int nItemRow = m_Subs.GetItemCount();
				int nIndex = m_Subs.InsertItem(nItemRow, strKey);
				m_Subs.SetItemText(nIndex, 0, strKey);
				m_Subs.SetItemText(nIndex, 1, strValue);
				UrlNames.Add(strKey);
				if (strValue == UrlFile) {
					subscribe = nIndex;
					m_Subs.SetCheck(subscribe, true);
				}
			}
			else if (Section[j] == '\0')
			{
				if (Section[j + 1] == '\0')
					break;//两个\0表示结束

				tempStr2 = Section + j + 1;
				int npos = tempStr2.Find('=');
				strKey = tempStr2.Left(npos);
				strValue = tempStr2.Mid(npos + 1);

				int nItemRow = m_Subs.GetItemCount();
				int nIndex = m_Subs.InsertItem(nItemRow, strKey);
				m_Subs.SetItemText(nIndex, 0, strKey);
				m_Subs.SetItemText(nIndex, 1, strValue);
				UrlNames.Add(strKey);
				UrlKey.Add(strValue);
				if (strValue == UrlFile) {
					subscribe = nIndex;
					m_Subs.SetCheck(subscribe, true);
				}
			}
		}
	}
}


void CPage_Subscribe::OnitemSelChange(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	// 点击已勾选的项，使该项再次被选中
	if (pNMLV->iItem == subscribe && !m_Subs.GetCheck(subscribe))
	{
		m_Subs.SetCheck(subscribe, true);
	}
	// 切换到其他项，让之前的项勾选取消
	else if (pNMLV->iItem != subscribe && m_Subs.GetCheck(pNMLV->iItem))
	{
		int _nTemp = subscribe;
		subscribe = pNMLV->iItem;
		m_Subs.SetCheck(_nTemp, false);
		CString urlstr;
		if (resetURL) {
			urlstr = UrlKey[subscribe];
		}
		else {
			GetPrivateProfileString(L"Subscription", UrlNames[subscribe], L"", urlstr.GetBufferSetLength(MAX_PATH), MAX_PATH, app3->iniFile);
			urlstr.ReleaseBuffer();
		}
		CFile file(app3->path + _T("\\config\\subscription"), CFile::modeWrite | CFile::modeCreate);
		
		//预转换，得到所需空间的大小，这次用的函数和上面名字相反 
		int ansiLen = ::WideCharToMultiByte(CP_UTF8, NULL, urlstr, (int)(wcslen(urlstr)), NULL, 0, NULL, NULL);
		//分配空间要给'\0'留个空间 
		//char* szAnsi = new char[ansiLen + 1];
		char* szAnsi = new char[ansiLen];
		//转换 
		//unicode版对应的strlen是wcslen 
		::WideCharToMultiByte(CP_UTF8, NULL, urlstr, (int)(wcslen(urlstr)), szAnsi, ansiLen, NULL, NULL);
		//最后加上'\0' 
		//szAnsi[ansiLen] = '\0';
		file.SeekToBegin();
		//写入内容 
		file.Write(szAnsi, ansiLen * sizeof(char));
		file.Flush();
		file.Close();
		delete[] szAnsi;
		szAnsi = NULL;
	}
	*pResult = 0;
}
