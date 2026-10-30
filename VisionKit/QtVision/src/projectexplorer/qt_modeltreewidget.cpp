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

#include <qt_modeltreewidget.h>
#include <qt_projectmodels.h>
#include <qt_project.h>
#include <qt_createprjnodes.h>
#include <qt_createnodetreebuilder.h>

#include <QFocusEvent>
#include <QHeaderView>
#include <QScrollBar>

#include <attr_product.h>
#include <vsn_string.h>

#include <vsn_last.h>

namespace VSN {
namespace QtVision {

/* ProjectTreeView */
class ProjectTreeView : public QTreeView
{
public:
    ProjectTreeView(QWidget* parent = nullptr)
        : QTreeView(parent)
    {
//-----------------------------------------------------------------------------
        setFrameStyle(QFrame::NoFrame);
        setUniformRowHeights(true);
        setTextElideMode(Qt::ElideNone);
        setAttribute(Qt::WA_MacShowFocusRect, false);

        setHeaderHidden(true);
        // We let the column adjust to contents, but note
        // the setting of a minimum size in resizeEvent()
        header()->setSectionResizeMode(QHeaderView::ResizeToContents);
        header()->setStretchLastSection(false);
//-----------------------------------------------------------------------------
        setAnimated(true);

        setIconSize(QSize(20, 20));
        setSelectionMode(QAbstractItemView::ExtendedSelection);
        setContextMenuPolicy(Qt::CustomContextMenu);
        connect(this, &ProjectTreeView::expanded,
            this, &ProjectTreeView::invalidateSize);
        connect(this, &ProjectTreeView::collapsed,
            this, &ProjectTreeView::invalidateSize);
    }
    void invalidateSize()
    {
        m_cachedSize = -1;
    }
    void setModel(QAbstractItemModel* newModel) override
    {
        // Note: Don't connect to column signals, as we have only one column
        if (model()) 
        {
            QAbstractItemModel* m = model();
            disconnect(m, &QAbstractItemModel::dataChanged,
                this, &ProjectTreeView::invalidateSize);
            disconnect(m, &QAbstractItemModel::layoutChanged,
                this, &ProjectTreeView::invalidateSize);
            disconnect(m, &QAbstractItemModel::modelReset,
                this, &ProjectTreeView::invalidateSize);
            disconnect(m, &QAbstractItemModel::rowsInserted,
                this, &ProjectTreeView::invalidateSize);
            disconnect(m, &QAbstractItemModel::rowsMoved,
                this, &ProjectTreeView::invalidateSize);
            disconnect(m, &QAbstractItemModel::rowsRemoved,
                this, &ProjectTreeView::invalidateSize);
        }
        if (newModel) 
        {
            connect(newModel, &QAbstractItemModel::dataChanged,
                this, &ProjectTreeView::invalidateSize);
            connect(newModel, &QAbstractItemModel::layoutChanged,
                this, &ProjectTreeView::invalidateSize);
            connect(newModel, &QAbstractItemModel::modelReset,
                this, &ProjectTreeView::invalidateSize);
            connect(newModel, &QAbstractItemModel::rowsInserted,
                this, &ProjectTreeView::invalidateSize);
            connect(newModel, &QAbstractItemModel::rowsMoved,
                this, &ProjectTreeView::invalidateSize);
            connect(newModel, &QAbstractItemModel::rowsRemoved,
                this, &ProjectTreeView::invalidateSize);
        }
        QTreeView::setModel(newModel);
    }
    int sizeHintForColumn(int column) const override
    {
        if (m_cachedSize < 0)
            m_cachedSize = QTreeView::sizeHintForColumn(column);
        return m_cachedSize;
    }
private:
    mutable int m_cachedSize = -1;
private:
    Q_DISABLE_COPY(ProjectTreeView);
};


/* ModelTreeWidget */
ModelTreeWidget::ModelTreeWidget(QWidget* parent)
    : QWidget(parent)
    , m_layout(nullptr)
    , m_toolBar(nullptr)
    , m_view(nullptr)
    , m_project(new Project)
{
//    m_toolBar = new QToolBar(this);
//    m_toolBar->addAction(m_actionRepSwitcher);
//    m_layout->addWidget(m_toolBar);
    m_view = new ProjectTreeView;
    m_model = new ProjectModels;
    m_view->setModel(m_model);
    setFocusProxy(m_view);

    m_layout = new QVBoxLayout();
    m_layout->addWidget(m_view);
//    m_layout->addWidget(m_toolBar);
    m_layout->setContentsMargins(0, 0, 0, 0);
    setLayout(m_layout);

    // connections
    connect(m_model, &ProjectModels::checkedChange,
        this, &ModelTreeWidget::handleCheckedItemChange);
//    connect(m_model, &FlatModel::renamed,
//        this, &ProjectTreeWidget::renamed);
//    connect(m_model, &FlatModel::requestExpansion,
//        m_view, &QTreeView::expand);
//    connect(m_view, &QAbstractItemView::activated,
//        this, &ProjectTreeWidget::openItem);
    connect(m_view->selectionModel(), &QItemSelectionModel::currentChanged,
        this, &ModelTreeWidget::handleCurrentItemChange);
    connect(m_view->selectionModel(), &QItemSelectionModel::selectionChanged,
        this, &ModelTreeWidget::slotSelectionChanged);
    connect(m_view, &QWidget::customContextMenuRequested,
        this, &ModelTreeWidget::showContextMenu);
//    connect(m_view, &QTreeView::expanded,
//        m_model, &FlatModel::onExpanded);
//    connect(m_view, &QTreeView::collapsed,
//        m_model, &FlatModel::onCollapsed);
}

ModelTreeWidget::~ModelTreeWidget()
{
    VSN_DELETE_AND_NULL(m_project);
    VSN_DELETE_AND_NULL(m_model)
}

// ---
static const TreeItem* findRootItem(ProjectModels* model, const MxObjectId& id)
{
    const TreeItem* item = model->findNonRootItem([id](TreeItem* item)
        {
            WrapperNode* wNode = dynamic_cast<WrapperNode*>(item);
            if (wNode != nullptr && (wNode->m_node != nullptr))
            {
                if (MxGrItemNode* grItemNode = dynamic_cast<MxGrItemNode*>(wNode->m_node))
                    return grItemNode->mxItem().ObjectId() == id ? item : nullptr;
            }
            return (TreeItem*)nullptr;
        });
    return item;
}

// ----------------------------------------------------------------------------
// upload project to display in tree
// ---
void ModelTreeWidget::setProject(MxModelExtension* model)
{
    m_model->clear();
    m_project->setRootProjectNode(nullptr);
    std::unique_ptr<MathModelNode> ptrModelNode = CreateNodeTreeBuilder::buildTree(model);
    m_project->setRootProjectNode(std::move(ptrModelNode));
    m_model->addOrRebuildProjectModel(m_project);
    m_view->expandToDepth(1);
/*
    ProjectNode* pNode = m_project->rootProjectNode();
    const QList<Node*> lstNode = pNode->nodes();
    for (auto& it : lstNode)
    {
        if (MxGrItemNode* grItemNode = dynamic_cast<MxGrItemNode*>(it))
        {
            if (const TreeItem* item = ::findRootItem(m_model, grItemNode->mxItem().ObjectId()))
            {
                QModelIndex index = m_model->indexForItem(item);
                m_view->expandToDepth(1);
                return;
            }
        }
    }
*/
}

// ----------------------------------------------------------------------------
// Set current object in tree by id
// ---
void ModelTreeWidget::setCurrentSelection(const MxObjectId& id)
{
    const TreeItem* item = m_model->findNonRootItem([id](TreeItem* item)
        {
            WrapperNode* wNode = dynamic_cast<WrapperNode*>(item);
            if (wNode != nullptr && (wNode->m_node != nullptr))
            {
                if (MxGrItemNode* grItemNode = dynamic_cast<MxGrItemNode*>(wNode->m_node))
                    return grItemNode->mxItem().ObjectId() == id ? item : nullptr;
            }
            return (TreeItem*)nullptr;
        });
    QModelIndex index = m_model->indexForItem(item);
    m_view->setCurrentIndex(index);
}

// ----------------------------------------------------------------------------
// select in the tree the objects that are specified in the array
// ---
void ModelTreeWidget::setSelection(const std::vector<MxObjectId>& ids)
{
    QItemSelectionModel* selectionModel = m_view->selectionModel();
    selectionModel->clearSelection();
    auto oldMode = m_view->selectionMode();
    m_view->setSelectionMode(QAbstractItemView::MultiSelection);

    for (auto& itItem : ids)
    {
        const TreeItem* item = m_model->findNonRootItem([itItem](TreeItem* item)
            {
                WrapperNode* wNode = dynamic_cast<WrapperNode*>(item);
                if (wNode != nullptr && (wNode->m_node != nullptr))
                {
                    if (MxGrItemNode* grItemNode = dynamic_cast<MxGrItemNode*>(wNode->m_node))
                        return grItemNode->mxItem().ObjectId() == itItem ? item : nullptr;
                }
                return (TreeItem*)nullptr;
            });
        
        if (item != nullptr)
        {
            QModelIndex index = m_model->indexForItem(item);
            m_view->setCurrentIndex(index);
            if (ids.size() > 1)
                selectionModel->select(index, QItemSelectionModel::Select);
        }
    }
    m_view->setSelectionMode(oldMode);
}

// ----------------------------------------------------------------------------
//
// ---
void ModelTreeWidget::handleCurrentItemChange(const QModelIndex& current)
{
    Q_UNUSED(current)
    Node* node = m_model->nodeForIndex(m_view->currentIndex());
    node = node;
}

// ----------------------------------------------------------------------------
//
// ---
void ModelTreeWidget::handleCheckedItemChange(const QModelIndex& index)
{
    if (MxGrItemNode* itemNode = dynamic_cast<MxGrItemNode*>(m_model->nodeForIndex(index)))
        emit checkedItemChanged(itemNode->mxItem(), itemNode->checked());
    m_view->viewport()->update();
}

// ----------------------------------------------------------------------------
//
// ---
void ModelTreeWidget::slotSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
    Q_UNUSED(selected);
    Q_UNUSED(deselected);
    std::vector<MxGrItem> listItem;
    QModelIndexList lstIndex = m_view->selectionModel()->selectedIndexes();
    for (auto& it : lstIndex)
    {
        if (MxGrItemNode* node = dynamic_cast<MxGrItemNode*>(m_model->nodeForIndex(it)))
        {
            MxGrItem item = node->mxItem();
            listItem.push_back(item);
        }
    }
    emit selectionChanged(listItem);
}

// ----------------------------------------------------------------------------
//
// ---
void ModelTreeWidget::showContextMenu(const QPoint& pos)
{
    QModelIndex index = m_view->indexAt(pos);
    Node* node = m_model->nodeForIndex(index);
    node = node;
//    ProjectTree::showContextMenu(this, m_view->mapToGlobal(pos), node);
}

// ----------------------------------------------------------------------------
//
// ---
void ModelTreeWidget::readSettings(QSettings& settings)
{
    Q_UNUSED(settings);
//    bool bGroupBox = settings.value("property", m_bGroupBox).toBool();
//    setRresentationProps(bGroupBox);
}

// ----------------------------------------------------------------------------
//
// ---
void ModelTreeWidget::writeSettings(QSettings& settings)
{
    Q_UNUSED(settings);
//    settings.setValue("property", m_bGroupBox);
}


} // namespace QtVision
} // namespace VSN
