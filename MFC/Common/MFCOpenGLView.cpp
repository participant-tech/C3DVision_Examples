#include "StdAfx.h"

#include "MFCOpenGLView.h"
#include "rc.h"

#include <vsn_last.h>

/////////////////////////////////////////////////////////////////////////////
// CMFCOpenGLView
IMPLEMENT_DYNAMIC(CMFCOpenGLView, CView)
BEGIN_MESSAGE_MAP(CMFCOpenGLView, CView)
  //{{AFX_MSG_MAP(CMFCOpenGLView)
  ON_WM_PAINT()
  ON_WM_MOUSEMOVE()
  ON_WM_LBUTTONDOWN()
  ON_WM_LBUTTONUP()
  ON_WM_MOUSEWHEEL()
  ON_WM_DESTROY()
  ON_WM_SETCURSOR()
  ON_WM_SIZE()
  ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
  ON_COMMAND(ID_RUN_MY_CODE, OnRunMyCode)
  //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
//
// ---
CMFCOpenGLView::CMFCOpenGLView()
  : m_pSceneView(NULL)
{
}

//-----------------------------------------------------------------------------
//
// ---
CMFCOpenGLView::~CMFCOpenGLView()
{
  delete m_pSceneView;
}


/////////////////////////////////////////////////////////////////////////////
// CMFCOpenGLView message handlers
//-------------------------------------------------------------------------------
//
// ---
#ifdef _UNICODE
BOOL CMFCOpenGLView::Create(wchar_t const * lpszClassName, wchar_t const * lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
  dwStyle = (dwStyle | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPED);
  BOOL bResult = CWnd::Create((LPCTSTR)lpszClassName, (LPCTSTR)lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
  // create the Vision GraphicsSceneView object corresponding with this MFC View, 
  // passing in the  the MFC View's window handle
  if (bResult)
    m_pSceneView = CreateGraphicsSceneView();
  return bResult;
}
BOOL CMFCOpenGLView::Create(unsigned short const * lpszClassName, unsigned short const * lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
  dwStyle = (dwStyle | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPED);
  BOOL bResult = CWnd::Create((LPCTSTR)lpszClassName, (LPCTSTR)lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
  // create the Vision GraphicsSceneView object corresponding with this MFC View, 
  // passing in the  the MFC View's window handle
  if (bResult)
    m_pSceneView = CreateGraphicsSceneView();
  return bResult;
}
#else
BOOL CMFCOpenGLView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
  dwStyle = (dwStyle | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPED);
  BOOL bResult =  CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
  // create the Vision GraphicsSceneView object corresponding with this MFC View, 
  // passing in the  the MFC View's window handle
  if (bResult)
    m_pSceneView = CreateGraphicsSceneView();
  return bResult;
}
#endif

//-------------------------------------------------------------------------------
// this functions creates a new CView Object, and initializes its camera,
// render mode, query dialog, and operator
// ---
void CMFCOpenGLView::OnInitialUpdate() 
{
  // we must call the base class initialization first to get the proper palette for this view
  // (either the same palette is shared among all views, or this view has a unique palette)
  CView::OnInitialUpdate();
  // This resets the camera so that it views the extents of the scene.
  m_pSceneView->FitWorld(NULL);
}

//-------------------------------------------------------------------------------
//
// ---
void CMFCOpenGLView::OnDraw(CDC* pDC)
{
}

//-------------------------------------------------------------------------------
//
// ---
void CMFCOpenGLView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
  CView::OnPrint(pDC, pInfo);
}

//-------------------------------------------------------------------------------
//
// ---
BOOL CMFCOpenGLView::PreCreateWindow(CREATESTRUCT& cs)
{
  cs.lpszClass = AfxRegisterWndClass(CS_OWNDC|CS_DBLCLKS|CS_HREDRAW|CS_VREDRAW);
  return CView::PreCreateWindow(cs);
}

//-------------------------------------------------------------------------------
//
// ---
void CMFCOpenGLView::OnPaint()
{
  if (m_pSceneView)
    m_pSceneView->Render();

  CPaintDC dc(this); // Calls CWnd::BeginPaint on ctor, CWnd::EndPaint on dtor
}

