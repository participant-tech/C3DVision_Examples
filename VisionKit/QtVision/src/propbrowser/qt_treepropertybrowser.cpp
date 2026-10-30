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

#include <qt_treepropertybrowser.h>
#include <QtCore/QSet>
#include <QtGui/QIcon>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtGui/QPainter>
#include <QtWidgets/QApplication>
#include <QtGui/QFocusEvent>
#include <QtWidgets/QStyle>
#include <QtGui/QPalette>

#include <qt_treepropertybrowserprivate.h>
#include <vsn_last.h>

namespace VSN {
namespace QtVision {

class PropertyEditorView;
/* TreePropBrowserPrivate */
class TreePropBrowserPrivate
{
    TreePropBrowser *q_ptr;
    VSN_DECLARE_PUBLIC(TreePropBrowser);
public:
    TreePropBrowserPrivate();
    void init(QWidget *parent);

    void propertyInserted(BrowserItem* index, BrowserItem* afterIndex);
    void propertyRemoved(BrowserItem* index);
    void propertyChanged(BrowserItem* index);
    QWidget* createEditor(Property* property, QWidget* parent) const
        { return q_ptr->createEditor(property, parent); }
    Property *indexToProperty(const QModelIndex &index) const;
    QTreeWidgetItem *indexToItem(const QModelIndex &index) const;
    BrowserItem *indexToBrowserItem(const QModelIndex &index) const;
    bool lastColumn(int column) const;
    void disableItem(QTreeWidgetItem *item) const;
    void enableItem(QTreeWidgetItem *item) const;
    bool hasValue(QTreeWidgetItem *item) const;

    void slotCollapsed(const QModelIndex &index);
    void slotExpanded(const QModelIndex &index);

    QColor calculatedBackgroundColor(BrowserItem *item) const;

    PropertyEditorView *treeWidget() const { return m_treeWidget; }
    bool markPropertiesWithoutValue() const { return m_markPropertiesWithoutValue; }

    BrowserItem *currentItem() const;
    void setCurrentItem(BrowserItem *browserItem, bool block);
    void editItem(BrowserItem *browserItem);

    void slotCurrentBrowserItemChanged(BrowserItem *item);
    void slotCurrentTreeItemChanged(QTreeWidgetItem *newItem, QTreeWidgetItem *);

    QTreeWidgetItem *editedItem() const;

private:
    void updateItem(QTreeWidgetItem *item);

    QMap<BrowserItem *, QTreeWidgetItem *> m_indexToItem;
    QMap<QTreeWidgetItem *, BrowserItem *> m_itemToIndex;
    QMap<BrowserItem *, QColor> m_indexToBackgroundColor;

    PropertyEditorView *m_treeWidget;

    bool m_headerVisible;
    TreePropBrowser::ResizeMode m_resizeMode;
    class PropertyEditorDelegate *m_delegate;
    bool m_markPropertiesWithoutValue;
    bool m_browserChangedBlocked;
    QIcon m_expandIcon;
};

/* PropertyEditorView */
PropertyEditorView::PropertyEditorView(QWidget *parent) :
    QTreeWidget(parent),
    m_editorPrivate(0)
{
    connect(header(), SIGNAL(sectionDoubleClicked(int)), this, SLOT(resizeColumnToContents(int)));
}

void PropertyEditorView::drawRow(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem opt = option;
    bool hasValue = true;
    if (m_editorPrivate) {
        Property *property = m_editorPrivate->indexToProperty(index);
        if (property)
            hasValue = property->hasValue();
    }
    if (!hasValue && m_editorPrivate->markPropertiesWithoutValue()) {
        const QColor c = option.palette.color(QPalette::Dark);
        painter->fillRect(option.rect, c);
        opt.palette.setColor(QPalette::AlternateBase, c);
    } else {
        const QColor c = m_editorPrivate->calculatedBackgroundColor(m_editorPrivate->indexToBrowserItem(index));
        if (c.isValid()) {
            painter->fillRect(option.rect, c);
            opt.palette.setColor(QPalette::AlternateBase, c.lighter(112));
        }
    }
    QTreeWidget::drawRow(painter, opt, index);
    QColor color = static_cast<QRgb>(QApplication::style()->styleHint(QStyle::SH_Table_GridLineColor, &opt));
    painter->save();
    painter->setPen(QPen(color));
    painter->drawLine(opt.rect.x(), opt.rect.bottom(), opt.rect.right(), opt.rect.bottom());
    painter->restore();
}

void PropertyEditorView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Return:
    case Qt::Key_Enter:
    case Qt::Key_Space:
        if (!m_editorPrivate->editedItem())
            if (const QTreeWidgetItem *item = currentItem())
                if (item->columnCount() >= 2 && ((item->flags() & (Qt::ItemIsEditable | Qt::ItemIsEnabled)) == (Qt::ItemIsEditable | Qt::ItemIsEnabled))) {
                    event->accept();
                    QModelIndex index = currentIndex();
                    if (index.column() == 0) {
                        index = index.sibling(index.row(), 1);
                        setCurrentIndex(index);
                    }
                    edit(index);
                    return;
                }
        break;
    default:
        break;
    }
    QTreeWidget::keyPressEvent(event);
}

