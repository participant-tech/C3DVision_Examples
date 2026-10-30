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

#ifndef __VSN_TREEPROPERTYBROWSERPRIVATE_H
#define __VSN_TREEPROPERTYBROWSERPRIVATE_H

#include <QTreeWidget>
#include <QItemDelegate>

#include <vsn_global.h>

namespace VSN {
namespace QtVision {

class TreePropBrowserPrivate;
/* PropertyEditorView */
class PropertyEditorView : public QTreeWidget
{
    Q_OBJECT
public:
    PropertyEditorView(QWidget* parent = 0);
public:
    void setEditorPrivate(TreePropBrowserPrivate* editorPrivate) { m_editorPrivate = editorPrivate; }
    QTreeWidgetItem* indexToItem(const QModelIndex& index) const { return itemFromIndex(index); }
protected:
    void keyPressEvent(QKeyEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void drawRow(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
private:
    TreePropBrowserPrivate* m_editorPrivate;
};

class Property;
/* PropertyEditorDelegate */
class PropertyEditorDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    PropertyEditorDelegate(QObject* parent = 0)
        : QItemDelegate(parent), m_editorPrivate(0), m_editedItem(0), m_editedWidget(0)
    {}
public:
    void setEditorPrivate(TreePropBrowserPrivate* editorPrivate)
    {
        m_editorPrivate = editorPrivate;
    }

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
        const QModelIndex& index) const;

    void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option,
        const QModelIndex& index) const;

    void paint(QPainter* painter, const QStyleOptionViewItem& option,
        const QModelIndex& index) const;

    QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const;

    void setModelData(QWidget*, QAbstractItemModel*,
        const QModelIndex&) const {}

    void setEditorData(QWidget*, const QModelIndex&) const {}

    bool eventFilter(QObject* object, QEvent* event);
    void closeEditor(Property* property);

    QTreeWidgetItem* editedItem() const { return m_editedItem; }

private slots:
    void slotEditorDestroyed(QObject* object);

private:
    int indentation(const QModelIndex& index) const;

    typedef QMap<QWidget*, Property*> EditorToPropertyMap;
    mutable EditorToPropertyMap m_editorToProperty;

    typedef QMap<Property*, QWidget*> PropertyToEditorMap;
    mutable PropertyToEditorMap m_propertyToEditor;
    TreePropBrowserPrivate* m_editorPrivate;
    mutable QTreeWidgetItem* m_editedItem;
    mutable QWidget* m_editedWidget;
};

} // namespace QtVision
} // namespace VSN

#endif /* __VSN_TREEPROPERTYBROWSERPRIVATE_H */
