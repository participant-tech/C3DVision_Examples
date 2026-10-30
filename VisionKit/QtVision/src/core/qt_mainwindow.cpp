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

#include <qt_mainwindow.h>

#include <QDir>
#include <QEvent>
#include <QCloseEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <QComboBox>
#include <QDesktopServices>
#include <QStyleFactory>
#include <QApplication>
#if (QT_VERSION <= QT_VERSION_CHECK(6, 0, 0))
#include <QDesktopWidget>
#endif

#include <qt_actionmanager.h>
#include <qt_icontext.h>
#include <qt_c3dstyle.h>
#include <qt_stylehelper.h>
#include <qt_modeldocument.h>
#include <qt_modelview.h>

#include <vsn_last.h>

namespace VSN {
namespace QtVision {

static inline QString recentFilesKey() { return QStringLiteral("recentFileList"); }
static inline QString fileKey() { return QStringLiteral("file"); }

static QStringList readRecentFiles(QSettings& settings)
{
    QStringList result;
    const int count = settings.beginReadArray(recentFilesKey());
    for (int i = 0; i < count; ++i)
    {
        settings.setArrayIndex(i);
        result.append(settings.value(fileKey()).toString());
    }
    settings.endArray();
    return result;
}

static void writeRecentFiles(const QStringList& files, QSettings& settings)
{
    const int count = files.size();
    settings.beginWriteArray(recentFilesKey());
    for (int i = 0; i < count; ++i)
    {
        settings.setArrayIndex(i);
        settings.setValue(fileKey(), files.at(i));
    }
    settings.endArray();
}

/* QtMainWindow */
QtMainWindow::QtMainWindow(CreateOptions controls)
    : QtAppMainWindow()
    , m_coreImpl(new ICore(this))
    , m_progressBar(nullptr)
    , m_idTeme(Default)
    , m_defaultStyle(QStyleFactory::keys().at(0)) 
    , m_defPpalette(style()->standardPalette())
    , m_isAboutScene(false)
    , m_isUntitled(true)
{
    Q_UNUSED(controls);
    setUnifiedTitleAndToolBarOnMac(true);
    new ActionManager(this);

    // TODO
    Context uniquecontexts = Context(Constants::C_GLOBAL);
    ActionManager::setContext(uniquecontexts);
}

//-----------------------------------------------------------------------------
// 
// ---
QtMainWindow::~QtMainWindow()
{
    delete m_coreImpl;
    m_coreImpl = nullptr;
}

//-----------------------------------------------------------------------------
//
// ---
void QtMainWindow::open()
{
    QStringList filters = QtVision::processFilters();
    QString oneLineFilters = filters.join("\n");
#ifdef Q_OS_WIN
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Choose a files"), m_lastDirectory, oneLineFilters);
#else
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Choose a files"), m_lastDirectory, oneLineFilters, nullptr,
        QFileDialog::DontUseNativeDialog);
#endif
    if (!files.isEmpty())
    {
        m_lastDirectory = QFileInfo(files.at(0)).absolutePath();
        openFiles(files);
    }
}

//-----------------------------------------------------------------------------
//
// ---
bool QtMainWindow::save()
{
    bool bSave = false;
    QStringList filters = QtVision::processFilters();
    QString oneLineFilters = filters.join("\n");
#ifdef Q_OS_WIN
    const QString fileName = QFileDialog::getSaveFileName(this, tr("Save Model"), m_lastDirectory, oneLineFilters);
#else
    const QString fileName = QFileDialog::getSaveFileName(this, tr("Save Model"), m_lastDirectory, oneLineFilters, nullptr,
        QFileDialog::DontUseNativeDialog);
#endif
    if (!fileName.isEmpty())
    {
        // set wait cursor
        QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
        activeSceneWidget()->modelEditor()->document()->save(fileName, bSave);
        if (!bSave)
            vsnWarning("Model write error");

        setCurrentFile(fileName);
        statusBar()->showMessage(tr("File saved"), 2000);
        QApplication::restoreOverrideCursor();
    }
    return bSave;
}

void QtMainWindow::saveAs()
{
    /*
    MdiChild* child = activeMdiChild();
    if (child && child->saveAs())
    {
        statusBar()->showMessage(tr("File saved"), 2000);
        QtMainWindow::prependToRecentFiles(child->currentFile());
    }
    */
}

//----------------------------------------------------------------------------
//
// ---
void QtMainWindow::updateRecentFileActions()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());

    const QStringList recentFiles = readRecentFiles(settings);
    const int count = qMin(int(MaxRecentFiles), recentFiles.size());
    int i = 0;
    for (; i < count; ++i)
    {
        const QString fileName = QFileInfo(recentFiles.at(i)).fileName();
        m_actionRecentFile[i]->setText(tr("&%1 %2").arg(i + 1).arg(fileName));
        m_actionRecentFile[i]->setData(recentFiles.at(i));
        m_actionRecentFile[i]->setVisible(true);
    }
    for (; i < MaxRecentFiles; ++i)
        m_actionRecentFile[i]->setVisible(false);
}