void PropertyEditorView::mousePressEvent(QMouseEvent *event)
{
    QTreeWidget::mousePressEvent(event);
    QTreeWidgetItem *item = itemAt(event->pos());

    if (item) {
        if ((item != m_editorPrivate->editedItem()) && (event->button() == Qt::LeftButton)
                && (header()->logicalIndexAt(event->pos().x()) == 1)
                && ((item->flags() & (Qt::ItemIsEditable | Qt::ItemIsEnabled)) == (Qt::ItemIsEditable | Qt::ItemIsEnabled))) {
            editItem(item, 1);
        } else if (!m_editorPrivate->hasValue(item) && m_editorPrivate->markPropertiesWithoutValue() && !rootIsDecorated()) {
            if (event->pos().x() + header()->offset() < 20)
                item->setExpanded(!item->isExpanded());
        }
    }
}

/* PropertyEditorDelegate */
int PropertyEditorDelegate::indentation(const QModelIndex &index) const
{
    if (!m_editorPrivate)
        return 0;

    QTreeWidgetItem *item = m_editorPrivate->indexToItem(index);
    int indent = 0;
    while (item->parent()) {
        item = item->parent();
        ++indent;
    }
    if (m_editorPrivate->treeWidget()->rootIsDecorated())
        ++indent;
    return indent * m_editorPrivate->treeWidget()->indentation();
}

void PropertyEditorDelegate::slotEditorDestroyed(QObject *object)
{
    if (QWidget *w = qobject_cast<QWidget *>(object)) {
        const EditorToPropertyMap::iterator it = m_editorToProperty.find(w);
        if (it != m_editorToProperty.end()) {
            m_propertyToEditor.remove(it.value());
            m_editorToProperty.erase(it);
        }
        if (m_editedWidget == w) {
            m_editedWidget = 0;
            m_editedItem = 0;
        }
    }
}

void PropertyEditorDelegate::closeEditor(Property *property)
{
    if (QWidget *w = m_propertyToEditor.value(property, 0))
        w->deleteLater();
}

QWidget* PropertyEditorDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem&, const QModelIndex& index) const
{
    if (index.column() == 1 && m_editorPrivate) {
        Property *property = m_editorPrivate->indexToProperty(index);
        QTreeWidgetItem *item = m_editorPrivate->indexToItem(index);
        if (property && item && (item->flags() & Qt::ItemIsEnabled)) {
            QWidget *editor = m_editorPrivate->createEditor(property, parent);
            if (editor) {
                editor->setAutoFillBackground(true);
                editor->installEventFilter(const_cast<PropertyEditorDelegate *>(this));
                connect(editor, SIGNAL(destroyed(QObject*)), this, SLOT(slotEditorDestroyed(QObject*)));
                m_propertyToEditor[property] = editor;
                m_editorToProperty[editor] = property;
                m_editedItem = item;
                m_editedWidget = editor;
            }
            return editor;
        }
    }
    return 0;
}

