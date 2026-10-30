#include "StdAfx.h"

#include "openglview.h"
#include <vsn_window.h>
#include <vsn_vision.h>

#include "rc.h"

#include <vsn_last.h>

/////////////////////////////////////////////////////////////////////////////
// OpenGLView

IMPLEMENT_DYNCREATE(OpenGLView, COpenGLView)
BEGIN_MESSAGE_MAP(OpenGLView, COpenGLView)
    //{{AFX_MSG_MAP(OpenGLView)
    ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEWHEEL()
    ON_WM_SETCURSOR()
    ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
    ON_COMMAND(ID_GOURAUD_SHADED, OnGouraudShaded)
    ON_COMMAND(ID_WIREFRAME, OnWireframe)
    ON_COMMAND(ID_HIDDENLINE, OnHiddenline)
    ON_COMMAND(ID_ZOOM, OnZoom)
    ON_COMMAND(ID_ZOOM_TO_EXTENTS, OnZoomToExtents)
    ON_COMMAND(ID_ZOOM_TO_WINDOW, OnZoomToWindow)
    ON_COMMAND(ID_ORBIT, OnOrbit)
    ON_UPDATE_COMMAND_UI(ID_ORBIT, OnUpdateOrbit)
    ON_COMMAND(ID_PAN, OnPan)
    ON_UPDATE_COMMAND_UI(ID_PAN, OnUpdatePan)
    ON_COMMAND(ID_WINDOW_SELECT, OnWindowSelect)
    ON_UPDATE_COMMAND_UI(ID_WINDOW_SELECT, OnUpdateWindowSelect)
    ON_UPDATE_COMMAND_UI(ID_ZOOM, OnUpdateZoom)
    ON_UPDATE_COMMAND_UI(ID_ZOOM_TO_WINDOW, OnUpdateZoomToWindow)
    ON_COMMAND(ID_RUN_MY_CODE, OnRunMyCode)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
//
// ---
OpenGLView::OpenGLView()
{
}

//-----------------------------------------------------------------------------
//
// ---
OpenGLView::~OpenGLView()
{
}

//-----------------------------------------------------------------------------
//  Функция вызывается после инициализации Vision.
// ---
void OpenGLView::InitializeOpenGL()
{
    GetViewport()->SetBackgroundColour(VSN::Color(0xC9, 0xEF, 0xFF));
    GetViewport()->GetCamera()->SetViewOrientation(IsoXYZ);
}

unsigned long OpenGLView::MapFlags(unsigned long state)
{
    unsigned long flags = 0;

    /*map the mfc events state to Vision*/
    if (state & MK_LBUTTON) flags |= PR_LBUTTON;
    if (state & MK_RBUTTON) flags |= PR_RBUTTON;
    if (state & MK_MBUTTON) flags |= PR_MBUTTON;
    if (state & MK_SHIFT) flags |= PR_SHIFT;
    if (state & MK_CONTROL) flags |= PR_CONTROL;

    return flags;
}

//-----------------------------------------------------------------------------
//
// ---
void OpenGLView::UpdateSceneForModel(MbModel* pModel)
{
    if (pModel == nullptr)
        return;
    SceneSegment* pSceneSegment = GetSceneContent()->GetRootSegment();
    ASSERT(pSceneSegment != nullptr);
    ProgressBuild* pProgressBuild = SceneGenerator::Instance()->CreateProgressBuild();
    SceneGenerator::Instance()->CreateSceneSegment(pModel, pSceneSegment);
    Object::Connect(pProgressBuild, &ProgressBuild::BuildAllCompleted, this, &OpenGLView::SlotFinishBuildRep);
}


//-----------------------------------------------------------------------------
//
// ---
void OpenGLView::SlotFinishBuildRep()
{
    GetViewport()->ZoomToFit(GetSceneContent()->GetBoundingBox());
}

/////////////////////////////////////////////////////////////////////////////
// OpenGLView message handlers

//-------------------------------------------------------------------------------
// resets the camera to view the world space extents of the model
// ---
void OpenGLView::OnZoomToExtents()
{
//    if (!GetTotalBoundingBox().IsEmpty())
//        d.m_pViewPort->ZoomToFit(GetTotalBoundingBox());
    Invalidate();
}

//-------------------------------------------------------------------------------
// sets wireframe render mode
// ---
void OpenGLView::OnWireframe()
{
    VSN_D(OpenGLView);
//    d.m_renderMode = WireframeMode;
    Invalidate();
}

//-------------------------------------------------------------------------------
// sets gouraud-shaded render mode
// ---
void OpenGLView::OnGouraudShaded()
{
//    d.m_renderMode = ShadedWithEdgesMode;
    Invalidate();
}

//-------------------------------------------------------------------------------
//
// ---
void OpenGLView::OnHiddenline()
{
//    d.m_renderMode = HiddenLinesVisibleMode;
    Invalidate();
}

//-------------------------------------------------------------------------------
//
// ---
void OpenGLView::OnZoom()
{
//    d.m_aciveInteractorStyle = ProcessManager::PR_Zoom;
}

