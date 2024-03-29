﻿
// ClashWardenDlg.h: 头文件
//

#pragma once
#include "CPage_Main.h"
#include "CPage_Subscribe.h"
#include "CPage_Option.h"
#include "CPage_About.h"

#define WM_TASKMESSAGE  WM_USER+1

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
	CPage_Subscribe m_Page2;
	CPage_Option m_Page3;
	CPage_About m_Page4;
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	NOTIFYICONDATA nid;

	// 生成的消息映射函数
	void setTray();
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT id, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnTaskMessage(WPARAM wParam, LPARAM lParam);
	afx_msg void OnShow();
	afx_msg void OnClose();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTcnSelchangeTab1(NMHDR* pNMHDR, LRESULT* pResult);
	CTabCtrl m_Tab;
	afx_msg void OnBnClickedCancel();
	afx_msg void OnDestroy();
};
