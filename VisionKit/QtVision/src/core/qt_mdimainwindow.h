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
#ifndef __QT_MDIMAINWINDOW_H
#define __QT_MDIMAINWINDOW_H

#include <QMdiArea>
#include <QMdiSubWindow>
#include <QDockWidget>

#include <qt_mainwindow.h>
#include <qt_global.h>

namespace VSN {
namespace QtVision {

class ModelView;

/* QtMdiMainWindow */
class QT_CLASS QtMdiMainWindow : public QtMainWindow
{
    Q_OBJECT
    VSN_OBJECT(QtMdiMainWindow)
public:
    explicit QtMdiMainWindow(CreateOptions controls = QtMainWindow::NoControl);
    ~QtMdiMainWindow() override;
public:
    // Returns a pointer to the current active subwindow.
    // If no window is currently active, nullptr is returned.
    ModelView* activeSceneWidget() const override;
    // Returns pointer to the model browser
    ModelTreeWidget* modelWidget() const;
    // Returns a pointer to the docking model browser
    QDockWidget* dockModelTreeWidget() const;
private:
    // Create model panel
    void createModelTreePanel();
protected Q_SLOTS:
    void fileNew();
    void updateModelTreeWidget(QMdiSubWindow* subWindow);
private:
    // interface initialization
    void initialization(CreateOptions controls);
    // Create default container for commands
    void registerDefaultContainers(bool createMenuBar);
    // Creating a default command
    void registerDefaultActions();
protected:
    virtual ModelView* createView() const;
    ModelView* createMdiChild();
    bool openFiles(const QStringList& files) override;
    bool loadFiles(const QStringList& files);
private:
    QMdiSubWindow* findMdiChild(const QString& fileName) const;
private Q_SLOTS:
    void exit();
    void aboutToShowView();
protected:
    void closeEvent(QCloseEvent* event) override;
protected:
    QMdiArea* m_mdiArea;
    QDockWidget* m_dockModelTreeWidget;

    QAction* m_actionNewFile = nullptr;
    QAction* m_actionOpenFile = nullptr;
    QAction* m_actionSaveFile = nullptr;
    QAction* m_actionExit = nullptr;
    QAction* m_actionPropsPanel = nullptr;
    QAction* m_actionModelPanel = nullptr;
    QAction* m_actionOutputPanel = nullptr;
//    QAction* m_actionAboutScene = nullptr;
private:
    Q_DISABLE_COPY(QtMdiMainWindow)
};

} // namespace QtVision
} // namespace VSN

#endif /* __QT_MDIMAINWINDOW_H */
