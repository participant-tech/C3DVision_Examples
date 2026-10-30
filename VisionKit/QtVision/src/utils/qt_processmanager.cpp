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

#include <qt_processmanager.h>
#include <qt_mainwindow.h>
#include <qt_modeleditor.h>
#include <qt_icore.h>

#include <qevent.h>

#include <vsn_prcamerazoombox.h>
#include <vsn_specialwidgets.h>

#include <vsn_last.h>

namespace VSN {
namespace QtVision {

/* ProcessManager */
ProcessManager::ProcessManager(QObject* parent)
    : QObject(parent)
    , m_sceneWidget(nullptr)
    , m_procCurrent(nullptr)
{
//    QtMainWindow* mainWindow = ICore::mainWindow();
//    mainWindow->installEventFilter(this);
    ICore::processContainer()->append(this);
}

// ---
ProcessManager::~ProcessManager() 
{
    if (ICore::processContainer())
        ICore::processContainer()->remove(this);
//    QtMainWindow* mainWindow = ICore::mainWindow();
//    mainWindow->removeEventFilter(this);
}

// ---
void ProcessManager::setSceneWidget(ModelView* sceneWidget)
{
    Q_ASSERT(sceneWidget != nullptr);
    m_sceneWidget = sceneWidget;
    m_sceneWidget->installEventFilter(this);
}

// ---
void ProcessManager::appendBackgroundProcess(uint idProc, Process* proc)
{
    Q_ASSERT(idProc > 0);
    Q_ASSERT(m_mapBackgroundProcess.find(idProc) == m_mapBackgroundProcess.cend());
    if (PrAbstractCamera* procCamera = vobject_cast<PrAbstractCamera*>(proc))
    {
        if (checkForIdenticalHotkeys(procCamera))
        {
            Q_ASSERT_X(false, "Error", "ProcessManager::appendBackgroundProcess: such hotkeys are already assigned to another process.");
            return;
        }
// TODO        if (idProc != pt_Zoom)
        {
            Object::Connect(procCamera, &PrAbstractCamera::signalActivated, this, &ProcessManager::backgroundProcessActivated);
            Object::Connect(procCamera, &PrAbstractCamera::signalDeactivated, this, &ProcessManager::backgroundProcessDeactivated);
        }
    }
    m_mapBackgroundProcess.insert({ idProc, proc });
}

// ---
void ProcessManager::removeBackgroundProcess(uint idProc)
{
    auto it = m_mapBackgroundProcess.find(idProc);
    if (it != m_mapBackgroundProcess.cend())
    {
        Process* process = it->second;
        m_mapBackgroundProcess.erase(it);
        delete process;
    }
}

Process* ProcessManager::getBackgroundProcess(uint idProc)
{
    if (auto it = m_mapBackgroundProcess.find(idProc); it != m_mapBackgroundProcess.end())
        return it->second;
    return nullptr;
}

//---------------------------------------------------------------------------------------
//
// ---
void ProcessManager::appendSuspendProcess(uint idProc, Process* proc)
{
    Q_ASSERT(idProc > 0);
    Q_ASSERT(m_mapSuspendingProcess.find(idProc) == m_mapSuspendingProcess.cend());
    if (PrAbstractCamera* procCamera = vobject_cast<PrAbstractCamera*>(proc))
    {
        if (checkForIdenticalHotkeys(procCamera))
        {
            Q_ASSERT_X(false, "Error", "ProcessManager::appendSuspendProcess: such hotkeys are already assigned to another process.");
            return;
        }
    }
    m_mapSuspendingProcess.insert({idProc, proc});
}

// ---
void ProcessManager::removeSuspendProcess(uint idProc)
{
    auto it = m_mapSuspendingProcess.find(idProc);
    if (it != m_mapSuspendingProcess.cend())
    {
        Process* process = it->second;
        m_mapSuspendingProcess.erase(it);
        delete process;

        m_procCurrent = nullptr;
        emit suspendProcessChanged();
    }
    enabledBackgroundProcesses(true);
}

//---------------------------------------------------------------------------------------
// stop background processes
// ---
void ProcessManager::enabledBackgroundProcesses(bool enabled)
{ 
// TODO:   for (auto& it : m_mapBackgroundProcess)
// TODO:       it.second->SetEnabled(enabled);

    if (ModelEditor* editor = m_sceneWidget->modelEditor())
    {
        if (SelectionManagerPtr ptrSelectionManager = editor->selectionManager())
        {
            ObjectList<PrBasicFindSelect*> lstProcs = ptrSelectionManager->GetObjectPickSelection()->GetFindProcesses();
            for (auto& it : lstProcs)
                it->SetEnabled(enabled);
        }
    }
}

// ---
void ProcessManager::clearProcess()
{
    for (auto& it : m_mapBackgroundProcess)
        delete it.second;
    m_mapBackgroundProcess.clear();
    m_procCurrent = nullptr;
}

//---------------------------------------------------------------------------------------
//
// ---
bool ProcessManager::isExistSuspendProcess(uint idProc) const
{ return m_mapSuspendingProcess.find(idProc) != m_mapSuspendingProcess.cend(); }

//---------------------------------------------------------------------------------------
// processes suspend other processes
// ---
void ProcessManager::createSuspendingProcesses(ProcessType prType)
{
    Q_ASSERT(m_sceneWidget != nullptr);
    GraphicsScene* pGraphicsScene = m_sceneWidget->graphicsScene();
    Q_ASSERT(pGraphicsScene != nullptr);
    Essence* pEssence = m_sceneWidget->graphicsEngine()->GetTopEssence();
    Q_ASSERT(pEssence != nullptr);

    // Create and add process ZoomBox
    if (prType == pt_ZoomBox)
    {
        GraphicsView* pGraphicsView = m_sceneWidget->graphicsView();
        PrCameraZoomBox* pProcess = new PrCameraZoomBox(pGraphicsView, pGraphicsScene, pEssence);
        m_procCurrent = pProcess;
        appendSuspendProcess(pt_ZoomBox, pProcess);
        emit suspendProcessChanged();
    }
    enabledBackgroundProcesses(false);
}

// ---
void ProcessManager::createProcessesCameraControls(ProcessTypes prType)
{
    Q_ASSERT(m_sceneWidget != nullptr);
    GraphicsScene* pGraphicsScene = m_sceneWidget->graphicsScene();
    Q_ASSERT(pGraphicsScene != nullptr);
    Essence* pEssence = m_sceneWidget->graphicsEngine()->GetTopEssence();
    Q_ASSERT(pEssence != nullptr);

    // Create and add process Orbit
    if (prType.testFlag(pt_Orbit))
    {
        PrCameraOrbit* pProcess = new PrCameraOrbit(pGraphicsScene, pEssence);
        pProcess->SetMouseButtonsActivate({ VSN::mb_RButton });
        appendBackgroundProcess(pt_Orbit, pProcess);
    }
    // Create and add process Rotate
    if (prType.testFlag(pt_Rotate))
    {
        PrCameraRotate* pProcess = new PrCameraRotate(pGraphicsScene, pEssence);
        pProcess->SetMouseButtonsActivate({ VSN::mb_RButton });
        appendBackgroundProcess(pt_Rotate, pProcess);
    }
    // Create and add process Rotate
    if (prType.testFlag(pt_ComplexRotation))
    {
        PrCameraComplexRotation* pProcess = new PrCameraComplexRotation(pGraphicsScene, pEssence);
        GravityPointWidget* pGravityPoint = pProcess->GetGravityPoint();
        pGravityPoint->SetStyle(GravityPointWidget::Style::SphereInTorus);
        pProcess->SetMouseButtonsActivate({ VSN::mb_RButton });
        pProcess->SetAlignedToScreenCenter(false);
        appendBackgroundProcess(pt_ComplexRotation, pProcess);
    }
    // Create and add process Pan
    if (prType.testFlag(pt_Pan))
    {
        PrCameraPan* pProcess = new PrCameraPan(pGraphicsScene, pEssence);
        pProcess->SetMouseButtonsActivate({ VSN::mb_MButton });
        appendBackgroundProcess(pt_Pan, pProcess);
    }
    // Create and add process Zoom
    if (prType.testFlag(pt_Zoom))
    {
        PrCameraZoomWheel* pProcess = new PrCameraZoomWheel(pGraphicsScene, pEssence);
        appendBackgroundProcess(pt_Zoom, pProcess);
    }
}

// ---
bool ProcessManager::eventFilter(QObject* watched, QEvent* event)
{ 
    if (watched != m_sceneWidget || m_procCurrent == nullptr)
        return QObject::eventFilter(watched, event);

    if (event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent* me = static_cast<QMouseEvent*>(event);
        if (me->button() == Qt::RightButton || me->button() == Qt::MiddleButton) 
        {
            for (auto& it : m_mapBackgroundProcess)
            {
                PrAbstractCamera* absCamera = vobject_cast<PrAbstractCamera*>(it.second);
                if (absCamera == nullptr)
                    continue;
                std::vector<int> lstKey = absCamera->GetMouseButtonsActivate();
                if (std::find(lstKey.cbegin(), lstKey.cend(), VSN::mb_RButton) != lstKey.cend() ||
                    std::find(lstKey.cbegin(), lstKey.cend(), VSN::mb_MButton) != lstKey.cend())
                {
                    removeCurrentSuspendProcess();
                    return false;
                }
            }
        }
    }

    if (event->type() == QEvent::KeyPress)
    {
        int key = static_cast<QKeyEvent*>(event)->key();
        switch (key)
        {
            case Qt::Key_Escape:
                return removeCurrentSuspendProcess();
            default:
                break;
        }
    }
    return QObject::eventFilter(watched, event);
}

// ----------------------------------------------------------------------------
// activating a specific background process
// ---
void ProcessManager::backgroundProcessActivated()
{
    PrAbstractCamera* procSender = vobject_cast<PrAbstractCamera*>(GetSender());
    Q_ASSERT(procSender != nullptr);
    // when a certain background process is activated, 
    // other background processes should be unavailable for 
    // the duration of its operation
    for (auto& it : m_mapBackgroundProcess)
    {
        if (PrAbstractCamera* procCamera = vobject_cast<PrAbstractCamera*>(it.second))
        {
            if (procSender != procCamera)
                procCamera->SetEnabled(false);
        }
    }
}

// ----------------------------------------------------------------------------
// deactivate a specific background process
// ---
void ProcessManager::backgroundProcessDeactivated()
{
    PrAbstractCamera* procSender = vobject_cast<PrAbstractCamera*>(GetSender());
    Q_ASSERT(procSender != nullptr);
    // restore background processes
    for (auto& it : m_mapBackgroundProcess)
    {
        if (PrAbstractCamera* procCamera = vobject_cast<PrAbstractCamera*>(it.second))
        {
            if (procSender != procCamera)
                procCamera->SetEnabled(true);
        }
    }
}

// ---
bool ProcessManager::removeCurrentSuspendProcess()
{
    if (m_procCurrent == nullptr)
        return false;
    for (auto& it : m_mapSuspendingProcess)
    {
        if (m_procCurrent == it.second)
        {
            removeSuspendProcess(it.first);
            m_procCurrent = nullptr;
            return true;
        }
    }
    return false;
}

// ---
bool ProcessManager::checkForIdenticalHotkeys(const PrAbstractCamera* proc)
{
    if (proc == nullptr)
        return false;
    for (auto& it : m_mapBackgroundProcess)
    {
        if (PrAbstractCamera* procCurrent = vobject_cast<PrAbstractCamera*>(it.second))
        {
            if (proc->GetMouseButtonsActivate() == procCurrent->GetMouseButtonsActivate())
                return true;
        }
    }
    return false;
}

/* PrManagerContainer */
ProcessManager* PrManagerContainer::get(ModelView* sceneWidget) const
{
    for (auto it : m_lstManagers)
    {
        if (it->sceneWidget() == sceneWidget)
            return it;
    }
    return nullptr;
}

// ---
void PrManagerContainer::append(ProcessManager* manager) { m_lstManagers.append(manager); }
void PrManagerContainer::remove(ProcessManager* manager) { m_lstManagers.removeOne(manager); }


} // namespace QtVision
} // namespace VSN
