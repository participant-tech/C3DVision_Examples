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
#ifndef __QT_MODELTREEWIDGET_H
#define __QT_MODELTREEWIDGET_H

#include <QToolBar>
#include <QWidget>
#include <QTreeView>
#include <QVBoxLayout>
#include <QSettings>

#include <mx_model_extension.h>
#include <qt_global.h>

class MxModelExtension;

namespace VSN {
namespace QtVision {

class Project;
class ProjectModels;
/* ModelTreeWidget */
class QT_CLASS ModelTreeWidget : public QWidget
{
    Q_OBJECT
public:
    ModelTreeWidget(QWidget* parent = nullptr);
    ~ModelTreeWidget() override;
public:
Q_SIGNALS:
    void selectionChanged(std::vector<MxGrItem> listItem);
    void checkedItemChanged(MxGrItem item, Qt::CheckState state);
public slots:
    // Upload project to display in tree
    void setProject(MxModelExtension* model);
    // Set current object in tree by id
    void setCurrentSelection(const MxObjectId& id);
    // Select in the tree the objects that are specified in the array
    void setSelection(const std::vector<MxObjectId>& ids);
private Q_SLOTS:
    void handleCurrentItemChange(const QModelIndex& current);
    void handleCheckedItemChange(const QModelIndex& index);
    void slotSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
    void showContextMenu(const QPoint& pos);
public:
    void readSettings(QSettings& settings);
    void writeSettings(QSettings& settings);
private:
    QVBoxLayout* m_layout;
    QToolBar* m_toolBar;
    QTreeView* m_view;
    ProjectModels* m_model;
    Project* m_project;
private:
    Q_DISABLE_COPY(ModelTreeWidget);
};

} // namespace QtVision
} // namespace VSN

#endif /* __QT_MODELTREEWIDGET_H */
