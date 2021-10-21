#pragma once


// CPage_Main 对话框

class CPage_Main : public CDialogEx
{
	DECLARE_DYNAMIC(CPage_Main)

public:
	CPage_Main(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CPage_Main();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_Main };
#endif

protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL KillProcessFromName(CString strProcessName);
	BOOL IsProcessExist(CString ProcessName);
	VOID ClashStatus();
	VOID ClashDataTime(bool isIP);
	BOOL ExecuteBat(CString strCmd, bool isIP);
	TCHAR* StringToChar(CString& str);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnstart();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedBtnstop();
	afx_msg void OnBnClickedBtncfg();
	afx_msg void OnBnClickedBtnip();
	afx_msg void OnBnClickedBtnconsole();
	afx_msg void OnBnClickedCtun();
};