void PropertyEditorDelegate::updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    Q_UNUSED(index);
    editor->setGeometry(option.rect.adjusted(0, 0, 0, -1));
}

void PropertyEditorDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
            const QModelIndex &index) const
{
    bool hasValue = true;
    if (m_editorPrivate) {
        Property *property = m_editorPrivate->indexToProperty(index);
        if (property)
            hasValue = property->hasValue();
    }
    QStyleOptionViewItem opt = option;
    if ((m_editorPrivate && index.column() == 0) || !hasValue) {
        Property *property = m_editorPrivate->indexToProperty(index);
        if (property && property->isModified()) {
            opt.font.setBold(true);
            opt.fontMetrics = QFontMetrics(opt.font);
        }
    }
    QColor c;
    if (!hasValue && m_editorPrivate->markPropertiesWithoutValue()) {
        c = opt.palette.color(QPalette::Dark);
        opt.palette.setColor(QPalette::Text, opt.palette.color(QPalette::BrightText));
    } else {
        c = m_editorPrivate->calculatedBackgroundColor(m_editorPrivate->indexToBrowserItem(index));
        if (c.isValid() && (opt.features & QStyleOptionViewItem::Alternate))
            c = c.lighter(112);
    }
    if (c.isValid())
        painter->fillRect(option.rect, c);
    opt.state &= ~QStyle::State_HasFocus;
    QItemDelegate::paint(painter, opt, index);

    opt.palette.setCurrentColorGroup(QPalette::Active);
    QColor color = static_cast<QRgb>(QApplication::style()->styleHint(QStyle::SH_Table_GridLineColor, &opt));
    painter->save();
    painter->setPen(QPen(color));
    if (!m_editorPrivate || (!m_editorPrivate->lastColumn(index.column()) && hasValue)) {
        int right = (option.direction == Qt::LeftToRight) ? option.rect.right() : option.rect.left();
        painter->drawLine(right, option.rect.y(), right, option.rect.bottom());
    }
    painter->restore();
}

QSize PropertyEditorDelegate::sizeHint(const QStyleOptionViewItem &option,
            const QModelIndex &index) const
{
    return QItemDelegate::sizeHint(option, index) + QSize(3, 4);
}

bool PropertyEditorDelegate::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::FocusOut) {
        QFocusEvent *fe = static_cast<QFocusEvent *>(event);
        if (fe->reason() == Qt::ActiveWindowFocusReason)
            return false;
    }
    return QItemDelegate::eventFilter(object, event);
}

/* TreePropBrowserPrivate */
TreePropBrowserPrivate::TreePropBrowserPrivate() 
    : m_treeWidget(0)
    , m_headerVisible(true)
    , m_resizeMode(TreePropBrowser::Stretch)
    , m_delegate(0)
    , m_markPropertiesWithoutValue(false)
    , m_browserChangedBlocked(false)
{
}

static QIcon drawIndicatorIcon(const QPalette &palette, QStyle *style)
{
    QPixmap pix(14, 14);
    pix.fill(Qt::transparent);
    QStyleOption branchOption;
    branchOption.rect = QRect(2, 2, 9, 9);
    branchOption.palette = palette;
    branchOption.state = QStyle::State_Children;

    QPainter p;
    p.begin(&pix);
    style->drawPrimitive(QStyle::PE_IndicatorBranch, &branchOption, &p);
    p.end();
    QIcon rc = pix;
    rc.addPixmap(pix, QIcon::Selected, QIcon::Off);
    // Draw opened state
    branchOption.state |= QStyle::State_Open;
    pix.fill(Qt::transparent);
    p.begin(&pix);
    style->drawPrimitive(QStyle::PE_IndicatorBranch, &branchOption, &p);
    p.end();

    rc.addPixmap(pix, QIcon::Normal, QIcon::On);
    rc.addPixmap(pix, QIcon::Selected, QIcon::On);
    return rc;
}

