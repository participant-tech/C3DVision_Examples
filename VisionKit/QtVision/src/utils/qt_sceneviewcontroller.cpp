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

#include <qt_sceneviewcontroller.h>
#include <qt_orientationbar.h>
#include <qt_mainwindow.h>
#include <qt_processmanager.h>
#include <qt_icore.h>

#include <vsn_last.h>

namespace VSN {
namespace QtVision {

#define PROP_ORIENTATION "Orientation"
#define PROP_MODE        "Mode"

/* SceneViewController */
SceneViewController::SceneViewController(QObject* parent)
    : QObject(parent)
    , m_sceneWidget(nullptr)
    , m_autoHideWindow(nullptr)
    , m_actionZoomBox(nullptr)
{
}

// ---------------------------------------------------------------------------------------
// Create a toolbar in each viewport that contains all 
// the common tools needed to control the view.
// ---
void SceneViewController::createHeadsUpViewToolbar(bool createMode) {
    auto createParam = HeadsUpToolTypes(HeadsUpToolType::ZoomToFit) | HeadsUpToolType::ZoomToBox | HeadsUpToolType::Orientation |
                       HeadsUpToolType::Isometry | HeadsUpToolType::Perspective;
    if (createMode)
        createParam |= HeadsUpToolType::RenderMode;
    createHeadsUpViewToolbar(createParam);
}

void SceneViewController::createHeadsUpViewToolbar(HeadsUpToolTypes types)
{
    if (m_autoHideWindow != nullptr)
        return;
    if (m_sceneWidget == nullptr)
    {
        VSN_ASSERT_X(m_sceneWidget != nullptr, "SceneViewController",
            "createHeadsUpViewToolbar() should be called after m_sceneWidget has been initialized!");
        return;
    }
    if (types == 0)
        return;

    m_autoHideWindow = new QtAutoHideWindow(m_sceneWidget);
    QToolBar* pHeadToolbar = new QToolBar(m_sceneWidget);

    bool beforeButton = false;

    if (types.testFlag(HeadsUpToolType::ZoomToFit))
    {
        QAction* actionZoomFit = new QAction(QIcon(":/res/zoomfit_48.png"), QObject::tr("Zoom Fit"), this);
        actionZoomFit->setProperty(PROP_ORIENTATION, QVariant((int)Orientation::CustomBase + 1));
        actionZoomFit->setShortcut(QKeySequence(Qt::Key_F9));
        pHeadToolbar->addAction(actionZoomFit);
        QObject::connect(actionZoomFit, SIGNAL(triggered()), this, SLOT(viewPortCommands()));
        beforeButton = true;
    }

    if (types.testFlag(HeadsUpToolType::ZoomToBox))
    {
        m_actionZoomBox = new QAction(QIcon(":/res/zoomframe_48.png"), QObject::tr("Enlarge view element"), this);
        m_actionZoomBox->setProperty(PROP_ORIENTATION, QVariant((int)Orientation::CustomBase + 3));
        m_actionZoomBox->setCheckable(true);
        pHeadToolbar->addAction(m_actionZoomBox);
        QObject::connect(ICore::processContainer()->get(m_sceneWidget), SIGNAL(suspendProcessChanged()), this,
            SLOT(updateActions()));
        QObject::connect(m_actionZoomBox, SIGNAL(triggered()), this, SLOT(viewPortCommands()));
        beforeButton = true;
    }

    if (types.testFlag(HeadsUpToolType::Orientation))
    {
        QAction* actionViewFront = new QAction(QIcon(":/res/view_front_48.png"), QObject::tr("Front"), this);
        actionViewFront->setProperty(PROP_ORIENTATION, QVariant((int)Orientation::Front));
        actionViewFront->setStatusTip(QObject::tr("Rotate and enlarge the model in front viewing orientation"));
        QObject::connect(actionViewFront, SIGNAL(triggered()), this, SLOT(viewPortCommands()));

        QAction* actionViewBack = new QAction(QIcon(":/res/view_back_48.png"), QObject::tr("Back"), this);
        actionViewBack->setProperty(PROP_ORIENTATION, QVariant((int)Orientation::Rear));
        actionViewBack->setStatusTip(QObject::tr("Rotate and enlarge the model in back viewing orientation"));
        QObject::connect(actionViewBack, SIGNAL(triggered()), this, SLOT(viewPortCommands()));

        QAction* actionViewTop = new QAction(QIcon(":/res/view_top_48.png"), QObject::tr("Top"), this);
        actionViewTop->setProperty(PROP_ORIENTATION, QVariant((int)Orientation::Up));
        actionViewTop->setStatusTip(QObject::tr("Rotate and enlarge the model in top viewing orientation"));
        QObject::connect(actionViewTop, SIGNAL(triggered()), this, SLOT(viewPortCommands()));

        QAction* actionViewBottom = new QAction(QIcon(":/res/view_bottom_48.png"), QObject::tr("Bottom"), this);
        actionViewBottom->setProperty(PROP_ORIENTATION, QVariant((int)Orientation::Down));
        actionViewBottom->setStatusTip(QObject::tr("Rotate and enlarge the model in bottom viewing orientation"));
        QObject::connect(actionViewBottom, SIGNAL(triggered()), this, SLOT(viewPortCommands()));

        QAction* actionViewLeft = new QAction(QIcon(":/res/view_left_48.png"), QObject::tr("Left"), this);
        actionViewLeft->setProperty(PROP_ORIENTATION, QVariant((int)Orientation::Left));
        actionViewLeft->setStatusTip(QObject::tr("Rotate and enlarge the model in left viewing orientation"));
        QObject::connect(actionViewLeft, SIGNAL(triggered()), this, SLOT(viewPortCommands()));

        QAction* actionViewRight = new QAction(QIcon(":/res/view_right_48.png"), QObject::tr("Right"), this);
        actionViewRight->setProperty(PROP_ORIENTATION, QVariant((int)Orientation::Right));
        actionViewLeft->setStatusTip(QObject::tr("Rotate and enlarge the model in right viewing orientation"));
        QObject::connect(actionViewRight, SIGNAL(triggered()), this, SLOT(viewPortCommands()));

        QtOrientationToolButton* orientationButton = new QtOrientationToolButton();
        orientationButton->setIcon(QIcon(":/res/view_orientation_48.png"));
    
        orientationButton->addActionToWidget(0, 1, actionViewTop);
        orientationButton->addActionToWidget(2, 1, actionViewBottom);
        orientationButton->addActionToWidget(1, 0, actionViewLeft);
        orientationButton->addActionToWidget(1, 1, actionViewFront);
        orientationButton->addActionToWidget(1, 2, actionViewRight);
        orientationButton->addActionToWidget(1, 3, actionViewBack);
        pHeadToolbar->addWidget(orientationButton);
        beforeButton = true;
    }

    // изометрия
    if (types.testFlag(HeadsUpToolType::Orientation))
    {
        QAction* actionIsoZXY = new QAction(QIcon(":/res/view_iso_x.png"), QObject::tr("ZXY"), this);
        actionIsoZXY->setProperty(PROP_ORIENTATION, QVariant((int)Orientation::IsoZXY));
        QObject::connect(actionIsoZXY, SIGNAL(triggered()), this, SLOT(viewPortCommands()));

        QAction* actionIsoXYZ = new QAction(QIcon(":/res/view_iso_y.png"), QObject::tr("XYZ"), this);
        actionIsoXYZ->setProperty(PROP_ORIENTATION, QVariant((int)Orientation::IsoXYZ));
        QObject::connect(actionIsoXYZ, SIGNAL(triggered()), this, SLOT(viewPortCommands()));

        QAction* actionIsoYZX = new QAction(QIcon(":/res/view_iso_z.png"), QObject::tr("YZX"), this);
        actionIsoYZX->setProperty(PROP_ORIENTATION, QVariant((int)Orientation::IsoYZX));
        QObject::connect(actionIsoYZX, SIGNAL(triggered()), this, SLOT(viewPortCommands()));

        QAction* actionIsoZXYX90 = new QAction(QIcon(":/res/view_iso_x_iso.png"), QObject::tr("ZXY RotatedX90"), this);
        actionIsoZXYX90->setProperty(PROP_ORIENTATION, QVariant((int)Orientation::IsoZXYRotatedX90));
        QObject::connect(actionIsoZXYX90, SIGNAL(triggered()), this, SLOT(viewPortCommands()));

        QAction* actionIsoXYZY90 = new QAction(QIcon(":/res/view_iso_y_iso.png"), QObject::tr("XYZ RotatedY90"), this);
        actionIsoXYZY90->setProperty(PROP_ORIENTATION, QVariant((int)Orientation::IsoXYZRotatedY90));
        QObject::connect(actionIsoXYZY90, SIGNAL(triggered()), this, SLOT(viewPortCommands()));

        QAction* actionIsoYZXZ90 = new QAction(QIcon(":/res/view_iso_z_iso.png"), QObject::tr("YZX RotatedZ90"), this);
        actionIsoYZXZ90->setProperty(PROP_ORIENTATION, QVariant((int)Orientation::IsoYZXRotatedZ90));
        QObject::connect(actionIsoYZXZ90, SIGNAL(triggered()), this, SLOT(viewPortCommands()));

        QtToolButton* tbIsometry = new QtToolButton();
        QAction* separatorIsometry = new QAction(tbIsometry);
        separatorIsometry->setSeparator(true);

        tbIsometry->addAction(actionIsoZXY);
        tbIsometry->addAction(actionIsoXYZ);
        tbIsometry->addAction(actionIsoYZX);
        tbIsometry->addAction(separatorIsometry);
        tbIsometry->addAction(actionIsoZXYX90);
        tbIsometry->addAction(actionIsoXYZY90);
        tbIsometry->addAction(actionIsoYZXZ90);

        tbIsometry->setCurrentAction(actionIsoXYZ);

        pHeadToolbar->addWidget(tbIsometry);
        beforeButton = true;
    }

    if (types.testFlag(HeadsUpToolType::Perspective))
    {
        if (beforeButton)
            pHeadToolbar->addSeparator();
        QAction* actionPerspective = new QAction(QIcon(":/res/perspectv_48.png"), QObject::tr("Perspective"), this);
        actionPerspective->setProperty(PROP_ORIENTATION, QVariant((int)Orientation::CustomBase + 2));
        actionPerspective->setCheckable(true);
        actionPerspective->setChecked(!m_sceneWidget->viewport()->IsOrthographicProjection());
        pHeadToolbar->addAction(actionPerspective);
        QObject::connect(actionPerspective, SIGNAL(triggered()), this, SLOT(viewPortCommands()));
        beforeButton = true;
    }

    if (types.testFlag(HeadsUpToolType::RenderMode))
    {
        if (beforeButton)
            pHeadToolbar->addSeparator();
        QAction* actionDimmedWireframe = new QAction(QIcon(":/res/dimmedWireframe.png"), QObject::tr("Dimmed wireframe"), this);
        actionDimmedWireframe->setProperty(PROP_MODE, QVariant((int)rm_ShadedWithEdges));
        QObject::connect(actionDimmedWireframe, SIGNAL(triggered()), this, SLOT(viewPortRenderMode()));

        QAction* actionShaded = new QAction(QIcon(":/res/shaded.png"), QObject::tr("Shaded"), this);
        actionShaded->setProperty(PROP_MODE, QVariant((int)rm_Shaded));
        QObject::connect(actionShaded, SIGNAL(triggered()), this, SLOT(viewPortRenderMode()));

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
        switch (m_sceneWidget->graphicsView()->GetRenderMode())
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
        beforeButton = true;
    }

    m_autoHideWindow->setToolBar(pHeadToolbar);
}

// ---
void SceneViewController::setSceneWidget(ModelView* sceneWidget)
{
    Q_ASSERT(sceneWidget != nullptr);
    m_sceneWidget = sceneWidget;
}

//-----------------------------------------------------------------------------
//
// ---
void SceneViewController::createCameraControlToolbar()
{
}

//-----------------------------------------------------------------------------
//
// ---
void SceneViewController::viewPortCommands()
{
    QAction* pAction = qobject_cast<QAction*>(sender());
    Orientation value = static_cast<Orientation>(pAction->property("Orientation").toInt());
    int val = int(Orientation::CustomBase);
    if ((int)value == (val + 1))
        m_sceneWidget->graphicsView()->ZoomToFit();
    else if ((int)value == (val + 2))
        m_sceneWidget->viewport()->SetOrthographicProjection(!pAction->isChecked());
    else if ((int)value == (val + 3))
    {
        if (ICore::processContainer()->get(m_sceneWidget)->isExistSuspendProcess(ProcessManager::pt_ZoomBox))
            ICore::processContainer()->get(m_sceneWidget)->removeSuspendProcess(ProcessManager::pt_ZoomBox);
        else
            ICore::processContainer()->get(m_sceneWidget)->createSuspendingProcesses(ProcessManager::pt_ZoomBox);
    }
    else
        m_sceneWidget->graphicsView()->SetOrientationCamera(value, true);
    // it is quite possible that the toolbar will take the focus 
    // from the child window,it is necessary to restore it
    ICore::mainWindow()->setFocus();
    m_sceneWidget->setFocus();
    // redraw the scene output window
    m_sceneWidget->update();
}

//-----------------------------------------------------------------------------
//
// ---
void SceneViewController::viewPortRenderMode()
{
    QAction* pAction = qobject_cast<QAction*>(sender());
    RenderMode value = static_cast<RenderMode>(pAction->property("Mode").toInt());
    m_sceneWidget->setRenderMode(value);
    // it is quite possible that the toolbar will take the focus
    // from the child window,it is necessary to restore it
    ICore::mainWindow()->setFocus();
    m_sceneWidget->setFocus();
    m_sceneWidget->update();
}

// ---
void SceneViewController::updateActions() 
{ 
    m_actionZoomBox->setChecked(ICore::processContainer()->get(m_sceneWidget)->isExistSuspendProcess(ProcessManager::pt_ZoomBox));
}

} // namespace QtVision
} // namespace VSN
