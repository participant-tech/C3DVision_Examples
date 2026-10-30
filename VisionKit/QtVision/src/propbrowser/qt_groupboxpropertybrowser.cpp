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

#include <qt_groupboxpropertybrowser.h>

#include <QtCore/QMap>
#include <QtCore/QSet>
#include <QtCore/QTimer>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <vsn_last.h>

namespace VSN {
namespace QtVision {

/* GroupBoxPropBrowserPrivate */
class GroupBoxPropBrowserPrivate
{
    GroupBoxPropBrowser* q_ptr;
    VSN_DECLARE_PUBLIC(GroupBoxPropBrowser);
public:
    void init(QWidget* parent);

    void propertyInserted(BrowserItem* index, BrowserItem* afterIndex);
    void propertyRemoved(BrowserItem* index);
    void propertyChanged(BrowserItem* index);

    QWidget* createEditor(Property* property, QWidget* parent) const { return q_ptr->createEditor(property, parent); }

    void slotEditorDestroyed();
    void slotUpdate();

    struct WidgetItem
    {
        QWidget* widget{nullptr};
        QLabel* label{nullptr};
        QLabel* widgetLabel{nullptr};
        QGroupBox* groupBox{nullptr};
        QGridLayout* layout{nullptr};
        QFrame* line{nullptr};
        WidgetItem* parent{nullptr};
        QList<WidgetItem*> children;
    };
private:
    void updateLater();
    void updateItem(WidgetItem* item);
    void insertRow(QGridLayout* layout, int row) const;
    void removeRow(QGridLayout* layout, int row) const;

    bool hasHeader(WidgetItem* item) const;

    QMap<BrowserItem*, WidgetItem*> m_indexToItem;
    QMap<WidgetItem*, BrowserItem*> m_itemToIndex;
    QMap<QWidget*, WidgetItem*> m_widgetToItem;
    QGridLayout* m_mainLayout = nullptr;
    QScrollArea* m_scrollArea = nullptr;
    QList<WidgetItem*> m_children;
    QList<WidgetItem*> m_recreateQueue;
};

void GroupBoxPropBrowserPrivate::init(QWidget* parent)
{
    m_scrollArea = new QScrollArea(parent);
    QWidget* gridContainer = new QWidget(m_scrollArea);

    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setWidget(gridContainer);

    QVBoxLayout* layout = new QVBoxLayout(parent);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_scrollArea);

    m_mainLayout = new QGridLayout(gridContainer);

