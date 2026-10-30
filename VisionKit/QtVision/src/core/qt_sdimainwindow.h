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
#ifndef __QT_SDIMAINWINDOW_H
#define __QT_SDIMAINWINDOW_H

#include <QDockWidget>
#include <qt_mainwindow.h>
#include <qt_global.h>

namespace VSN {
namespace QtVision {

class ModelView;

/* QtSdiMainWindow */
class QT_CLASS QtSdiMainWindow : public QtMainWindow
{
    Q_OBJECT
    VSN_OBJECT(QtSdiMainWindow)
public:
    explicit QtSdiMainWindow(CreateOptions controls = QtMainWindow::NoControl, ModelView* widget = nullptr);
    ~QtSdiMainWindow() override;
public:
    // Returns a pointer to the current active subwindow.
    // If no window is currently active, nullptr is returned.
    ModelView* activeSceneWidget() const override;
    // Returns the pointer to the central rendering widget
    ModelView* sceneWidget() const;
    // Returns pointer to the property browser
    virtual QtPropBrowserWidget* propertyWidget() const;
    // Returns pointer to the model browser
    ModelTreeWidget* modelWidget() const;
    // Returns pointer to the output panel
    QDockWidget* outputWidget() const;
    // Returns pointer to the model editor
    ModelEditor* modelEditor() const;
    // Returns pointer to the process manager
    ProcessManager* processManager() const;
    // The controller graphic area displays the details and allows you to control them.
    SceneViewController* viewController() const;
private:
    // Set new central widget for rendering
    void setSceneWidget(ModelView* widget);
    // Create properties panel
    void createPropertiesPanel();
    // Create model panel
    void createModelTreePanel();
    // Create a panel for output
    void createOutputPanel();
    // Create a standard panel for commands
    void createStandardBar();
    // Create a command bar for commands
    void createCommandBar();
    // Создать панель фильтров объектов
    void createFilterObjectsBar();
    // Create a standard menu for commands
    QMenu* createStandardContextMenu(QMenu* inMenu = nullptr);
    // Create default container for commands
    void registerDefaultContainers(bool createMenuBar);
    // Creating a default command
    void registerDefaultActions();
public:
    // Create standard processes for camera control
    void createStandardProcessesCamera();
//    bool openFile(QFile& file);
private:
    // Open all selected files and merge them into one model(MbModel)
    bool openFiles(const QStringList& filesName) override;
private:
    // Initialization of additional parameters of the main window
    void initializing(CreateOptions controls, ModelView* widget);
    // Create a central widget for rendering
    void createSceneWidget();
    void setProgressIndicatorVisible(bool visible);
//    QtSdiMainWindow* findMainWindow(const QString& fileName) const;
private Q_SLOTS:
    void exit();
    void documentWasModified();
    void aboutToShowView();
protected:
    bool event(QEvent* event) override;
    void actionEvent(QActionEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
#if 0
    void contextMenuEvent(QContextMenuEvent* event) override;
#endif
private:
    ModelView* m_modelView;
    QDockWidget* m_dockPropBrowserWidget;
    QDockWidget* m_dockModelTreeWidget;
    QDockWidget* m_dockOutputWidget;
    ModelEditor* m_modelEditor;
    ProcessManager* m_processManager;
    SceneViewController* m_viewController;
    QPoint m_mousePress;

    QWidget* m_progressIndicator = nullptr;
    QTimer m_showProgressTimer;

    QAction* m_actionOpenFile = nullptr;
    QAction* m_actionSaveFile = nullptr;
    QAction* m_actionExit     = nullptr;
    QAction* m_actionPropsPanel = nullptr;
    QAction* m_actionModelPanel = nullptr;
    QAction* m_actionOutputPanel = nullptr;
private:
    Q_DISABLE_COPY(QtSdiMainWindow)
};

} // namespace QtVision
} // namespace VSN

#endif /* __QT_SDIMAINWINDOW_H */
