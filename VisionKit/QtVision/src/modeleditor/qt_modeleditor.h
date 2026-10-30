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
#ifndef __QT_MODELEDITOR_H
#define __QT_MODELEDITOR_H

#include <QObject>
#include <QActionGroup>
#include <vsn_object.h>
#include <vsn_selectionmanager.h>

#include <mx_model_extension.h>
#include <qt_openglwidget.h>
#include <qt_modelnodes.h>
#include <qt_global.h>

namespace VSN {
namespace QtVision {

class ModelDocument;
class ModelTreeWidget;

/* ModelEditor */
class QT_CLASS ModelEditor : public QObject, public Object
{
    Q_OBJECT
    VSN_OBJECT(ModelEditor)
public:
    enum AllowActSelectOption
    {
        NoSelect     = 0x0000,
        Vertex = 0x0001,
        Edge   = 0x0002,
        Face   = 0x0004,
        Body   = 0x0008,
        Area   = 0x0010,
        Prim   = Vertex | Edge | Face | Body,
    };
    Q_ENUM(AllowActSelectOption)
    Q_DECLARE_FLAGS(AllowActSelectOptions, AllowActSelectOption)
    Q_FLAG(AllowActSelectOptions)
public:
    ModelEditor(QObject* parent = nullptr);
    ~ModelEditor();
public:
    // Returns pointer to the application document
    ModelDocument* document() const;
    // Returns pointer to the model(function overloaded for convenience)
    MxModelExtension* model() const;
    // Returns a pointer to the SelectionManager
    SelectionManagerPtr selectionManager() const;
    // Set object selection options
    void setSelectionTool(AllowActSelectOptions options);
    // sync selection with model tree all the time
    bool setSyncSelectionWithModelTree(bool sync);
public:
    // Create actions to filter by selecting objects
    QList<QAction*> createActionsSelectFilter();
    // Set pointer to model tree
    void setModelTreeWidget(ModelTreeWidget* modelTree);
    // Set the pointer to the scene window
    void setModelSceneWidget(QtOpenGLSceneWidget* sceneWidget);
    // Clear editor data when loading with a new project
    void clearData();
Q_SIGNALS:
    void signalVisibleChanged(MxGrItem item, bool& changeSegment);
public Q_SLOTS:
    void slotVisibleItemChanged(MxGrItem item, Qt::CheckState state);
    void slotSetupIDMapping(const NodeKey& key, const NodeKey& keyItem, const MxObjectId& id);
    void slotSelectionChanged(const std::vector<MxGrItem>& selectionItems);
protected Q_SLOTS:
    void slotFilterTriggered(QAction*);
    void slotItemSelectModified();
    void slotInitializeRendering();
private:
    void updateActionCheckFilter();
    // collect all keys by model
    void gatherAllChildrenHelper(const MxGrItem& item, ObjectList<SelectionItem*>& keys);
private:
    bool m_syncSelectionWithModelTree; // sync selection with model tree all the time
    AllowActSelectOptions m_flagSelectOptions;
    SelectionManagerPtr   m_ptrSelectManager;
    PrFindSelectArea*     m_pFindArea;

    ModelDocument*       m_document;
    QtOpenGLSceneWidget* m_sceneWidget;
    ModelTreeWidget*     m_modelTree;
    // map of correspondence between visual object identifiers and model ones
    std::map<NodeKey, MxObjectId> m_visIdMapping;
    std::map<NodeKey, MxObjectId> m_visItemIdMapping; // for item
    // map of correspondence between model object identifiers and visual
    std::map<MxObjectId, NodeKey> m_mxIdMapping;
    std::map<MxObjectId, NodeKey> m_mxItemIdMapping; // for item

//    QAction* m_actionDeleteBodies;
    QAction* m_actionSelectBodies;
    QAction* m_actionSelectVertices;
    QAction* m_actionSelectEdges;
    QAction* m_actionSelectFaces;
    QActionGroup* m_actionsGroupFilter;

    bool m_blockCallRepeat; // to avoid being called again through SelectManager
    bool m_initializeRendering;
};

} // namespace QtVision
} // namespace VSN

#endif /* __QT_MODELEDITOR_H */
