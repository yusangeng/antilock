// AntiLockDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AntiLock.h"
#include "AntiLockDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_NOTIFY_ICON_MESSAGE (WM_USER + 1000)

// CAntiLockDlg �Ի���




CAntiLockDlg::CAntiLockDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAntiLockDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAntiLockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_ENABLED, m_chkEnabled);
}

BEGIN_MESSAGE_MAP(CAntiLockDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_NOTIFY_ICON_MESSAGE, &CAntiLockDlg::OnNotifyIcon)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_QUIT, &CAntiLockDlg::OnBnClickedButtonQuit)
	ON_BN_CLICKED(IDC_BUTTON_MIN, &CAntiLockDlg::OnBnClickedButtonMin)
END_MESSAGE_MAP()


// CAntiLockDlg ��Ϣ�������

BOOL CAntiLockDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	HWND handle = this->GetSafeHwnd();
	LONG val = GetWindowLongPtr(handle, GWL_STYLE);

	SetWindowLong(handle, GWL_STYLE, val & ~WS_BORDER); // ȥ���߿�

	// ��С��������
	NOTIFYICONDATA nid;

	nid.cbSize = sizeof(nid);
	nid.hIcon = m_hIcon;
	nid.hWnd   = GetSafeHwnd();
	GetWindowText(nid.szTip, sizeof(nid.szTip));
	nid.uCallbackMessage = WM_NOTIFY_ICON_MESSAGE;
	nid.uFlags = NIF_MESSAGE|NIF_TIP|NIF_ICON;
	nid.uID = 1;

	Shell_NotifyIcon(NIM_ADD, &nid);

	// ��궨ʱ��
	SetTimer(1, 1000, NULL);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAntiLockDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CAntiLockDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAntiLockDlg::OnBnClickedButtonQuit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ��С��������
	NOTIFYICONDATA nid;

	nid.cbSize = sizeof(nid);
	nid.hWnd = GetSafeHwnd();
	nid.uID = 1;

	Shell_NotifyIcon(NIM_DELETE, &nid);

	this->OnOK();
}

void CAntiLockDlg::OnBnClickedButtonMin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShowWindow(SW_HIDE);
}

LRESULT CAntiLockDlg::OnNotifyIcon(WPARAM wp, LPARAM lp)
{
	switch(lp)
	{
	case WM_LBUTTONDBLCLK:
		ShowWindow(SW_SHOW);
		break;
	}

	return 0;
}

void CAntiLockDlg::OnTimer(UINT nIDEvent) 
{
	if (!m_chkEnabled.GetCheck()) {
		return;
	}

	INPUT data;

	ZeroMemory(&data, sizeof(data));

	data.mi.dwFlags = 1;
	data.mi.dx = 0;
	data.mi.dy = 0;

	SendInput(1, &data, sizeof(data));

	// Call base class handler.
	CDialog::OnTimer(nIDEvent);
}