void QtMainWindow::openRecentFile()
{
    if (const QAction* action = qobject_cast<const QAction*>(sender()))
    {
        QStringList files;
        files.append(action->data().toString());
        openFiles(files);
    }
}

// Returns a pointer to the progressBar
QProgressBar* QtMainWindow::progressBarWidget() const { return m_progressBar; }

//-----------------------------------------------------------------------------
// Returns a pointer to the current active subwindow.
// If no window is currently active, nullptr is returned.
// ---
ModelView* QtMainWindow::activeSceneWidget() const { return nullptr; }
// Returns pointer to the property browser
QtPropBrowserWidget* QtMainWindow::propertyWidget() const { return nullptr; }

//-----------------------------------------------------------------------------
// Returns a pointer to the main window (the pointer may be null)
// ---
QtMainWindow* QtMainWindow::findMainWindow()
{
    const QList<QWidget*> topLevelWidgets = QApplication::topLevelWidgets();
    for (QWidget* widget : topLevelWidgets)
    {
        if (QtMainWindow* mainWin = qobject_cast<QtMainWindow*>(widget))
            return mainWin;
    }
    return nullptr;
}

//-----------------------------------------------------------------------------
// returns true if scene information is enabled
// ---
bool QtMainWindow::isVisibleAboutScene() const { return m_isAboutScene; }

//-----------------------------------------------------------------------------
//
// ---
void QtMainWindow::setCurrentFile(const QString& fileName)
{
    static int sequenceNumber = 1;

    m_isUntitled = fileName.isEmpty();
    if (m_isUntitled)
        m_curFile = qApp->applicationName() + " - " + QString("%1[*]").arg(tr("NONAME%1.c3d").arg(sequenceNumber++));
    else
        m_curFile = qApp->applicationName() + " - " + QString("%1[*]").arg(fileName);
//        m_curFile = QFileInfo(fileName).canonicalFilePath();

    activeSceneWidget()->modelEditor()->document()->setModified(false);
    setWindowModified(false);

// TODO:   if (!m_isUntitled && windowFilePath() != fileName)
// TODO:       QtMainWindow::prependToRecentFiles(fileName);

    setWindowTitle(m_curFile);
    setWindowFilePath(m_curFile);
}

//-----------------------------------------------------------------------------
// Open
// ---
bool QtMainWindow::openFile(QFile& file)
{
    ModelDocument* modelDocument = activeSceneWidget()->modelEditor()->document();
    if (modelDocument->openFile(file))
    {
        emit openNewModel(modelDocument->model());
        return true;
    }
    return false;
}

//-----------------------------------------------------------------------------
// Open all selected file(MbModel)
// ---
bool QtMainWindow::openFile(const QString& fileName)
{
    QStringList filesName;
    filesName << fileName;
    return openFiles(filesName);
}