void TreePropBrowserPrivate::init(QWidget *parent)
{
    QHBoxLayout *layout = new QHBoxLayout(parent);
    layout->setContentsMargins(QMargins());
    m_treeWidget = new PropertyEditorView(parent);
    m_treeWidget->setEditorPrivate(this);
    m_treeWidget->setIconSize(QSize(18, 18));
    layout->addWidget(m_treeWidget);

    m_treeWidget->setColumnCount(2);
    QStringList labels;
    labels.append(QCoreApplication::translate("TreePropBrowser", "Property"));
    labels.append(QCoreApplication::translate("TreePropBrowser", "Value"));
    m_treeWidget->setHeaderLabels(labels);
    m_treeWidget->setAlternatingRowColors(true);
    m_treeWidget->setEditTriggers(QAbstractItemView::EditKeyPressed);
    m_delegate = new PropertyEditorDelegate(parent);
    m_delegate->setEditorPrivate(this);
    m_treeWidget->setItemDelegate(m_delegate);
    m_treeWidget->header()->setSectionsMovable(false);
    m_treeWidget->header()->setSectionResizeMode(QHeaderView::Stretch);

    m_expandIcon = drawIndicatorIcon(q_ptr->palette(), q_ptr->style());

    QObject::connect(m_treeWidget, SIGNAL(collapsed(QModelIndex)), q_ptr, SLOT(slotCollapsed(QModelIndex)));
    QObject::connect(m_treeWidget, SIGNAL(expanded(QModelIndex)), q_ptr, SLOT(slotExpanded(QModelIndex)));
    QObject::connect(m_treeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), q_ptr, SLOT(slotCurrentTreeItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)));
}

BrowserItem *TreePropBrowserPrivate::currentItem() const
{
    if (QTreeWidgetItem *treeItem = m_treeWidget->currentItem())
        return m_itemToIndex.value(treeItem);
    return 0;
}

void TreePropBrowserPrivate::setCurrentItem(BrowserItem *browserItem, bool block)
{
    const bool blocked = block ? m_treeWidget->blockSignals(true) : false;
    if (browserItem == 0)
        m_treeWidget->setCurrentItem(0);
    else
        m_treeWidget->setCurrentItem(m_indexToItem.value(browserItem));
    if (block)
        m_treeWidget->blockSignals(blocked);
}

Property *TreePropBrowserPrivate::indexToProperty(const QModelIndex &index) const
{
    QTreeWidgetItem *item = m_treeWidget->indexToItem(index);
    BrowserItem *idx = m_itemToIndex.value(item);
    if (idx)
        return idx->property();
    return 0;
}

BrowserItem *TreePropBrowserPrivate::indexToBrowserItem(const QModelIndex &index) const
{
    QTreeWidgetItem *item = m_treeWidget->indexToItem(index);
    return m_itemToIndex.value(item);
}

QTreeWidgetItem *TreePropBrowserPrivate::indexToItem(const QModelIndex &index) const
{
    return m_treeWidget->indexToItem(index);
}

bool TreePropBrowserPrivate::lastColumn(int column) const
{
    return m_treeWidget->header()->visualIndex(column) == m_treeWidget->columnCount() - 1;
}

void TreePropBrowserPrivate::disableItem(QTreeWidgetItem *item) const
{
    Qt::ItemFlags flags = item->flags();
    if (flags & Qt::ItemIsEnabled) {
        flags &= ~Qt::ItemIsEnabled;
        item->setFlags(flags);
        m_delegate->closeEditor(m_itemToIndex[item]->property());
        const int childCount = item->childCount();
        for (int i = 0; i < childCount; i++) {
            QTreeWidgetItem *child = item->child(i);
            disableItem(child);
        }
    }
}

void TreePropBrowserPrivate::enableItem(QTreeWidgetItem *item) const
{
    Qt::ItemFlags flags = item->flags();
    flags |= Qt::ItemIsEnabled;
    item->setFlags(flags);
    const int childCount = item->childCount();
    for (int i = 0; i < childCount; i++) {
        QTreeWidgetItem *child = item->child(i);
        Property *property = m_itemToIndex[child]->property();
        if (property->isEnabled()) {
            enableItem(child);
        }
    }
}

