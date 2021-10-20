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

	DECLARE_MESSAGE_MAP()
};