//-------------------------------------------------------------------------------
//
// ---
unsigned long CMFCOpenGLView::InitMapFlags(unsigned long state)
{
  unsigned long flags = 0;
  // map the mfc events state to MVP
  if(state & MK_LBUTTON) flags |= PR_LBUTTON;
  if(state & MK_RBUTTON) flags |= PR_RBUTTON;
  if(state & MK_MBUTTON) flags |= PR_MBUTTON;
  if(state & MK_SHIFT)   flags |= PR_SHIFT;
  if(state & MK_CONTROL) flags |= PR_CONTROL;
  return flags;
}

//-------------------------------------------------------------------------------
//
// ---
void CMFCOpenGLView::OnLButtonDown(UINT nFlags, CPoint point)
{
  _ASSERT(m_pSceneView != NULL);

  MouseEvent event(ProcessEvent::LButtonDown);
  event.SetFlags(InitMapFlags(nFlags));
  event.SetScreenPos(Point(point.x, point.y));
  m_pSceneView->OnLButtonDown(event);

  CView::OnLButtonDown(nFlags, point);
}

//-------------------------------------------------------------------------------
//
// ---
void CMFCOpenGLView::OnMouseMove(UINT nFlags, CPoint point)
{
  CView::OnMouseMove(nFlags, point);

  _ASSERT(m_pSceneView != NULL);

  MouseEvent event(ProcessEvent::MouseMove);
  event.SetFlags(InitMapFlags(nFlags));
  event.SetScreenPos(Point(point.x, point.y));
  m_pSceneView->OnMouseMove(event);
}

//-------------------------------------------------------------------------------
//
// ---
void CMFCOpenGLView::OnLButtonUp(UINT nFlags, CPoint point)
{
  _ASSERT(m_pSceneView != NULL);

  MouseEvent event(ProcessEvent::LButtonUp);
  event.SetFlags(InitMapFlags(nFlags));
  event.SetScreenPos(Point(point.x, point.y));
  m_pSceneView->OnLButtonUp(event);

  CView::OnLButtonUp(nFlags, point);
}

//-------------------------------------------------------------------------------
//
// ---
BOOL CMFCOpenGLView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
  _ASSERT(m_pSceneView != NULL);

  WheelEvent event;
  event.SetFlags(InitMapFlags(nFlags));
  event.SetWheelDelta(zDelta);
  m_pSceneView->OnMouseWheel(event);

  return CView::OnMouseWheel(nFlags, zDelta, pt);
}

//-------------------------------------------------------------------------------
//
// ---
void CMFCOpenGLView::OnDestroy()
{
  _ASSERT(m_pSceneView != NULL);
  m_pSceneView->Destroy();
  CView::OnDestroy();
}

//-------------------------------------------------------------------------------
//
// ---
void CMFCOpenGLView::OnFileSaveAs() 
{
/*
  CString filter = _T("C3D Stream File (*.c3d)|*.c3d|C3D Metafile (*.c3d)|*.c3d||");

  CFileDialog my_dlg(FALSE, _T(".c3d"), nullptr, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_NOREADONLYRETURN, filter, nullptr);

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
void CMFCOpenGLView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView) 
{
  if (CMFCOpenGLView* pDeactiveGlView = dynamic_cast<CMFCOpenGLView*>(pDeactiveView))
  {
  }

  if (CMFCOpenGLView* pActivateGlView = dynamic_cast<CMFCOpenGLView*>(pActivateView))
  {
  }

  CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

//-------------------------------------------------------------------------------
//
// ---
void CMFCOpenGLView::OnRunMyCode() 
{
  // this is a function in which developers can
  // write their own simple C3D functions
  AfxMessageBox(_T(""));
}

//-----------------------------------------------------------------------------
//
// ---
BOOL CMFCOpenGLView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
  ::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
  // let the processing continue - a child window may want to set one of its own
  return FALSE;
}

//-----------------------------------------------------------------------------
//
// ---
void CMFCOpenGLView::OnSize(UINT nType, int cx, int cy)
{
  CView::OnSize(nType, cx, cy);

  if (0 >= cx || 0 >= cy || nType == SIZE_MINIMIZED)
    return;

  if (m_pSceneView)
    m_pSceneView->UpdateResize(cx, cy);
}

/////////////////////////////////////////////////////////////////////////////
// CMFCOpenGLView diagnostics

#ifdef _DEBUG
//-------------------------------------------------------------------------------
//
// ---
void CMFCOpenGLView::AssertValid() const
{
  CView::AssertValid();
}

//-------------------------------------------------------------------------------
//
// ---
void CMFCOpenGLView::Dump(CDumpContext& dc) const
{
  CView::Dump(dc);
}
#endif //_DEBUG