bool TreePropBrowserPrivate::hasValue(QTreeWidgetItem *item) const
{
    BrowserItem *browserItem = m_itemToIndex.value(item);
    if (browserItem)
        return browserItem->property()->hasValue();
    return false;
}

void TreePropBrowserPrivate::propertyInserted(BrowserItem *index, BrowserItem *afterIndex)
{
    QTreeWidgetItem *afterItem = m_indexToItem.value(afterIndex);
    QTreeWidgetItem *parentItem = m_indexToItem.value(index->parent());

    QTreeWidgetItem *newItem = 0;
    if (parentItem) {
        newItem = new QTreeWidgetItem(parentItem, afterItem);
    } else {
        newItem = new QTreeWidgetItem(m_treeWidget, afterItem);
    }
    m_itemToIndex[newItem] = index;
    m_indexToItem[index] = newItem;

    newItem->setFlags(newItem->flags() | Qt::ItemIsEditable);
    newItem->setExpanded(true);

    updateItem(newItem);
}

void TreePropBrowserPrivate::propertyRemoved(BrowserItem *index)
{
    QTreeWidgetItem *item = m_indexToItem.value(index);

    if (m_treeWidget->currentItem() == item) {
        m_treeWidget->setCurrentItem(0);
    }

    delete item;

    m_indexToItem.remove(index);
    m_itemToIndex.remove(item);
    m_indexToBackgroundColor.remove(index);
}

void TreePropBrowserPrivate::propertyChanged(BrowserItem *index)
{
    QTreeWidgetItem *item = m_indexToItem.value(index);

    updateItem(item);
}

void TreePropBrowserPrivate::updateItem(QTreeWidgetItem *item)
{
    Property *property = m_itemToIndex[item]->property();
    QIcon expandIcon;
    if (property->hasValue()) {
        const QString valueToolTip = property->valueToolTip();
        const QString valueText = property->valueText();
        item->setToolTip(1, valueToolTip.isEmpty() ? valueText : valueToolTip);
        item->setIcon(1, property->valueIcon());
        item->setText(1, valueText);
    } else if (markPropertiesWithoutValue() && !m_treeWidget->rootIsDecorated()) {
        expandIcon = m_expandIcon;
    }
    item->setIcon(0, expandIcon);
    item->setFirstColumnSpanned(!property->hasValue());
    const QString descriptionToolTip  = property->descriptionToolTip();
    const QString propertyName = property->propertyName();
    item->setToolTip(0, descriptionToolTip.isEmpty() ? propertyName : descriptionToolTip);
    item->setStatusTip(0, property->statusTip());
    item->setWhatsThis(0, property->whatsThis());
    item->setText(0, propertyName);
    bool wasEnabled = item->flags() & Qt::ItemIsEnabled;
    bool isEnabled = wasEnabled;
    if (property->isEnabled()) {
        QTreeWidgetItem *parent = item->parent();
        if (!parent || (parent->flags() & Qt::ItemIsEnabled))
            isEnabled = true;
        else
            isEnabled = false;
    } else {
        isEnabled = false;
    }
    if (wasEnabled != isEnabled) {
        if (isEnabled)
            enableItem(item);
        else
            disableItem(item);
    }
    m_treeWidget->viewport()->update();
}

QColor TreePropBrowserPrivate::calculatedBackgroundColor(BrowserItem *item) const
{
    BrowserItem *i = item;
    const QMap<BrowserItem *, QColor>::const_iterator itEnd = m_indexToBackgroundColor.constEnd();
    while (i) {
        QMap<BrowserItem *, QColor>::const_iterator it = m_indexToBackgroundColor.constFind(i);
        if (it != itEnd)
            return it.value();
        i = i->parent();
    }
    return QColor();
}

