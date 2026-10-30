/****************************************************************************
**
** MIT License
** Copyright(c) 2025 C3D-Labs
**
** Permission is hereby granted, free of charge, to any person obtaining
** a copy of this software and associated documentation files(the "Software"),
** to deal in the Software without restriction, including without limitation
** the rights to use, copy, modify, merge, publish, distribute, sublicense,
** and / or sell copies of the Software, and to permit persons to whom
** the Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included
** in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
** OTHERWISE,ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
** USE OR OTHER DEALINGS IN THE SOFTWARE.
**
****************************************************************************/

#include <mfc_openglview.h>
#include <mfc_scenerenderer.h>
#include <tool_enabler.h>
#include <mfc_licensewnd.h>
#include <vsn_last.h>

namespace VSN {

namespace MfcVision {

IMPLEMENT_DYNCREATE(COpenGLView, CView)
BEGIN_MESSAGE_MAP(COpenGLView, CView)
    //{{AFX_MSG_MAP(COpenGLView)
    ON_WM_CREATE()
    ON_WM_DESTROY()
    ON_WM_PAINT()
    ON_WM_SIZE()
    ON_WM_SETCURSOR()
    ON_WM_SHOWWINDOW()
    ON_WM_SETFOCUS()
    ON_WM_KILLFOCUS()
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

//-----------------------------------------------------------------------------
// Конструктор по умолчанию.
// ---
COpenGLView::COpenGLView()
    : m_pSceneRenderer(new CSceneRenderer)
{
}

//-----------------------------------------------------------------------------
// Деструктор OpenGLWidget освобождает созданные ресурсы
// ---
COpenGLView::~COpenGLView()
{
    VSN_DELETE_AND_NULL(m_pSceneRenderer);
}

//-----------------------------------------------------------------------------
//
// ---
void COpenGLView::MakeCurrent()
{ m_pSceneRenderer->MakeCurrent(); }

//-----------------------------------------------------------------------------
//
// ---
void COpenGLView::DoneCurrent()
{ m_pSceneRenderer->DoneCurrent(); }

//-----------------------------------------------------------------------------
// Вернуть указатель на источник освешения сцены.
// ---
Light* COpenGLView::GetMainLight() const
{ return m_pSceneRenderer->GetMainLight(); }

//-----------------------------------------------------------------------------
// Вернуть указатель на Viewport для отображения сцены.
// ---
Viewport* COpenGLView::GetViewport() const
{ return m_pSceneRenderer->GetViewport(); }

//-----------------------------------------------------------------------------
// Вернуть указатель на содержимое сцены.
// ---
SceneContentPtr COpenGLView::GetSceneContent() const
{ return m_pSceneRenderer->GetSceneContent(); }

//-----------------------------------------------------------------------------
// Вернуть указатель на содержимое сцены.
// ---
ObjectPickSelection* COpenGLView::GetObjectPickSelection() const
{ return m_pSceneRenderer->GetGraphicsView()->GetSceneEngine()->GetObjectPickSelection(); }

//-----------------------------------------------------------------------------
// Вернуть указатель на CSceneRenderer
// ---
CSceneRenderer* COpenGLView::GetSceneRenderer() const
{ return m_pSceneRenderer; }

//-----------------------------------------------------------------------------
// Вернуть указатель на содержимое сцены
// ---
GraphicsScene* COpenGLView::GetGraphicsScene() const
{ return m_pSceneRenderer->GetGraphicsScene(); }

//-----------------------------------------------------------------------------
// Функция вызывается после инициализации Vision
// ---
void COpenGLView::InitializeOpenGL()
{
}

//-------------------------------------------------------------------------------
//
// ---
#ifdef _UNICODE
BOOL COpenGLView::Create(wchar_t const * lpszClassName, wchar_t const * lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
    dwStyle = (dwStyle | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS /*| WS_OVERLAPPED*/);
    return CView::Create((LPCTSTR)lpszClassName, (LPCTSTR)lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}
BOOL COpenGLView::Create(unsigned short const * lpszClassName, unsigned short const * lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
    dwStyle = (dwStyle | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPED);
    return CView::Create((LPCTSTR)lpszClassName, (LPCTSTR)lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}
#else
BOOL COpenGLView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
    dwStyle = (dwStyle | WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPED);
    return CView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}
#endif

//-----------------------------------------------------------------------------
// Создать окно и захватить ресурсы OpenGL, а также произвести инициализацию Vision
// ---
int COpenGLView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;
    m_pSceneRenderer->DoCreate(m_hWnd);
    InitializeOpenGL();
    return 0;
}

//-----------------------------------------------------------------------------
//
// ---
void COpenGLView::OnDestroy()
{
    m_pSceneRenderer->DoDestroy();
    CView::OnDestroy();
}

//-------------------------------------------------------------------------------
//
// ---
void COpenGLView::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    m_pSceneRenderer->DoDraw();
}

//-----------------------------------------------------------------------------
//
// ---
void COpenGLView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
    if (bActivate)
        m_pSceneRenderer->DoPreparingToDisplay();
    else
        m_pSceneRenderer->DoDraw();
    CView::OnActivateView(bActivate, pActivateView, pDeactiveView);
}

