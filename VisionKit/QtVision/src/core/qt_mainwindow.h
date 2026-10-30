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

///////////////////////////////////////////////////////////////////////////////
/**
  \file
  \brief \ru .
         \en .\~
*/
///////////////////////////////////////////////////////////////////////////////
#ifndef __QT_MAINWINDOW_H
#define __QT_MAINWINDOW_H

#include <QMenu>
#include <QFlags>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QProgressBar>
#include <QTimer>
#include <QFile>

#include <templ_sptr.h>
#include <model_entity.h>

#include <qt_icore.h>
#include <qt_appmainwindow.h>
#include <qt_openglwidget.h>
#include <qt_modeleditor.h>
#include <qt_commandbar.h>
#include <qt_modeltreewidget.h>
#include <qt_propbrowserwidget.h>
#include <qt_sceneviewcontroller.h>
#include <qt_processmanager.h>
#include <qt_global.h>

namespace VSN {
namespace QtVision {

class ModelView;

/* QtMainWindow */
class QT_CLASS QtMainWindow : public QtAppMainWindow
{
    Q_OBJECT
    VSN_OBJECT(QtMainWindow)
public:
    enum CreateOption
    {
        NoControl   = 0x00000000,
        PropsPanel  = 0x00000001,
        ModelPanel  = 0x00000002,
        OutputPanel = 0x00000004,

        MenuBar     = 0x00000008,
        StandardBar = 0x00000010,
        FilterBar   = 0x00000020,
        StatusBar   = 0x00000040,
        CmdBar      = 0x00000080
    };
    Q_DECLARE_FLAGS(CreateOptions, CreateOption)
public:
    explicit QtMainWindow(CreateOptions controls = QtMainWindow::NoControl);
    ~QtMainWindow() override;
public Q_SLOTS:
    void open();
    bool save();
    void saveAs();
    void updateRecentFileActions();
    void openRecentFile();
public:
    // Returns pointer to the progressBar
    QProgressBar* progressBarWidget() const;
public:
    // Returns a pointer to the current active subwindow.
    // If no window is currently active, nullptr is returned.
    virtual ModelView* activeSceneWidget() const;
    // Returns pointer to the property browser
    virtual QtPropBrowserWidget* propertyWidget() const;

    // Returns pointer to the main window (the pointer may be null)
    static QtMainWindow* findMainWindow();
    // returns theme style id
    ThemeId idStyleTeme() const { return m_idTeme; }
    // returns true if scene information is enabled
    bool isVisibleAboutScene() const;
public:
    // Open all selected file(MbModel)
    bool openFile(QFile& file);
    bool openFile(const QString& filesName);
    void setCurrentFile(const QString& fileName);
protected:
    // Open all selected files and merge them into one model(MbModel)
    virtual bool openFiles(const QStringList& filesName);
protected:
    // Create status bar
    void createStatusBar();
    // Recent Files Menu
    QMenu* createRecentFileSubMenu(QMenu* pMenu);
    // create standard actions
    void createStandardActions();
protected:
    bool maybeSave();
    void readSettings();
    void writeSettings();
    virtual void readState(QSettings& settings);
    virtual void writeState(QSettings& settings);

    static bool hasRecentFiles();
    void prependToRecentFiles(const QString& fileName);
    void setRecentFilesVisible(bool visible);
public Q_SLOTS:
    // Subject changed
    void setCurrentIndexTheme(int index);
    // Subject changed
    void setVisibleInfoAboutScene(bool isVisible);
Q_SIGNALS:
    void openNewModel(MxModelExtension* model);
    void currentIndexThemeChanged(int index);

    void setVisibleProgress(bool);
    void buildProgress(int);
    void setProgressRange(int minimum, int maximum);
    void resetProgress();
protected:
    void closeEvent(QCloseEvent* event) override;
protected:
    enum { MaxRecentFiles = 9 };
    ICore* m_coreImpl = nullptr;
    QProgressBar* m_progressBar;
    ThemeId m_idTeme;
    QString m_defaultStyle;
    QString m_lastDirectory;
    QString m_curFile;
    QPalette m_defPpalette;
    bool m_isAboutScene;
    bool m_isUntitled;

    QAction* m_actionRecentFile[MaxRecentFiles];
    QAction* m_actionRecentFileSeparator;
    QAction* m_actionRecentFileSubMenu;
    QAction* m_actionAboutScene = nullptr;
private:
    Q_DISABLE_COPY(QtMainWindow)
};

} // namespace QtVision
} // namespace VSN

#endif /* __QT_MAINWINDOW_H */
