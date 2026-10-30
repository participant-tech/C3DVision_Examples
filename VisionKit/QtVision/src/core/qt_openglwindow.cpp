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

#include <qt_openglwindow.h>
#include <qt_eventlistener.h>
#include <QtCore/QDebug>
#include <QtGui/QOpenGLContext>
#include <vsn_last.h>

namespace VSN {
namespace QtVision {

extern void reportContextStatus(OpenGLContextInterface::InitStatus status);

#define FPS 0

/* RenderAreaSelector */
class RenderAreaSelector : public AbsVisionComponent
{
public:
    RenderAreaSelector(QtOpenGLWindow* glWindow, Object* pParent = nullptr)
        : AbsVisionComponent(pParent)
        , m_glWindow(glWindow)
    {
    }

    void FrameMade() override
    { 
#if FPS > 0
        const int elapsed = m_time.elapsed();
        if (elapsed >= 100)
            m_fps = m_frames / (elapsed / 1000.0);
#endif

        bool swapBuffers = m_glWindow->m_pContext->MakeCurrent();
        if (!swapBuffers)
            return;
        m_glWindow->paintGL(); // call user code

        m_glWindow->m_pContext->SwapBuffers();
        m_glWindow->m_pContext->DoneCurrent();
#if FPS > 0
        if (!(m_frames % 100))
        {
            if (const int elapsed = m_time.elapsed())
                m_fps = m_frames / (elapsed / 1000.0);

            m_time.start();
            m_frames = 0;
        }
        ++m_frames;
        qWarning("FPS: %d", qRound(m_fps));
#endif
//        m_glWindow->requestUpdate();
    }
protected:
    QtOpenGLWindow* m_glWindow;
};


/* QtOpenGLWindow */
QtOpenGLWindow::QtOpenGLWindow(QWindow* parent) 
    : QWindow(parent)
    , m_pContext(nullptr)
    , m_debugLogger(nullptr)
{
    setSurfaceType(QWindow::OpenGLSurface);
    resize(1024, 768);
}

//-----------------------------------------------------------------------------
//
// ---
QtOpenGLWindow::~QtOpenGLWindow()
{
    VSN_DELETE_AND_NULL(m_pContext);
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLWindow::makeCurrent()
{
    if (m_pContext != nullptr)
        m_pContext->MakeCurrent();
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLWindow::renderLater()
{
    // Schedule an UpdateRequest event in the event loop
    // that will be send with the next VSync.
    requestUpdate(); // call public slot requestUpdate()
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLWindow::renderNow()
{
    // initialize on first call
    if (m_pContext == nullptr)
        initOpenGL();
    if (m_pContext->MakeCurrent())
        paintGL(); // call user code
    
    m_pContext->SwapBuffers();
    m_pContext->DoneCurrent();
}

//-----------------------------------------------------------------------------
//
// ---
bool QtOpenGLWindow::event(QEvent* event)
{
    
    const bool needsRedraw = (event->type() == QEvent::UpdateRequest);
    if (needsRedraw)
        renderNow();
    return QWindow::event(event);
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLWindow::exposeEvent(QExposeEvent* /*event*/)
{
    renderNow(); // update right now
    // Note: if were just to request an update on next sync, i.e. by
    //       calling renderLater() (or requestUpdate()) we get
    //       white glitches when enlarging the window. Since we don't want that,
    //       we simply render right away so that the new window size
    //       is already reflected by the adjusted viewport we render into.
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLWindow::resizeEvent(QResizeEvent* event)
{
    QWindow::resizeEvent(event);

    // initialize on first call
    if (m_pContext == nullptr)
        initOpenGL();

    resizeGL(width(), height());
    renderLater();
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLWindow::showEvent(QShowEvent* event)
{
    // initialize on first call
    if (m_pContext == nullptr)
        initOpenGL();
    QWindow::showEvent(event);
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLWindow::onMessageLogged(const QOpenGLDebugMessage& msg)
{
    QString prefix;
    // Format based on severity
    switch (msg.severity()) 
    {
        case QOpenGLDebugMessage::NotificationSeverity:
            prefix += "++++";
        break;
        case QOpenGLDebugMessage::HighSeverity:
            prefix += "+++";
        break;
        case QOpenGLDebugMessage::MediumSeverity:
            prefix += "++";
        break;
        case QOpenGLDebugMessage::LowSeverity:
            prefix += "+";
        break;
        case QOpenGLDebugMessage::InvalidSeverity:
            prefix += "+?+";
        break;
        case QOpenGLDebugMessage::AnySeverity: // no prefix
        break;
    }
    prefix += " [";
    // Format based on source
#define CASE(c) case QOpenGLDebugMessage::c: prefix += #c; break
    switch (msg.source())
    {
        CASE(APISource);
        CASE(WindowSystemSource);
        CASE(ShaderCompilerSource);
        CASE(ThirdPartySource);
        CASE(ApplicationSource);
        CASE(OtherSource);
        CASE(InvalidSource);
        CASE(AnySource);
    }
 #undef CASE
    prefix += ":";
    // Format based on type
 #define CASE(c) case QOpenGLDebugMessage::c: prefix += #c; break
    switch (msg.type())
    {
        CASE(ErrorType);
        CASE(DeprecatedBehaviorType);
        CASE(UndefinedBehaviorType);
        CASE(PortabilityType);
        CASE(PerformanceType);
        CASE(OtherType);
        CASE(MarkerType);
        CASE(GroupPushType);
        CASE(GroupPopType);
        CASE(InvalidType);
        CASE(AnyType);
    }
#undef CASE
    prefix += "] ";
    qDebug().noquote().nospace() << prefix << msg.message() << "\n";
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLWindow::initOpenGL()
{
    Q_ASSERT(m_pContext == nullptr);
    RenderingAreaFormat areaFormat;
    m_pContext = new QtOpenGLContext(this, areaFormat);

    QSurfaceFormat format = QSurfaceFormat::defaultFormat();
    format.setDepthBufferSize(24);
    format.setSamples(4);
    format.setStencilBufferSize(8);
    format.setSwapInterval(0);
    setFormat(format);
    QSurfaceFormat::setDefaultFormat(format);

    m_pContext->create();
    if (!m_pContext->MakeCurrent())
    {
        Q_ASSERT(false);
    }
    Q_ASSERT(m_pContext->isValid());
    const auto initStatus = m_pContext->Initialize();
    if (initStatus != OpenGLContextInterface::InitStatus::Ok)
    {
        reportContextStatus(initStatus);
        std::exit(EXIT_FAILURE);
    }
#ifdef GL_DEBUG
    if (m_pContext->hasExtension(QByteArrayLiteral("GL_KHR_debug")))
        qDebug() << "GL_KHR_debug extension available";
    else
        qWarning() << "GL_KHR_debug extension *not* available";
    m_debugLogger = new QOpenGLDebugLogger(this);
    if (m_debugLogger->initialize()) {
        qDebug() << "Debug Logger initialized\n";
        connect(m_debugLogger, SIGNAL(messageLogged(QOpenGLDebugMessage)), this, SLOT(onMessageLogged(QOpenGLDebugMessage)));
        m_debugLogger->startLogging();
    }
    qDebug() << "DepthBufferSize = " << m_pContext->format().depthBufferSize();
#endif // GL_DEBUG
    initializeGL(); // call user code
}

/* QtOpenGLSceneWindow */
QtOpenGLSceneWindow::QtOpenGLSceneWindow(QWindow* parent)
    : QtOpenGLWindow(parent)
    , m_bInitialized(false)
    , m_pEventFilter(nullptr)
    , m_pGraphicsView(std::make_shared<GraphicsView>(std::make_shared<GraphicsSceneEngine>()))
{
}

//-----------------------------------------------------------------------------
//
// ---
QtOpenGLSceneWindow::~QtOpenGLSceneWindow()
{
    m_pContext->MakeCurrent();
    m_pGraphicsView->PreparingToDestroy();
    m_pGraphicsView.reset();
    m_pContext->DoneCurrent();
    VSN_DELETE_AND_NULL(m_pEventFilter);
}

// Вернуть указатель на источник освещения сцены
Light* QtOpenGLSceneWindow::mainLight() const
{ return m_pGraphicsView->GetGraphicsScene()->GetMainLight(); }
// Вернуть указатель на камеру
Camera* QtOpenGLSceneWindow::camera() const
{ return viewport()->GetCamera(); }
// Вернуть указатель на Viewport для отображения сцены
Viewport* QtOpenGLSceneWindow::viewport() const
{ return m_pGraphicsView->GetViewport().get(); }
// Вернуть указатель на содержимое сцены
SceneContentPtr QtOpenGLSceneWindow::sceneContent()
{ return m_pGraphicsView->GetGraphicsScene()->GetSceneContent(); }
// Вернуть указатель на графическую сцену
GraphicsScene* QtOpenGLSceneWindow::graphicsScene() const
{ return m_pGraphicsView->GetGraphicsScene(); }
// Вернуть указатель на компонент выбора объектов
ObjectPickSelection* QtOpenGLSceneWindow::objectPickSelection() const
{ return m_pGraphicsView->GetSceneEngine()->GetObjectPickSelection(); }
// Вернуть указатель на GraphicsSceneEngine
GraphicsSceneEnginePtr QtOpenGLSceneWindow::graphicsEngine() const
{ return m_pGraphicsView->GetSceneEngine(); }
// Вернуть указатель на GraphicsView
GraphicsViewPtr QtOpenGLSceneWindow::ptrGraphicsView() const
{ return m_pGraphicsView; }
// Вернуть указатель на GraphicsView
GraphicsView* QtOpenGLSceneWindow::graphicsView() const
{ return m_pGraphicsView.get(); }

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWindow::initializeGL()
{
    m_pGraphicsView->Initialize();

//    VisionEnginePtr enginePtr = m_pGraphicsView->GetSceneEngine()->GetVisionEngine();
//    enginePtr->ComponentInstallation(new RenderAreaSelector(this));

    m_pEventFilter = new QtConverterEventListener(this, m_pGraphicsView->GetGraphicsScene());
    Object::Connect(m_pGraphicsView.get(), &GraphicsView::OnViewModified, 
        this, &QtOpenGLWindow::renderLater);
    Object::Connect(m_pGraphicsView->GetViewport().get(), &Viewport::RefreshScreen, 
        this, &QtOpenGLWindow::renderLater);
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWindow::paintGL()
{
    if (m_pContext == nullptr)
        return;
    if (RenderStatistics::IsActivated())
        RenderStatistics::ResetRenderCounters();
//    m_pEventFilter->setDevicePixelRatio(devicePixelRatio());
    m_pGraphicsView->DoRender();
}

void QtOpenGLSceneWindow::mouseMoveEvent(QMouseEvent* event)
{
    QtOpenGLWindow::mouseMoveEvent(event);
    processActivation();
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWindow::focusInEvent(QFocusEvent* event)
{
    QtOpenGLWindow::focusInEvent(event);
    processActivation();
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWindow::focusOutEvent(QFocusEvent* event)
{
    QtOpenGLWindow::focusOutEvent(event);
    processDeactivation();
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWindow::resizeGL(int width, int height)
{
    if (m_pContext == nullptr)
        return;
    
    if (m_pContext->MakeCurrent() && OpenGLContextInterface::GetCurrentContext() && 
        m_pContext == OpenGLContextInterface::GetCurrentContext())
    {
        m_pEventFilter->setDevicePixelRatio(devicePixelRatio());
        m_pGraphicsView->DoResize(width * devicePixelRatio(), height * devicePixelRatio());
    }
    m_pContext->DoneCurrent();
/*
    if (m_pAboutScene != nullptr)
    {
        const int margin = 10;
        QRect rc = rect();
        QSize sz = m_pAboutScene->sizeHint();
        rc.setTopLeft(QPoint(rc.right() - sz.width() - margin, margin));
        d.m_pAboutScene->setPosition(rc.topLeft());
    }
*/
}

//-----------------------------------------------------------------------------
//
// ---
bool QtOpenGLSceneWindow::event(QEvent* event)
{
    return QtOpenGLWindow::event(event);
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWindow::showEvent(QShowEvent* event)
{
    if (m_bInitialized)
        return;
    QtOpenGLWindow::showEvent(event);
    m_pGraphicsView->PreparingToDisplay();
    m_bInitialized = true;
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWindow::processActivation()
{
    if (Essence* pEssence = m_pGraphicsView->GetSceneEngine()->GetTopEssence())
    {
        auto list = pEssence->FindChildren<Process*>();
        for (const auto& it : list)
        {
            it->SetViewport(m_pGraphicsView->GetViewport().get());
            bool bConnect = Object::Connect(it, &Process::OnModified, this, &QtOpenGLWindow::renderLater);
            Q_ASSERT(bConnect != false);
            if (PrAbstractCamera* pAbsProcess = vobject_cast<PrAbstractCamera*>(it))
            {
                bConnect = Object::Connect(pAbsProcess, &PrAbstractCamera::OnCameraModified, this, &QtOpenGLWindow::renderLater);
                Q_ASSERT(bConnect != false);
                VSN_UNUSED(bConnect);
            }

        }
    }
}

//-----------------------------------------------------------------------------
//
// ---
void QtOpenGLSceneWindow::processDeactivation()
{
    if (Essence* pEssence = m_pGraphicsView->GetSceneEngine()->GetTopEssence())
    {
        auto list = pEssence->FindChildren<Process*>();
        for (const auto& it : list)
        {
            it->SetViewport(m_pGraphicsView->GetViewport().get());
            Object::Disconnect(it, &Process::OnModified, this, &QtOpenGLWindow::renderLater);

            if (PrAbstractCamera* pAbsProcess = vobject_cast<PrAbstractCamera*>(it))
                Object::Disconnect(pAbsProcess, &PrAbstractCamera::OnCameraModified, this, &QtOpenGLWindow::renderLater);
        }
    }
}

} // namespace QtVision

} // namespace VSN
