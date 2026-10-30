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

#include <qt_eventlistener.h>
#include <qt_openglwidget.h>
#include <qscreen.h>
#include <vsn_last.h>

namespace VSN {
namespace QtVision {

/* QtConverterEventListener */
QtConverterEventListener::QtConverterEventListener(QObject* pParent, GraphicsScene* pGraphicsScene)
    : QObject(pParent)
    , m_pListenerEvent(pGraphicsScene)
    , m_idleTimerId(-1)
    , m_devicePixelRatio(1.0)
{
    Q_ASSERT(m_pListenerEvent != nullptr);
    parent()->installEventFilter(this);
#ifndef VSN_OS_WIN
    m_idleTimerId = startTimer(QGuiApplication::primaryScreen()->refreshRate());
#endif
}

//-----------------------------------------------------------------------------
//
// ---
QtConverterEventListener::~QtConverterEventListener()
{
    parent()->removeEventFilter(this);
}

//-----------------------------------------------------------------------------
//
// ---
bool QtConverterEventListener::keyPressEvent(QKeyEvent* event)
{
    KeyEvent processEvent(ProcessEvent::KeyDown, event->key(), event->nativeScanCode(), event->nativeVirtualKey(), event->nativeModifiers());
    BaseApplication::GetInstance()->OnProcessSendEvent(m_pListenerEvent, &processEvent);
    return false;
}

//-----------------------------------------------------------------------------
//
// ---
bool QtConverterEventListener::keyReleaseEvent(QKeyEvent* event)
{
    KeyEvent processEvent(ProcessEvent::KeyUp, event->key(), event->nativeScanCode(), event->nativeVirtualKey(), event->nativeModifiers());
    BaseApplication::GetInstance()->OnProcessSendEvent(m_pListenerEvent, &processEvent);
    return false;
}

//-----------------------------------------------------------------------------
//
// ---
bool QtConverterEventListener::mouseHoverEvent(QHoverEvent* event)
{
    Q_ASSERT(m_pListenerEvent != nullptr);
    int flags = 0;
    PointI posMouse(event->posF().x() * m_devicePixelRatio, event->posF().y() * m_devicePixelRatio);
    HoverEvent processEvent(ProcessEvent::HoverMove, posMouse, PointI());
    processEvent.SetFlags(flags);
    BaseApplication::GetInstance()->OnProcessSendEvent(m_pListenerEvent, &processEvent);
    return false;
}

//-----------------------------------------------------------------------------
//
// ---
static int mapModifiers(Qt::KeyboardModifiers state)
{
    int flag = 0;
    if (state & Qt::ShiftModifier)
        flag |= mb_Shift;
    if (state & Qt::ControlModifier)
        flag |= mb_Control;
    if (state & Qt::AltModifier)
        flag |= mb_Alt;
    return flag;
}

//-----------------------------------------------------------------------------
//
// ---
bool QtConverterEventListener::mousePressEvent(QMouseEvent* event)
{
    Q_ASSERT(m_pListenerEvent != nullptr);
    ProcessEvent::EventType type = ProcessEvent::None;
    int flags = mapModifiers(event->modifiers());
    if (event->button() == Qt::LeftButton)
    {
        flags |= mb_LButton;
        type = ProcessEvent::LButtonDown;
    }
    else if (event->button() == Qt::MiddleButton)
    {
        flags |= mb_MButton;
        type = ProcessEvent::MButtonDown;
    }
    else if (event->button() == Qt::RightButton)
    {
        flags |= mb_RButton;
        type = ProcessEvent::RButtonDown;
    }

    PointI screenPos(event->screenPos().x() * m_devicePixelRatio, event->screenPos().y() * m_devicePixelRatio);
    PointI windowPos(event->windowPos().x() * m_devicePixelRatio, event->windowPos().y() * m_devicePixelRatio);
    PointI localPos(event->localPos().x() * m_devicePixelRatio, event->localPos().y() * m_devicePixelRatio);

    ViewportPtr ptrViewport = m_pListenerEvent->GetViewport();
    MouseEvent processEvent(type);
    processEvent.SetFlags(flags);
    processEvent.SetViewport(ptrViewport != nullptr ? ptrViewport->GetId() : 0);
    checkShareContexts(processEvent);
    processEvent.SetScreenPos(screenPos);
    processEvent.SetWindowPos(windowPos);
    processEvent.SetClientPos(localPos);
    BaseApplication::GetInstance()->OnProcessSendEvent(m_pListenerEvent, &processEvent);
    return false;
}

//-----------------------------------------------------------------------------
//
// ---
bool QtConverterEventListener::mouseMoveEvent(QMouseEvent* event)
{
    int flags = mapModifiers(event->modifiers());
    if (event->buttons() == Qt::LeftButton)
        flags |= mb_LButton;
    if (event->buttons() == Qt::MiddleButton)
        flags |= mb_MButton;
    if (event->buttons() == Qt::RightButton)
        flags |= mb_RButton;

    PointI screenPos(event->screenPos().x() * m_devicePixelRatio, event->screenPos().y() * m_devicePixelRatio);
    PointI windowPos(event->windowPos().x() * m_devicePixelRatio, event->windowPos().y() * m_devicePixelRatio);
    PointI localPos(event->localPos().x() * m_devicePixelRatio, event->localPos().y() * m_devicePixelRatio);

    ViewportPtr ptrViewport = m_pListenerEvent->GetViewport();
    MouseEvent processEvent(ProcessEvent::MouseMove);
    processEvent.SetFlags(flags);
    processEvent.SetViewport(ptrViewport != nullptr ? ptrViewport->GetId() : 0);
    checkShareContexts(processEvent);
    processEvent.SetScreenPos(screenPos);
    processEvent.SetWindowPos(windowPos);
    processEvent.SetClientPos(localPos);
    BaseApplication::GetInstance()->OnProcessSendEvent(m_pListenerEvent, &processEvent);
    return false;
}

//-----------------------------------------------------------------------------
//
// ---
bool QtConverterEventListener::mouseReleaseEvent(QMouseEvent* event)
{
    ProcessEvent::EventType type = ProcessEvent::None;
    int flags = mapModifiers(event->modifiers());
    if (event->button() == Qt::LeftButton)
    {
        flags |= mb_LButton;
        type = ProcessEvent::LButtonUp;
    }
    else if (event->button() == Qt::MiddleButton)
    {
        flags |= mb_MButton;
        type = ProcessEvent::MButtonUp;
    }
    else if (event->button() == Qt::RightButton)
    {
        flags |= mb_RButton;
        type = ProcessEvent::RButtonUp;
    }

    PointI screenPos(event->screenPos().x() * m_devicePixelRatio, event->screenPos().y() * m_devicePixelRatio);
    PointI windowPos(event->windowPos().x() * m_devicePixelRatio, event->windowPos().y() * m_devicePixelRatio);
    PointI localPos(event->localPos().x() * m_devicePixelRatio, event->localPos().y() * m_devicePixelRatio);

    ViewportPtr ptrViewport = m_pListenerEvent->GetViewport();
    MouseEvent processEvent(type);
    processEvent.SetFlags(flags);
    processEvent.SetViewport(ptrViewport != nullptr ? ptrViewport->GetId() : 0);
    checkShareContexts(processEvent);
    processEvent.SetScreenPos(screenPos);
    processEvent.SetWindowPos(windowPos);
    processEvent.SetClientPos(localPos);
    BaseApplication::GetInstance()->OnProcessSendEvent(m_pListenerEvent, &processEvent);
    return false;
}

//-----------------------------------------------------------------------------
//
// ---
bool QtConverterEventListener::mouseDoubleClickEvent(QMouseEvent* event)
{
    ProcessEvent::EventType type = ProcessEvent::None;
    int flags = mapModifiers(event->modifiers());
    if (event->button() == Qt::LeftButton)
    {
        flags |= mb_LButton;
        type = ProcessEvent::LButtonDblClk;
    }
    else if (event->button() == Qt::MiddleButton)
    {
        flags |= mb_MButton;
        type = ProcessEvent::MButtonDblClk;
    }
    else if (event->button() == Qt::RightButton)
    {
        flags |= mb_RButton;
        type = ProcessEvent::RButtonDblClk;
    }

    PointI screenPos(event->screenPos().x() * m_devicePixelRatio, event->screenPos().y() * m_devicePixelRatio);
    PointI windowPos(event->windowPos().x() * m_devicePixelRatio, event->windowPos().y() * m_devicePixelRatio);
    PointI localPos(event->localPos().x() * m_devicePixelRatio, event->localPos().y() * m_devicePixelRatio);

    ViewportPtr ptrViewport = m_pListenerEvent->GetViewport();
    MouseEvent processEvent(type);
    processEvent.SetFlags(flags);
    processEvent.SetViewport(ptrViewport != nullptr ? ptrViewport->GetId() : 0);
    checkShareContexts(processEvent);
    processEvent.SetScreenPos(screenPos);
    processEvent.SetWindowPos(windowPos);
    processEvent.SetClientPos(localPos);
    BaseApplication::GetInstance()->OnProcessSendEvent(m_pListenerEvent, &processEvent);
    return false;
}

//-----------------------------------------------------------------------------
//
// ---
bool QtConverterEventListener::mouseWheelEvent(QWheelEvent* event)
{
    WheelEvent processEvent;
    int flags = mapModifiers(event->modifiers());
    processEvent.SetFlags(flags);

#if (QT_VERSION <= QT_VERSION_CHECK(6, 0, 0))
    processEvent.SetWheelDelta(event->delta());
    processEvent.SetWindowPos(PointI(event->pos().x(), event->pos().y()));
#else
    processEvent.SetWheelDelta(event->angleDelta().y() * m_devicePixelRatio);
    processEvent.SetWindowPos(PointI(event->position().x() * m_devicePixelRatio, event->position().y() * m_devicePixelRatio));
#endif
    BaseApplication::GetInstance()->OnProcessSendEvent(m_pListenerEvent, &processEvent);
    return false;
}

//-----------------------------------------------------------------------------
//
// ---
bool QtConverterEventListener::mouseEnterEvent(QEnterEvent* event)
{
    ViewportPtr ptrViewport = m_pListenerEvent->GetViewport();
    MouseEvent processEvent(ProcessEvent::MouseEnter);

    PointI screenPos(event->screenPos().x() * m_devicePixelRatio, event->screenPos().y() * m_devicePixelRatio);
    PointI windowPos(event->windowPos().x() * m_devicePixelRatio, event->windowPos().y() * m_devicePixelRatio);
    PointI localPos(event->localPos().x() * m_devicePixelRatio, event->localPos().y() * m_devicePixelRatio);

    processEvent.SetFlags(0);
    processEvent.SetViewport(ptrViewport != nullptr ? ptrViewport->GetId() : 0);
    checkShareContexts(processEvent);
    processEvent.SetScreenPos(screenPos);
    processEvent.SetWindowPos(windowPos);
    processEvent.SetClientPos(localPos);
    BaseApplication::GetInstance()->OnProcessSendEvent(m_pListenerEvent, &processEvent);
    return false;
}

//-----------------------------------------------------------------------------
//
// ---
bool QtConverterEventListener::mouseLeaveEvent(QEvent* event)
{
    VSN_UNUSED(event);
    ViewportPtr ptrViewport = m_pListenerEvent->GetViewport();
    MouseEvent processEvent(ProcessEvent::MouseLeave);
    processEvent.SetViewport(ptrViewport != nullptr ? ptrViewport->GetId() : 0);
    checkShareContexts(processEvent);
    BaseApplication::GetInstance()->OnProcessSendEvent(m_pListenerEvent, &processEvent);
    return false;
}

//-----------------------------------------------------------------------------
//
// ---
bool QtConverterEventListener::checkShareContexts(MouseEvent& processEvent)
{
    if (!QApplication::instance()->testAttribute(Qt::AA_ShareOpenGLContexts))  return false;

    if (QtOpenGLSceneWidget* pWidget = dynamic_cast<QtOpenGLSceneWidget*> (this->parent()))
    {
        Viewport* pViewWid = pWidget->viewport();
        if(!pViewWid)  return false;
        if (pViewWid->GetId() != processEvent.GetViewport())
            processEvent.SetViewport(pViewWid->GetId());
    }
    return true;
}

//-----------------------------------------------------------------------------
// Перегрузка для внутренних работ.
// ---
bool QtConverterEventListener::eventFilter(QObject* watched, QEvent* event)
{
    if (watched != parent())
        return QObject::eventFilter(watched, event);

    switch (event->type())
    {
        case QEvent::KeyPress:
            return keyPressEvent(static_cast<QKeyEvent*>(event));
        case QEvent::KeyRelease:
            return keyReleaseEvent(static_cast<QKeyEvent*>(event));
        case QEvent::HoverMove:
            return mouseHoverEvent(static_cast<QHoverEvent*>(event));
        case QEvent::MouseMove:
            return mouseMoveEvent(static_cast<QMouseEvent*>(event));
        case QEvent::MouseButtonDblClick:
            return mouseDoubleClickEvent(static_cast<QMouseEvent*>(event));
        case QEvent::MouseButtonPress:
            return mousePressEvent(static_cast<QMouseEvent*>(event));
        case QEvent::MouseButtonRelease:
            return mouseReleaseEvent(static_cast<QMouseEvent*>(event));
        case QEvent::Wheel:
            return mouseWheelEvent(static_cast<QWheelEvent*>(event));
        case QEvent::Enter:
            return mouseEnterEvent(static_cast<QEnterEvent*>(event));
        case QEvent::Leave:
            return mouseLeaveEvent(event);
        default:
            break;
    }
    return QObject::eventFilter(watched, event);
}

//-----------------------------------------------------------------------------
//
// ---
void QtConverterEventListener::timerEvent(QTimerEvent* event)
{
    if (event->timerId() == m_idleTimerId)
        BaseApplication::OnProcessSendPostedEvents();
    else
        QObject::timerEvent(event);
}

} // namespace QtVision
} // namespace VSN
