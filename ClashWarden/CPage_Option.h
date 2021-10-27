#pragma once


// CPage_Option 对话框

class CPage_Option : public CDialogEx
{
	DECLARE_DYNAMIC(CPage_Option)

public:
	CPage_Option(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CPage_Option();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Option };
#endif

protected:
	HRESULT CreateLink(LPCTSTR lpszPathObj, LPCTSTR lpszPathLink, LPCTSTR lpszLocation);
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnstartup();
	afx_msg void OnBnClickedBtnnostartup();
};
