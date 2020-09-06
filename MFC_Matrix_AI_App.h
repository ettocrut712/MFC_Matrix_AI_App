
// MFC_Matrix_AI_App.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCMatrixAIAppApp:
// See MFC_Matrix_AI_App.cpp for the implementation of this class
//

class CMFCMatrixAIAppApp : public CWinApp
{
public:
	CMFCMatrixAIAppApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCMatrixAIAppApp theApp;