//-----------------------------------------------------------------------------
// Open all selected files and merge them into one model(MbModel)
// ---
bool QtMainWindow::openFiles(const QStringList& filesName)
{
    Q_UNUSED(filesName);
    Q_ASSERT(false);
    return false;
}

//-----------------------------------------------------------------------------
// Ccreate status bar
// ---
void QtMainWindow::createStatusBar()
{
    setStatusBar(new QStatusBar());

    QFontMetrics fm = fontMetrics();
    int width = fm.boundingRect(QString("XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX")).width();
    m_progressBar = new QProgressBar();
    m_progressBar->setFixedWidth(width);
    m_progressBar->setTextVisible(true);
    statusBar()->addPermanentWidget(m_progressBar);

    QObject::connect(this, &QtMainWindow::buildProgress, m_progressBar, &QProgressBar::setValue);
    QObject::connect(this, &QtMainWindow::setProgressRange, m_progressBar, &QProgressBar::setRange);
    QObject::connect(this, &QtMainWindow::resetProgress, m_progressBar, &QProgressBar::reset);
    QObject::connect(this, &QtMainWindow::setVisibleProgress, m_progressBar, &QProgressBar::setVisible);
    // by default the progress bar is off it will be turned on when needed
    m_progressBar->setVisible(false);

    QComboBox* styleSwincher = new QComboBox();
    styleSwincher->setToolTip(QObject::tr("Switch display theme"));
    styleSwincher->addItem(QString("Default"), QVariant(QtVision::Default));
    styleSwincher->addItem(QString("Dark"), QVariant(QtVision::Dark));
    styleSwincher->addItem(QString("Dark-Flat"), QVariant(QtVision::FlatDark));
    styleSwincher->setCurrentIndex(QtVision::Default);
    QObject::connect(styleSwincher, SIGNAL(currentIndexChanged(int)), this, SLOT(setCurrentIndexTheme(int)));
    QObject::connect(this, SIGNAL(currentIndexThemeChanged(int)), styleSwincher, SLOT(setCurrentIndex(int)));
    statusBar()->addPermanentWidget(styleSwincher);

    QToolButton* infoSite = new QToolButton();
    infoSite->setIcon(QIcon(":/res/sitec3dlabs_48.png"));
    infoSite->setToolTip(QObject::tr("Visit website c3dlabs"));
    int height = styleSwincher->sizeHint().height();
    infoSite->setMinimumSize(QSize(height, height));
    QObject::connect(infoSite, &QToolButton::clicked,
        []() { QDesktopServices::openUrl(QUrl(QStringLiteral("https://c3dlabs.com"))); });
    statusBar()->addPermanentWidget(infoSite);

    QToolButton* infoScene = new QToolButton();
    infoScene->setDefaultAction(m_actionAboutScene);
    infoScene->setMinimumSize(QSize(height, height));
    statusBar()->addPermanentWidget(infoScene);
}

//-----------------------------------------------------------------------------
// create recent Files Menu
// ---
QMenu* QtMainWindow::createRecentFileSubMenu(QMenu* pMenu)
{
    QMenu* recentMenu = pMenu->addMenu(tr("Recent..."));
    connect(recentMenu, &QMenu::aboutToShow, this, &QtMainWindow::updateRecentFileActions);
    m_actionRecentFileSubMenu = recentMenu->menuAction();
    for (int i = 0; i < MaxRecentFiles; ++i)
    {
        m_actionRecentFile[i] = recentMenu->addAction(QString(), this, &QtMainWindow::openRecentFile);
        m_actionRecentFile[i]->setVisible(false);
    }
    m_actionRecentFileSeparator = pMenu->addSeparator();
    return recentMenu;
}

//-----------------------------------------------------------------------------
// create standard actions
// ---
void QtMainWindow::createStandardActions()
{
    const QIcon aboutSceneIcon = QIcon::fromTheme("about-scene", QIcon(":/res/about_scene_48.png"));
    m_actionAboutScene = new QAction(aboutSceneIcon, tr("About the scene"), this);
    m_actionAboutScene->setStatusTip(tr("Brief information about the scene"));
    m_actionAboutScene->setCheckable(true);
    m_actionAboutScene->setChecked(m_isAboutScene);
    connect(m_actionAboutScene, &QAction::triggered, this, &QtMainWindow::setVisibleInfoAboutScene);
}

