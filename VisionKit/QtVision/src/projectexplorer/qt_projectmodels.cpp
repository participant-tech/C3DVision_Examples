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

#include <qt_projectmodels.h>
#include <qt_createprjnodes.h>
#include <qt_project.h>

#include <vsn_last.h>

namespace VSN {
namespace QtVision {

void WrapperNode::appendClone(const WrapperNode& node)
{
    WrapperNode* clone = new WrapperNode(node.m_node);
    appendChild(clone);
    for (const WrapperNode* child : node)
        clone->appendClone(*child);
}

/* ProjectModels */
ProjectModels::ProjectModels(QObject* parent)
    : TreeModel<WrapperNode, WrapperNode>(new WrapperNode(nullptr), parent)
{
//    handleProjectAdded(project);
}

// ----------------------------------------------------------------------------
//
// ---
ProjectModels::~ProjectModels()
{
}

// ----------------------------------------------------------------------------
//
// ---
QVariant ProjectModels::data(const QModelIndex& index, int role) const
{
    const Node* const node = nodeForIndex(index);
    if (!node)
        return QVariant();

    const FolderNode* const folderNode = node->asFolderNode();
    const ContainerNode* const containerNode = node->asContainerNode();
    const Project* const project = containerNode ? containerNode->project() : nullptr;

    switch (role)
    {
        case Qt::DisplayRole:
            return node->displayName();
        case Qt::CheckStateRole:
            if (folderNode->isCheckable())
                return folderNode->checked();
            return QVariant();
        case Qt::DecorationRole:
            {
//                if (!folderNode)
//                    return node->asFileNode()->icon();
                if (!project)
                    return folderNode->icon();
                else
                    return containerNode->rootProjectNode() ? 
                        containerNode->rootProjectNode()->icon() : QVariant();
// 
//                static QIcon warnIcon = Utils::Icons::WARNING.icon();
//                static QIcon emptyIcon = Utils::Icons::EMPTY16.icon();
//                if (project->needsConfiguration())
//                    return warnIcon;
//                if (bs && bs->isParsing())
//                    return emptyIcon;
//                if (!target || !project->projectIssues(target->kit()).isEmpty())
//                    return warnIcon;
//                return containerNode->rootProjectNode() ? containerNode->rootProjectNode()->icon()
//                    : folderNode->icon();
            }
    }
    return QVariant();
}

// ----------------------------------------------------------------------------
//
// ---
Qt::ItemFlags ProjectModels::flags(const QModelIndex& index) const
{
    if (!index.isValid())
        return {};
    // We claim that everything is editable
    // That's slightly wrong
    // We control the only view, and that one does the checks
    Qt::ItemFlags f = Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsDragEnabled;
    if (Node* node = nodeForIndex(index)) 
    {
        if (!node->asProjectNode()) 
        {
            // either folder or file node
            if (node->supportsAction(Rename, node))
                f = f | Qt::ItemIsEditable;
            if (node->supportsAction(Check, node))
                f = f | Qt::ItemIsUserCheckable;
        }
        else if (node->supportsAction(ProjectAction::AddExistingFile, node))
            f |= Qt::ItemIsDropEnabled;
    }
    return f;
}

// ----------------------------------------------------------------------------
//
// ---
bool ProjectModels::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (!index.isValid())
        return false;

    Node* node = nodeForIndex(index);
    QTV_ASSERT(node, return false);

