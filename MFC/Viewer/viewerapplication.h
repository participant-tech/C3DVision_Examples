
// viewerapplication.h : main header file for the ViewerApplication application
//
#pragma once

#ifndef __AFXWIN_H__
#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols
#include <vsn_application.h>

class Application;
// ViewerApplication:
// See viewerapplication.cpp for the implementation of this class
//
class ViewerApplication : public CWinAppEx
{
public:
    ViewerApplication();
    // Overrides
public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();

    // Implementation
    UINT  m_nAppLook;
    BOOL  m_bHiColorIcons;

    virtual void PreLoadState();
    virtual void LoadCustomState();
    virtual void SaveCustomState();
protected:
    afx_msg void OnAppAbout();
protected:
    DECLARE_MESSAGE_MAP()
private:
    Application* m_pApplication;
};

extern ViewerApplication theApp;
