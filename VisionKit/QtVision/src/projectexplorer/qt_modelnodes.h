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
#ifndef __QT_MODELNODES_H
#define __QT_MODELNODES_H

#include <qt_treemodel.h>
#include <qt_global.h>

namespace VSN {
namespace QtVision {

class Project;

enum ProjectAction 
{
    // Special value to indicate that the actions are handled by the parent
    InheritedFromParent,
    AddSubProject,
    AddExistingProject,
    RemoveSubProject,
    // Let's the user select to which project file
    // the file is added
    AddNewFile,
    AddExistingFile,
    // Add files, which match user defined filters,
    // from an existing directory and its subdirectories
    AddExistingDirectory,
    // Removes a file from the project, optionally also
    // delete it on disc
    RemoveFile,
    // Deletes a file from the file system, informs the project
    // that a file was deleted
    // DeleteFile is a define on windows...
    EraseFile,
    Rename,
    Check,
    // hides actions that use the path(): Open containing folder, open terminal here and Find in Directory
    HidePathActions,
    HideFileActions,
    HideFolderActions,
};

class FolderNode;
class ProjectNode;
class AssemblyNode;
class ContainerNode;
// Documentation inside.
class Node
{
public:
    enum PriorityLevel 
    {
        DefaultPriority = 0,
        DefaultFilePriority = 100000,
        DefaultFolderPriority = 200000,
        DefaultVirtualFolderPriority = 300000,
        DefaultProjectPriority = 400000,
        DefaultProjectFilePriority = 500000
    };

    virtual ~Node();

    virtual bool isFolderNodeType() const { return false; }
    virtual bool isProjectNodeType() const { return false; }

    int priority() const;

    ProjectNode* parentProjectNode() const; // parent project, will be nullptr for the top-level project
    FolderNode* parentFolderNode() const; // parent folder or project

    ProjectNode* managingProject();  // project managing this node.
                                     // result is the container's rootProject node if this is a project container node
                                     // (i.e. possibly null)
                                     // or node if node is a top-level ProjectNode directly below a container
                                     // or node->parentProjectNode() for all other cases.
    const ProjectNode* managingProject() const; // see above.

    Project* getProject() const;

    int line() const;
    virtual QString displayName() const;
    virtual const QIcon& icon() const;
    virtual QString tooltip() const;
    bool isEnabled() const;
    void setEnabled(bool enabled);
    bool isCheckable() const;
    void setCheckable(bool checkable);
    bool listInProject() const;
    bool isGenerated() const;

    virtual Qt::CheckState checked() const;
    virtual void setCheck(Qt::CheckState state);
    virtual bool supportsAction(ProjectAction action, const Node* node) const;

    virtual FolderNode* asFolderNode() { return nullptr; }
    virtual const FolderNode* asFolderNode() const { return nullptr; }
    virtual ProjectNode* asProjectNode() { return nullptr; }
    virtual const ProjectNode* asProjectNode() const { return nullptr; }
    virtual ContainerNode* asContainerNode() { return nullptr; }
    virtual const ContainerNode* asContainerNode() const { return nullptr; }

    virtual QString buildKey() const { return QString(); }

    void setParentFolderNode(FolderNode* parentFolder);

    void setListInProject(bool l);
    void setIsGenerated(bool g);
    void setPriority(int priority);
    void setLine(int line);
protected:
    Node();
    Node(const Node& other) = delete;
    bool operator=(const Node& other) = delete;
private:
    FolderNode* m_parentFolderNode = nullptr;
    int m_line = -1;
    int m_priority = DefaultPriority;

    enum NodeFlag : quint16 {
        FlagNone = 0,
        FlagIsEnabled = 1 << 0,
        FlagIsCheckable = 1 << 1,
        FlagIsGenerated = 1 << 2,
        FlagListInProject = 1 << 3,
    };
    NodeFlag m_flags = FlagIsEnabled;
protected:
    QIcon m_icon;
};

/* FolderNode */
class FolderNode : public Node
{
public:
    FolderNode(const QString& folderPath);
public:
    QString displayName() const override;
    // only safe from UI thread
    const QIcon& icon() const override;

    bool isEmpty() const;

    void forEachGenericNode(const std::function<void(Node*)>& genericTask) const;

    FolderNode* asFolderNode() override { return this; }
    const FolderNode* asFolderNode() const override { return this; }
    const QList<Node*> nodes() const;
    void addNode(std::unique_ptr<Node>&& node);
protected:
    std::vector<std::unique_ptr<Node>> m_nodes;
private:
    QString m_displayName;
};

/* ProjectNode */
class ProjectNode : public FolderNode
{
public:
    explicit ProjectNode(const QString& projectFilePath);
    ~ProjectNode();
public:
    ProjectNode* asProjectNode() final { return this; }
    const ProjectNode* asProjectNode() const final { return this; }
};

/* ContainerNode */
class ContainerNode : public FolderNode
{
public:
    ContainerNode(Project* project);
public:
    QString displayName() const final;
    ContainerNode* asContainerNode() final { return this; }
    const ContainerNode* asContainerNode() const final { return this; }

    ProjectNode* rootProjectNode() const;
    Project* project() const { return m_project; }
    void removeAllChildren();
private:
    Project* m_project;
};

} // namespace QtVision
} // namespace VSN

#endif /* __QT_MODELNODES_H */
