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
#include <QFileInfo>
#include <QDialog>
#include <QCloseEvent>

#include <qt_mdimainwindow.h>
#include <qt_modelview.h>
#include <qt_actioncontainer.h>
#include <qt_actionmanager.h>

#include <vsn_last.h>

namespace VSN {
namespace QtVision {

/* QtMdiMainWindow */
QtMdiMainWindow::QtMdiMainWindow(CreateOptions controls)
    : QtMainWindow(controls)
    , m_mdiArea(new QMdiArea(this))
    , m_dockModelTreeWidget(nullptr)
{
    initialization(controls);
    readSettings();
}

//-----------------------------------------------------------------------------
// 
// ---
QtMdiMainWindow::~QtMdiMainWindow()
{
}

//-----------------------------------------------------------------------------
// Returns a pointer to the current active subwindow.
// If no window is currently active, nullptr is returned.
// ---
ModelView* QtMdiMainWindow::activeSceneWidget() const
{
    if (QMdiSubWindow* subWindow = m_mdiArea->activeSubWindow())
        return qobject_cast<ModelView*>(subWindow->widget());
    return nullptr;
}

// Returns a pointer to the property browser
ModelTreeWidget* QtMdiMainWindow::modelWidget() const
{ return m_dockModelTreeWidget != nullptr ? (ModelTreeWidget*)m_dockModelTreeWidget->widget() : nullptr; }
// Returns a pointer to the docking model browser
QDockWidget* QtMdiMainWindow::dockModelTreeWidget() const { return m_dockModelTreeWidget; }

//-----------------------------------------------------------------------------
// interface initialization
// ---
void QtMdiMainWindow::initialization(CreateOptions controls)
{
    m_mdiArea->setViewMode(QMdiArea::TabbedView);
    m_mdiArea->setTabsClosable(true);
    m_mdiArea->setTabsMovable(true);
//    m_mdiArea->setDocumentMode(true);
    m_mdiArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_mdiArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setCentralWidget(m_mdiArea);
    connect(m_mdiArea, &QMdiArea::subWindowActivated, this, &QtMdiMainWindow::updateModelTreeWidget);

    createStandardActions();

    if (controls.testFlag(QtMainWindow::ModelPanel))
        createModelTreePanel();
    if (controls.testFlag(QtMainWindow::MenuBar))
    {
        registerDefaultContainers(controls.testFlag(QtMainWindow::MenuBar));
        registerDefaultActions();
    }
    // create requested controls
    if (controls.testFlag(QtMainWindow::StatusBar))
        createStatusBar();
}

//-----------------------------------------------------------------------------
// Create model panel
// ---
void QtMdiMainWindow::createModelTreePanel()
{
    m_dockModelTreeWidget = new QDockWidget(QObject::tr("Projects"), this);
    m_dockModelTreeWidget->setObjectName("vsn_id_model_browser");
    addDockWidget(Qt::LeftDockWidgetArea, m_dockModelTreeWidget);
}

//----------------------------------------------------------------------------
//
// ---
void QtMdiMainWindow::fileNew()
{
    ModelView* child = createMdiChild();
    child->newFile();
    child->show();
}

// ---
void QtMdiMainWindow::updateModelTreeWidget(QMdiSubWindow* subWindow) 
{
    QList<QMdiSubWindow*> subWindows = m_mdiArea->subWindowList();
    if (subWindow == nullptr && subWindows.isEmpty())
        return;

    for (auto it : subWindows)
    {
        QMdiSubWindow* window = it;
        ModelView* modelView = qobject_cast<ModelView*>(window->widget());
        if (window == subWindow)
        {
            if (modelView != nullptr)
                modelView->activationView();
        }
        else if (modelView != nullptr) 
        {
            modelView->deactivationView();
        }
    }
}

//-----------------------------------------------------------------------------
// Create default container for commands
// ---
void QtMdiMainWindow::registerDefaultContainers(bool createMenuBar)
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
    filemenu->appendGroup(Constants::G_FILE_NEW);
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
    QObject::connect(mview->menu(), &QMenu::aboutToShow, this, &QtMdiMainWindow::aboutToShowView);
}

//-----------------------------------------------------------------------------
// Creating a default command
// ---
void QtMdiMainWindow::registerDefaultActions()
{
    ActionContainer* mfile = ActionManager::actionContainer(Constants::M_FILE);
    ActionContainer* mview = ActionManager::actionContainer(Constants::M_VIEW);

    // File menu separators
    mfile->addSeparator(Constants::G_FILE_SAVE);
//    mfile->addSeparator(Constants::G_FILE_EXPORT);
//    mfile->addSeparator(Constants::G_FILE_PRINT);
    mfile->addSeparator(Constants::G_FILE_CLOSE);
    mfile->addSeparator(Constants::G_FILE_OTHER);

    // New Action
    const QIcon newIcon = QIcon::fromTheme("document-new", QIcon(":/res/newfile_48.png"));
    m_actionNewFile = new QAction(newIcon, tr("&New..."), this);
    Command* cmd = ActionManager::registerAction(m_actionNewFile, Constants::NEW);
    cmd->setDefaultKeySequence(QKeySequence::New);
    cmd->action()->setStatusTip(tr("Создать новый файл"));
    mfile->addAction(cmd, Constants::G_FILE_NEW);
    connect(m_actionNewFile, &QAction::triggered, this, &QtMdiMainWindow::fileNew);
    // Open Action
    const QIcon openIcon = QIcon::fromTheme("document-open", QIcon(":/res/openfile_48.png"));
    m_actionOpenFile = new QAction(openIcon, tr("&Open..."), this);
    cmd = ActionManager::registerAction(m_actionOpenFile, Constants::OPEN);
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
//    connect(m_actionSaveFile, &QAction::triggered, this, &QtMdiMainWindow::save);
//    connect(modelEditor()->document(), &ModelDocument::modificationChanged, m_actionSaveFile, &QAction::setEnabled);

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
    connect(m_actionExit, &QAction::triggered, this, &QtMdiMainWindow::exit);
    
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
/*
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
*/
}

// ---
ModelView* QtMdiMainWindow::createView() const { return nullptr; }

//----------------------------------------------------------------------------
//
// ---
ModelView* QtMdiMainWindow::createMdiChild()
{
    ModelView* child = createView();
    child->setMinimumSize(320, 200);
    m_mdiArea->addSubWindow(child);
    return child;
}

// ---
bool QtMdiMainWindow::openFiles(const QStringList& files)
{
    if (files.count() == 1)
    {
        QString fileName = files.at(0);
        if (QMdiSubWindow* existing = findMdiChild(fileName))
        {
            m_mdiArea->setActiveSubWindow(existing);
            return true;
        }
    }
    const bool succeeded = loadFiles(files);
    if (succeeded)
        statusBar()->showMessage(tr("File loaded"), 2000);
    return succeeded;
}

//----------------------------------------------------------------------------
//
// ---
bool QtMdiMainWindow::loadFiles(const QStringList& files)
{
    ModelView* child = createMdiChild();
    const bool succeeded = child->loadFiles(files);
    if (succeeded)
        child->show();
    else
        child->close();

    if (succeeded && files.count() == 1)
    {
        QString fileName = files.at(0);
        setCurrentFile(fileName);
        QtMainWindow::prependToRecentFiles(fileName);
    }
    return succeeded;
}

//----------------------------------------------------------------------------
//
// ---
QMdiSubWindow* QtMdiMainWindow::findMdiChild(const QString& fileName) const
{
    QString canonicalFilePath = QFileInfo(fileName).canonicalFilePath();
    const QList<QMdiSubWindow*> subWindows = m_mdiArea->subWindowList();
    for (QMdiSubWindow* window : subWindows)
    {
        ModelView* mdiChild = qobject_cast<ModelView*>(window->widget());
        if (mdiChild->currentFile() == canonicalFilePath)
            return window;
    }
    return nullptr;
}

//-----------------------------------------------------------------------------
//
// ---
void QtMdiMainWindow::aboutToShowView()
{
//    if (m_dockPropBrowserWidget != nullptr && m_actionPropsPanel != nullptr)
//        m_actionPropsPanel->setChecked(m_dockPropBrowserWidget->isVisible());
    if (m_dockModelTreeWidget != nullptr && m_actionModelPanel != nullptr)
        m_actionModelPanel->setChecked(m_dockModelTreeWidget->isVisible());
//    if (m_dockOutputWidget != nullptr && m_actionOutputPanel != nullptr)
//        m_actionOutputPanel->setChecked(m_dockOutputWidget->isVisible());
}

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
void QtMdiMainWindow::exit()
{
    // this function is most likely called from a user action
    // that is from an event handler of an object
    // since on close we are going to delete everything
    // so to prevent the deleting of that object we
    // just append it
    QMetaObject::invokeMethod(
        this,
        [this]
        {
            // Modal dialogs block the close event. So close them, in case this was triggered from
            // a RestartDialog in the settings dialog.
            acceptModalDialogs();
            close();
        },
        Qt::QueuedConnection);
}

//----------------------------------------------------------------------------
//
// ---
void QtMdiMainWindow::closeEvent(QCloseEvent* event)
{
    m_mdiArea->closeAllSubWindows();
    if (m_mdiArea->currentSubWindow()) 
    {
        event->ignore();
    }
    else 
    {
        writeSettings();
        event->accept();
    }
}

} // namespace QtVision
} // namespace VSN
