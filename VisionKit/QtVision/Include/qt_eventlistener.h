////////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru .
         \en . \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __EVENTLISTENER_H
#define __EVENTLISTENER_H

#include <qevent.h>
#include <QApplication>
#include <qt_global.h>

namespace VSN {

/** \brief \ru ВНИМАНИЕ! Этот файл не является частью API Vision. Он необходим для иллюстрации использования 
               ядра Vision с библиотекой Qt и ее классами. Этот заголовочный файл может изменяться от версии 
               к версии без предупреждения или полностью удаляться.
           \en WARNING! The file is not a part of API Vision. It is needed to illustrate using of the Vision kernel
               with Qt library and its classes. This header file can be changed from version to version with
               no warning or completely deleted.\~
*/
class MouseEvent;
class GraphicsScene;

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
class QtConverterEventListener : public QObject
{
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit QtConverterEventListener(QObject* pParent, GraphicsScene* pListenerEvent);
    /// \ru Деструктор. \en Destructor. \~
    ~QtConverterEventListener() override;
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

} // namespace QtVision
} // namespace VSN

#endif // __EVENTLISTENER_H