void TreePropBrowserPrivate::slotCollapsed(const QModelIndex &index)
{
    QTreeWidgetItem *item = indexToItem(index);
    BrowserItem *idx = m_itemToIndex.value(item);
    if (item)
        emit q_ptr->collapsed(idx);
}

void TreePropBrowserPrivate::slotExpanded(const QModelIndex &index)
{
    QTreeWidgetItem *item = indexToItem(index);
    BrowserItem *idx = m_itemToIndex.value(item);
    if (item)
        emit q_ptr->expanded(idx);
}

void TreePropBrowserPrivate::slotCurrentBrowserItemChanged(BrowserItem *item)
{
    if (!m_browserChangedBlocked && item != currentItem())
        setCurrentItem(item, true);
}

void TreePropBrowserPrivate::slotCurrentTreeItemChanged(QTreeWidgetItem *newItem, QTreeWidgetItem *)
{
    BrowserItem *browserItem = newItem ? m_itemToIndex.value(newItem) : 0;
    m_browserChangedBlocked = true;
    q_ptr->setCurrentItem(browserItem);
    m_browserChangedBlocked = false;
}

QTreeWidgetItem *TreePropBrowserPrivate::editedItem() const
{
    return m_delegate->editedItem();
}

void TreePropBrowserPrivate::editItem(BrowserItem *browserItem)
{
    if (QTreeWidgetItem *treeItem = m_indexToItem.value(browserItem, 0)) {
        m_treeWidget->setCurrentItem (treeItem, 1);
        m_treeWidget->editItem(treeItem, 1);
    }
}

/* TreePropBrowser */
TreePropBrowser::TreePropBrowser(QWidget *parent)
    : AbsPropBrowser(parent), d_ptr(new TreePropBrowserPrivate)
{
    d_ptr->q_ptr = this;

    d_ptr->init(this);
    connect(this, SIGNAL(currentItemChanged(BrowserItem*)), this, SLOT(slotCurrentBrowserItemChanged(BrowserItem*)));
}

TreePropBrowser::~TreePropBrowser()
{
}

int TreePropBrowser::indentation() const
{
    return d_ptr->m_treeWidget->indentation();
}

void TreePropBrowser::setIndentation(int i)
{
    d_ptr->m_treeWidget->setIndentation(i);
}

bool TreePropBrowser::rootIsDecorated() const
{
    return d_ptr->m_treeWidget->rootIsDecorated();
}

void TreePropBrowser::setRootIsDecorated(bool show)
{
    d_ptr->m_treeWidget->setRootIsDecorated(show);
    for (auto it = d_ptr->m_itemToIndex.cbegin(), end = d_ptr->m_itemToIndex.cend(); it != end; ++it) {
        Property *property = it.value()->property();
        if (!property->hasValue())
            d_ptr->updateItem(it.key());
    }
}

bool TreePropBrowser::alternatingRowColors() const
{
    return d_ptr->m_treeWidget->alternatingRowColors();
}

void TreePropBrowser::setAlternatingRowColors(bool enable)
{
    d_ptr->m_treeWidget->setAlternatingRowColors(enable);
}

bool TreePropBrowser::isHeaderVisible() const
{
    return d_ptr->m_headerVisible;
}

void TreePropBrowser::setHeaderVisible(bool visible)
{
    if (d_ptr->m_headerVisible == visible)
        return;

    d_ptr->m_headerVisible = visible;
    d_ptr->m_treeWidget->header()->setVisible(visible);
}

TreePropBrowser::ResizeMode TreePropBrowser::resizeMode() const
{
    return d_ptr->m_resizeMode;
}

void TreePropBrowser::setResizeMode(TreePropBrowser::ResizeMode mode)
{
    if (d_ptr->m_resizeMode == mode)
        return;

    d_ptr->m_resizeMode = mode;
    QHeaderView::ResizeMode m = QHeaderView::Stretch;
    switch (mode) {
        case TreePropBrowser::Interactive:      m = QHeaderView::Interactive;      break;
        case TreePropBrowser::Fixed:            m = QHeaderView::Fixed;            break;
        case TreePropBrowser::ResizeToContents: m = QHeaderView::ResizeToContents; break;
        case TreePropBrowser::Stretch:
        default:                                      m = QHeaderView::Stretch;          break;
    }
    d_ptr->m_treeWidget->header()->setSectionResizeMode(m);
}

