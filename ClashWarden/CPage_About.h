#pragma once


// CPage_About 对话框

class CPage_About : public CDialogEx
{
	DECLARE_DYNAMIC(CPage_About)

public:
	CPage_About(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CPage_About();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_About };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	CString ReadAppVersion(bool including_build);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMClickLinkhome(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnNMClickLinkgpl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMClickSyslink3(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedBtnhosts();
};
