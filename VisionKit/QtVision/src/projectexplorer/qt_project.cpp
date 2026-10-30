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

#include <qt_project.h>
#include <qt_modelnodes.h>

#include <vsn_last.h>

namespace VSN {
namespace QtVision {

/* Project */
Project::Project(QObject* parent)
    : QObject(parent)
{
    m_displayName = "Project";
    // Only set up containernode after d is set so that it will find the project directory!
    m_containerNode = std::make_unique<ContainerNode>(this);
}

// ----------------------------------------------------------------------------
//
// ---
Project::~Project()
{
    // Make sure our root node is null when deleting the actual node
    std::unique_ptr<ProjectNode> oldNode = std::move(m_rootProjectNode);
}
// ---
QString Project::displayName() const
{ return m_displayName; }
// ---
ContainerNode* Project::containerNode() const
{ return m_containerNode.get(); }
// ---
ProjectNode* Project::rootProjectNode() const
{ return m_rootProjectNode.get(); }
// ---
void Project::setRootProjectNode(std::unique_ptr<ProjectNode>&& root)
{
    QTV_ASSERT(m_rootProjectNode.get() != root.get() || !root, return);

    if (root && root->isEmpty()) {
        // Something went wrong with parsing: At least the project file needs to be
        // shown so that the user can fix the breakage.
        // Do not leak root and use default project tree in this case.
        root.reset();
    }

    if (root) 
    {
//        ProjectTree::applyTreeManager(root.get(), ProjectTree::AsyncPhase);
//        ProjectTree::applyTreeManager(root.get(), ProjectTree::FinalPhase);
        root->setParentFolderNode(m_containerNode.get());
    }

    std::unique_ptr<ProjectNode> oldNode = std::move(m_rootProjectNode);

    m_rootProjectNode = std::move(root);
    if (oldNode || m_rootProjectNode)
        handleSubTreeChanged(m_containerNode.get());
}

// ---
void Project::handleSubTreeChanged(FolderNode* node)
{
    Q_UNUSED(node);
    QVector<const Node*> nodeList;
    if (m_rootProjectNode) 
    {
        m_rootProjectNode->forEachGenericNode([&nodeList](const Node* n) {
            nodeList.append(n);
            });
//        sort(nodeList, &nodeLessThan);
    }
//    m_sortedNodeList = nodeList;

//    ProjectTree::emitSubtreeChanged(node);
//    emit fileListChanged();
}

} // namespace QtVision
} // namespace VSN
