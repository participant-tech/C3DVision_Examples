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
  \brief \ru .
         \en . \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __OPENGLWIDGETPRIVATE_H
#define __OPENGLWIDGETPRIVATE_H

#include <qevent.h>
#include <qt_openglwidget.h>
#include <qt_global.h>

namespace VSN {
namespace QtVision {
//------------------------------------------------------------------------------
/** \brief \ru Класс QtConverterEventListener служит для интеграции с событийной моделью Qt и Vision.
           \en QtConverterEventListener class gives integration with event Qt model and Vision. \~
    \details \ru В первую очередь, QtConverterEventListener необходим для обеспечения работы Vision
                 с манипуляторами, такими как мышь, клавиатура и др. Кроме того, ConverterEvent служит
                 для конвертации определенных событий Qt в понятные события для Vision.
              \en QtConverterEventListener is primarily needed to provide functioning of Vision with
                  such manipulators as mouse, keyboard, etc. Besides, ConverterEvent provides converting
                  certain Qt events to familiar events for Vision. \n \~
    \ingroup Vision_OpenGL
*/
// ---
class QT_CLASS QtConverterEventListener : public QObject
{
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit QtConverterEventListener(QObject* pParent, GraphicsScene* pListenerEvent);
    /// \ru Деструктор. \en Destructor. \~
    virtual ~QtConverterEventListener();
public:
    inline void setDevicePixelRatio(double pixelRatio) { m_devicePixelRatio = pixelRatio; }
protected:
    bool keyPressEvent(QKeyEvent* event);
    bool keyReleaseEvent(QKeyEvent* event);
    bool mouseHoverEvent(QHoverEvent* event);
    bool mousePressEvent(QMouseEvent* event);
    bool mouseMoveEvent(QMouseEvent* event);
    bool mouseReleaseEvent(QMouseEvent* event);
    bool mouseDoubleClickEvent(QMouseEvent* event);
    bool mouseWheelEvent(QWheelEvent* event);
    bool mouseEnterEvent(QEnterEvent* event);
    bool mouseLeaveEvent(QEvent* event);
protected:
    /// \ru Перегрузка для внутренних работ. \en Overload for internal workings.
    bool eventFilter(QObject* watched, QEvent* event) override;
    void timerEvent(QTimerEvent* event) override;
private:
    bool checkShareContexts(MouseEvent& event);
protected:
    GraphicsScene* m_pListenerEvent;
    int m_idleTimerId;
    qreal m_devicePixelRatio;
};

class QtOpenGLContextShell;
/* QtOpenGLWidgetPrivate */
class QtOpenGLWidgetPrivate
{
protected:
    VSN_DECLARE_PUBLIC(QtOpenGLWidget);
public:
    explicit QtOpenGLWidgetPrivate(OpenGLContextContainer* pSharedContainer = nullptr)
        : m_bInitialized(false)
        , m_bUpdatePending(false)
        , m_pSharedContainer(pSharedContainer)
        , m_pQContext(nullptr)
    {
    }
    virtual ~QtOpenGLWidgetPrivate();
    virtual void initialize();
    void reset();
    void renderNow();
    void renderLater();
public:
    bool m_bInitialized;    ///< признак инициализация контекста
    bool m_bUpdatePending;
    OpenGLContextContainer* m_pSharedContainer;
    QtOpenGLContextShell* m_pQContext;
};

} // namespace QtVision

} // namespace VSN

#endif // __OPENGLWIDGETPRIVATE_H
