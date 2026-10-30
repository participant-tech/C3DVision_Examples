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

#include <qt_modelnodes.h>
#include <qt_project.h>

#include <QThread>

#include <vsn_last.h>

namespace VSN {
namespace QtVision {

//-----------------------------------------------------------------------------
// The Node class is the base class of all nodes in the node hierarchy.

// The nodes are arranged in a tree where leaves are FileNodes and non-leaves are FolderNodes
// A Project is a special Folder that manages the files and normal folders underneath it.

// The Watcher emits signals for structural changes in the hierarchy.
// A Visitor can be used to traverse all Projects and other Folders.

// ProjectExplorer::FileNode, ProjectExplorer::AssemblyNode, ProjectExplorer::ProjectNode
// ProjectExplorer::NodesWatcher
// ----
Node::Node() = default;

void Node::setPriority(int p)
{
    m_priority = p;
}

void Node::setLine(int line)
{
    m_line = line;
}

void Node::setListInProject(bool l)
{
    if (l)
        m_flags = static_cast<NodeFlag>(m_flags | FlagListInProject);
    else
        m_flags = static_cast<NodeFlag>(m_flags & ~FlagListInProject);
}

void Node::setIsGenerated(bool g)
{
    if (g)
        m_flags = static_cast<NodeFlag>(m_flags | FlagIsGenerated);
    else
        m_flags = static_cast<NodeFlag>(m_flags & ~FlagIsGenerated);
}

Node::~Node() = default;

int Node::priority() const
{
    return m_priority;
}

//-----------------------------------------------------------------------------
// Returns true if the Node should be listed as part of the projects file list.
//---
bool Node::listInProject() const
{
    return (m_flags & FlagListInProject) == FlagListInProject;
}

//-----------------------------------------------------------------------------
// The project that owns and manages the node. It is the first project in the list
// of ancestors.
// ---
ProjectNode* Node::parentProjectNode() const
{
    if (!m_parentFolderNode)
        return nullptr;
    auto pn = m_parentFolderNode->asProjectNode();
    if (pn)
        return pn;
    return m_parentFolderNode->parentProjectNode();
}

// The parent in the node hierarchy.
FolderNode* Node::parentFolderNode() const
{ return m_parentFolderNode; }

// ---
ProjectNode* Node::managingProject()
{
    if (asContainerNode())
        return asContainerNode()->rootProjectNode();
    QTV_ASSERT(m_parentFolderNode, return nullptr);
    ProjectNode* pn = parentProjectNode();
    return pn ? pn : asProjectNode(); // projects manage themselves...
}

const ProjectNode* Node::managingProject() const
{
    return const_cast<Node*>(this)->managingProject();
}
// ---
Project* Node::getProject() const
{
    if (const ContainerNode* const cn = asContainerNode())
        return cn->project();
    if (!m_parentFolderNode)
        return nullptr;
    return m_parentFolderNode->getProject();
}

int Node::line() const
{
    return m_line;
}

QString Node::displayName() const
{
    return "";
}

const QIcon& Node::icon() const { return m_icon; }
QString Node::tooltip() const { return ""; }

// ----------------------------------------------------------------------------
// 
// ---
bool Node::isEnabled() const
{
    if ((m_flags & FlagIsEnabled) == 0)
        return false;
    FolderNode* parent = parentFolderNode();
    return parent ? parent->isEnabled() : true;
}

// ----------------------------------------------------------------------------
// 
// ---
void Node::setEnabled(bool enabled)
{
    if (enabled)
        m_flags = static_cast<NodeFlag>(m_flags | FlagIsEnabled);
    else
        m_flags = static_cast<NodeFlag>(m_flags & ~FlagIsEnabled);
}

// ----------------------------------------------------------------------------
// 
// ---
bool Node::isCheckable() const
{
    return (m_flags & FlagIsCheckable) != 0;
}

// ----------------------------------------------------------------------------
// 
// ---
void Node::setCheckable(bool checkable)
{
    if (checkable)
        m_flags = static_cast<NodeFlag>(m_flags | FlagIsCheckable);
    else
        m_flags = static_cast<NodeFlag>(m_flags & ~FlagIsCheckable);
}

// ----------------------------------------------------------------------------
// Returns true if the file is automatically generated by a compile step.
// ---
bool Node::isGenerated() const
{ return (m_flags & FlagIsGenerated) == FlagIsGenerated; }

// ---
Qt::CheckState Node::checked() const 
{ return Qt::Unchecked; }
// ---
void Node::setCheck(Qt::CheckState checkState) 
{ Q_UNUSED(checkState); Q_ASSERT(false); }

// ----------------------------------------------------------------------------
//
// ---
bool Node::supportsAction(ProjectAction, const Node*) const
{
    return false;
}

void Node::setParentFolderNode(FolderNode* parentFolder)
{
    m_parentFolderNode = parentFolder;
}

/* FolderNode */
FolderNode::FolderNode(const QString& folderPath)
{
    m_displayName = folderPath;
}

// Contains the display name that should be used in a view.
QString FolderNode::displayName() const
{ 
    return m_displayName; 
}

const QIcon& FolderNode::icon() const
{
    return Node::icon();
    /*
    QTV_CHECK(QThread::currentThread() == QCoreApplication::instance()->thread());

    // Instantiating the Icon provider is expensive.
    if (auto strPtr = Utils::get_if<QString>(&m_icon)) {
        m_icon = QIcon(*strPtr);
    }
    else if (auto directoryIconPtr = Utils::get_if<DirectoryIcon>(&m_icon)) {
        m_icon = directoryIconPtr->icon();
    }
    else if (auto creatorPtr = Utils::get_if<IconCreator>(&m_icon)) {
        m_icon = (*creatorPtr)();
    }
    else {
        auto iconPtr = Utils::get_if<QIcon>(&m_icon);
        if (!iconPtr || iconPtr->isNull())
            m_icon = Core::FileIconProvider::icon(QFileIconProvider::Folder);
    }
    return Utils::get<QIcon>(m_icon);
*/
}

// ---
bool FolderNode::isEmpty() const
{ return m_nodes.size() == 0; }

// ---
void FolderNode::forEachGenericNode(const std::function<void(Node*)>& genericTask) const
{
    for (const std::unique_ptr<Node>& n : m_nodes) 
    {
        genericTask(n.get());
        if (FolderNode* fn = n->asFolderNode())
            fn->forEachGenericNode(genericTask);
    }
}

// ---
const QList<Node*> FolderNode::nodes() const
{
    QList<Node*> list;
    int size = static_cast<int>(m_nodes.size());
    list.reserve(size);
    for (int it = 0; size > it;++it )
        list.push_back(m_nodes.at(it).get());
    return list;
}

//  Adds a node specified by node to the internal list of nodes.
void FolderNode::addNode(std::unique_ptr<Node>&& node)
{
    QTV_ASSERT(node, return);
    QTV_ASSERT(!node->parentFolderNode(), qDebug("Node has already a parent folder"));
    node->setParentFolderNode(this);
    m_nodes.emplace_back(std::move(node));
}

/* ProjectNode */
ProjectNode::ProjectNode(const QString& projectFilePath)
    : FolderNode(projectFilePath)
{
    m_icon = QIcon(":/res/project.ico");
}

// ----------------------------------------------------------------------------
//
// ---
ProjectNode::~ProjectNode()
{
}

/* ContainerNode */
ContainerNode::ContainerNode(Project* project)
    : FolderNode("")
    , m_project(project)
{
}

QString ContainerNode::displayName() const
{
    QString name = m_project->displayName();
    return name;
}

// ---
ProjectNode* ContainerNode::rootProjectNode() const { return m_project->rootProjectNode(); }
void ContainerNode::removeAllChildren() { m_nodes.clear(); }



} // namespace QtVision
} // namespace VSN
