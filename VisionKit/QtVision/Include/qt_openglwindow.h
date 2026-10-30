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
  \brief \ru Классы QtOpenGLWindow, QtOpenGLSceneWindow реализует интеграцию C3D Vision c Qt. Представленные классы
             необходимы для рендеринга графики Vision с помощью OpenGL.
         \en QtOpenGLWindow, QtOpenGLSceneWindow class implements integration of C3D Vision with Qt.
             The presented classes are necessary to render graphics with OpenGL. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __OPENGLWINDOW_H
#define __OPENGLWINDOW_H

#include <QWindow>
#include <QOpenGLDebugLogger>

#include <vsn_vision.h>

#include <qt_openglcontext.h>
#include <qt_global.h>

namespace VSN {

namespace QtVision {

//------------------------------------------------------------------------------
/** \brief \ru Класс QtOpenGLWindow реализует интеграцию C3D Vision c Qt.
           \en QtOpenGLWindow class implements integration of C3D Vision with Qt. \~
    \details \ru QtOpenGLWindow необходим для работы C3D Vision с другими классами библиотеки Qt. Например,
                 как самостоятельный виджет или может быть применен в качестве viewport для GraphicsView
                 и GraphicsScene. Vision внутри работает с собственным представлением контекста OpenGl
                 (OpenGLContextInterface), и класс QtOpenGLWindow содержит некоторые оболочки, обеспечивающие
                 совместную работу QOpenGLContext и OpenGLContextInterface.
             \en QtOpenGLWindow is needed for C3D Vision to operate with other classes of the Qt library,
                 for example, as an independent widget or can be applied as the viewport for both GraphicsView
                 and GraphicsScene. C3D Vision inside operates with its own representation of OpenGL context
                 (OpenGLContextInterface), and QtOpenGLWindow class contains certain shells providing the ability
                 for QtOpenGLWindow and OpenGLContextInterface to operate jointly. \n \~
    \ingroup Vision_OpenGL
*/
// ---
class QT_CLASS QtOpenGLWindow : public QWindow, public Object
{
    Q_OBJECT
    VSN_OBJECT(QtOpenGLWindow)
public:
    explicit QtOpenGLWindow(QWindow* parent = nullptr);
    virtual ~QtOpenGLWindow();
public:
    QOpenGLContext* context() const { return m_pContext; }
    void makeCurrent();
public Q_SLOTS:
    /**
        \brief \ru Перенаправляет на слот requestUpdate(), регистрирующий 
                   событие updateRequest в цикле событий, 
                   которое будет выдано при следующей VSync.
               \en Redirects to slot requestUpdate(), which registers 
                   an UpdateRequest event in the event loop to be 
                   issued with next VSync. \~
    */
    void renderLater();
    /**
        \brief \ru Непосредственно перерисовывает вид прямо 
                   сейчас (эта функция вызывается из event()
                   и exposeEvent().
               \en Directly repaints the view right now 
                   (this function is called from event() 
                   and exposeEvent(). \~
    */
    void renderNow();
protected:
    bool event(QEvent* event) override;
    void exposeEvent(QExposeEvent* event) override;
    void resizeEvent(QResizeEvent* event) override;
protected:
    /**
        \brief \ru Вызывается при первом показе окна.
               \en Called on first show of the window. Re-implement 
                   with your own OpenGL initialization code. \~
    */
    virtual void initializeGL() = 0;
    /**
        \brief \ru Вызывается всякий раз, когда порт просмотра изменяется (геометрия окна).
               \en Called whenever the view port changes (window geometry). Re-implement
                   in your own code, for example to update the projection matrix.
                   This function is called from resizeEvent() and thus before paintGL(). \~
    */
    virtual void resizeGL(int width, int height) { Q_UNUSED(width) Q_UNUSED(height) }
    /**
        \brief \ru Вызывается сразу после того, как контекст OpenGL стал текущим. 
                   Повторная реализация в производных классах для фактического рисования.
               \en Called just after the OpenGL context was made current. Re-implement in
                   derived classes to do the actual painting. \~
    */
    virtual void paintGL() = 0;
protected:
    void showEvent(QShowEvent* event) override;
private Q_SLOTS:
    /* Receives debug messages from QOpenGLDebugLogger */
    void onMessageLogged(const QOpenGLDebugMessage& msg);
private:
    /* Helper function to initialize the OpenGL context. */
    void initOpenGL();
protected:
    QtOpenGLContext* m_pContext;
private:
    QOpenGLDebugLogger* m_debugLogger;
private:
    friend class RenderAreaSelector;
    Q_DISABLE_COPY(QtOpenGLWindow);
};

class QtConverterEventListener;
/* QtOpenGLSceneWindow */
class QT_CLASS QtOpenGLSceneWindow : public QtOpenGLWindow
{
    Q_OBJECT
    VSN_OBJECT(QtOpenGLSceneWindow)
public:
    explicit QtOpenGLSceneWindow(QWindow* parent = nullptr);
    virtual ~QtOpenGLSceneWindow();
public:
    /// \ru Вернуть указатель на источник освещения сцены. \en Returns a pointer to the lighting source in the scene. \~
    Light* mainLight() const;
    /// \ru Вернуть указатель на камеру. \en Returns a pointer to the camera. \~
    Camera* camera() const;
    /// \ru Вернуть указатель на Viewport для отображения сцены. \en Returns a pointer to Viewport for displaying the scene. \~
    Viewport* viewport() const;
    /// \ru Вернуть указатель на содержимое сцены. \en Returns a pointer to the scene content. \~
    SceneContentPtr sceneContent();
    /// \ru Вернуть указатель на графическую сцену. \en Returns a pointer to the graphic scene. \~
    GraphicsScene* graphicsScene() const;
    /// \ru Вернуть указатель на компонент выбора объектов. \en Returns a pointer to the item of the object selection. \~
    ObjectPickSelection* objectPickSelection() const;
    /// \ru Вернуть указатель на GraphicsSceneEngine. \en Returns a pointer to GraphicsSceneEngine. \~
    GraphicsSceneEnginePtr graphicsEngine() const;
    /// \ru Вернуть указатель на GraphicsView. \en Returns a pointer to GraphicsView. \~
    GraphicsViewPtr ptrGraphicsView() const;
    /// \ru Вернуть указатель на GraphicsView. \en Returns a pointer to GraphicsView. \~
    GraphicsView* graphicsView() const;
protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;
protected:
    virtual bool event(QEvent* event) override;
    virtual void showEvent(QShowEvent* event) override;
    virtual void mouseMoveEvent(QMouseEvent*);
    virtual void focusInEvent(QFocusEvent* event) override;
    virtual void focusOutEvent(QFocusEvent* event) override;
    virtual void resizeGL(int width, int height);
protected:
    void processActivation();
    void processDeactivation();
private:
    bool m_bInitialized;
    GraphicsViewPtr m_pGraphicsView;
    QtConverterEventListener* m_pEventFilter;
private:
    Q_DISABLE_COPY(QtOpenGLSceneWindow);
};

} // namespace QtVision

} // namespace VSN

#endif // __OPENGLWINDOW_H