int TreePropBrowser::splitterPosition() const
{
    return d_ptr->m_treeWidget->header()->sectionSize(0);
}

void TreePropBrowser::setSplitterPosition(int position)
{
    d_ptr->m_treeWidget->header()->resizeSection(0, position);
}

void TreePropBrowser::setExpanded(BrowserItem *item, bool expanded)
{
    QTreeWidgetItem *treeItem = d_ptr->m_indexToItem.value(item);
    if (treeItem)
        treeItem->setExpanded(expanded);
}

bool TreePropBrowser::isExpanded(BrowserItem *item) const
{
    QTreeWidgetItem *treeItem = d_ptr->m_indexToItem.value(item);
    if (treeItem)
        return treeItem->isExpanded();
    return false;
}

bool TreePropBrowser::isItemVisible(BrowserItem *item) const
{
    if (const QTreeWidgetItem *treeItem = d_ptr->m_indexToItem.value(item))
        return !treeItem->isHidden();
    return false;
}

void TreePropBrowser::setItemVisible(BrowserItem *item, bool visible)
{
    if (QTreeWidgetItem *treeItem = d_ptr->m_indexToItem.value(item))
        treeItem->setHidden(!visible);
}

void TreePropBrowser::setBackgroundColor(BrowserItem *item, const QColor &color)
{
    if (!d_ptr->m_indexToItem.contains(item))
        return;
    if (color.isValid())
        d_ptr->m_indexToBackgroundColor[item] = color;
    else
        d_ptr->m_indexToBackgroundColor.remove(item);
    d_ptr->m_treeWidget->viewport()->update();
}

QColor TreePropBrowser::backgroundColor(BrowserItem *item) const
{
    return d_ptr->m_indexToBackgroundColor.value(item);
}

QColor TreePropBrowser::calculatedBackgroundColor(BrowserItem *item) const
{
    return d_ptr->calculatedBackgroundColor(item);
}

void TreePropBrowser::setPropertiesWithoutValueMarked(bool mark)
{
    if (d_ptr->m_markPropertiesWithoutValue == mark)
        return;

    d_ptr->m_markPropertiesWithoutValue = mark;
    for (auto it = d_ptr->m_itemToIndex.cbegin(), end = d_ptr->m_itemToIndex.cend(); it != end; ++it) {
        Property *property = it.value()->property();
        if (!property->hasValue())
            d_ptr->updateItem(it.key());
    }
    d_ptr->m_treeWidget->viewport()->update();
}

bool TreePropBrowser::propertiesWithoutValueMarked() const
{
    return d_ptr->m_markPropertiesWithoutValue;
}

void TreePropBrowser::itemInserted(BrowserItem *item, BrowserItem *afterItem)
{
    d_ptr->propertyInserted(item, afterItem);
}

void TreePropBrowser::itemRemoved(BrowserItem *item)
{
    d_ptr->propertyRemoved(item);
}

void TreePropBrowser::itemChanged(BrowserItem *item)
{
    d_ptr->propertyChanged(item);
}

void TreePropBrowser::editItem(BrowserItem *item)
{
    d_ptr->editItem(item);
}

void TreePropBrowser::slotCollapsed(const QModelIndex& index)
{
    d_ptr->slotCollapsed(index);
}

void TreePropBrowser::slotExpanded(const QModelIndex& index)
{
    d_ptr->slotExpanded(index);
}

void TreePropBrowser::slotCurrentBrowserItemChanged(BrowserItem* item)
{
    d_ptr->slotCurrentBrowserItemChanged(item);
}

void TreePropBrowser::slotCurrentTreeItemChanged(QTreeWidgetItem* newItem, QTreeWidgetItem* item)
{
    d_ptr->slotCurrentTreeItemChanged(newItem, item);
}

} // namespace QtVision
} // namespace VSN