    if (role == Qt::CheckStateRole)
    {
        if (node->isCheckable() && node->checked() == Qt::PartiallyChecked)
            return false;
        node->setCheck(static_cast<Qt::CheckState>(value.toUInt()));
//        updateCheckChildrenTree(node);
//        updateCheckParentsTree(node);
        emit checkedChange(index);
        return true;
    }
    if (role != Qt::EditRole)
        return false;
    return true;
}

// ----------------------------------------------------------------------------
//
// ---
void ProjectModels::addFolderNode(WrapperNode* parent, FolderNode* folderNode, QSet<Node*>* seen)
{
    for (Node* node : folderNode->nodes()) 
    {
        if (FolderNode* subFolderNode = node->asFolderNode()) 
        {
            if (!seen->contains(subFolderNode)) 
            {
                seen->insert(subFolderNode);
                auto wrapperNnode = new WrapperNode(subFolderNode);
                parent->appendChild(wrapperNnode);
                addFolderNode(wrapperNnode, subFolderNode, seen);
            }
            else 
                addFolderNode(parent, subFolderNode, seen);
        }
    }
}

// ----------------------------------------------------------------------------
//
// ---
Node* ProjectModels::nodeForIndex(const QModelIndex& index) const
{
    WrapperNode* flatNode = itemForIndex(index);
    return flatNode ? flatNode->m_node : nullptr;
}

// ----------------------------------------------------------------------------
//
// ---
WrapperNode* ProjectModels::nodeForProject(const Project* project) const
{
    QTV_ASSERT(project, return nullptr);
    ContainerNode* containerNode = project->containerNode();
    QTV_ASSERT(containerNode, return nullptr);
    return rootItem()->findFirstLevelChild([containerNode](WrapperNode* node) {
        return node->m_node == containerNode;
        });
}

// ---
static bool compareProjectNames(const WrapperNode* lhs, const WrapperNode* rhs)
{
    Node* p1 = lhs->m_node;
    Node* p2 = rhs->m_node;
//    const int displayNameResult = caseFriendlyCompare(p1->displayName(), p2->displayName());
    int displayNameResult = 1; // caseFriendlyCompare(p1->displayName(), p2->displayName());
    if (displayNameResult != 0)
        return displayNameResult < 0;
    return p1 < p2; // sort by pointer value
}

// ----------------------------------------------------------------------------
//
// ---
void ProjectModels::addOrRebuildProjectModel(Project* project)
{
    WrapperNode* container = nodeForProject(project);
    if (container) 
    {
        container->removeChildren();
        project->containerNode()->removeAllChildren();
    }
    else 
    {
        container = new WrapperNode(project->containerNode());
        rootItem()->insertOrderedChild(container, &compareProjectNames);
    }

    QSet<Node*> seen;
    if (ProjectNode* projectNode = project->rootProjectNode())
        addFolderNode(container, projectNode, &seen);
}

// ----------------------------------------------------------------------------
//
// ---
void ProjectModels::updateCheckChildrenTree(Node* node)
{
    QTV_ASSERT(node, return);
    if (node && node->isCheckable())
    {
        if (FolderNode* folderNode = node->asFolderNode())
        {
            QList<Node*> nodes = folderNode->nodes();
            uint count = nodes.size(); // if there are no children then we leave it as is
            if (count == 0)
                return;
            else if (count == 1) // if there is one child then we leave it as is
                return;
            for (auto it : nodes)
                it->setCheck(node->checked());
            return;
        }
    }
}

// ----------------------------------------------------------------------------
//
// ---
void ProjectModels::updateCheckParentsTree(Node* node)
{
    QTV_ASSERT(node, return);

    FolderNode* parentNode = node->parentFolderNode();
    if (parentNode != nullptr && parentNode->isCheckable())
    {
        bool isDifferentStates = false;
        QList<Node*> nodes = parentNode->nodes();
        uint count = nodes.size(); // if there are no children then we leave it as is
        if (count == 0)
            return;
        else if (count == 1) // if there is one child then we leave it as is
            return;

        Qt::CheckState prevChecked = nodes.at(0)->checked();
        // Check the children, if the condition of at least one child 
        // does not match the parent, then the parent is not determined
        for (auto it : parentNode->nodes())
        {
            if (it->isCheckable())
            {
                Qt::CheckState realCheckState = it->checked();
                if (realCheckState != prevChecked)
                {
                    isDifferentStates = true;
                    break;
                }
                prevChecked = realCheckState;
            }
        }
        parentNode->setCheck(isDifferentStates ? Qt::PartiallyChecked : prevChecked);
//        updateCheckParentsTree(parentNode);
    }
}

// ----------------------------------------------------------------------------
//
// ---
void ProjectModels::handleProjectAdded(Project* project)
{
    QTV_ASSERT(project, return);
/*
    connect(project, &Project::anyParsingStarted,
        this, [this, project]() {
            if (nodeForProject(project))
                parsingStateChanged(project);
        });
    connect(project, &Project::anyParsingFinished,
        this, [this, project]() {
            if (nodeForProject(project))
                parsingStateChanged(project);
            emit ProjectTree::instance()->nodeActionsChanged();
        });
*/
    addOrRebuildProjectModel(project);
}

} // namespace QtVision
} // namespace VSN