// ---
bool QtMainWindow::maybeSave()
{
    if (activeSceneWidget())
    if (!activeSceneWidget()->modelEditor()->document()->isModified())
        return true;
    const QMessageBox::StandardButton ret = QMessageBox::warning(this, tr("SDI"),
        tr("The document has been modified.\n"
           "Do you want to save your changes?"),
        QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    switch (ret)
    {
        case QMessageBox::Save:
            return save();
        case QMessageBox::Cancel:
            return false;
        default:
            break;
    }
    return true;
}

//-----------------------------------------------------------------------------
//
// ---
void QtMainWindow::readSettings()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());

    // Load base settings (last working directory, upload/download limits).
    m_lastDirectory = settings.value("lastDirectory").toString();
    if (m_lastDirectory.isEmpty())
        m_lastDirectory = QDir::currentPath();

    QByteArray geo_data = settings.value("geometry", QByteArray()).toByteArray();
    bool result = restoreGeometry(geo_data);
    if (!result)
    {
#if (QT_VERSION <= QT_VERSION_CHECK(6, 0, 0))
        const QRect availableGeometry = QApplication::desktop()->availableGeometry(this);
        static int factor = 3;
        resize(QSize(2 * availableGeometry.width() / factor, 2 * availableGeometry.height() / factor));
        move(QPoint((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2));
#else
        static int factor = 3;
        const QRect availableGeometry = screen()->availableGeometry();
        resize(2 * availableGeometry.width() / factor, 2 * availableGeometry.height() / factor);
        move((availableGeometry.width() - width()) / 2, (availableGeometry.height() - height()) / 2);
#endif
    }
    QByteArray layout_data = settings.value("layout", QByteArray()).toByteArray();
    restoreState(layout_data);
    uint index = static_cast<uint>(QtVision::Default);
    ThemeId idTeme = static_cast<ThemeId>(settings.value("style", QVariant(index)).toUInt());
    setCurrentIndexTheme(static_cast<uint>(idTeme));
    emit currentIndexThemeChanged(static_cast<uint>(idTeme));
    readState(settings);
}

//-----------------------------------------------------------------------------
//
// ---
void QtMainWindow::writeSettings()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());

    settings.setValue("LastDirectory", m_lastDirectory);

    QByteArray geo_data = saveGeometry();
    settings.setValue("geometry", geo_data);

    QByteArray layout_data = saveState();
    settings.setValue("layout", layout_data);
    settings.setValue("style", static_cast<uint>(m_idTeme));
    writeState(settings);
}

// ---
void QtMainWindow::readState(QSettings& settings)
{
    bool isAboutScene = settings.value("isAboutScene", QVariant(m_isAboutScene)).toBool();
    m_actionAboutScene->setChecked(isAboutScene);
    setVisibleInfoAboutScene(isAboutScene);

    if (QtVision::QtPropBrowserWidget* propPanel = propertyWidget())
        propPanel->readSettings(settings);
}

// ---
void QtMainWindow::writeState(QSettings& settings)
{
    settings.setValue("isAboutScene", static_cast<bool>(m_isAboutScene));
    if (QtPropBrowserWidget* propPanel = propertyWidget())
        propPanel->writeSettings(settings);
}

//----------------------------------------------------------------------------
//
// ---
bool QtMainWindow::hasRecentFiles()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    const int count = settings.beginReadArray(recentFilesKey());
    settings.endArray();
    return count > 0;
}

//----------------------------------------------------------------------------
//
// ---
void QtMainWindow::prependToRecentFiles(const QString& fileName)
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    const QStringList oldRecentFiles = readRecentFiles(settings);

    QStringList recentFiles = oldRecentFiles;
    recentFiles.removeAll(fileName);
    recentFiles.prepend(fileName);