//-------------------------------------------------------------------------------
//
// ---
void OpenGLView::OnUpdateZoom(CCmdUI* pCmdUI)
{
    VSN_D(OpenGLView);
//    pCmdUI->SetCheck(d.m_aciveInteractorStyle == ProcessManager::PR_Zoom);
}

//-------------------------------------------------------------------------------
//
// ---
void OpenGLView::OnZoomToWindow()
{
}

//-------------------------------------------------------------------------------
//
// ---
void OpenGLView::OnOrbit()
{
//    d.m_aciveInteractorStyle = ProcessManager::PR_Rotate;
}

//-------------------------------------------------------------------------------
//
// ---
void OpenGLView::OnUpdateOrbit(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(GetProcessManager()->GetActiveProcessId() == ProcessManager::PR_Rotate);
}

//-------------------------------------------------------------------------------
//
// ---
void OpenGLView::OnPan()
{
    VSN_D(OpenGLView);
//    d.m_aciveInteractorStyle = ProcessManager::PR_Panoramic;
}

//-------------------------------------------------------------------------------
//
// ---
void OpenGLView::OnUpdatePan(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(GetProcessManager()->GetActiveProcessId() == ProcessManager::PR_Panoramic);
}

//-------------------------------------------------------------------------------
//
// ---
void OpenGLView::OnWindowSelect()
{
//    d.m_aciveInteractorStyle = ProcessManager::PR_NoActive;
}

//-------------------------------------------------------------------------------
//
// ---
void OpenGLView::OnUpdateZoomToWindow(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(0);
}

//-------------------------------------------------------------------------------
//
// ---
void OpenGLView::OnUpdateWindowSelect(CCmdUI* pCmdUI)
{
    pCmdUI->SetCheck(0);
}

//-------------------------------------------------------------------------------
//
// ---
#ifdef _UNICODE
BOOL OpenGLView::Create(wchar_t const * lpszClassName, wchar_t const * lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
    dwStyle = (dwStyle | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPED);
    return CWnd::Create((LPCTSTR)lpszClassName, (LPCTSTR)lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}
BOOL OpenGLView::Create(unsigned short const * lpszClassName, unsigned short const * lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
    dwStyle = (dwStyle | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPED);
    return CWnd::Create((LPCTSTR)lpszClassName, (LPCTSTR)lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}
#else
BOOL OpenGLView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
    dwStyle = (dwStyle | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPED);
    return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}
#endif

//-------------------------------------------------------------------------------
// this functions creates a new CView Object, and initializes its camera,
// render mode, query dialog, and operator
void OpenGLView::OnInitialUpdate()
{
    // we must call the base class initialization first to get the proper palette for this view
    // (either the same palette is shared among all views, or this view has a unique palette)
    COpenGLView::OnInitialUpdate();
//    d.m_pCurrentProcess = d.m_pDefaultProcess;
}

//-------------------------------------------------------------------------------
//
// ---
void OpenGLView::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
    COpenGLView::OnPrint(pDC, pInfo);
}

//-------------------------------------------------------------------------------
//
// ---
BOOL OpenGLView::PreCreateWindow(CREATESTRUCT& cs)
{
    cs.lpszClass = AfxRegisterWndClass(CS_OWNDC | CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW);
    return CView::PreCreateWindow(cs);
}

//-------------------------------------------------------------------------------
//
// ---
void OpenGLView::OnFileSaveAs()
{
    /*
    CString filter = _T("C3D Stream File (*.c3d)|*.hsf|C3D Metafile (*.c3d)|*.c3d||");

    CFileDialog my_dlg(FALSE, _T(".c3d"), nullptr, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOREADONLYRETURN,
    filter, nullptr);

    CString pathname;
    int width = 8, height = 10;

    CSampleHDoc * pDoc = (CSampleHDoc *)GetDocument();

    if (my_dlg.DoModal())
    {
    }
    */
}

//-------------------------------------------------------------------------------
//
// ---
void OpenGLView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
    if (OpenGLView* pDeactiveGlView = dynamic_cast<OpenGLView*>(pDeactiveView))
    {
        pDeactiveGlView->DoneCurrent();
        pDeactiveGlView->UpdateWindow();
    }

    if (OpenGLView* pActivateGlView = dynamic_cast<OpenGLView*>(pActivateView))
    {
        pActivateGlView->MakeCurrent();
        pActivateGlView->UpdateWindow();
    }
    COpenGLView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

//-------------------------------------------------------------------------------
//
// ---
void OpenGLView::OnRunMyCode()
{
    // this is a function in which developers can
    // write their own simple C3D functions
    AfxMessageBox(_T(""));
}

//-----------------------------------------------------------------------------
//
// ---
BOOL OpenGLView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
    ::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
    // let the processing continue - a child window may want to set one of its own
    return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// OpenGLView diagnostics

#ifdef _DEBUG
//-------------------------------------------------------------------------------
//
// ---
void OpenGLView::AssertValid() const
{
    COpenGLView::AssertValid();
}

//-------------------------------------------------------------------------------
//
// ---
void OpenGLView::Dump(CDumpContext& dc) const
{
    COpenGLView::Dump(dc);
}
#endif //_DEBUG

