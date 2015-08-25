// AntiLockDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CAntiLockDlg 对话框
class CAntiLockDlg : public CDialog
{
// 构造
public:
	CAntiLockDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_ANTILOCK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CButton m_chkEnabled;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedButtonQuit();
	afx_msg void OnBnClickedButtonMin();
	afx_msg LRESULT OnNotifyIcon(WPARAM wp, LPARAM lp);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
