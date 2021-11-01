// CPage_About.cpp: 实现文件
//

#include "pch.h"
#include "ClashWarden.h"
#include "CPage_About.h"
#include "afxdialogex.h"


// CPage_About 对话框

IMPLEMENT_DYNAMIC(CPage_About, CDialogEx)
CClashWardenApp* app4 = (CClashWardenApp*)AfxGetApp();
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
	ON_NOTIFY(NM_CLICK, IDC_LinkHome, &CPage_About::OnNMClickLinkhome)
	ON_NOTIFY(NM_CLICK, IDC_LinkGPL, &CPage_About::OnNMClickLinkgpl)
	ON_NOTIFY(NM_CLICK, IDC_SYSLINK3, &CPage_About::OnNMClickSyslink3)
	ON_BN_CLICKED(IDC_BTNHosts, &CPage_About::OnBnClickedBtnhosts)
END_MESSAGE_MAP()


// CPage_About 消息处理程序
CString CPage_About::ReadAppVersion()
{
	CString version;

	HRSRC rsrc = ::FindResource(AfxGetInstanceHandle(), MAKEINTRESOURCE(VS_VERSION_INFO), RT_VERSION);
	HGLOBAL global;
	if (rsrc && (global = ::LoadResource(AfxGetInstanceHandle(), rsrc)) != NULL)
	{
		VS_FIXEDFILEINFO* ver = (VS_FIXEDFILEINFO*)((BYTE*)::LockResource(global) + 0x28);
		if (ver->dwSignature == 0xfeef04bd)
		{
			version.Format(_T("Version %d.%u.%u Build %u\r\n%s"),
				(int)HIWORD(ver->dwProductVersionMS), (int)LOWORD(ver->dwProductVersionMS),
				(int)HIWORD(ver->dwProductVersionLS), (int)LOWORD(ver->dwProductVersionLS),
				sizeof(TCHAR) == 1 ? _T("ASCII") : _T("Unicode"));
		}
		::FreeResource(global);
	}

	return version;
}

void CPage_About::OnNMClickLinkhome(NMHDR* pNMHDR, LRESULT* pResult)
{
	PNMLINK pNMLink = (PNMLINK)pNMHDR;
	::ShellExecute(m_hWnd, _T("open"), pNMLink->item.szUrl, NULL, NULL, SW_SHOWNORMAL);
	*pResult = 0;
}


BOOL CPage_About::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString version_;
	version_ = L"Clash Warden\r\n" + ReadAppVersion() + L", "
#ifdef _WIN64
		L"x64"
#else
		L"x86"
#endif
		L" Release";
	GetDlgItem(IDC_Version)->SetWindowText(version_);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CPage_About::OnNMClickLinkgpl(NMHDR* pNMHDR, LRESULT* pResult)
{
	PNMLINK pNMLink = (PNMLINK)pNMHDR;
	::ShellExecute(m_hWnd, _T("open"), pNMLink->item.szUrl, NULL, NULL, SW_SHOWNORMAL);
	*pResult = 0;
}


void CPage_About::OnNMClickSyslink3(NMHDR* pNMHDR, LRESULT* pResult)
{
	PNMLINK pNMLink = (PNMLINK)pNMHDR;
	::ShellExecute(m_hWnd, _T("open"), pNMLink->item.szUrl, NULL, NULL, SW_SHOWNORMAL);
	*pResult = 0;
}


void CPage_About::OnBnClickedBtnhosts()
{
	ShellExecute(NULL, _T("open"), app4->path + L"\\bin\\github-hosts.bat", NULL, 0, SW_SHOW);
}
