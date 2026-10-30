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

#ifndef __OPENGLWINDOW_H
#define __OPENGLWINDOW_H

#include <afxwin.h>
#include <vsn_vision.h>
#include <vsn_global.h>
#include <mfc_visiondef.h>

namespace VSN {
namespace MfcVision {

class CSceneRenderer;
//------------------------------------------------------------------------------
/** \brief \ru Класс COpenGLView - это окно для рендеринга графики Vision с помощью OpenGL.
           \en NO TRANSLATION. \~
    \details \ru .
             \en NO TRANSLATION. \n \~
    \ingroup Vision_OpenGL
*/
// ---
class MFC_CLASS COpenGLWnd : public CWnd
{
    DECLARE_DYNCREATE(COpenGLWnd)
public:
    /// \ru Конструктор по умолчанию. \en NO TRANSLATION.
    COpenGLWnd();
    /// \ru Деструктор OpenGLWnd освобождает созданные ресурсы. \en NO TRANSLATION.
    virtual ~COpenGLWnd();
public:
    /// \ru Вернуть указатель на источник освешения сцены. \en Returns a pointer to scene lighting source. \~
    Light* GetMainLight() const;
    /// \ru Вернуть указатель на Viewport для отображения сцены. \en NO TRANSLATION. \~
    Viewport* GetViewport() const;
    /// \ru Вернуть указатель на содержимое сцены. \en NO TRANSLATION. \~
    SceneContentPtr GetSceneContent() const;
    /// \ru Вернуть указатель на GraphicsView. \en NO TRANSLATION. \~
    GraphicsViewPtr GetGraphicsView() const;
    /// \ru Вернуть указатель на CSceneRenderer. \en NO TRANSLATION. \~
    CSceneRenderer* GetSceneRenderer() const;
protected:
    /// \ru Функция вызывается после инициализации Vision. \en NO TRANSLATION. \~
    virtual void InitializeOpenGL();
    // for processing Windows messages
    BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult) override;
protected:
    //{{AFX_MSG(MFCContext
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnDestroy();
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    afx_msg void OnPaint();
    afx_msg void OnSize(UINT nType, int cx, int cy);
protected:
    DECLARE_MESSAGE_MAP()
private:
    CSceneRenderer* m_pSceneRenderer;
};

} // namespace MfcVision

} // namespace VSN


#endif /* __OPENGLWINDOW_H */

