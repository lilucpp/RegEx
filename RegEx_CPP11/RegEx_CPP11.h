
// RegEx_CPP11.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CRegExCPP11App:
// See RegEx_CPP11.cpp for the implementation of this class
//

class CRegExCPP11App : public CWinApp
{
public:
	CRegExCPP11App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CRegExCPP11App theApp;
