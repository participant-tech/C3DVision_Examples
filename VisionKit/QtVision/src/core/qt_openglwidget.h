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
  \brief \ru Класс QtOpenGLWidget реализует интеграцию C3D Vision c Qt. Представленные классы 
             необходимы для рендеринга графики Vision с помощью OpenGL.
         \en QtOpenGLWidget class implements integration of C3D Vision with Qt.
             The presented classes are necessary to render graphics with OpenGL. \~
*/
////////////////////////////////////////////////////////////////////////////////
#ifndef __OPENGLWIDGET_H
#define __OPENGLWIDGET_H

#include <QApplication>
#include <QWidget>
#if (QT_VERSION <= QT_VERSION_CHECK(6, 0, 0))
#include <QOpenGLWidget>
#else
#include <QtOpenGLWidgets/QOpenGLWidget>
#endif
#include <QSurfaceFormat>

#include <vsn_vision.h>
#include <vsn_application.h>
#include <vsn_meshgeometry.h>
#include <vsn_graphicsview.h>
#include <vsn_graphicssceneengine.h>
#include <vsn_objectpickselection.h>
#include <vsn_openglcontextinterface.h>
#include <vsn_statisticsposition.h>
#include <qt_cursors.h>
#include <qt_headsuptoolbar.h>
#include <qt_theme.h>
#include <qt_global.h>

