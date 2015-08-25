// AntiLockDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "AntiLock.h"
#include "AntiLockDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_NOTIFY_ICON_MESSAGE (WM_USER + 1000)

// CAntiLockDlg 对话框




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


// CAntiLockDlg 消息处理程序

BOOL CAntiLockDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	HWND handle = this->GetSafeHwnd();
	LONG val = GetWindowLongPtr(handle, GWL_STYLE);

	SetWindowLong(handle, GWL_STYLE, val & ~WS_BORDER); // 去掉边框

	// 最小化到托盘
	NOTIFYICONDATA nid;

	nid.cbSize = sizeof(nid);
	nid.hIcon = m_hIcon;
	nid.hWnd   = GetSafeHwnd();
	GetWindowText(nid.szTip, sizeof(nid.szTip));
	nid.uCallbackMessage = WM_NOTIFY_ICON_MESSAGE;
	nid.uFlags = NIF_MESSAGE|NIF_TIP|NIF_ICON;
	nid.uID = 1;

	Shell_NotifyIcon(NIM_ADD, &nid);

	// 鼠标定时器
	SetTimer(1, 1000, NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CAntiLockDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CAntiLockDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAntiLockDlg::OnBnClickedButtonQuit()
{
	// TODO: 在此添加控件通知处理程序代码
	// 最小化到托盘
	NOTIFYICONDATA nid;

	nid.cbSize = sizeof(nid);
	nid.hWnd = GetSafeHwnd();
	nid.uID = 1;

	Shell_NotifyIcon(NIM_DELETE, &nid);

	this->OnOK();
}

void CAntiLockDlg::OnBnClickedButtonMin()
{
	// TODO: 在此添加控件通知处理程序代码
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

