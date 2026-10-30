#include "StdAfx.h"
#include <tool_log.h>
#include <tool_enabler.h>
#include <vsn_application.h>
#include <tool_enabler.h>
#include <mfc_openglview.h>
#include "cubeview.h"
#include <vsn_last.h>

using namespace VSN;

/* Cube: implements the MFC application */
class Cube : public CWinApp
{
public:
    Cube() : m_pView(NULL) {}
public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();
    /*virtual int Run();*/
    virtual BOOL OnIdle(LONG lCount);
protected:
    CubeView* m_pView;
protected:
    DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(Cube, CWinApp)
END_MESSAGE_MAP()

/* instance of the MFC application */
Cube              cube_app;
VSN::Application  vsnApp;

/* updates the GL window */
BOOL Cube::OnIdle(LONG lCount)
{
    VSN_UNUSED(lCount);
    Sleep(1);
    return TRUE;
}

/* called when the application exits */
int Cube::ExitInstance()
{
    CWinApp::ExitInstance();
    /* destroy the window and the OpenGL rendering context */
    VSN_DELETE_AND_NULL(m_pView);
    return 0;
}

/* called when the application starts */
BOOL Cube::InitInstance()
{
    c3d::EnableMemoryLeakDump();

    Math::SetMultithreadedMode(mtm_Off);

    if (!MfcVision::activateLicense())
        return 0;

    CWinApp::InitInstance();
    RenderingAreaFormat format;
    format.SetDepthBufferSize(24);
    format.SetStencilBufferSize(8);
    format.SetSamples(4);
    format.SetSwapInterval(0);
    RenderingAreaFormat::SetDefaultFormat(format);

    CRect actualDesktop;
    GetWindowRect(GetDesktopWindow(), &actualDesktop);

    CPoint pos(200, 200);
    CSize sz(2 * actualDesktop.Width() / 3, 2 * actualDesktop.Height() / 3);
    // instance the MFC window/OpenGLContext 
    m_pView = new CubeView;
    CString className = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS, ::LoadCursor(nullptr, IDC_ARROW), nullptr, ::LoadIcon(nullptr, IDI_WINLOGO));
    if (m_pView->CreateEx(WS_EX_APPWINDOW | WS_EX_ACCEPTFILES, className, _TEXT("MFCView"), 
        WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, pos.x, pos.y, sz.cx, sz.cy, 0, 0, 0))
    {
        m_pMainWnd = m_pView;
        m_pView->ShowWindow(m_nCmdShow);
        m_pView->UpdateWindow();
    }
    return TRUE;
}
