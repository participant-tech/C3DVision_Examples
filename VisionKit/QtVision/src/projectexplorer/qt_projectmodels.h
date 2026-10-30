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
#ifndef __QT_PROJECTMODELS_H
#define __QT_PROJECTMODELS_H

#include <QToolBar>
#include <QWidget>
#include <QTreeView>
#include <QVBoxLayout>
#include <QSettings>

#include <qt_modelnodes.h>
#include <qt_treemodel.h>
#include <qt_global.h>

namespace VSN {
namespace QtVision {

/* WrapperNode */
class WrapperNode : public TypedTreeItem<WrapperNode>
{
public:
    explicit WrapperNode(Node* node) : m_node(node) {}
    Node* m_node = nullptr;
    void appendClone(const WrapperNode& node);
};

/* ProjectModels */
class ProjectModels : public TreeModel<WrapperNode, WrapperNode>
{
    Q_OBJECT
public:
    explicit ProjectModels(QObject* parent = nullptr);
    ~ProjectModels() override;
public:
    // QAbstractItemModel
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    bool setData(const QModelIndex& index, const QVariant& value, int role) override;

    Node* nodeForIndex(const QModelIndex& index) const;

    void addFolderNode(WrapperNode* parent, FolderNode* folderNode, QSet<Node*>* seen);

    WrapperNode* nodeForProject(const Project* project) const;
    void addOrRebuildProjectModel(Project* project);
signals:
//    void renamed(const Utils::FilePath& oldName, const Utils::FilePath& newName);
    void checkedChange(const QModelIndex& index);
private:
    void updateCheckChildrenTree(Node* node);
    void updateCheckParentsTree(Node* node);
    void handleProjectAdded(Project* project);
private:
    Q_DISABLE_COPY(ProjectModels);
};


} // namespace QtVision
} // namespace VSN

#endif /* __QT_PROJECTMODELS_H */
