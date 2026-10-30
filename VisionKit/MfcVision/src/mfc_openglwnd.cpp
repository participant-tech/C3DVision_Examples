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

#include "mfc_stdafx.h"
#include "mfc_openglwnd.h"
#include "mfc_scenerenderer.h"
#include <vsn_last.h>

namespace VSN {
namespace MfcVision {

IMPLEMENT_DYNCREATE(COpenGLWnd, CWnd)
//-----------------------------------------------------------------------------
BEGIN_MESSAGE_MAP(COpenGLWnd, CWnd)
    ON_WM_CREATE()
    ON_WM_DESTROY()
    ON_WM_SHOWWINDOW()
    ON_WM_PAINT()
    ON_WM_SIZE()
END_MESSAGE_MAP()

/* COpenGLWnd */
//-----------------------------------------------------------------------------
//
// ---
COpenGLWnd::COpenGLWnd()
    : m_pSceneRenderer(new CSceneRenderer)
{
}

//-----------------------------------------------------------------------------
//
// ---
COpenGLWnd::~COpenGLWnd()
{
    VSN_DELETE_AND_NULL(m_pSceneRenderer);
}

//-----------------------------------------------------------------------------
// Вернуть указатель на источник освешения сцены.
// ---
Light* COpenGLWnd::GetMainLight() const
{ return m_pSceneRenderer->GetMainLight(); }

//-----------------------------------------------------------------------------
// Вернуть указатель на Viewport для отображения сцены.
// ---
Viewport* COpenGLWnd::GetViewport() const
{ return m_pSceneRenderer->GetViewport();}

//-----------------------------------------------------------------------------
// Вернуть указатель на содержимое сцены.
// ---
SceneContentPtr COpenGLWnd::GetSceneContent() const
{ return m_pSceneRenderer->GetSceneContent(); }

//-----------------------------------------------------------------------------
// Вернуть указатель на GraphicsView.
// ---
GraphicsViewPtr COpenGLWnd::GetGraphicsView() const
{ return m_pSceneRenderer->GetGraphicsView(); }

// Вернуть указатель на CSceneRenderer
CSceneRenderer* COpenGLWnd::GetSceneRenderer() const 
{ return m_pSceneRenderer; }

//-----------------------------------------------------------------------------
// Функция вызывается после инициализации Vision
// ---
void COpenGLWnd::InitializeOpenGL()
{
}

//-----------------------------------------------------------------------------
// for processing Windows messages
// ---
BOOL COpenGLWnd::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
    MSG msg{};
    msg.message = message;
    msg.wParam = wParam;
    msg.lParam = lParam;
    if (m_pSceneRenderer->OnWinEvent(&msg))
        return TRUE;
    return CWnd::OnWndMsg(message, wParam, lParam, pResult);
}

//-----------------------------------------------------------------------------
// Создать окно и захватить ресурсы OpenGL, а также произвести инициализацию Vision
// ---
int COpenGLWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
        return -1;
    m_pSceneRenderer->DoCreate(m_hWnd);
    InitializeOpenGL();
    return 0;
}

//-----------------------------------------------------------------------------
//
// ---
void COpenGLWnd::OnDestroy()
{
    m_pSceneRenderer->DoDestroy();
    CWnd::OnDestroy();
}

//-----------------------------------------------------------------------------
//
// ---
void COpenGLWnd::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CWnd::OnShowWindow(bShow, nStatus);
    if (bShow)
        m_pSceneRenderer->DoPreparingToDisplay();
}

//-----------------------------------------------------------------------------
//
// ---
void COpenGLWnd::OnPaint()
{
    CPaintDC dc(this); // device context for painting
    m_pSceneRenderer->DoDraw();
}

//-----------------------------------------------------------------------------
//
// ---
void COpenGLWnd::OnSize(UINT nType, int cx, int cy)
{
    CWnd::OnSize(nType, cx, cy);
    if (0 >= cx || 0 >= cy || nType == SIZE_MINIMIZED)
        return;
    m_pSceneRenderer->DoResize(cx, cy);
}

} // namespace MfcVision
} // namespace VSN