//    recentFiles.insert(0, fileName);

// TODO    if (oldRecentFiles.size() != recentFiles.size() && !std::equal(oldRecentFiles.begin(), oldRecentFiles.end(), recentFiles.begin()))
// TODO    if (oldRecentFiles.size() != recentFiles.size())
    if (!oldRecentFiles.contains(fileName))
        writeRecentFiles(recentFiles, settings);

    setRecentFilesVisible(!recentFiles.isEmpty());
}

//----------------------------------------------------------------------------
//
// ---
void QtMainWindow::setRecentFilesVisible(bool visible)
{
    m_actionRecentFileSubMenu->setVisible(visible);
    m_actionRecentFileSeparator->setVisible(visible);
}

//-----------------------------------------------------------------------------
//
// ---
static void initializingTheme(ThemeId id, const QString& styleName)
{
    Theme* pTheme = new Theme("window", qApp);
    QString strTheme = ":/res/flat-light.c3dtheme";
    QString baseName = styleName;
    // Примените стиль Fusion, если у нас есть темная тема в Windows или Linux,
    // потому что QStyle по умолчанию может не подойти для нее.
    if (id == Dark)
    {
        strTheme = ":/res/dark.c3dtheme";
        baseName = QLatin1String("fusion");
    }
    else if (id == FlatDark)
    {
        strTheme = ":/res/flat-dark.c3dtheme";
        baseName = QLatin1String("fusion");
    }
    QSettings settings(strTheme, QSettings::IniFormat);
    pTheme->readSettings(settings);

    setVisionTheme(pTheme);
    StyleHelper::setBaseColor(QColor(StyleHelper::DEFAULT_BASE_COLOR));
    QApplication::setStyle(new C3DStyle(baseName));
    QApplication::setPalette(pTheme->palette());
}

//-----------------------------------------------------------------------------
// Subject changed
// ---
void QtMainWindow::setCurrentIndexTheme(int index)
{
    m_idTeme = QtVision::Default;
    switch (index)
    {
        case Default: // Default theme
            m_idTeme = QtVision::Default;
            break;
        case Dark: // Dark theme
            m_idTeme = QtVision::Dark;
            break;
        case FlatDark: // Dark-Flat theme
            m_idTeme = QtVision::FlatDark;
            break;
        default:
            break;
    }

    if (m_idTeme == QtVision::Default)
    {
        if (m_defaultStyle.isEmpty())
            return;
    }
    initializingTheme(m_idTeme, m_defaultStyle);

    if (QtVision::visionTheme())
    {
        QColor clr = QtVision::visionTheme()->palette().color(QPalette::Dark);
        Color clrBackground(clr.red(), clr.green(), clr.blue());
        if (QtOpenGLSceneWidget* sceneWidget = activeSceneWidget())
            sceneWidget->viewport()->SetGradientBackgroundColour(clrBackground.GetLighter(120), clrBackground.GetLighter(240));
    }
    else if (QtOpenGLSceneWidget* sceneWidget = activeSceneWidget())
        sceneWidget->viewport()->SetGradientBackgroundColour(QtVision::topColor, QtVision::bottomColor);
    update();
}

//-----------------------------------------------------------------------------
// Brief information about the scene
// ---
void QtMainWindow::setVisibleInfoAboutScene(bool isVisible)
{
    if (m_isAboutScene == isVisible)
        return;
    m_isAboutScene = isVisible;

    QtOpenGLSceneWidget* pSceneWidget = activeSceneWidget();
    if (pSceneWidget == nullptr)
        return;
    // Render Statistics
    pSceneWidget->graphicsScene()->ShowStatistics(isVisible);
    pSceneWidget->update();
}


//-----------------------------------------------------------------------------
//
// ---
void QtMainWindow::closeEvent(QCloseEvent* event)
{
    if (maybeSave())
    {
        writeSettings();
        event->accept();
    }
    else
        event->ignore();
}

} // namespace QtVision
} // namespace VSN
