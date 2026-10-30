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

#include <qt_openglwidget.h>
#include <QApplication>
#include <QScreen>
#include <QWindow>
#include <QMessageBox>
#include <QDesktopServices>
#include <QProcessEnvironment>
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QOffscreenSurface>
#include <QOpenGLPaintDevice>
#include <QOpenGLFramebufferObject>
#include <QSettings>

#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
#include <QScreen>
#else
#include <QDesktopWidget>
#endif

#include <tool_enabler.h>

#include <vsn_window.h>
#include <vsn_openglfbo.h>
#include <vsn_graphicsview.h>
#include <vsn_renderstatistics.h>
#include <vsn_graphicssceneengine.h>
#include <vsn_graphicsscene.h>
#include <vsn_texture2d.h>
#include <vsn_glfixedfunctionsproxy.h>

#include <qt_openglcontext.h>
#include <qt_eventlistener.h>
#include <qt_licensewnd.h>


#include <vsn_last.h>

namespace VSN {
namespace QtVision {
// ---
extern void reportContextStatus(OpenGLContextInterface::InitStatus status)
{
    switch (status)
    {
        case OpenGLContextInterface::InitStatus::UnsupportedOpenGL:
            std::cerr << "Vision requires OpenGL" << OpenGLContextInterface::GetRequiredOpenGLVersion().ToString();
            break;
        case OpenGLContextInterface::InitStatus::InvalidCurrentContext:
            std::cerr << "OpenGL context not set or invalid";
            break;
        case OpenGLContextInterface::InitStatus::Ok:
            break;
        default:
            std::cerr << "Unknown context status";
    }
}


/* QtOpenGLSceneWidget */
QtOpenGLSceneWidget::QtOpenGLSceneWidget(QWidget* parent, Qt::WindowFlags f)
    : QOpenGLWidget(parent, f)
    , m_bInitialized(false)
    , m_bUpdatePending(false)
    , m_pSharedContainer(nullptr)
    , m_pQContext(nullptr)
    , m_pGraphicsView(std::make_shared<GraphicsView>(std::make_shared<GraphicsSceneEngine>()))
    , m_pEventFilter(nullptr)
    , m_pAutoHideWindow(nullptr)
{
    setUpdateBehavior(QOpenGLWidget::PartialUpdate);
}

//-----------------------------------------------------------------------------
// Special constructor.
// ---
QtOpenGLSceneWidget::QtOpenGLSceneWidget(GraphicsSceneEnginePtr engine, OpenGLContextContainer* sharedContainer, QWidget* parent, Qt::WindowFlags f)
    : QOpenGLWidget(parent, f)
    , m_bInitialized(false)
    , m_bUpdatePending(false)
    , m_pSharedContainer(sharedContainer)
    , m_pQContext(nullptr)
    , m_pGraphicsView(std::make_shared<GraphicsView>(engine))
    , m_pEventFilter(nullptr)
    , m_pAutoHideWindow(nullptr)
{
    setUpdateBehavior(QOpenGLWidget::PartialUpdate);
}

//-----------------------------------------------------------------------------
//
// ---
QtOpenGLSceneWidget::~QtOpenGLSceneWidget()
{
    makeCurrent();
    m_pGraphicsView->PreparingToDestroy();
    m_pGraphicsView.reset();
    doneCurrent();
    VSN_DELETE_AND_NULL(m_pEventFilter);
    reset();
}

// ---
void QtOpenGLSceneWidget::makeCurrent()
{ if (m_pQContext) m_pQContext->MakeCurrent(); }
// ---
void QtOpenGLSceneWidget::doneCurrent()
{ if (m_pQContext) m_pQContext->DoneCurrent(); }

//-----------------------------------------------------------------------------
// Вернуть указатель на OpenGLContextInterface.
// ---
OpenGLContextInterface* QtOpenGLSceneWidget::contextInterface() { return m_pQContext; }

//-----------------------------------------------------------------------------
//
// ---
QImage QtOpenGLSceneWidget::grabFrameImage(const GraphicsView* pGraphicsView, int nWidth, int nHeight,
    const SnapshotSettings& settings)
{
    makeCurrent();
    Image image = pGraphicsView->ToImage(nWidth, nHeight, settings);
    if (!image.IsValid())
        return QImage();
    size_t size = nWidth * nHeight;
    QImage::Format format = QImage::Format::Format_Invalid;
    switch (image.GetFormat())
    {
        case Image::Format::UINT8:
            format = QImage::Format_Indexed8;
            break;
        case Image::Format::UINT24:
            size *= 3;
            format = QImage::Format_RGB888;
            break;
        case Image::Format::UINT32:
            size *= 4;
            format = QImage::Format_ARGB32;
            break;
        default:
            size = 0;
            break;
    };
    QImage qImage = QImage(image.GetWidth(), image.GetHeight(), format);
    memcpy(qImage.bits(), image.GetBits(), image.GetWidth() * image.GetHeight() * 4);
    return qImage.mirrored();
}

// ---
void QtOpenGLSceneWidget::showCompanyWebSite() { QDesktopServices::openUrl(QUrl(QStringLiteral("https://c3dlabs.com"))); }
// Просто вызывает функцию QWidget::update(). Служит для совместимости слотов.
void QtOpenGLSceneWidget::updateWidget() { update(); }
// Просто вызывает функцию QWidget::rapaint(). Служит для совместимости слотов.
void QtOpenGLSceneWidget::repaintWidget() 
{ 
    repaint(); 
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidget::initializeGL()
{
    if (!m_bInitialized && window() && window()->windowHandle())
    {
        initialize();
        emit initializeRendering();
    }
}

// ---
GraphicsScene* QtOpenGLSceneWidget::graphicsScene() const
{ return m_pGraphicsView->GetGraphicsScene(); }

//-----------------------------------------------------------------------------
// Вернуть указатель на компонент выбора объектов.
// ---
ObjectPickSelection* QtOpenGLSceneWidget::objectPickSelection() const
{
    return m_pGraphicsView->GetSceneEngine()->GetObjectPickSelection();
}

//-----------------------------------------------------------------------------
// Вернуть указатель на GraphicsSceneEngine.
// ---
GraphicsSceneEnginePtr QtOpenGLSceneWidget::graphicsEngine() const
{
    return m_pGraphicsView->GetSceneEngine();
}

//-----------------------------------------------------------------------------
// Вернуть указатель на GraphicsView.
// ---
GraphicsViewPtr QtOpenGLSceneWidget::ptrGraphicsView() const
{
    return m_pGraphicsView;
}

//-----------------------------------------------------------------------------
// Вернуть указатель на GraphicsView
// ---
GraphicsView* QtOpenGLSceneWidget::graphicsView() const
{
    return m_pGraphicsView.get();
}

//-----------------------------------------------------------------------------
// Показать статистику
// ---
void QtOpenGLSceneWidget::showStatistics(bool show)
{
    graphicsScene()->ShowStatistics(show);
}

//-----------------------------------------------------------------------------
// Установка позиции статистики
// ---
void QtOpenGLSceneWidget::setStatisticsPosition(StatisticsPosition position)
{
    graphicsScene()->SetStatisticsPosition(position);
}

#define PROP_ORIENTATION "Orientation"
#define PROP_MODE        "Mode"

//-----------------------------------------------------------------------------
// Вернуть указатель на основной источник света
// ---
QtAutoHideWindow* QtOpenGLSceneWidget::headToolbar(bool createMode)
{
    if (m_pAutoHideWindow != nullptr)
        return m_pAutoHideWindow;

    m_pAutoHideWindow = new QtAutoHideWindow(this);
    QToolBar* pHeadToolbar = new QToolBar(this);

    QAction* actionViewFront = new QAction(QIcon(":/res/view_front_48.png"), QObject::tr("Front"), this);
    actionViewFront->setProperty(PROP_ORIENTATION, QVariant((int)Orientation::Front));
    pHeadToolbar->addAction(actionViewFront);
    QObject::connect(actionViewFront, SIGNAL(triggered()), this, SLOT(viewPortCommands()));

    QAction* actionViewBack = new QAction(QIcon(":/res/view_back_48.png"), QObject::tr("Back"), this);
    actionViewBack->setProperty(PROP_ORIENTATION, QVariant((int)Orientation::Rear));
    pHeadToolbar->addAction(actionViewBack);
    QObject::connect(actionViewBack, SIGNAL(triggered()), this, SLOT(viewPortCommands()));

    QAction* actionViewTop = new QAction(QIcon(":/res/view_top_48.png"), QObject::tr("Top"), this);
    actionViewTop->setProperty(PROP_ORIENTATION, QVariant((int)Orientation::Up));
    pHeadToolbar->addAction(actionViewTop);
    QObject::connect(actionViewTop, SIGNAL(triggered()), this, SLOT(viewPortCommands()));

    QAction* actionViewBottom = new QAction(QIcon(":/res/view_bottom_48.png"), QObject::tr("Bottom"), this);
    actionViewBottom->setProperty(PROP_ORIENTATION, QVariant((int)Orientation::Down));
    pHeadToolbar->addAction(actionViewBottom);
    QObject::connect(actionViewBottom, SIGNAL(triggered()), this, SLOT(viewPortCommands()));

    QAction* actionViewLeft = new QAction(QIcon(":/res/view_left_48.png"), QObject::tr("Left"), this);
    actionViewLeft->setProperty(PROP_ORIENTATION, QVariant((int)Orientation::Left));
    pHeadToolbar->addAction(actionViewLeft);
    QObject::connect(actionViewLeft, SIGNAL(triggered()), this, SLOT(viewPortCommands()));

    QAction* actionViewRight = new QAction(QIcon(":/res/view_right_48.png"), QObject::tr("Right"), this);
    actionViewRight->setProperty(PROP_ORIENTATION, QVariant((int)Orientation::Right));
    pHeadToolbar->addAction(actionViewRight);
    QObject::connect(actionViewRight, SIGNAL(triggered()), this, SLOT(viewPortCommands()));

    QAction* actionViewIsometry_xyz = new QAction(QIcon(":/res/isometry_x.png"), QObject::tr("Isometry"), this);
    actionViewIsometry_xyz->setProperty(PROP_ORIENTATION, QVariant((int)Orientation::IsoXYZ));
    pHeadToolbar->addAction(actionViewIsometry_xyz);
    QObject::connect(actionViewIsometry_xyz, SIGNAL(triggered()), this, SLOT(viewPortCommands()));

    pHeadToolbar->addSeparator();

    QAction* actionZoomFit = new QAction(QIcon(":/res/view_all_48.png"), QObject::tr("Zoom Fit"), this);
    actionZoomFit->setProperty(PROP_ORIENTATION, QVariant((int)Orientation::CustomBase + 1));
    actionZoomFit->setShortcut(QKeySequence(Qt::Key_F9));
    pHeadToolbar->addAction(actionZoomFit);
    QObject::connect(actionZoomFit, SIGNAL(triggered()), this, SLOT(viewPortCommands()));

    QAction* actionPerspective = new QAction(QIcon(":/res/perspectv_48.png"), QObject::tr("Perspective"), this);
    actionPerspective->setProperty(PROP_ORIENTATION, QVariant((int)Orientation::CustomBase + 2));
    actionPerspective->setCheckable(true);
    actionPerspective->setChecked(!viewport()->IsOrthographicProjection());
    pHeadToolbar->addAction(actionPerspective);
    QObject::connect(actionPerspective, SIGNAL(triggered()), this, SLOT(viewPortCommands()));

    if (createMode)
    {
        pHeadToolbar->addSeparator();

        QAction* actionDimmedWireframe = new QAction(QIcon(":/res/dimmedWireframe.png"), QObject::tr("Dimmed wireframe"), this);
        actionDimmedWireframe->setProperty(PROP_MODE, QVariant((int)rm_ShadedWithEdges));
        QObject::connect(actionDimmedWireframe, SIGNAL(triggered()), this, SLOT(viewPortRenderMode()));
        QObject::connect(actionDimmedWireframe, SIGNAL(triggered()), this, SLOT(WireframeGeometryManager_DoVisible()));

        QAction* actionShaded = new QAction(QIcon(":/res/shaded.png"), QObject::tr("Shaded"), this);
        actionShaded->setProperty(PROP_MODE, QVariant((int)rm_Shaded));
        QObject::connect(actionShaded, SIGNAL(triggered()), this, SLOT(viewPortRenderMode()));
        QObject::connect(actionShaded, SIGNAL(triggered()), this, SLOT(WireframeGeometryManager_DoInvisible()));

        QAction* actionWirefrmquad = new QAction(QIcon(":/res/wirefrmgrids_48.png"), QObject::tr("Wirefrm quad"), this);
        actionWirefrmquad->setProperty(PROP_MODE, QVariant((int)rm_WireframeQuadrangle));
        actionWirefrmquad->setEnabled(false);
        QObject::connect(actionWirefrmquad, SIGNAL(triggered()), this, SLOT(viewPortRenderMode()));

        QAction* actionWirefrm = new QAction(QIcon(":/res/wirefrm.png"), QObject::tr("Wirefrm"), this);
        actionWirefrm->setProperty(PROP_MODE, QVariant((int)rm_Wireframe));
        QObject::connect(actionWirefrm, SIGNAL(triggered()), this, SLOT(viewPortRenderMode()));

        QAction* actionHiddenremoved = new QAction(QIcon(":/res/hiddenremoved.png"), QObject::tr("Hidden Lines Removed"), this);
        actionHiddenremoved->setProperty(PROP_MODE, QVariant((int)rm_HiddenLinesRemoved));
        QObject::connect(actionHiddenremoved, SIGNAL(triggered()), this, SLOT(viewPortRenderMode()));

        QtToolButton* pToolButton = new QtToolButton();
        QAction* currentAction = actionDimmedWireframe;
        switch (graphicsView()->GetRenderMode())
        {
            case rm_Shaded:
                currentAction = actionShaded;
                break;
            case rm_WireframeQuadrangle:
                currentAction = actionWirefrmquad;
                break;
            case rm_Wireframe:
                currentAction = actionWirefrm;
                break;
            case rm_HiddenLinesRemoved:
                currentAction = actionHiddenremoved;
                break;
            default:
                currentAction = actionDimmedWireframe;
                break;
        }
        pToolButton->setCurrentAction(actionDimmedWireframe);

        pToolButton->addAction(actionDimmedWireframe);
        pToolButton->addAction(actionShaded);
        pToolButton->addAction(actionWirefrmquad);
        pToolButton->addAction(actionWirefrm);
        pToolButton->addAction(actionHiddenremoved);
        pHeadToolbar->addWidget(pToolButton);
    }

    m_pAutoHideWindow->setToolBar(pHeadToolbar);
    return m_pAutoHideWindow;
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidget::viewPortCommands()
{
    QAction* pAction = qobject_cast<QAction*>(sender());
    Orientation value = static_cast<Orientation>(pAction->property("Orientation").toInt());
    int val = int(Orientation::CustomBase);
    if ((int)value == (val + 1))
        graphicsView()->ZoomToFit();
    else if ((int)value == (val + 2))
        viewport()->SetOrthographicProjection(!pAction->isChecked());
    else
        graphicsView()->SetOrientationCamera(value, true);
    update();
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidget::viewPortRenderMode()
{
    QAction* pAction = qobject_cast<QAction*>(sender());
    RenderMode value = static_cast<RenderMode>(pAction->property("Mode").toInt());
    setRenderMode(value);
    update();
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidget::setRenderMode(RenderMode mode)
{
    graphicsView()->SetRenderMode(mode);
    update();
}

//-----------------------------------------------------------------------------
// Вернуть указатель на основной источник света
// ---
Light* QtOpenGLSceneWidget::mainLight() const
{ return m_pGraphicsView->GetGraphicsScene()->GetMainLight(); }

//-----------------------------------------------------------------------------
//
// ---
Camera* QtOpenGLSceneWidget::camera() const
{ return viewport()->GetCamera(); }

//-----------------------------------------------------------------------------
// Вернуть указатель на Viewport для отображения сцены.
// ---
Viewport* QtOpenGLSceneWidget::viewport() const
{ return m_pGraphicsView->GetViewport().get(); }

//-----------------------------------------------------------------------------
// Вернуть указатель на содержимое сцены.
// ---
SceneContentPtr QtOpenGLSceneWidget::sceneContent()
{ return m_pGraphicsView->GetGraphicsScene()->GetSceneContent(); }

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidget::resizeGL(int w, int h)
{
    QOpenGLWidget::resizeGL(w, h);
    if (m_pQContext == nullptr)
        return;
    
    if (m_pQContext->MakeCurrent() && OpenGLContextInterface::GetCurrentContext() && 
        m_pQContext == OpenGLContextInterface::GetCurrentContext())
    {
        qreal pixelRatio = devicePixelRatio();
        m_pEventFilter->setDevicePixelRatio(pixelRatio);
        m_pGraphicsView->DoResize(w * pixelRatio, h * pixelRatio);
    }
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidget::paintGL()
{
    if (m_pQContext == nullptr || !updatesEnabled() || !isVisible())
        return;

    m_pEventFilter->setDevicePixelRatio(devicePixelRatio());

    if (m_pQContext->MakeCurrent())
        m_pGraphicsView->DoRender();

    m_pQContext->DoneCurrent(); // C3D-10302

#ifdef Q_OS_WIN
    if (RenderStatistics::IsActivated() || GlobalFlags::IsBatchingMode())
        update();
#endif
}

//-----------------------------------------------------------------------------
//
// ---
bool QtOpenGLSceneWidget::event(QEvent* event)
{
    if (event->type() == QEvent::WindowChangeInternal && 
        m_bInitialized && !qGuiApp->testAttribute(Qt::AA_ShareOpenGLContexts))
        reset();

    bool ok = QOpenGLWidget::event(event);

    switch (event->type())
    {
        case QEvent::UpdateRequest:
            if (m_bUpdatePending)
            {
                update();
                m_bUpdatePending = false;
                return true;
            }
            break;
        case QEvent::WindowChangeInternal:
            if (qGuiApp->testAttribute(Qt::AA_ShareOpenGLContexts))
                break;
            if (m_bInitialized)
                reset();
            // FALLTHROUGH
        case QEvent::Show: // reparenting may not lead to a resize so reinitalize on Show too
            if (!m_bInitialized && !size().isEmpty() && window() && window()->windowHandle())
                initialize();
            break;
        default:
            break;
    }
    return ok;
}

//-----------------------------------------------------------------------------
//
// ---
#if (QT_VERSION <= QT_VERSION_CHECK(6, 0, 0))
void QtOpenGLSceneWidget::enterEvent(QEvent* event)
#else
void QtOpenGLSceneWidget::enterEvent(QEnterEvent* event)
#endif
{
    QOpenGLWidget::enterEvent(event);
    m_pGraphicsView->GetSceneEngine()->GetObjectPickSelection()->SetOpenGLContext(m_pQContext);
    m_pGraphicsView->GetSceneEngine()->GetObjectPickSelection()->SetViewport(m_pGraphicsView->GetViewport());
    processActivation();
}

//-----------------------------------------------------------------------------
//
// ---
 void QtOpenGLSceneWidget::leaveEvent(QEvent* event)
{
     QOpenGLWidget::leaveEvent(event);
    processDeactivation();
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidget::focusInEvent(QFocusEvent* event)
{
    QOpenGLWidget::focusInEvent(event);
    processActivation();
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidget::focusOutEvent(QFocusEvent* event)
{
    QOpenGLWidget::focusOutEvent(event);
    processDeactivation();
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidget::showEvent(QShowEvent* event)
{
    VSN_UNUSED(event);
    if (!m_bInitialized)
        return;
    m_pGraphicsView->PreparingToDisplay();
    renderLater();
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidget::closeEvent(QCloseEvent* event) { QOpenGLWidget::closeEvent(event); }

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidget::ZoomToFit()
{
    if ( viewport() && sceneContent() )
        viewport()->ZoomToFit(sceneContent()->GetBoundingBox());
}

//-----------------------------------------------------------------------------
//
// ---
bool QtOpenGLSceneWidget::OnEvent(ProcessEvent* event)
{
    if (event->GetType() == ProcessEvent::Draw)
        repaint();
    return Object::OnEvent(event);
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidget::initialize()
{
    if (m_bInitialized)
        return;

    qApp->setWindowIcon(QIcon(":/res/crystal.ico"));
    makeCurrent();
    m_pQContext = new QtOpenGLContextShell(this, m_pSharedContainer);
    m_pQContext->MakeCurrent();
    const auto initStatus = m_pQContext->Initialize();
    if (initStatus != OpenGLContextInterface::InitStatus::Ok)
    {
        reportContextStatus(initStatus);
        std::exit(EXIT_FAILURE);
    }

    if (QtVision::visionTheme())
    {
        QColor clr = QtVision::visionTheme()->palette().color(QPalette::Dark);
        Color clrBackground(clr.red(), clr.green(), clr.blue());
        viewport()->SetGradientBackgroundColour(clrBackground.GetLighter(120), clrBackground.GetLighter(240));
    }
    else
        viewport()->SetGradientBackgroundColour(QtVision::topColor, QtVision::bottomColor);

    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);
    setAttribute(Qt::WA_Hover, true);
    m_pGraphicsView->Initialize();
    m_pEventFilter = new QtConverterEventListener(this, m_pGraphicsView->GetGraphicsScene());
    Object::Connect(m_pGraphicsView.get(), &GraphicsView::OnViewModified, this, &QtOpenGLSceneWidget::repaintWidget);
    Object::Connect(m_pGraphicsView->GetViewport().get(), &Viewport::RefreshScreen, this, &QtOpenGLSceneWidget::updateWidget);
    m_bInitialized = true;
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidget::reset()
{
    VSN_DELETE_AND_NULL(m_pQContext);
    m_bInitialized = false;
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidget::renderLater()
{
    if (!m_bUpdatePending)
    {
        m_bUpdatePending = true;
        QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
    }
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidget::processActivation()
{
    if (Essence* pEssence = m_pGraphicsView->GetSceneEngine()->GetTopEssence())
    {
        auto list = pEssence->FindChildren<Process*>();
        for (const auto& it : list)
        {
            it->SetViewport(m_pGraphicsView->GetViewport().get());
            bool bConnect = Object::Connect(it, &Process::OnModified, this, &QtOpenGLSceneWidget::updateWidget);
            if (PrAbstractCamera* pAbsProcess = vobject_cast<PrAbstractCamera*>(it))
            {
                bConnect =
                    Object::Connect(pAbsProcess, &PrAbstractCamera::OnCameraModified, this, &QtOpenGLSceneWidget::updateWidget);
                Q_ASSERT(bConnect != false);
                VSN_UNUSED(bConnect);
            }
        }
    }
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWidget::processDeactivation()
{
    if (Essence* pEssence = m_pGraphicsView->GetSceneEngine()->GetTopEssence())
    {
        auto list = pEssence->FindChildren<Process*>();
        for (const auto& it : list)
        {
            it->SetViewport(m_pGraphicsView->GetViewport().get());
            Object::Disconnect(it, &Process::OnModified, this, &QtOpenGLSceneWidget::updateWidget);

            if (PrAbstractCamera* pAbsProcess = vobject_cast<PrAbstractCamera*>(it))
                Object::Disconnect(pAbsProcess, &PrAbstractCamera::OnCameraModified, this, &QtOpenGLSceneWidget::updateWidget);
        }
    }
}

//-----------------------------------------------------------------------------
// Creating processes to control the camera.
// ---
QT_FUNC(void) createProcessesCameraControls(GraphicsSceneEnginePtr ptrEngine, ProcessTypes prType, SceneSegment* pParent)
{
    Q_ASSERT(ptrEngine != nullptr);
    GraphicsScene* pGraphicsScene = ptrEngine->GetGraphicsScene();
    Q_ASSERT(pGraphicsScene != nullptr);
    Essence* pEssence = pParent == nullptr ? ptrEngine->GetTopEssence() : pParent;
    Q_ASSERT(pEssence != nullptr);

    // Create and add process Orbit
    if (prType.CheckFlag(pt_Orbit))
    {
        PrCameraOrbit* pProcess = new PrCameraOrbit(pGraphicsScene, pEssence);
        pProcess->SetMouseButtonsActivate({ VSN::mb_RButton });
    }
    // Create and add process Rotate
    if (prType.CheckFlag(pt_Rotate))
    {
        PrCameraRotate* pProcess = new PrCameraRotate(pGraphicsScene, pEssence);
        pProcess->SetMouseButtonsActivate({ VSN::mb_RButton });
    }
    // Create and add process Rotate
    if (prType.CheckFlag(pt_ComplexRotation))
    {
        PrCameraComplexRotation* pProcess = new PrCameraComplexRotation(pGraphicsScene, pEssence);
        pProcess->SetMouseButtonsActivate({ VSN::mb_RButton });
    }
    // Create and add process Pan
    if (prType.CheckFlag(pt_Pan))
    {
        PrCameraPan* pProcess = new PrCameraPan(pGraphicsScene, pEssence);
        pProcess->SetMouseButtonsActivate({ VSN::mb_MButton });
    }
    // Create and add process Zoom
    if (prType.CheckFlag(pt_Zoom))
    {
        PrCameraZoomWheel* pProcess = new PrCameraZoomWheel(pGraphicsScene, pEssence);
        VSN_UNUSED(pProcess);
    }
}

namespace {
//-----------------------------------------------------------------------------
// Setting the format for QSurface.
// ---
void setSurfaceFormat()
{
    QSurfaceFormat format;

    format.setDepthBufferSize(24);
    format.setSamples(4);
    format.setStencilBufferSize(8);
    format.setSwapInterval(0);
    const OpenGLVersion requiredOpenGL = OpenGLContextInterface::GetRequiredOpenGLVersion();
    format.setProfile(requiredOpenGL.GetProfile() == OpenGLProfile::Compatibility ? QSurfaceFormat::CompatibilityProfile
                                                                                  : QSurfaceFormat::CoreProfile);

    if (GlobalFlags::GetCoreContext())
    {
        format.setOptions(QSurfaceFormat::DeprecatedFunctions);
    }

    if (OpenGLContextInterface::ShouldCreateDebugContext())
        format.setOptions(format.options() | QSurfaceFormat::DebugContext);

    QSurfaceFormat::setDefaultFormat(format);
}
} // namespace

/* SurfaceFormat */
struct SurfaceFormat {SurfaceFormat() { setSurfaceFormat(); }};
static SurfaceFormat format;

//-----------------------------------------------------------------------------
// License check
// ---
QT_FUNC(bool) activateLicense()
{
    VSN_ASSERT_X(QApplication::instance() != nullptr, "QtVision::activateLicense()", "QtVision::activateLicense() should be called after QApplication created!");

    if (!IsMathVisionEnable())
    {
        QtVision::LicenseWnd licenseWnd;
        return licenseWnd.Activate();
    }

    return true;
}

/// \ru Позиционирование главного окна. \en Positioning the main window.
QT_FUNC(void) setWindowPosition(QWidget& widget)
{
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
    const QRect availableGeometry = widget.screen()->availableGeometry();
#else
    const QRect availableGeometry = QApplication::desktop()->availableGeometry();
#endif
    widget.resize(QSize(2 * availableGeometry.width() / 3, 2 * availableGeometry.height() / 3));
    widget.move(QPoint((availableGeometry.width() - widget.width()) / 2, (availableGeometry.height() - widget.height()) / 2));
}

const QString strFilters   = QObject::tr("Files *.c3d *.sat *.obj *.step *.stp *.x_b *.x_t *.jt *.JT *.igs");
const QString strFileC3D   = QObject::tr("File C3D (*.c3d)");
const QString strFileOBJ   = QObject::tr("File OBJ (*.obj)");
const QString strFileACISC = QObject::tr("File ACISC (*.sat)");
const QString strFileSTEP  = QObject::tr("File STEP (*.step)");
const QString strFileStp   = QObject::tr("File STEP (*.stp)");
const QString strFilePARASOLID = QObject::tr("File PARASOLID (*.x_b *.x_t)");
const QString strFileJT    = QObject::tr("File JT (*.jt *.JT)");
const QString strFileStl   = QObject::tr("File stl (*.stl *.STL)");
const QString strFileIgs   = QObject::tr("File stl (*.igs)");
#ifdef _USE_PLUGINS_
const QString strFileNX    = QObject::tr("File NX (*.prt *.PRT)");
const QString strFileSW    = QObject::tr("File SolidWorks (*.sldprt *.SLDPRT)");
const QString strFileIFC   = QObject::tr("File IFC (*.ifc *.IFC)");
const QString strFileCATIA = QObject::tr("File CATIA (*.CATPart *.CATPart)");
#endif

QT_FUNC(QStringList) processFilters()
{
    QStringList filters;
    filters.append(strFilters);
    filters.append(strFileC3D);
    filters.append(strFileOBJ);
    filters.append(strFileACISC);
    filters.append(strFileSTEP);
    filters.append(strFileStp);
    filters.append(strFilePARASOLID);
    filters.append(strFileJT);
    filters.append(strFileStl);
    filters.append(strFileIgs);
#ifdef _USE_PLUGINS_
    filters.append(strFileNX);
    filters.append(strFileSW);
    filters.append(strFileIFC);
    filters.append(strFileCATIA);
#endif
    return filters;
}

} // namespace QtVision
} // namespace VSN
