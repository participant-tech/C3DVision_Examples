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

////////////////////////////////////////////////////////////////////////////////
/**
    \file
    \brief \ru Эти классы необходимы для интеграции Vision с Qt, чтобы обеспечить работу Vision
               c контекстом Qt и разным набором функций любой версии OpenGL.
           \en These classes are needed to integrate Vision with Qt and provides Vision
               with services to work with Qt context and different function set of any OpenGL version. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __QT_OPENGLCONTEXT_H
#define __QT_OPENGLCONTEXT_H

#include <QWindow>
#if (QT_VERSION <= QT_VERSION_CHECK(6, 0, 0))
#include <QOpenGLWidget>
#else
#include <QtOpenGLWidgets/QOpenGLWidget>
#endif
#include <QOpenGLContext>

#include <vsn_vision.h>

namespace VSN {
namespace QtVision {
//------------------------------------------------------------------------------
/** \brief \ru Класс QtOpenGLContext интегрирует QOpenGLContext для работы его в Vision.
           \en QtOpenGLContext class integrates QOpenGLContext for it to work in Vision. \~
    \details \ru QtOpenGLContext представляет набор функций для работы внутри Vision, а также
                 для установки текущего OpenGL контекста и его "свепирования" при отрисовке.
             \en QtOpenGLContext class represents a set of functions to work inside Vision
                 and also to set the current OpenGL context and its swapping while rendering. \n \~
    \ingroup QtVision
*/
// ---
class QtOpenGLContext : public QOpenGLContext, public OpenGLContextInterface
{
public:
    explicit QtOpenGLContext(QWindow* pWindow, RenderingAreaFormat frm);
    ~QtOpenGLContext() override;
public:
    bool MakeCurrent() override;
    void DoneCurrent() override;
    void SwapBuffers() override;
    RenderingAreaFormat GetFormat() const override;
    FunctionPtr GetProcAddress(const std::string& procName) const override;
    bool IsValid() const override;
    bool HasExtension(const String& extension) const override;
    unsigned int GetDefaultFrameBufferObject() const override;
    OpenGLContextContainer* GetContextContainer() const override;
    bool IsOpenGLES() const override;
protected:
    QWindow* m_pWindow;
    RenderingAreaFormat m_areaFormat;
    OpenGLContextContainer* m_pContextContainer;
};


//------------------------------------------------------------------------------
/** \brief \ru Класс QtOpenGLContextShell является оболочкой для QOpenGLContext.
           \en QtOpenGLContextShell class is a shell for QOpenGLContext. \~
    \details \ru Класс QtOpenGLContextShell инкапсулирует QOpenGLContext и перевызывает основной функционал, 
                 который необходим для совместной работы Vision и QOpenGLWidget.
             \en QtOpenGLContextShell class uncollapses QOpenGLContext and recalls the main functional
                 necessary for Vision and QOpenGLWidget to work jointly. \n \~
    \ingroup QtVision
*/
// ---
class QtOpenGLContextShell : public OpenGLContextInterface
{
public:
    explicit QtOpenGLContextShell(QOpenGLWidget* pWidget, OpenGLContextContainer* sharedContainer = nullptr);
    ~QtOpenGLContextShell() override;
public:
    virtual bool MakeCurrent() override;
    virtual void DoneCurrent() override;
    virtual FunctionPtr GetProcAddress(const std::string& procName) const override;
    virtual bool IsValid() const override;
    virtual bool HasExtension(const String& extension) const override;
    virtual unsigned int GetDefaultFrameBufferObject() const override;
    virtual OpenGLContextContainer* GetContextContainer() const override;
    virtual bool IsOpenGLES() const override;
public:
    QOpenGLContext* context() const;
protected:
    QOpenGLWidget* m_pWidget;
    OpenGLContextContainer* m_pContextContainer;
};

} // namespace QtVision

} // namespace VSN

#endif // __QT_OPENGLCONTEXT_H
