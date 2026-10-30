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

#include <qt_openglcontext.h>
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOpenGLExtraFunctions>

#include <vsn_last.h>

namespace VSN {
namespace QtVision {

//----------------------------------------------------------------------------
//
// ---
QtOpenGLContext::QtOpenGLContext(QWindow* pWindow, RenderingAreaFormat frm)
    : m_pWindow(pWindow)
    , m_areaFormat(frm)
    , m_pContextContainer(new OpenGLContextContainer)
{
    m_pContextContainer->AddContext(this);
}

//----------------------------------------------------------------------------
//
// ---
QtOpenGLContext::~QtOpenGLContext()
{
    m_pContextContainer->RemoveContext(this);
}

//----------------------------------------------------------------------------
//
// ---
bool QtOpenGLContext::MakeCurrent()
{
    if (QOpenGLContext::makeCurrent(m_pWindow))
    {
        if (QOpenGLContext::currentContext() != this)
        {
            Q_ASSERT(false);
            return false;
        }
        return OpenGLContextInterface::MakeCurrent();
    }
    return false;
}

//----------------------------------------------------------------------------
//
// ---
void QtOpenGLContext::DoneCurrent()
{
    OpenGLContextInterface::DoneCurrent();
    QOpenGLContext::doneCurrent();
}

//----------------------------------------------------------------------------
//
// ---
void QtOpenGLContext::SwapBuffers()
{
    QOpenGLContext::swapBuffers(m_pWindow);
}

//----------------------------------------------------------------------------
//
// ---
RenderingAreaFormat QtOpenGLContext::GetFormat() const 
{ 
    return m_areaFormat; 
}

// ---
FunctionPtr QtOpenGLContext::GetProcAddress(const std::string& procName) const 
{ return (FunctionPtr)getProcAddress(procName.c_str()); }

// ---
bool QtOpenGLContext::IsValid() const 
{ return QOpenGLContext::isValid(); }

// ---
bool QtOpenGLContext::HasExtension(const String& extension) const
{ return QOpenGLContext::hasExtension(extension.c_str()); }

// ---
unsigned int QtOpenGLContext::GetDefaultFrameBufferObject() const 
{ return QOpenGLContext::defaultFramebufferObject(); }

//----------------------------------------------------------------------------
//
// ---
OpenGLContextContainer* QtOpenGLContext::GetContextContainer() const 
{ return m_pContextContainer; }

//----------------------------------------------------------------------------
//
// ---
bool QtOpenGLContext::IsOpenGLES() const 
{ return QOpenGLContext::isOpenGLES(); }

//----------------------------------------------------------------------------
//
// ---
QtOpenGLContextShell::QtOpenGLContextShell(QOpenGLWidget* pWidget, OpenGLContextContainer* sharedContainer)
    : m_pWidget(pWidget)
    , m_pContextContainer(sharedContainer ? sharedContainer : new OpenGLContextContainer)
{
    m_pContextContainer->AddContext(this);
}

//----------------------------------------------------------------------------
//
// ---
QtOpenGLContextShell::~QtOpenGLContextShell()
{
    m_pContextContainer->RemoveContext(this);
}

//----------------------------------------------------------------------------
//
// ---
bool QtOpenGLContextShell::MakeCurrent()
{
    if (m_pWidget == nullptr || m_pWidget->context() == nullptr)
        return false;

    m_pWidget->makeCurrent();
    if (QOpenGLContext::currentContext() != m_pWidget->context())
    {
        Q_ASSERT(false);
        return false;
    }

    return OpenGLContextInterface::MakeCurrent();
}

//----------------------------------------------------------------------------
//
// ---
void QtOpenGLContextShell::DoneCurrent()
{
    OpenGLContextInterface::DoneCurrent();
    if (QOpenGLContext::currentContext() != nullptr)
        return;
    if (m_pWidget != nullptr)
        m_pWidget->doneCurrent();
}

FunctionPtr QtOpenGLContextShell::GetProcAddress(const std::string& procName) const 
{ return (FunctionPtr)m_pWidget->context()->getProcAddress(procName.c_str()); }
bool QtOpenGLContextShell::IsValid() const 
{ return m_pWidget->context()->isValid(); }
bool QtOpenGLContextShell::HasExtension(const String& extension) const
{
    QByteArray extensionVal = extension.c_str();
    bool bResult = m_pWidget->context()->hasExtension(extensionVal);
    return bResult;
}
GLuint QtOpenGLContextShell::GetDefaultFrameBufferObject() const 
{ return m_pWidget->context()->defaultFramebufferObject(); }
OpenGLContextContainer* QtOpenGLContextShell::GetContextContainer() const 
{ return m_pContextContainer; }
bool QtOpenGLContextShell::IsOpenGLES() const 
{ return m_pWidget->context()->isOpenGLES(); }
QOpenGLContext* QtOpenGLContextShell::context() const
{ return m_pWidget->context(); }

} // namespace QtVision
} // namespace VSN
