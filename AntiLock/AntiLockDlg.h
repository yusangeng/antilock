// AntiLockDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CAntiLockDlg �Ի���
class CAntiLockDlg : public CDialog
{
// ����
public:
	CAntiLockDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ANTILOCK_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CButton m_chkEnabled;

	// ���ɵ���Ϣӳ�亯��
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
