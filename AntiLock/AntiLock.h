// AntiLock.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CAntiLockApp:
// �йش����ʵ�֣������ AntiLock.cpp
//

class CAntiLockApp : public CWinApp
{
public:
	CAntiLockApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CAntiLockApp theApp;