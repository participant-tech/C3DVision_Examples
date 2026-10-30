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

#include <qt_sdimainwindow.h>
#include <QActionEvent>
#include <QSettings>
#include <QEvent>
//#include <QComboBox>
//#include <QDesktopServices>
#include <QDockWidget>
#include <QFileDialog>
#include <QMessageBox>
#include <QProgressBar>
#include <QStyleFactory>

#include <conv_exchange_settings.h>
#include <conv_model_exchange.h>
#include <conv_predefined.h>

#include <qt_actioncontainer.h>
#include <qt_actionmanager.h>

#include <qt_c3dstyle.h>
#include <qt_commandbar.h>
#include <qt_coreconstants.h>
#include <qt_modeldocument.h>
#include <qt_modelview.h>
#include <qt_progressindicator.h>
#include <qt_stylehelper.h>
#include <vsn_orientationmarker.h>

#include <vsn_last.h>

namespace VSN {
namespace QtVision {

/* QtSdiMainWindow */
QtSdiMainWindow::QtSdiMainWindow(CreateOptions controls, ModelView* widget)
    : QtMainWindow(controls)
    , m_modelView(nullptr)
    , m_dockPropBrowserWidget(nullptr)
    , m_dockModelTreeWidget(nullptr)
    , m_dockOutputWidget(nullptr)
    , m_modelEditor(nullptr)
    , m_processManager(nullptr)
    , m_viewController(nullptr)
    , m_actionOpenFile(nullptr)
    , m_actionSaveFile(nullptr)
{
    initializing(controls, widget);
    readSettings();
}

//-----------------------------------------------------------------------------
// 
// ---
QtSdiMainWindow::~QtSdiMainWindow()
{
}

//-----------------------------------------------------------------------------
// Initialization of additional parameters of the main window
// ---
void QtSdiMainWindow::initializing(CreateOptions controls, ModelView* widget)
{
    m_modelEditor = new ModelEditor(this);
    connect(m_modelEditor->document(), &ModelDocument::modificationChanged, this, &QtSdiMainWindow::documentWasModified);

    createStandardActions();

    if (widget == nullptr)
        createSceneWidget();
    else
        setSceneWidget(widget);

    m_processManager = new ProcessManager(this);
    m_processManager->setSceneWidget(sceneWidget());
    m_viewController = new SceneViewController(this);
    m_viewController->setSceneWidget(sceneWidget());

    m_modelEditor->setModelSceneWidget(sceneWidget());

    if (controls.testFlag(QtSdiMainWindow::PropsPanel))
        createPropertiesPanel();
    if (controls.testFlag(QtSdiMainWindow::ModelPanel))
    {
        createModelTreePanel();
        m_modelEditor->setModelTreeWidget(modelWidget());
    }
    if (controls.testFlag(QtSdiMainWindow::OutputPanel))
        createOutputPanel();

    if (controls.testFlag(QtSdiMainWindow::MenuBar))
    {
        registerDefaultContainers(controls.testFlag(QtSdiMainWindow::MenuBar));
        registerDefaultActions();
    }

    // create requested controls
    if (controls.testFlag(QtSdiMainWindow::StatusBar))
        createStatusBar();
    if (controls.testFlag(QtSdiMainWindow::CmdBar))
        createCommandBar();
    if (controls.testFlag(QtSdiMainWindow::StandardBar))
        createStandardBar();
    if (controls.testFlag(QtSdiMainWindow::FilterBar))
        createFilterObjectsBar();
}

// Returns a pointer to the current active subwindow.
// If no window is currently active, nullptr is returned.
ModelView* QtSdiMainWindow::activeSceneWidget() const { return m_modelView; }
// Returns the pointer to the central rendering widget
ModelView* QtSdiMainWindow::sceneWidget() const { return m_modelView; }
// Returns a pointer to the property browser
QtPropBrowserWidget* QtSdiMainWindow::propertyWidget() const
{ return m_dockPropBrowserWidget != nullptr ? (QtPropBrowserWidget*)m_dockPropBrowserWidget->widget() : nullptr; }

// Returns a pointer to the property browser
ModelTreeWidget* QtSdiMainWindow::modelWidget() const
{ return m_dockModelTreeWidget != nullptr ? (ModelTreeWidget*)m_dockModelTreeWidget->widget() : nullptr; }

// Returns pointer to the output panel
QDockWidget* QtSdiMainWindow::outputWidget() const { return m_dockOutputWidget; }

// Returns a pointer to the model editor
ModelEditor* QtSdiMainWindow::modelEditor() const { return m_modelEditor; }
// Returns pointer to the process manager
ProcessManager* QtSdiMainWindow::processManager() const { return m_processManager; }
// The controller graphic area displays the details and allows you to control them.
SceneViewController* QtSdiMainWindow::viewController() const { return m_viewController; }


//-----------------------------------------------------------------------------
// Set new central widget for rendering
// ---
void QtSdiMainWindow::setSceneWidget(ModelView* widget)
{
    if (widget == nullptr)
        return;
    if (m_modelView != widget)
    {
        delete m_modelView;
        m_modelView = widget;

        m_modelView->setModelEditor(m_modelEditor);
        setCentralWidget(m_modelView);
    }
}

//-----------------------------------------------------------------------------
// Create properties panel
// ---
void QtSdiMainWindow::createPropertiesPanel()
{
    m_dockPropBrowserWidget = new QDockWidget(QObject::tr("Properties"), this);
    m_dockPropBrowserWidget->setObjectName("vsn_id_property_browser");
    QtPropBrowserWidget* browserLayout = new QtPropBrowserWidget;
    m_dockPropBrowserWidget->setWidget(browserLayout);
    addDockWidget(Qt::RightDockWidgetArea, m_dockPropBrowserWidget);
}

//-----------------------------------------------------------------------------
// Create model panel
// ---
void QtSdiMainWindow::createModelTreePanel()
{
    m_dockModelTreeWidget = new QDockWidget(QObject::tr("Projects"), this);
    m_dockModelTreeWidget->setObjectName("vsn_id_model_browser");
    ModelTreeWidget* modelTreeLayout = new ModelTreeWidget;
    m_dockModelTreeWidget->setWidget(modelTreeLayout);
    addDockWidget(Qt::LeftDockWidgetArea, m_dockModelTreeWidget);
}

//-----------------------------------------------------------------------------
// Create a panel for output
// ---
void QtSdiMainWindow::createOutputPanel()
{ 
    m_dockOutputWidget = new QDockWidget(QObject::tr("Output"), this);
    addDockWidget(Qt::BottomDockWidgetArea, m_dockOutputWidget);
}

//-----------------------------------------------------------------------------
// Create a standard panel for commands
// ---
void QtSdiMainWindow::createStandardBar()
{
    QToolBar* fileToolBar = addToolBar(QObject::tr("File"));
    fileToolBar->addAction(m_actionOpenFile);
    fileToolBar->addAction(m_actionSaveFile);
}

//-----------------------------------------------------------------------------
// Create a command bar for commands
// ---
void QtSdiMainWindow::createCommandBar()
{
    QtCommandBar* commandBar = new QtCommandBar(this);
    addToolBar(Qt::LeftToolBarArea, commandBar);
}

//-----------------------------------------------------------------------------
// Создать панель фильтров объектов
// ---
void QtSdiMainWindow::createFilterObjectsBar()
{
    QList<QAction*> actions = m_modelEditor->createActionsSelectFilter();
    QToolBar* filterToolBar = addToolBar(QObject::tr("Select Filter"));
    filterToolBar->addActions(actions);
}

//-----------------------------------------------------------------------------
// Create a standard menu for commands
// ---
QMenu* QtSdiMainWindow::createStandardContextMenu(QMenu* inMenu)
{
    bool deleteMenu = true;
    QMenu* menu = inMenu ? inMenu : new QMenu(this);
    if (m_dockPropBrowserWidget != nullptr)
    {
        menu->addAction(m_actionPropsPanel);
        deleteMenu = false;
    }
    if (m_dockModelTreeWidget != nullptr)
    {
        menu->addAction(m_actionModelPanel);
        deleteMenu = false;
    }
    if (m_dockOutputWidget != nullptr)
        menu->addAction(m_actionOutputPanel);

    if (deleteMenu)
    {
        VSN_DELETE_AND_NULL(menu);
    }
    else
        QObject::connect(menu, &QMenu::aboutToShow, this, &QtSdiMainWindow::aboutToShowView);
    return menu;
}

//-----------------------------------------------------------------------------
// Create default container for commands
// ---
void QtSdiMainWindow::registerDefaultContainers(bool createMenuBar)
{
    ActionContainer* menubar = ActionManager::createMenuBar(Constants::MENU_BAR);
    if (!HostOsInfo::isMacHost() && createMenuBar) // System menu bar on Mac
        setMenuBar(menubar->menuBar());

    menubar->appendGroup(Constants::G_FILE);
    menubar->appendGroup(Constants::G_VIEW);

    // File Menu
    ActionContainer* filemenu = ActionManager::createMenu(Constants::M_FILE);
    menubar->addMenu(filemenu, Constants::G_FILE);
    filemenu->menu()->setTitle(tr("&File"));
    filemenu->appendGroup(Constants::G_FILE_OPEN);
    filemenu->appendGroup(Constants::G_FILE_SAVE);
    filemenu->appendGroup(Constants::G_FILE_CLOSE);
    filemenu->appendGroup(Constants::G_FILE_OTHER);

//    connect(filemenu->menu(), &QMenu::aboutToShow, this, &MainWindow::aboutToShowRecentFiles);

    ActionContainer* mview = ActionManager::createMenu(Constants::M_VIEW);
    menubar->addMenu(mview, Constants::G_VIEW);
    mview->menu()->setTitle(tr("&View"));
//    mview->appendGroup(Constants::G_VIEW_VIEWS);
    mview->appendGroup(Constants::G_VIEW_PANES);
    QObject::connect(mview->menu(), &QMenu::aboutToShow, this, &QtSdiMainWindow::aboutToShowView);
}

//-----------------------------------------------------------------------------
// Creating a default command
// ---
void QtSdiMainWindow::registerDefaultActions()
{
    ActionContainer* mfile = ActionManager::actionContainer(Constants::M_FILE);
    ActionContainer* mview = ActionManager::actionContainer(Constants::M_VIEW);

    // File menu separators
    mfile->addSeparator(Constants::G_FILE_SAVE);
//    mfile->addSeparator(Constants::G_FILE_EXPORT);
//    mfile->addSeparator(Constants::G_FILE_PRINT);
    mfile->addSeparator(Constants::G_FILE_CLOSE);
    mfile->addSeparator(Constants::G_FILE_OTHER);

    // Open Action
    const QIcon openIcon = QIcon::fromTheme("document-open", QIcon(":/res/openfile_48.png"));
    m_actionOpenFile = new QAction(openIcon, tr("&Open..."), this);
    Command* cmd = ActionManager::registerAction(m_actionOpenFile, Constants::OPEN);
    cmd->setDefaultKeySequence(QKeySequence::Open);
    cmd->action()->setStatusTip(tr("Open an existing file"));
    mfile->addAction(cmd, Constants::G_FILE_OPEN);
    connect(m_actionOpenFile, &QAction::triggered, this, &QtMainWindow::open);
    // Save Action
    const QIcon saveIcon = QIcon::fromTheme("document-save", QIcon(":/res/savefile_48.png"));
    m_actionSaveFile = new QAction(saveIcon, tr("&Save"), this);
    m_actionSaveFile->setEnabled(false);
    cmd = ActionManager::registerAction(m_actionSaveFile, Constants::SAVE);
    cmd->setDefaultKeySequence(QKeySequence::Save);
    cmd->action()->setStatusTip(tr("Save the document to disk"));
    mfile->addAction(cmd, Constants::G_FILE_SAVE);
    connect(m_actionSaveFile, &QAction::triggered, this, &QtSdiMainWindow::save);
    connect(modelEditor()->document(), &ModelDocument::modificationChanged, m_actionSaveFile, &QAction::setEnabled);

    // creating a submenu of recently opened files
    ActionContainer* filemenu = ActionManager::createMenu(Constants::M_FILE);
    createRecentFileSubMenu(filemenu->menu());
    setRecentFilesVisible(QtMainWindow::hasRecentFiles());

    // Exit Action
    const QIcon exitIcon = QIcon::fromTheme(QLatin1String("application-exit"));
    m_actionExit = new QAction(exitIcon, tr("E&xit"), this);
    m_actionExit->setMenuRole(QAction::QuitRole);
    cmd = ActionManager::registerAction(m_actionExit, Constants::EXIT);
    cmd->setDefaultKeySequence(QKeySequence(tr("Ctrl+Q")));
    mfile->addAction(cmd, Constants::G_FILE_OTHER);
    connect(m_actionExit, &QAction::triggered, this, &QtSdiMainWindow::exit);

    // Projects panel Action
    if (m_dockModelTreeWidget != nullptr)
    {
        const QIcon modelIcon; // = QIcon::fromTheme("document-save", QIcon(":/res/save_file32.png"));
        m_actionModelPanel = new QAction(modelIcon, tr("P&rojects panel"), this);
        cmd = ActionManager::registerAction(m_actionModelPanel, Constants::TOGGLE_MODEL_PANEL);
        cmd->setDefaultKeySequence(QKeySequence(useMacShortcuts ? tr("Ctrl+0") : tr("Alt+0")));
        cmd->action()->setStatusTip(tr("Show/hide projects panel"));
        m_actionModelPanel->setCheckable(true);
        mview->addAction(cmd, Constants::G_VIEW_PANES);
        connect(m_actionModelPanel, &QAction::triggered, this,
            [this](bool visible) { m_dockModelTreeWidget->setVisible(visible); });
    }

    // Projects panel Action
    if (m_dockPropBrowserWidget != nullptr)
    {
        const QIcon propIcon; // = QIcon::fromTheme("document-save", QIcon(":/res/save_file32.png"));
        m_actionPropsPanel = new QAction(propIcon, tr("&Properties panel"), this);
        cmd = ActionManager::registerAction(m_actionPropsPanel, Constants::TOGGLE_PROPS_PANEL);
        cmd->setDefaultKeySequence(QKeySequence(useMacShortcuts ? tr("Ctrl+9") : tr("Alt+9")));
        cmd->action()->setStatusTip(tr("Show/hide properties panel"));
        m_actionPropsPanel->setCheckable(true);
        mview->addAction(cmd, Constants::G_VIEW_PANES);
        connect(m_actionPropsPanel, &QAction::triggered, this,
            [this](bool visible) { m_dockPropBrowserWidget->setVisible(visible); });
    }
    // Output panel Action
    if (m_dockOutputWidget != nullptr)
    {
        const QIcon propIcon; // = QIcon::fromTheme("document-save", QIcon(":/res/save_file32.png"));
        m_actionOutputPanel = new QAction(propIcon, tr("&Output panel"), this);
        cmd = ActionManager::registerAction(m_actionOutputPanel, Constants::TOGGLE_OUTPUT_PANEL);
        cmd->setDefaultKeySequence(QKeySequence(useMacShortcuts ? tr("Ctrl+8") : tr("Alt+8")));
        cmd->action()->setStatusTip(tr("Show/hide output panel"));
        m_actionOutputPanel->setCheckable(true);
        mview->addAction(cmd, Constants::G_VIEW_PANES);
        connect(m_actionOutputPanel, &QAction::triggered, this, 
            [this](bool visible) { m_dockOutputWidget->setVisible(visible); });
    }
}

//-----------------------------------------------------------------------------
// Create standard processes for camera control
// ---
void QtSdiMainWindow::createStandardProcessesCamera()
{
    QtOpenGLSceneWidget* wd = qobject_cast<QtOpenGLSceneWidget*>(centralWidget());
    QTV_ASSERT(wd, return);
    SceneSegment* pTopSegment = wd->sceneContent()->GetRootSegment();
    QTV_ASSERT(pTopSegment, return);
    PrCameraRotate* pProcessRotate = new PrCameraRotate(wd->graphicsEngine()->GetGraphicsScene(), pTopSegment);
    pProcessRotate->SetMouseButtonsActivate({VSN::mb_RButton});
    PrCameraPan* pProcessPan = new PrCameraPan(wd->graphicsEngine()->GetGraphicsScene(), pTopSegment);
    pProcessPan->SetMouseButtonsActivate({VSN::mb_MButton});
    new PrCameraZoomWheel(wd->graphicsEngine()->GetGraphicsScene(), pTopSegment);
}

//-----------------------------------------------------------------------------
// Open all selected files and merge them into one model(MbModel)
// ---
bool QtSdiMainWindow::openFiles(const QStringList& filesName)
{
    if (filesName.isEmpty())
        return false;

    m_progressBar->setVisible(true);
    m_progressBar->reset();
    m_progressBar->setRange(0, filesName.count());
    connect(modelEditor()->document(), &ModelDocument::numReadFileChanged, m_progressBar, &QProgressBar::setValue);
    statusBar()->showMessage(QObject::tr("Reading selected file(s)"));
    // set wait cursor
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
    bool bOpenFiles = modelEditor()->document()->openFiles(filesName);
    // clear editor data when loading with a new project
    m_modelEditor->clearData();
    // restore old cursor view
    QApplication::restoreOverrideCursor();
    disconnect(modelEditor()->document(), &ModelDocument::numReadFileChanged, m_progressBar, &QProgressBar::setValue);
    statusBar()->clearMessage();

    m_progressBar->reset();
    m_progressBar->setVisible(false);

    setCurrentFile(filesName.size() == 1 ? filesName[0] : QString());

    if (filesName.count() == 1)
    {
        QString fileName = filesName.at(0);
        QtMainWindow::prependToRecentFiles(fileName);
    }

    emit openNewModel(modelEditor()->document()->model());
    return bOpenFiles;
}

//-----------------------------------------------------------------------------
// Create a central widget for rendering
// ---
void QtSdiMainWindow::createSceneWidget() { setSceneWidget(new ModelView); }

//-----------------------------------------------------------------------------
//
// ---
void QtSdiMainWindow::setProgressIndicatorVisible(bool visible)
{
    if (!visible)
    {
        m_progressIndicator->hide();
        return;
    }
    const QSize iconSize = m_progressIndicator->sizeHint();
/*    m_progressIndicator->setGeometry(m_fileLineEdit->button(Utils::FancyLineEdit::Right)->geometry().x()
        - iconSize.width(),
        (m_fileLineEdit->height() - iconSize.height()) / 2,
        iconSize.width(),
        iconSize.height());
*/
    m_progressIndicator->show();
}

// ---
void QtSdiMainWindow::documentWasModified() { setWindowModified(true); }

// ---
static void acceptModalDialogs()
{
    const QWidgetList topLevels = QApplication::topLevelWidgets();
    QList<QDialog*> dialogsToClose;
    for (QWidget* topLevel : topLevels)
    {
        if (auto dialog = qobject_cast<QDialog*>(topLevel))
        {
            if (dialog->isModal())
                dialogsToClose.append(dialog);
        }
    }
    for (QDialog* dialog : dialogsToClose)
        dialog->accept();
}

// ---
void QtSdiMainWindow::exit()
{
    // this function is most likely called from a user action
    // that is from an event handler of an object
    // since on close we are going to delete everything
    // so to prevent the deleting of that object we
    // just append it
    QMetaObject::invokeMethod(this,
        [this]
        {
            // Modal dialogs block the close event. So close them, in case this was triggered from
            // a RestartDialog in the settings dialog.
            acceptModalDialogs();
            close();
        },
        Qt::QueuedConnection);
}

//-----------------------------------------------------------------------------
//
// ---
void QtSdiMainWindow::aboutToShowView()
{
    if (m_dockPropBrowserWidget != nullptr && m_actionPropsPanel != nullptr)
        m_actionPropsPanel->setChecked(m_dockPropBrowserWidget->isVisible());
    if (m_dockModelTreeWidget != nullptr && m_actionModelPanel != nullptr)
        m_actionModelPanel->setChecked(m_dockModelTreeWidget->isVisible());
    if (m_dockOutputWidget != nullptr && m_actionOutputPanel != nullptr)
        m_actionOutputPanel->setChecked(m_dockOutputWidget->isVisible());
}

//-----------------------------------------------------------------------------
//
// ---
bool QtSdiMainWindow::event(QEvent* event) { return QtAppMainWindow::event(event); }
void QtSdiMainWindow::actionEvent(QActionEvent* event) { QtAppMainWindow::actionEvent(event); }
void QtSdiMainWindow::mousePressEvent(QMouseEvent* event) { m_mousePress = event->globalPos(); }

//-----------------------------------------------------------------------------
//
// ---
void QtSdiMainWindow::mouseReleaseEvent(QMouseEvent* event)
{
    Q_UNUSED(event);
    /*
    // If we move the mouse more than DragDistance then the popup-menu is not shown
    if (event->button() != Qt::RightButton ||
        (event->globalPos() - m_mousePress).manhattanLength() > QApplication::startDragDistance())
        return;
    if (QMenu* menu = createStandardContextMenu())
    {
        menu->setAttribute(Qt::WA_DeleteOnClose);
        menu->popup(event->globalPos());
    }
*/
}

//-----------------------------------------------------------------------------
//
// ---
#if 0
void QtSdiMainWindow::contextMenuEvent(QContextMenuEvent* event)
{
    // If we move the mouse more than DragDistance then the popup-menu is not shown
    if ((event->globalPos() - m_mousePress).manhattanLength() > QApplication::startDragDistance())
        return;

    if (QMenu* menu = createStandardContextMenu())
    {
        menu->setAttribute(Qt::WA_DeleteOnClose);
        menu->popup(event->globalPos());
    }
}
#endif

} // namespace QtVision
} // namespace VSN