//-----------------------------------------------------------------------------
//
// ---
void COpenGLView::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CView::OnShowWindow(bShow, nStatus);
    if (bShow)
        m_pSceneRenderer->DoPreparingToDisplay();
}

//-----------------------------------------------------------------------------
//
// ---
void COpenGLView::OnDraw(CDC* pDC)
{
    VSN_UNUSED(pDC);
}

//-----------------------------------------------------------------------------
// for processing Windows messages
// ---
BOOL COpenGLView::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
    MSG msg{};
    msg.message = message;
    msg.wParam = wParam;
    msg.lParam = lParam;
    if (m_pSceneRenderer->OnWinEvent(&msg))
        return TRUE;
    return CView::OnWndMsg(message, wParam, lParam, pResult);
}

//-------------------------------------------------------------------------------
//
// ---
BOOL COpenGLView::PreCreateWindow(CREATESTRUCT& cs)
{
    cs.lpszClass = AfxRegisterWndClass(CS_OWNDC | CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW);
    return CView::PreCreateWindow(cs);
}

//-----------------------------------------------------------------------------
//
// ---
void COpenGLView::OnSize(UINT nType, int cx, int cy)
{
    if (0 >= cx || 0 >= cy || nType == SIZE_MINIMIZED)
        return;
    m_pSceneRenderer->DoResize(cx, cy);
    CView::OnSize(nType, cx, cy);
}

//-----------------------------------------------------------------------------
//
// ---
BOOL COpenGLView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
    VSN_UNUSED(pWnd);
    VSN_UNUSED(nHitTest);
    VSN_UNUSED(message);
    ::SetCursor(AfxGetApp()->LoadStandardCursor(IDC_ARROW));
    // let the processing continue - a child window may want to set one of its own
    return FALSE;
}

//-----------------------------------------------------------------------------
//
// ---
void COpenGLView::OnSetFocus(CWnd* pOldWnd)
{
    CView::OnSetFocus(pOldWnd);
    m_pSceneRenderer->DoSetFocus(pOldWnd);
}

//-----------------------------------------------------------------------------
//
// ---
void COpenGLView::OnKillFocus(CWnd* pNewWnd)
{
    CView::OnKillFocus(pNewWnd);
    m_pSceneRenderer->DoKillFocus(pNewWnd);
}

//-----------------------------------------------------------------------------
// License check
// ---
MFC_FUNC(bool) activateLicense()
{
    if (!IsMathVisionEnable())
    {
        MfcVision::LicenseWnd licenseWnd;
        return licenseWnd.Activate();
    }

    return true;
}

} // namespace MfcVision

} // namespace VSN
