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

#include <qt_modeleditor.h>
#include <qt_modeldocument.h>
#include <qt_modeltreewidget.h>
#include <vsn_last.h>

namespace VSN {
namespace QtVision {

/* ModelEditor */
ModelEditor::ModelEditor(QObject* parent)
    : QObject(parent)
    , m_syncSelectionWithModelTree(true)
    , m_flagSelectOptions(ModelEditor::NoSelect)
    , m_ptrSelectManager(nullptr)
    , m_pFindArea(nullptr)
    , m_document(new ModelDocument(this))
    , m_sceneWidget(nullptr)
    , m_modelTree(nullptr)
    , m_actionSelectBodies(nullptr)
    , m_actionSelectVertices(nullptr)
    , m_actionSelectEdges(nullptr)
    , m_actionSelectFaces(nullptr)
    , m_actionsGroupFilter(nullptr)
    , m_blockCallRepeat(false)
    , m_initializeRendering(false)
{
}

// ----------------------------------------------------------------------------
//
// ---
ModelEditor::~ModelEditor()
{
}

// Returns pointer to the application document
ModelDocument* ModelEditor::document() const { return m_document; }
// Returns pointer to the model (function overloaded for convenience)
MxModelExtension* ModelEditor::model() const { return m_document->model(); }
// Returns a pointer to the SelectionManager
SelectionManagerPtr ModelEditor::selectionManager() const { return m_ptrSelectManager; }

// ----------------------------------------------------------------------------
// Set object selection options
// ---
void ModelEditor::setSelectionTool(AllowActSelectOptions options)
{
    if (m_ptrSelectManager != nullptr) // protection against re-creation
    {
        Q_ASSERT(m_ptrSelectManager != nullptr);
        return;
    }

    bool bSelect = options.testFlag(ModelEditor::Vertex) || options.testFlag(ModelEditor::Edge) ||
        options.testFlag(ModelEditor::Face) || options.testFlag(ModelEditor::Body);
    m_flagSelectOptions = options;
    if (bSelect)
    {
        if (m_ptrSelectManager == nullptr) // protection against re-creation
            m_ptrSelectManager = std::make_shared<SelectionManager>();

        m_ptrSelectManager->SetSceneContent(m_sceneWidget->sceneContent());
        m_ptrSelectManager->SetHighlightColor(Color(81, 178, 255));
        m_ptrSelectManager->SetSelectionMatchesTransparency(true);
        m_ptrSelectManager->SetObjectPickSelection(m_sceneWidget->objectPickSelection());
        m_ptrSelectManager->SetSelectionMode(SelectionManager::MultiSelection);
        m_ptrSelectManager->SetDynamicHighlighting(true);

        Object::Connect(m_ptrSelectManager.get(), &SelectionManager::signalStateModified, 
            m_sceneWidget, &QtOpenGLSceneWidget::updateWidget);
        Object::Connect(m_ptrSelectManager.get(), &SelectionManager::signalItemsSelectModified, this, &ModelEditor::slotItemSelectModified);
        Object::Connect(m_ptrSelectManager.get(), &SelectionManager::signalItemSelectModified, this, &ModelEditor::slotItemSelectModified);
        Object::Connect(m_ptrSelectManager.get(), &SelectionManager::signalFilterModified,this, &ModelEditor::updateActionCheckFilter);

        //if (GlobalFlags::IsBatchingMode())
        //{
        //    Object::Connect(m_ptrSelectManager.get(), &SelectionManager::signalItemsSelectModified, &Batching::MeshGeometryManager::slotSelect);
        //    Object::Connect(m_ptrSelectManager.get(), &SelectionManager::signalItemSelectModified, &Batching::MeshGeometryManager::slotSelect);
        //}

        if (options.testFlag(ModelEditor::Area))
        {
            m_pFindArea = new PrFindSelectArea(m_sceneWidget->graphicsScene());
            m_pFindArea->SetMouseButtonsActivate(
                { VSN::mb_LButton ,
                (VSN::mb_LButton | VSN::mb_Control),  // Multi (-oldObject +newObject)
                (VSN::mb_LButton | VSN::mb_Shift) }); // Multi (+oldObject)
//            m_pFindArea->SetRectType(PrFindSelectArea::at_OnlyCutting);
            if (m_initializeRendering)
                m_sceneWidget->objectPickSelection()->AddFindProcess(m_pFindArea);
        }
    }
    else if (options.testFlag(ModelEditor::NoSelect) && m_ptrSelectManager == nullptr)
    {
        m_flagSelectOptions = ModelEditor::NoSelect;
        m_ptrSelectManager.reset();
        m_sceneWidget->objectPickSelection()->RemoveFindProcess(m_pFindArea);
        VSN_DELETE_AND_NULL(m_pFindArea);
    }
    updateActionCheckFilter();
}

// sync selection with model tree all the time
bool ModelEditor::setSyncSelectionWithModelTree(bool sync)
{ 
    bool saveSync = m_syncSelectionWithModelTree;
    m_syncSelectionWithModelTree = sync; 
    return saveSync;
}

// ----------------------------------------------------------------------------
// Create actions to filter by selecting objects
// ---
QList<QAction*> ModelEditor::createActionsSelectFilter()
{
    m_actionsGroupFilter = new QActionGroup(this);
    m_actionsGroupFilter->setExclusive(false);

    const QIcon iconBodies = QIcon::fromTheme("editor-filter-bodies", QIcon(":/res/selectfilter_body_48.png"));
    m_actionSelectBodies = new QAction(iconBodies, tr("Bodies"), this);
    m_actionSelectBodies->setCheckable(true);
    m_actionsGroupFilter->addAction(m_actionSelectBodies);

    const QIcon iconVertices = QIcon::fromTheme("editor-filter-vertices", QIcon(":/res/selectfilter_vertex_48.png"));
    m_actionSelectVertices = new QAction(iconVertices, tr("Vertices"), this);
    m_actionSelectVertices->setCheckable(true);
    m_actionsGroupFilter->addAction(m_actionSelectVertices);

    const QIcon iconEdges = QIcon::fromTheme("editor-filter-edges", QIcon(":/res/selectfilter_edge_48.png"));
    m_actionSelectEdges = new QAction(iconEdges, tr("Edges"), this);
    m_actionSelectEdges->setCheckable(true);
    m_actionsGroupFilter->addAction(m_actionSelectEdges);

    const QIcon iconFaces = QIcon::fromTheme("editor-filter-faces", QIcon(":/res/selectfilter_face_48.png"));
    m_actionSelectFaces = new QAction(iconFaces, tr("Faces"), this);
    m_actionSelectFaces->setCheckable(true);
    m_actionsGroupFilter->addAction(m_actionSelectFaces);
    QObject::connect(m_actionsGroupFilter, SIGNAL(triggered(QAction*)), this, SLOT(slotFilterTriggered(QAction*)));
    return m_actionsGroupFilter->actions();
}

// ----------------------------------------------------------------------------
// Set pointer to model tree
// ---
void ModelEditor::setModelTreeWidget(ModelTreeWidget* modelTree)
{
    if (modelTree == nullptr || m_modelTree != nullptr)
        return;
    m_modelTree = modelTree;
    connect(m_modelTree, &ModelTreeWidget::selectionChanged, this, &ModelEditor::slotSelectionChanged);
    connect(m_modelTree, &ModelTreeWidget::checkedItemChanged, this, &ModelEditor::slotVisibleItemChanged);
    connect(document(), &ModelDocument::contentsChanged, m_modelTree, &ModelTreeWidget::setProject);
}

// ----------------------------------------------------------------------------
// Set the pointer to the scene window
// ---
void ModelEditor::setModelSceneWidget(QtOpenGLSceneWidget* sceneWidget)
{
    if (sceneWidget == nullptr || m_sceneWidget != nullptr)
        return;
    m_sceneWidget = sceneWidget;
    connect(m_sceneWidget, &QtOpenGLSceneWidget::initializeRendering, this, &ModelEditor::slotInitializeRendering);
}

// ----------------------------------------------------------------------------
// Clear editor data when loading with a new project
// ---
void ModelEditor::clearData()
{
    m_mxIdMapping.clear();
    m_mxItemIdMapping.clear();
    m_visIdMapping.clear();
    m_visItemIdMapping.clear();
}

// ----------------------------------------------------------------------------
//
// ---
void ModelEditor::slotVisibleItemChanged(MxGrItem item, Qt::CheckState state)
{
    NodeKey key = NodeKey::ZERO;
    MxObjectId id = item.ObjectId();
    auto it = m_mxIdMapping.find(id);
    if (it != m_mxIdMapping.end())
        key = it->second;
        
    SetVisible(item, state == Qt::Checked);

    bool changeSegment = true;
    emit signalVisibleChanged(item, changeSegment);

    if (changeSegment && !key.IsNull())
    {
        SceneContentPtr sceneContent = m_sceneWidget->sceneContent();
        Q_ASSERT(sceneContent != nullptr);
        if (SceneSegment* segment = sceneContent->GetSegment(key))
            segment->SetVisible(state == Qt::Checked);
    }
    m_document->setModified();
    m_sceneWidget->update();
}

// ----------------------------------------------------------------------------
// Setting up mapping of visual and mathematical identifiers
// ---
void ModelEditor::slotSetupIDMapping(const NodeKey& key, const NodeKey& keyItem, const MxObjectId& id)
{
    m_mxIdMapping.insert({ id, key });
    m_visIdMapping.insert({ key, id });

    if (!keyItem.IsNull())
    {
        m_mxItemIdMapping.insert({ id, keyItem });
        m_visItemIdMapping.insert({ keyItem, id });
    }
}

// collect all keys by model
void ModelEditor::gatherAllChildrenHelper(const MxGrItem& item, ObjectList<SelectionItem*>& selItems)
{
    for (MxGrItem subItem : item.SubItems()) // Пока итератор предоставляет `subItem` "по значению".
    {
        NodeKey key = NodeKey::ZERO;
        auto it = m_mxIdMapping.find(subItem.ObjectId());
        if (it != m_mxIdMapping.end())
            key = it->second;
        if (!key.IsNull())
        {
            auto itItem = m_mxItemIdMapping.find(subItem.ObjectId());
            if (m_sceneWidget->sceneContent()->SegmentHasGeometry(key))
                selItems << new InstSelectionItem(key, itItem != m_mxItemIdMapping.end() ? 
                    itItem->second : NodeKey::ZERO, m_ptrSelectManager.get());
            gatherAllChildrenHelper(subItem, selItems);
        }
    }
}

// ----------------------------------------------------------------------------
// 
// ---
void ModelEditor::slotSelectionChanged(const std::vector<MxGrItem>& selectionItems)
{
    if (m_sceneWidget == nullptr)
        return;
    ObjectList<SelectionItem*> selItems;
    for (auto& it : selectionItems)
    {
        NodeKey key = NodeKey::ZERO;
        // Get an unique id of the tree node.
        MxObjectId id = it.ObjectId();
        auto itEx = m_mxIdMapping.find(id);
        if (itEx != m_mxIdMapping.end())
            key = itEx->second;

        if (!key.IsNull())
        {
            auto itItem = m_mxItemIdMapping.find(id);
            if (m_sceneWidget->sceneContent()->SegmentHasGeometry(key))
                selItems << new InstSelectionItem(key, itItem != m_mxItemIdMapping.end() ? 
                    itItem->second : NodeKey::ZERO, m_ptrSelectManager.get());
            gatherAllChildrenHelper(it, selItems);
        }
    }
    if (m_ptrSelectManager)
    {
        m_blockCallRepeat = true;
        m_ptrSelectManager->UnselectAll();
        m_ptrSelectManager->Select(selItems);
        m_blockCallRepeat = false;
    }
}

// ----------------------------------------------------------------------------
// 
// ---
void ModelEditor::slotItemSelectModified()
{
    if (m_modelTree == nullptr || m_blockCallRepeat || !m_syncSelectionWithModelTree)
        return;
    std::vector<MxObjectId> ids;
    auto selectionItems = m_ptrSelectManager->GetSelectionItems();
    for (auto itCurrent : selectionItems)
    {
        if (InstSelectionItem* item = dynamic_cast<InstSelectionItem*>(itCurrent))
        {
            auto it = m_visIdMapping.find(item->GetNodeKey());
            if (it != m_visIdMapping.end())
            {
                auto itItem = m_visItemIdMapping.find(item->GetItemKey());
                ids.push_back(itItem != m_visItemIdMapping.end() ? itItem->second : it->second);
            }
        }
    }
    bool blockSignals = m_modelTree->blockSignals(true);
    m_modelTree->setSelection(ids);
    m_modelTree->blockSignals(blockSignals);
}

// ----------------------------------------------------------------------------
// 
// ---
void ModelEditor::slotFilterTriggered(QAction* action)
{
    Filter filer = m_ptrSelectManager->GetFilterObject();
    if (action == m_actionSelectBodies)
        m_ptrSelectManager->SetBodySelectionEnabled(action->isChecked());
    else if (action == m_actionSelectFaces)
        m_ptrSelectManager->SetFaceSelectionEnabled(action->isChecked());
    else if (action == m_actionSelectEdges)
        m_ptrSelectManager->SetEdgeSelectionEnabled(action->isChecked());
    else if (action == m_actionSelectVertices)
        m_ptrSelectManager->SetVertexSelectionEnabled(action->isChecked());
}

// ----------------------------------------------------------------------------
// 
// ---
void ModelEditor::slotInitializeRendering()
{
    if (m_initializeRendering)
        return;
    m_initializeRendering = true;
    if (m_pFindArea)
        m_sceneWidget->objectPickSelection()->AddFindProcess(m_pFindArea);
}

// ----------------------------------------------------------------------------
// 
// ---
void ModelEditor::updateActionCheckFilter()
{
    if (m_actionsGroupFilter == nullptr || m_ptrSelectManager == nullptr)
        return;

    Filter filer = m_ptrSelectManager->GetFilterObject();
    auto lstActions = m_actionsGroupFilter->actions();
    for (auto it = lstActions.begin(); it != lstActions.end(); ++it)
    {
        QAction* action = (*it);
        if (action == m_actionSelectBodies)
        {
            action->setChecked(filer.CheckFlag(SubBody));
            action->setEnabled(m_flagSelectOptions.testFlag(ModelEditor::Body));
        }
        else if (action == m_actionSelectFaces)
        {
            action->setChecked(filer.CheckFlag(SubFace));
            action->setEnabled(m_flagSelectOptions.testFlag(ModelEditor::Face));
        }
        else if (action == m_actionSelectEdges)
        {
            action->setChecked(filer.CheckFlag(SubEdge));
            action->setEnabled(m_flagSelectOptions.testFlag(ModelEditor::Edge));
        }
        else if (action == m_actionSelectVertices)
        {
            action->setChecked(filer.CheckFlag(SubVertex));
            action->setEnabled(m_flagSelectOptions.testFlag(ModelEditor::Vertex));
        }
    }
}


} // namespace QtVision
} // namespace VSN