    QLayoutItem* item = new QSpacerItem(0, 0, QSizePolicy::Fixed, QSizePolicy::Expanding);
    m_mainLayout->addItem(item, 0, 0);
}

void GroupBoxPropBrowserPrivate::slotEditorDestroyed()
{
    QWidget* editor = qobject_cast<QWidget*>(q_ptr->sender());
    if (!editor)
        return;
    if (!m_widgetToItem.contains(editor))
        return;
    m_widgetToItem[editor]->widget = nullptr;
    m_widgetToItem.remove(editor);
}

void GroupBoxPropBrowserPrivate::slotUpdate()
{
    for (WidgetItem* item : qAsConst(m_recreateQueue))
    {
        WidgetItem* par = item->parent;
        QWidget* w = 0;
        QGridLayout* l = 0;
        int oldRow = -1;
        if (!par)
        {
            w = q_ptr;
            l = m_mainLayout;
            oldRow = m_children.indexOf(item);
        }
        else
        {
            w = par->groupBox;
            l = par->layout;
            oldRow = par->children.indexOf(item);
            if (hasHeader(par))
                oldRow += 2;
        }

        if (item->widget)
            item->widget->setParent(w);
        else if (item->widgetLabel)
            item->widgetLabel->setParent(w);
        else
            item->widgetLabel = new QLabel(w);

        int span = 1;
        if (item->widget)
            l->addWidget(item->widget, oldRow, 1, 1, 1);
        else if (item->widgetLabel)
            l->addWidget(item->widgetLabel, oldRow, 1, 1, 1);
        else
            span = 2;

        item->label = new QLabel(w);
        item->label->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
        l->addWidget(item->label, oldRow, 0, 1, span);

        updateItem(item);
    }
    m_recreateQueue.clear();
}

void GroupBoxPropBrowserPrivate::updateLater() { QTimer::singleShot(0, q_ptr, SLOT(slotUpdate())); }

void GroupBoxPropBrowserPrivate::propertyInserted(BrowserItem* index, BrowserItem* afterIndex)
{
    WidgetItem* afterItem = m_indexToItem.value(afterIndex);
    WidgetItem* parentItem = m_indexToItem.value(index->parent());

    WidgetItem* newItem = new WidgetItem();
    newItem->parent = parentItem;

    QGridLayout* layout = 0;
    QWidget* parentWidget = 0;
    int row = -1;
    if (!afterItem)
    {
        row = 0;
        if (parentItem)
            parentItem->children.insert(0, newItem);
        else
            m_children.insert(0, newItem);
    }
    else
    {
        if (parentItem)
        {
            row = parentItem->children.indexOf(afterItem) + 1;
            parentItem->children.insert(row, newItem);
        }
        else
        {
            row = m_children.indexOf(afterItem) + 1;
            m_children.insert(row, newItem);
        }
    }
    if (parentItem && hasHeader(parentItem))
        row += 2;

    if (!parentItem)
    {
        layout = m_mainLayout;
        parentWidget = q_ptr;
    }
    else
    {
        if (!parentItem->groupBox)
        {
            m_recreateQueue.removeAll(parentItem);
            WidgetItem* par = parentItem->parent;
            QWidget* w = nullptr;
            QGridLayout* l = nullptr;
            int oldRow = -1;
            if (!par)
            {
                w = q_ptr;
                l = m_mainLayout;
                oldRow = m_children.indexOf(parentItem);
            }
            else
            {
                w = par->groupBox;
                l = par->layout;
                oldRow = par->children.indexOf(parentItem);
                if (hasHeader(par))
                    oldRow += 2;
            }
            parentItem->groupBox = new QGroupBox(w);
            parentItem->layout = new QGridLayout();
            parentItem->groupBox->setLayout(parentItem->layout);
            if (parentItem->label)
            {
                l->removeWidget(parentItem->label);
                delete parentItem->label;
                parentItem->label = 0;
            }
            if (parentItem->widget)
            {
                l->removeWidget(parentItem->widget);
                parentItem->widget->setParent(parentItem->groupBox);
                parentItem->layout->addWidget(parentItem->widget, 0, 0, 1, 2);
                parentItem->line = new QFrame(parentItem->groupBox);
            }
            else if (parentItem->widgetLabel)
            {
                l->removeWidget(parentItem->widgetLabel);
                delete parentItem->widgetLabel;
                parentItem->widgetLabel = 0;
            }
            if (parentItem->line)
            {
                parentItem->line->setFrameShape(QFrame::HLine);
                parentItem->line->setLineWidth(1);
                // TODO: setEnabled
                parentItem->line->setEnabled(false);
                //                parentItem->line->setFrameShadow(QFrame::Sunken);
                parentItem->layout->addWidget(parentItem->line, 1, 0, 1, 2);
            }
            l->addWidget(parentItem->groupBox, oldRow, 0, 1, 2);
            updateItem(parentItem);
        }
        layout = parentItem->layout;
        parentWidget = parentItem->groupBox;
    }

    newItem->label = new QLabel(parentWidget);
    newItem->label->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    newItem->widget = createEditor(index->property(), parentWidget);
    if (!newItem->widget)
    {
        newItem->widgetLabel = new QLabel(parentWidget);
    }
    else
    {
        QObject::connect(newItem->widget, SIGNAL(destroyed()), q_ptr, SLOT(slotEditorDestroyed()));
        m_widgetToItem[newItem->widget] = newItem;
    }

    insertRow(layout, row);
    int span = 1;
    if (newItem->widget)
        layout->addWidget(newItem->widget, row, 1);
    else if (newItem->widgetLabel)
        layout->addWidget(newItem->widgetLabel, row, 1);
    else
        span = 2;
    layout->addWidget(newItem->label, row, 0, 1, span);

    m_itemToIndex[newItem] = index;
    m_indexToItem[index] = newItem;

    updateItem(newItem);
}

void GroupBoxPropBrowserPrivate::propertyRemoved(BrowserItem* index)
{
    WidgetItem* item = m_indexToItem.value(index);

    m_indexToItem.remove(index);
    m_itemToIndex.remove(item);

    WidgetItem* parentItem = item->parent;

    int row = -1;

    if (parentItem)
    {
        row = parentItem->children.indexOf(item);
        parentItem->children.removeAt(row);
        if (hasHeader(parentItem))
            row += 2;
    }
    else
    {
        row = m_children.indexOf(item);
        m_children.removeAt(row);
    }

    if (item->widget)
        delete item->widget;
    if (item->label)
        delete item->label;
    if (item->widgetLabel)
        delete item->widgetLabel;
    if (item->groupBox)
        delete item->groupBox;

    if (!parentItem)
    {
        removeRow(m_mainLayout, row);
    }
    else if (parentItem->children.count() != 0)
    {
        removeRow(parentItem->layout, row);
    }
    else
    {
        WidgetItem* par = parentItem->parent;
        QGridLayout* l = 0;
        int oldRow = -1;
        if (!par)
        {
            l = m_mainLayout;
            oldRow = m_children.indexOf(parentItem);
        }
        else
        {
            l = par->layout;
            oldRow = par->children.indexOf(parentItem);
            if (hasHeader(par))
                oldRow += 2;
        }

        if (parentItem->widget)
        {
            parentItem->widget->hide();
            parentItem->widget->setParent(0);
        }
        else if (parentItem->widgetLabel)
        {
            parentItem->widgetLabel->hide();
            parentItem->widgetLabel->setParent(0);
        }
        else
        {
            // parentItem->widgetLabel = new QLabel(w);
        }
        l->removeWidget(parentItem->groupBox);
        delete parentItem->groupBox;
        parentItem->groupBox = 0;
        parentItem->line = 0;
        parentItem->layout = 0;
        if (!m_recreateQueue.contains(parentItem))
            m_recreateQueue.append(parentItem);
        updateLater();
    }
    m_recreateQueue.removeAll(item);
    delete item;
}

void GroupBoxPropBrowserPrivate::insertRow(QGridLayout* layout, int row) const
{
    QMap<QLayoutItem*, QRect> itemToPos;
    int idx = 0;
    while (idx < layout->count())
    {
        int r, c, rs, cs;
        layout->getItemPosition(idx, &r, &c, &rs, &cs);
        if (r >= row)
        {
            itemToPos[layout->takeAt(idx)] = QRect(r + 1, c, rs, cs);
        }
        else
        {
            idx++;
        }
    }
    const QMap<QLayoutItem*, QRect>::ConstIterator icend = itemToPos.constEnd();
    for (QMap<QLayoutItem*, QRect>::ConstIterator it = itemToPos.constBegin(); it != icend; ++it)
    {
        const QRect r = it.value();
        layout->addItem(it.key(), r.x(), r.y(), r.width(), r.height());
    }
}

void GroupBoxPropBrowserPrivate::removeRow(QGridLayout* layout, int row) const
{
    QMap<QLayoutItem*, QRect> itemToPos;
    int idx = 0;
    while (idx < layout->count())
    {
        int r, c, rs, cs;
        layout->getItemPosition(idx, &r, &c, &rs, &cs);
        if (r > row)
            itemToPos[layout->takeAt(idx)] = QRect(r - 1, c, rs, cs);
        else
            idx++;
    }
    const QMap<QLayoutItem*, QRect>::ConstIterator icend = itemToPos.constEnd();
    for (QMap<QLayoutItem*, QRect>::ConstIterator it = itemToPos.constBegin(); it != icend; ++it)
    {
        const QRect r = it.value();
        layout->addItem(it.key(), r.x(), r.y(), r.width(), r.height());
    }
}

bool GroupBoxPropBrowserPrivate::hasHeader(WidgetItem* item) const
{
    if (item->widget)
        return true;
    return false;
}

void GroupBoxPropBrowserPrivate::propertyChanged(BrowserItem* index)
{
    WidgetItem* item = m_indexToItem.value(index);
    updateItem(item);
}

void GroupBoxPropBrowserPrivate::updateItem(WidgetItem* item)
{
    Property* property = m_itemToIndex[item]->property();
    if (item->groupBox)
    {
        QFont font = item->groupBox->font();
        font.setUnderline(property->isModified());
        item->groupBox->setFont(font);
        item->groupBox->setTitle(property->propertyName());
        item->groupBox->setToolTip(property->descriptionToolTip());
        item->groupBox->setStatusTip(property->statusTip());
        item->groupBox->setWhatsThis(property->whatsThis());
        item->groupBox->setEnabled(property->isEnabled());
    }
    if (item->label)
    {
        QFont font = item->label->font();
        font.setUnderline(property->isModified());
        item->label->setFont(font);
        item->label->setText(property->propertyName());
        item->label->setToolTip(property->descriptionToolTip());
        item->label->setStatusTip(property->statusTip());
        item->label->setWhatsThis(property->whatsThis());
        item->label->setEnabled(property->isEnabled());
    }
    if (item->widgetLabel)
    {
        QFont font = item->widgetLabel->font();
        font.setUnderline(false);
        item->widgetLabel->setFont(font);
        item->widgetLabel->setText(property->valueText());
        item->widgetLabel->setEnabled(property->isEnabled());
    }
    if (item->widget)
    {
        QFont font = item->widget->font();
        font.setUnderline(false);
        item->widget->setFont(font);
        item->widget->setEnabled(property->isEnabled());
        const QString valueToolTip = property->valueToolTip();
        item->widget->setToolTip(valueToolTip.isEmpty() ? property->valueText() : valueToolTip);
    }
    // item->setIcon(1, property->valueIcon());
}

/* GroupBoxPropBrowser */
GroupBoxPropBrowser::GroupBoxPropBrowser(QWidget* parent)
    : AbsPropBrowser(parent)
    , d_ptr(new GroupBoxPropBrowserPrivate)
{
    d_ptr->q_ptr = this;
    d_ptr->init(this);
}

GroupBoxPropBrowser::~GroupBoxPropBrowser()
{
    const QMap<GroupBoxPropBrowserPrivate::WidgetItem*, BrowserItem*>::ConstIterator icend = d_ptr->m_itemToIndex.constEnd();
    for (QMap<GroupBoxPropBrowserPrivate::WidgetItem*, BrowserItem*>::ConstIterator it = d_ptr->m_itemToIndex.constBegin();
         it != icend; ++it)
        delete it.key();
}

void GroupBoxPropBrowser::itemInserted(BrowserItem* item, BrowserItem* afterItem) { d_ptr->propertyInserted(item, afterItem); }

void GroupBoxPropBrowser::itemRemoved(BrowserItem* item) { d_ptr->propertyRemoved(item); }

void GroupBoxPropBrowser::itemChanged(BrowserItem* item) { d_ptr->propertyChanged(item); }

void GroupBoxPropBrowser::slotUpdate() { d_ptr->slotUpdate(); }

void GroupBoxPropBrowser::slotEditorDestroyed() { d_ptr->slotEditorDestroyed(); }

} // namespace QtVision
} // namespace VSN
