// CPage_Subscribe.cpp: 实现文件
//

#include "pch.h"
#include "ClashWarden.h"
#include "CPage_Subscribe.h"
#include "afxdialogex.h"

#define MAX_SECTION 2600

// CPage_Subscribe 对话框

IMPLEMENT_DYNAMIC(CPage_Subscribe, CDialogEx)

CStringArray  UrlNames, UrlKey;
CClashWardenApp* app3 = (CClashWardenApp*)AfxGetApp();

CPage_Subscribe::CPage_Subscribe(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_Subscribe, pParent)
{

}

CPage_Subscribe::~CPage_Subscribe()
{
	CString inivalue;
	inivalue.Format(L"%d", app3->subscribe);
	WritePrivateProfileString(L"General", L"SubscribeSN", inivalue, app3->iniFile);
	if (resetURL) {
		WritePrivateProfileString(L"Subscription", L"anaer", L"https://raw.githubusercontent.com/anaer/Sub/main/clash.yaml", app3->iniFile);
		WritePrivateProfileString(L"Subscription", L"oslook(github)", L"https://raw.githubusercontent.com/oslook/clash-freenode/main/clash.yaml", app3->iniFile);
		WritePrivateProfileString(L"Subscription", L"oslook(cdn)", L"https://cdn.jsdelivr.net/gh/oslook/clash-freenode@master/clash.yaml --no-check-certificate", app3->iniFile);
		WritePrivateProfileString(L"Subscription", L"free9999", L"https://gitlab.com/free9999/ipupdate/-/raw/master/clash/config.yaml --no-check-certificate", app3->iniFile);
		WritePrivateProfileString(L"Subscription", L"warden", L"https://gitlab.com/warden3/subscription/-/raw/main/config.yaml --no-check-certificate", app3->iniFile);
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
	m_Subs.SetColumnWidth(0, (int)(rect.Width()*0.25));
	m_Subs.SetColumnWidth(1, (int)(rect.Width() * 0.75));

	getSubsSection(L"Subscription");
	if (app3->subscribe > -1) {
		m_Subs.SetCheck(app3->subscribe, true);
	}


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

VOID CPage_Subscribe::getSubsSection(const CString ini_section)
{
	TCHAR Section[MAX_SECTION] = { 0 };
	//ZeroMemory(Section, MAX_SECTION);
	CString tempStr2, strKey, strValue;
	GetPrivateProfileSection(ini_section, Section, MAX_SECTION, app3->iniFile);
	if (Section[0] == '\0') {
		UrlNames.Add(L"anaer");
		UrlNames.Add(L"oslook(github)");
		UrlNames.Add(L"oslook(cdn)");
		UrlNames.Add(L"free9999");
		UrlNames.Add(L"warden");
		UrlKey.Add(L"https://raw.githubusercontent.com/anaer/Sub/main/clash.yaml");
		UrlKey.Add(L"https://raw.githubusercontent.com/oslook/clash-freenode/main/clash.yaml");
		UrlKey.Add(L"https://cdn.jsdelivr.net/gh/oslook/clash-freenode@master/clash.yaml --no-check-certificate");
		UrlKey.Add(L"https://gitlab.com/free9999/ipupdate/-/raw/master/clash/config.yaml --no-check-certificate");
		UrlKey.Add(L"https://gitlab.com/warden3/subscription/-/raw/main/config.yaml --no-check-certificate");
		m_Subs.InsertItem(0, UrlNames[0]);
		m_Subs.SetItemText(0, 0, UrlNames[0]);
		m_Subs.SetItemText(0, 1, UrlKey[0]);
		m_Subs.InsertItem(1, UrlNames[1]);
		m_Subs.SetItemText(1, 0, UrlNames[1]);
		m_Subs.SetItemText(1, 1, UrlKey[1]);
		m_Subs.InsertItem(2, UrlNames[2]);
		m_Subs.SetItemText(2, 0, UrlNames[2]);
		m_Subs.SetItemText(2, 1, UrlKey[2]);
		m_Subs.InsertItem(3, UrlNames[3]);
		m_Subs.SetItemText(3, 0, UrlNames[3]);
		m_Subs.SetItemText(3, 1, UrlKey[3]);
		m_Subs.InsertItem(4, UrlNames[4]);
		m_Subs.SetItemText(4, 0, UrlNames[4]);
		m_Subs.SetItemText(4, 1, UrlKey[4]);
		resetURL = true;
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
		for (int j = 0; j < UrlKey.GetSize(); j++)
		{
			if (UrlKey[j] == UrlFile) {
				app3->subscribe = j;
			}
		}
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
			}
		}
	}
}


void CPage_Subscribe::OnitemSelChange(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	// 点击已勾选的项，使该项再次被选中
	if (pNMLV->iItem == app3->subscribe && !m_Subs.GetCheck(app3->subscribe))
	{
		m_Subs.SetCheck(app3->subscribe, true);
	}
	// 切换到其他项，让之前的项勾选取消
	else if (pNMLV->iItem != app3->subscribe && m_Subs.GetCheck(pNMLV->iItem))
	{
		int _nTemp = app3->subscribe;
		app3->subscribe = pNMLV->iItem;
		m_Subs.SetCheck(_nTemp, false);
		CString urlstr;
		if (resetURL) {
			urlstr = UrlKey[app3->subscribe];
		}
		else {
			GetPrivateProfileString(L"Subscription", UrlNames[app3->subscribe], L"", urlstr.GetBufferSetLength(MAX_PATH), MAX_PATH, app3->iniFile);
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
