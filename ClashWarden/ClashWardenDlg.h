
// ClashWardenDlg.h: 头文件
//

#pragma once
#include "CPage_Main.h"
#include "CPage_Option.h"
#include "CPage_About.h"

// CClashWardenDlg 对话框
class CClashWardenDlg : public CDialogEx
{
// 构造
public:
	CClashWardenDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLASHWARDEN_DIALOG };
#endif

	protected:
	CPage_Main m_Page1;
	CPage_Option m_Page2;
	CPage_About m_Page3;
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	CTabCtrl m_Tab;
};