namespace VSN {
namespace QtVision {

class QtOpenGLContextShell;
class QtAutoHideWindow;
class QtConverterEventListener;
//------------------------------------------------------------------------------
/** \brief \ru Класс QtOpenGLSceneWidget - это виджет для рендеринга графики Vision с помощью OpenGL.
           \en QtOpenGLSceneWidget is a widget for rendering C3D Vision graphics with OpenGL. \~
    \details \ru Класс QtOpenGLSceneWidget полностью самостоятельный, создает и инициализирует 
                 в полной мере компоненты Vision. Этот класс представляет необходимые функции для работы с Vision. 
                 Класс QtOpenGLSceneWidget самостоятельно устанавливает текущий контест OpenGL, когда это необходимо. 
             \en QtOpenGLSceneWidget class is fully autonomous, so it completely creates and initialises
                 C3D Vision components. This class provides required functions to work with C3D Vision.
                 QtOpenGLSceneWidget class independently sets the current OpenGL context when necessary. \n \~
    \ingroup Vision_OpenGL
*/
// ---
class QT_CLASS QtOpenGLSceneWidget : public QOpenGLWidget, public Object
{
    Q_OBJECT
    VSN_OBJECT(QtOpenGLSceneWidget)
public:
    /// \ru Конструктор по умолчанию. \en Default constructor. \~
    explicit QtOpenGLSceneWidget(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    /// \ru Специальный конструктор. \en Special constructor. \~
    explicit QtOpenGLSceneWidget(GraphicsSceneEnginePtr engine, OpenGLContextContainer* sharedContainer, 
                QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
    /// \ru Деструктор OpenGLWidget освобождает созданные ресурсы. \en OpenGLWidget destructor releases created resources. \~
    ~QtOpenGLSceneWidget() override;
public:
    /**
    \brief \ru Подготовка OpenGL для рендеринга в этом виджете (установить текущий OpenGL контекст).
           \en Prepares OpenGL for rendering in the widget. Sets the current OpenGL context.
        \detaild \ru Нет необходимости вызывать эту функцию в большинстве случаев, потому что она
                     вызывается автоматически перед вызовом paintGL().
                 \en There is no need to call this function in most cases, as it is called automatically
                     before calling paintGL().
    */
    using QOpenGLWidget::makeCurrent;
    void makeCurrent();
    /**
    \brief \ru Освободить OpenGL контекст.
           \en Releases OpenGL context.
        \detailed \ru Нет необходимости вызывать эту функцию в большинстве случаев, поскольку
                      в функции paintGL() контекст будет назначен и освобожден.
                  \en There is no need to call this function in most cases, as there will be the context set and
                      released in paintGL() function.
    */
    using QOpenGLWidget::doneCurrent;
    void doneCurrent();

    /// \ru Вернуть указатель на OpenGLContextInterface. \en Returns a pointer to OpenGLContextInterface. \~
    OpenGLContextInterface* contextInterface();
    /// \ru Нарисовать сцену и сохранить в картинку. \en Draw a scene and save it as a picture. \~
    QImage grabFrameImage(const GraphicsView* pGraphicsView, int width, int height, const SnapshotSettings& settings);
public Q_SLOTS:
    /// \ru Показать сайт компании. \en Show the company website. \~
    void showCompanyWebSite();
public:
    /// \ru Просто вызывает функцию QWidget::update(). Служит для совместимости слотов.
    /// \en Just calls QWidget::update() function. Serves for compatibility of slots. \~
    VSN_SLOT(Public, updateWidget, void updateWidget())
    /// \ru Просто вызывает функцию QWidget::repaint(). Служит для совместимости слотов.
    /// \en Just calls QWidget::repaint() function. Serves for compatibility of slots. \~
    VSN_SLOT(Public, repaintWidget, void repaintWidget())
Q_SIGNALS:
    void initializeRendering();
protected:
    /// \ru Инициализация OpenGL ресурсов. \en Initialises OpenGL resources. \~
    void initializeGL() override;
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
public:
    /// \ru Показать статистику отрисовки. \en Shows render statistics. \~
    void showStatistics(bool show);
    /// \ru Установить позицию статистики. \en Sets statistics position. \~
    void setStatisticsPosition(StatisticsPosition position);
public:
    QtAutoHideWindow* headToolbar(bool createMode = false);
public Q_SLOTS:
    void viewPortCommands();
    void viewPortRenderMode();
    void setRenderMode(RenderMode mode);
public:
    /// \ru Масштабировать модель до размера viewport по габариту модели. \en Zooms the model to ensure the bounding box of the model fits inside the viewport. \~
    VSN_SLOT(Public, ZoomToFit, void ZoomToFit())
protected:
    void resizeGL(int w, int h) override;
    void paintGL() override;
    bool event(QEvent* event) override;
#if (QT_VERSION <= QT_VERSION_CHECK(6, 0, 0))
    void enterEvent(QEvent* event) override;
#else
    void enterEvent(QEnterEvent* event) override;
#endif
    void leaveEvent(QEvent* event) override;
    void focusInEvent(QFocusEvent* event) override;
    void focusOutEvent(QFocusEvent* event) override;
    void showEvent(QShowEvent* event) override;
    void closeEvent(QCloseEvent* event) override;
    bool OnEvent(ProcessEvent* event);
private:
    void initialize();
    void reset();
    void renderLater();
    void processActivation();
    void processDeactivation();
private:
    bool m_bInitialized; ///< признак инициализация контекста
    bool m_bUpdatePending;
    OpenGLContextContainer* m_pSharedContainer;
    QtOpenGLContextShell* m_pQContext;

    GraphicsViewPtr m_pGraphicsView;
    QtConverterEventListener* m_pEventFilter;
    QtAutoHideWindow* m_pAutoHideWindow;
private:
    Q_DISABLE_COPY(QtOpenGLSceneWidget);
    friend class QtRenderSelection;
};

enum ProcessType
{
    pt_Pan             = 0x01, ///< \ru Инициализация процесса параномирования. \en Initializes the pan process. \~
    pt_Orbit           = 0x02, ///< \ru Инициализация процесса вращения вокруг орбиты. \en Initializes the process of rotation about the orbit. \~
    pt_Rotate          = 0x04, ///< \ru Инициализация процесса вращения вокруг центра габарита. \en Initialization the process of rotation about the center of the boundbox. \~
    pt_ComplexRotation = 0x08, ///< \ru Инициализация процесса вращения вокруг оси. \en Initialization the process of rotation about the axis. \~
    pt_Zoom            = 0x10, ///< \ru Инициализация процесса масштабирования. \en Initializes the zoom process. \~
    pt_AllProcess = pt_Orbit | pt_Zoom | pt_Pan,
};
VSN_DECLARE_FLAGS(ProcessTypes, ProcessType)

enum ThemeId
{
    Default,    ///< \ru Тема по умолчанию. \en Default theme.
    Dark,       ///< \ru Темная тема. \en Dark theme. \~
    FlatDark,   ///< \ru Темная плоская тема. \en Dark-Flat theme. \~
};

//static Color topColor    = Color(174, 174, 174);
//static Color bottomColor = Color(250, 250, 250);

static Color topColor = Color(250, 250, 250);
static Color bottomColor = Color(174, 174, 174);

/// \ru Создание процессов для управления камерой. \en Creates processes to control the camera. \~
QT_FUNC(void) createProcessesCameraControls(GraphicsSceneEnginePtr ptrEngine, ProcessTypes prType = pt_AllProcess, 
    SceneSegment* pParent = nullptr);

/// \ru Проверка лицензии. \en License check.
QT_FUNC(bool) activateLicense();
/// \ru Инициализация темы. \en Initializing a theme.
// QT_FUNC(void) initializingTheme(ThemeId id = Default);
/// \ru Позиционирование главного окна. \en Positioning the main window.
QT_FUNC(void) setWindowPosition(QWidget& widget);
//
QT_FUNC(QStringList) processFilters();

} // namespace QtVision
} // namespace VSN

#endif // __OPENGLWIDGET_H
