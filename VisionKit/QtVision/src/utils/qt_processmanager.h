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
#ifndef __QT_PROCESSMANAGER_H
#define __QT_PROCESSMANAGER_H

#include <QObject>
//#include <qt_openglwidget.h>
#include <qt_modelview.h>
#include <qt_global.h>

namespace VSN {
namespace QtVision {

//class ModelEditor;

/* ProcessManager */
class QT_CLASS ProcessManager : public QObject, public Object
{
    Q_OBJECT
    VSN_OBJECT(ProcessManager)
public:
    enum ProcessType
    {
        pt_Pan = 0x01, ///< \ru Инициализация процесса параномирования. \en Initializes the pan process. \~
        pt_Orbit = 0x02, ///< \ru Инициализация процесса вращения вокруг орбиты. \en Initializes the process of rotation about the orbit. \~
        pt_Rotate = 0x04, ///< \ru Инициализация процесса вращения вокруг центра габарита. \en Initialization the process of rotation about the center of the boundbox. \~
        pt_ComplexRotation = 0x08, ///< \ru Инициализация процесса вращения вокруг оси. \en Initialization the process of rotation about the axis. \~
        pt_Zoom    = 0x10, ///< \ru Инициализация процесса масштабирования. \en Initializes the zoom process. \~
        pt_ZoomBox = 0x20, ///< \ru Инициализация процесса масштабирования. \en Initializes the zoom process. \~
        pt_AllProcess = pt_Rotate | pt_Zoom | pt_Pan,
    };
    Q_ENUM(ProcessType)
    Q_DECLARE_FLAGS(ProcessTypes, ProcessType)
    Q_FLAG(ProcessTypes)
public:
    ProcessManager(QObject* parent);
    ~ProcessManager() override;
public:
    ModelView* sceneWidget() const { return m_sceneWidget; }
    void setSceneWidget(ModelView* sceneWidget);
    // Returns pointer to the model editor
//    ModelEditor* modelEditor() const { return m_modelEditor; }
//    void setModelEditor(ModelEditor* modelEditor) { m_modelEditor = modelEditor; }
public:
    // add processes
    void appendBackgroundProcess(uint idProc, Process* proc);
    void removeBackgroundProcess(uint idProc);
    Process* getBackgroundProcess(uint idProc);
    bool isExistSuspendProcess(uint idProc) const;
    void appendSuspendProcess(uint idProc, Process* proc);
    void removeSuspendProcess(uint idProc);

    // stop background processes
    void enabledBackgroundProcesses(bool enabled);
    void clearProcess();
    // processes suspend other processes
    void createSuspendingProcesses(ProcessType prType);
    // create background processes
    void createProcessesCameraControls(ProcessTypes prType = pt_AllProcess);
Q_SIGNALS:
    void suspendProcessChanged();
protected:
    bool eventFilter(QObject* watched, QEvent* event) override;
private:
    // activating a specific background process
    VSN_SLOT(Protected, backgroundProcessActivated, void backgroundProcessActivated())
    // deactivate a specific background process
    VSN_SLOT(Protected, backgroundProcessActivated, void backgroundProcessDeactivated())
private:
    bool removeCurrentSuspendProcess();
    bool checkForIdenticalHotkeys(const PrAbstractCamera* proc);
private:
    ModelView* m_sceneWidget;
//    ModelEditor* m_modelEditor;
    Process* m_procCurrent;
    std::unordered_map<uint, Process*> m_mapSuspendingProcess;
    std::unordered_map<uint, Process*> m_mapBackgroundProcess;
};

/* ProcessManagerContainer */
class QT_CLASS PrManagerContainer
{
public:
    PrManagerContainer() = default;
public:
    ProcessManager* get(ModelView* sceneWidget) const;
    void append(ProcessManager* manager);
    void remove(ProcessManager* manager);
private:
    QList<ProcessManager*> m_lstManagers;
};

} // namespace QtVision
} // namespace VSN

#endif /* __QT_PROCESSMANAGER_H */

